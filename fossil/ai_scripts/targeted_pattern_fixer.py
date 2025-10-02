#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
翻译术语数据库定向模式修复工具
此工具专注于处理特定格式的术语问题，特别是文件+描述格式，并解决重复术语问题。
"""

import sqlite3
import os
import re
from datetime import datetime

class TargetedPatternTermFixer:
    def __init__(self, db_path='translation_terms.db'):
        self.db_path = db_path
        self.conn = None
        self.cursor = None
        self.fix_log = {
            'started_at': datetime.now().strftime('%Y-%m-%d %H:%M:%S'),
            'fixed_order_issues': [],
            'fixed_duplicates': [],
            'skipped_terms': [],
            'error_terms': [],
            'stats': {}
        }

    def connect_db(self):
        """连接到SQLite数据库"""
        try:
            self.conn = sqlite3.connect(self.db_path)
            self.cursor = self.conn.cursor()
            print(f"已连接到数据库: {self.db_path}")
            return True
        except sqlite3.Error as e:
            print(f"数据库连接错误: {e}")
            return False

    def close_db(self):
        """关闭数据库连接"""
        if self.conn:
            self.conn.commit()
            self.conn.close()
            print("数据库连接已关闭")

    def create_backup(self):
        """创建数据库备份"""
        backup_time = datetime.now().strftime('%Y%m%d_%H%M%S')
        backup_path = f'translation_terms.db.targeted_fix_backup_{backup_time}'
        
        try:
            # 首先关闭当前连接
            if self.conn:
                self.close_db()
                
            # 复制数据库文件
            import shutil
            shutil.copy2(self.db_path, backup_path)
            
            # 重新连接数据库
            self.connect_db()
            
            print(f"数据库已备份到 {backup_path}")
            return True
        except Exception as e:
            print(f"创建数据库备份时出错: {e}")
            # 尝试重新连接数据库
            self.connect_db()
            return False

    def is_chinese(self, text):
        """判断文本是否包含中文"""
        if not text:
            return False
        text_str = str(text)
        return bool(re.search(r'[\u4e00-\u9fa5]', text_str))

    def is_english(self, text):
        """判断文本是否主要是英文"""
        if not text:
            return False
        text_str = str(text)
        # 如果包含中文，则不是英文
        if re.search(r'[\u4e00-\u9fa5]', text_str):
            return False
        # 英文文本通常包含字母
        return bool(re.search(r'[a-zA-Z]', text_str))

    def is_filename_description(self, text):
        """检测是否为文件名+描述的模式，如 'shun.c - 页面标题'"""
        if not text:
            return False
        text_str = str(text)
        # 模式：文件名.扩展名 - 描述文本
        pattern = r'^[a-zA-Z0-9_]+\.[a-zA-Z0-9]+\s*-\s*'
        return bool(re.match(pattern, text_str))

    def find_file_pattern_terms(self):
        """查找文件+描述格式的术语记录"""
        try:
            self.cursor.execute(
                "SELECT id, english_term, chinese_translation, source_file FROM terms ORDER BY id"
            )
            all_terms = self.cursor.fetchall()
            
            file_pattern_terms = []
            for term in all_terms:
                term_id, english, chinese, source = term
                
                # 检查条件：
                # 1. 中文术语是文件名+描述格式，英文术语包含中文
                # 2. 或者英文术语包含中文，中文术语是文件名+描述格式
                # 3. 优先处理已知的文件模式（shun.c, setup.c等）
                
                known_files = ['shun.c', 'setup.c', 'artifact.c', 'repo.c', 'db.c']
                
                chinese_str = str(chinese) if chinese is not None else ''
                english_str = str(english) if english is not None else ''
                
                # 检查是否包含已知文件名
                contains_known_file = False
                for known_file in known_files:
                    if known_file in chinese_str or known_file in english_str:
                        contains_known_file = True
                        break
                
                # 判断是否需要修复
                if (
                    # 情况1: 中文是文件名+描述，英文包含中文
                    (self.is_filename_description(chinese_str) and self.is_chinese(english_str)) or
                    # 情况2: 英文是文件名+描述，中文包含中文
                    (self.is_filename_description(english_str) and self.is_chinese(chinese_str)) or
                    # 情况3: 包含已知文件名且存在中英文混合
                    (contains_known_file and ((self.is_chinese(english_str) and self.is_english(chinese_str)) or 
                                             (self.is_chinese(chinese_str) and self.is_english(english_str))))
                ):
                    file_pattern_terms.append({
                        'id': term_id,
                        'english': english,
                        'chinese': chinese,
                        'source': source
                    })
            
            return file_pattern_terms
        except sqlite3.Error as e:
            print(f"查找文件模式记录时出错: {e}")
            return []

    def find_duplicate_terms(self):
        """查找重复的术语记录"""
        try:
            # 查找英文术语重复的记录
            self.cursor.execute(
                """
                SELECT english_term, source_file, GROUP_CONCAT(id) as ids, COUNT(*) as count 
                FROM terms 
                GROUP BY english_term, source_file 
                HAVING COUNT(*) > 1
                """
            )
            duplicate_groups = self.cursor.fetchall()
            
            duplicates = []
            for group in duplicate_groups:
                english_term, source_file, ids_str, count = group
                ids = [int(id_str) for id_str in ids_str.split(',')]
                duplicates.append({
                    'english_term': english_term,
                    'source_file': source_file,
                    'ids': ids,
                    'count': count
                })
            
            return duplicates
        except sqlite3.Error as e:
            print(f"查找重复记录时出错: {e}")
            return []

    def fix_term_order(self, term_id, english_term, chinese_term):
        """修复单个术语顺序"""
        try:
            # 将None转换为空字符串
            english_term = str(english_term) if english_term is not None else ''
            chinese_term = str(chinese_term) if chinese_term is not None else ''
            
            # 执行更新
            self.cursor.execute(
                "UPDATE terms SET english_term = ?, chinese_translation = ? WHERE id = ?",
                (chinese_term, english_term, term_id)
            )
            
            # 记录修复情况
            self.fix_log['fixed_order_issues'].append({
                'id': term_id,
                'old_english': english_term,
                'old_chinese': chinese_term,
                'new_english': chinese_term,
                'new_chinese': english_term
            })
            
            return True
        except sqlite3.Error as e:
            print(f"修复术语ID={term_id}顺序时出错: {e}")
            self.fix_log['error_terms'].append({
                'id': term_id,
                'english_term': english_term,
                'chinese_term': chinese_term,
                'error': str(e)
            })
            return False

    def fix_duplicate_terms(self, duplicate_group):
        """修复重复术语组"""
        try:
            english_term = duplicate_group['english_term']
            source_file = duplicate_group['source_file']
            duplicate_ids = duplicate_group['ids']
            
            # 获取所有重复记录的详细信息
            detailed_records = []
            for term_id in duplicate_ids:
                self.cursor.execute(
                    "SELECT id, english_term, chinese_translation, source_file FROM terms WHERE id = ?",
                    (term_id,)
                )
                record = self.cursor.fetchone()
                if record:
                    detailed_records.append({
                        'id': record[0],
                        'english': record[1],
                        'chinese': record[2],
                        'source': record[3]
                    })
            
            # 确定要保留的记录（通常是第一个）
            keep_id = duplicate_ids[0]
            delete_ids = duplicate_ids[1:]
            
            # 删除重复记录
            deleted_count = 0
            for term_id in delete_ids:
                try:
                    self.cursor.execute("DELETE FROM terms WHERE id = ?", (term_id,))
                    deleted_count += 1
                except sqlite3.Error as e:
                    print(f"删除重复记录ID={term_id}时出错: {e}")
                    continue
            
            # 记录修复情况
            if deleted_count > 0:
                self.fix_log['fixed_duplicates'].append({
                    'english_term': english_term,
                    'source_file': source_file,
                    'kept_id': keep_id,
                    'deleted_ids': delete_ids,
                    'deleted_count': deleted_count
                })
                
            return deleted_count > 0
        except sqlite3.Error as e:
            print(f"修复重复组时出错: {e}")
            return False

    def preview_problems(self, file_pattern_terms, duplicate_terms):
        """预览问题记录"""
        print("\n===== 文件模式问题记录预览 (前20条) =====")
        print("ID | 英文术语 (前30字符)      | 中文术语 (前30字符)     | 源文件")
        print("---|-------------------------------|-------------------------------|--------")
        
        # 只显示前20条记录
        for term in file_pattern_terms[:20]:
            english_trunc = str(term['english'])[:30] if term['english'] else "None"
            chinese_trunc = str(term['chinese'])[:30] if term['chinese'] else "None"
            source = term['source'] if term['source'] else "Unknown"
            print(f"{term['id']:3d} | {english_trunc:<30} | {chinese_trunc:<30} | {source}")
        
        if len(file_pattern_terms) > 20:
            print(f"... 还有 {len(file_pattern_terms) - 20} 条记录")
        
        print("\n===== 重复术语记录预览 =====")
        print("英文术语 (前30字符)      | 源文件 | 重复次数 | ID列表")
        print("-------------------------------|--------|---------|-------")
        
        for dup in duplicate_terms:
            english_trunc = str(dup['english_term'])[:30] if dup['english_term'] else "None"
            source = dup['source_file'] if dup['source_file'] else "Unknown"
            print(f"{english_trunc:<30} | {source:<8} | {dup['count']:8d} | {dup['ids']}")
        
        print("==============================\n")

    def run_fix(self):
        """运行定向修复流程"""
        print("===== 翻译术语数据库定向模式修复 =====")
        print(f"开始时间: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        
        # 1. 创建数据库备份
        if not self.create_backup():
            print("警告: 无法创建数据库备份")
            # 询问用户是否继续
            if input("是否继续修复过程？(y/n): ").lower() != 'y':
                print("修复过程已取消")
                return False
        
        # 2. 连接数据库
        if not self.connect_db():
            print("修复失败：无法连接数据库")
            return False
        
        try:
            # 3. 获取数据库统计信息
            self.cursor.execute("SELECT COUNT(*) FROM terms")
            total_terms = self.cursor.fetchone()[0]
            print(f"数据库总记录数: {total_terms}")
            
            # 4. 查找文件模式问题记录
            file_pattern_terms = self.find_file_pattern_terms()
            print(f"发现 {len(file_pattern_terms)} 条文件模式问题记录")
            
            # 5. 查找重复术语记录
            duplicate_terms = self.find_duplicate_terms()
            print(f"发现 {len(duplicate_terms)} 组重复术语记录")
            
            # 6. 预览问题记录
            self.preview_problems(file_pattern_terms, duplicate_terms)
            
            # 7. 修复文件模式问题记录
            fixed_order_count = 0
            if file_pattern_terms:
                print(f"\n开始修复文件模式问题记录...")
                for term in file_pattern_terms:
                    if self.fix_term_order(term['id'], term['english'], term['chinese']):
                        fixed_order_count += 1
                        # 每修复10条记录显示一次进度
                        if fixed_order_count % 10 == 0:
                            print(f"已修复 {fixed_order_count}/{len(file_pattern_terms)} 条顺序问题记录...")
            
            # 8. 修复重复术语记录
            fixed_dup_count = 0
            if duplicate_terms:
                print(f"\n开始修复重复术语记录...")
                for dup in duplicate_terms:
                    if self.fix_duplicate_terms(dup):
                        fixed_dup_count += 1
                        print(f"已修复 {fixed_dup_count}/{len(duplicate_terms)} 组重复术语")
            
            # 9. 生成修复报告
            self.generate_fix_report()
            
            # 10. 更新统计信息
            self.cursor.execute("SELECT COUNT(*) FROM terms")
            final_count = self.cursor.fetchone()[0]
            
            self.fix_log['stats'] = {
                'initial_count': total_terms,
                'final_count': final_count,
                'fixed_order_count': fixed_order_count,
                'file_pattern_count': len(file_pattern_terms),
                'fixed_dup_count': fixed_dup_count,
                'duplicate_group_count': len(duplicate_terms)
            }
            
            print("\n===== 修复总结 =====")
            print(f"修复前记录数: {total_terms}")
            print(f"修复后记录数: {final_count}")
            print(f"文件模式问题记录: {len(file_pattern_terms)} 条")
            print(f"成功修复顺序问题: {fixed_order_count} 条")
            print(f"重复术语组数: {len(duplicate_terms)} 组")
            print(f"成功修复重复组: {fixed_dup_count} 组")
            print(f"跳过术语: {len(self.fix_log['skipped_terms'])} 条")
            print(f"修复出错术语: {len(self.fix_log['error_terms'])} 条")
            print("====================")
            
            return True
            
        except Exception as e:
            print(f"修复过程中发生错误: {e}")
            import traceback
            traceback.print_exc()
            return False
        finally:
            # 关闭数据库连接
            self.close_db()

    def generate_fix_report(self, filename='translation_terms_targeted_fix_report.md'):
        """生成修复报告"""
        try:
            with open(filename, 'w', encoding='utf-8') as f:
                f.write(f"# 翻译术语定向模式修复报告\n\n")
                f.write(f"报告生成时间: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n")
                
                # 统计信息
                f.write("## 修复统计\n\n")
                f.write(f"- 数据库总记录数 (修复前): {self.fix_log['stats'].get('initial_count', 0)}\n")
                f.write(f"- 数据库总记录数 (修复后): {self.fix_log['stats'].get('final_count', 0)}\n")
                f.write(f"- 文件模式问题记录: {self.fix_log['stats'].get('file_pattern_count', 0)} 条\n")
                f.write(f"- 成功修复顺序问题: {self.fix_log['stats'].get('fixed_order_count', 0)} 条\n")
                f.write(f"- 重复术语组数: {self.fix_log['stats'].get('duplicate_group_count', 0)} 组\n")
                f.write(f"- 成功修复重复组: {self.fix_log['stats'].get('fixed_dup_count', 0)} 组\n")
                f.write(f"- 跳过的术语: {len(self.fix_log['skipped_terms'])} 条\n")
                f.write(f"- 修复出错的术语: {len(self.fix_log['error_terms'])} 条\n\n")
                
                # 修复的顺序问题列表
                if self.fix_log['fixed_order_issues']:
                    f.write("## 修复的顺序问题列表\n\n")
                    f.write("| ID | 原英文术语 | 原中文翻译 | 修复后英文术语 | 修复后中文翻译 |\n")
                    f.write("|---|---|---|---|---|\n")
                    
                    # 只显示前50条记录
                    for term in self.fix_log['fixed_order_issues'][:50]:
                        f.write(f"| {term['id']} | {term['old_english'][:50]} | {term['old_chinese'][:50]} | {term['new_english'][:50]} | {term['new_chinese'][:50]} |\n")
                    
                    if len(self.fix_log['fixed_order_issues']) > 50:
                        f.write(f"| ... | ... | ... | ... | ... |\n")
                        f.write(f"| 总计 {len(self.fix_log['fixed_order_issues'])} 条记录 | | | | |\n")
                    f.write("\n")
                
                # 修复的重复术语列表
                if self.fix_log['fixed_duplicates']:
                    f.write("## 修复的重复术语列表\n\n")
                    f.write("| 英文术语 | 源文件 | 保留的ID | 删除的ID列表 | 删除数量 |\n")
                    f.write("|---|---|---|---|---|\n")
                    
                    for dup in self.fix_log['fixed_duplicates']:
                        f.write(f"| {dup['english_term'][:50]} | {dup['source_file']} | {dup['kept_id']} | {dup['deleted_ids']} | {dup['deleted_count']} |\n")
                    f.write("\n")
                
                # 跳过的术语列表
                if self.fix_log['skipped_terms']:
                    f.write("## 跳过的术语列表\n\n")
                    f.write("| ID | 英文术语 | 中文翻译 | 跳过原因 |\n")
                    f.write("|---|---|---|---|\n")
                    
                    for term in self.fix_log['skipped_terms']:
                        f.write(f"| {term['id']} | {term['english_term'][:50]} | {term['chinese_term'][:50]} | {term['reason']} |\n")
                    f.write("\n")
                
                # 错误记录
                if self.fix_log['error_terms']:
                    f.write("## 修复出错的术语\n\n")
                    f.write("| ID | 英文术语 | 中文术语 | 错误信息 |\n")
                    f.write("|---|---|---|---|\n")
                    
                    for term in self.fix_log['error_terms']:
                        error_msg = str(term.get('error', '')).replace('|', '\\|')[:100]
                        f.write(f"| {term['id']} | {term['english_term'][:50]} | {term['chinese_term'][:50]} | {error_msg} |\n")
                    f.write("\n")
                
                # 建议
                f.write("## 修复建议\n\n")
                f.write("1. 修复完成后，建议运行 `final_verification.py` 进行验证\n")
                f.write("2. 对于复杂的术语问题，建议手动检查确认\n")
                f.write("3. 如果修复效果不理想，可以使用备份文件恢复数据库\n")
            
            file_size = os.path.getsize(filename) / 1024  # KB
            print(f"修复报告已导出到 {filename} ({round(file_size, 2)} KB)")
            return True
        except Exception as e:
            print(f"生成修复报告时出错: {e}")
            return False

if __name__ == "__main__":
    fixer = TargetedPatternTermFixer()
    success = fixer.run_fix()
    
    print("\n===== 修复完成 =====")
    
    if success:
        print("定向模式修复完成！")
        print("详细的修复报告可在 translation_terms_targeted_fix_report.md 中查看。")
        print("建议运行 final_verification.py 进行最终验证。")
    else:
        print("定向模式修复过程中出现问题，请查看上面的详细报告。")