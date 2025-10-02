#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
翻译术语数据库智能交互式修复工具
此工具提供更谨慎的修复策略，支持预览和交互式修复，精确处理剩余的特定模式问题。
"""

import sqlite3
import os
import re
import json
from datetime import datetime

class SmartInteractiveTermFixer:
    def __init__(self, db_path='translation_terms.db'):
        self.db_path = db_path
        self.conn = None
        self.cursor = None
        self.fix_log = {
            'started_at': datetime.now().strftime('%Y-%m-%d %H:%M:%S'),
            'fixed_terms': [],
            'skipped_terms': [],
            'error_terms': [],
            'stats': {}
        }
        self.dry_run = False  # 默认为实际执行模式

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
        backup_path = f'translation_terms.db.smart_fix_backup_{backup_time}'
        
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

    def is_code_snippet(self, text):
        """检测是否为代码片段"""
        if not text:
            return False
        text_str = str(text)
        # 常见代码模式
        code_patterns = [
            r'entry_attribute\(',
            r'onoff_attribute\(',
            r'textarea_attribute\(',
            r'cgi_printf\(',
            r'style_header\(',
            r'<[a-zA-Z]+>',  # HTML标签
        ]
        for pattern in code_patterns:
            if re.search(pattern, text_str):
                return True
        return False

    def analyze_term_pair(self, english_term, chinese_term):
        """分析术语对，返回可能的问题类型"""
        # 将None转换为空字符串
        english_term = str(english_term) if english_term is not None else ''
        chinese_term = str(chinese_term) if chinese_term is not None else ''
        
        # 类型1: 英文字段包含中文，中文字段不包含中文
        if self.is_chinese(english_term) and not self.is_chinese(chinese_term):
            return 'cn_in_en'
        
        # 类型2: 英文字段是文件名+描述，中文字段是纯中文
        if self.is_filename_description(english_term) and self.is_chinese(chinese_term):
            return 'filename_description'
        
        # 类型3: 中文字段是英文，英文字段不是英文
        if self.is_english(chinese_term) and not self.is_english(english_term):
            return 'en_in_cn'
        
        # 类型4: 两个字段都是代码，但顺序可能有问题
        if self.is_code_snippet(english_term) and self.is_code_snippet(chinese_term):
            # 检查代码字段中是否有明显的中英文差异
            if self.is_chinese(english_term) and self.is_english(chinese_term):
                return 'code_mixed'
        
        # 类型5: 特殊情况 - 中文在前、英文在后（常见技术术语）
        common_terms = ['Artifact', 'Server', 'URL', 'HTTP', 'API', 'JSON', 'XML']
        if self.is_chinese(english_term) and self.is_english(chinese_term):
            for term in common_terms:
                if term.lower() in chinese_term.lower():
                    return 'tech_term_swapped'
        
        return None  # 没有检测到问题

    def find_problem_terms(self):
        """查找可能有问题的术语记录"""
        try:
            self.cursor.execute(
                "SELECT id, english_term, chinese_translation, source_file FROM terms ORDER BY id"
            )
            all_terms = self.cursor.fetchall()
            
            problem_terms = []
            for term in all_terms:
                term_id, english, chinese, source = term
                problem_type = self.analyze_term_pair(english, chinese)
                if problem_type:
                    problem_terms.append({
                        'id': term_id,
                        'english': english,
                        'chinese': chinese,
                        'source': source,
                        'problem_type': problem_type
                    })
            
            return problem_terms
        except sqlite3.Error as e:
            print(f"查找问题记录时出错: {e}")
            return []

    def check_conflict(self, term_id, new_english, source_file):
        """检查是否存在冲突的记录"""
        try:
            # 检查是否存在相同的英文术语+源文件组合
            self.cursor.execute(
                "SELECT id FROM terms WHERE english_term = ? AND source_file = ? AND id != ?",
                (new_english, source_file, term_id)
            )
            existing_id = self.cursor.fetchone()
            return existing_id is not None
        except sqlite3.Error as e:
            print(f"检查冲突时出错: {e}")
            return False

    def fix_term(self, term_id, english_term, chinese_term, source_file):
        """修复单个术语记录"""
        try:
            # 将None转换为空字符串
            english_term = str(english_term) if english_term is not None else ''
            chinese_term = str(chinese_term) if chinese_term is not None else ''
            source_file = str(source_file) if source_file is not None else 'Unknown'
            
            # 检查冲突
            if self.check_conflict(term_id, chinese_term, source_file):
                print(f"跳过ID={term_id}: 存在冲突记录")
                self.fix_log['skipped_terms'].append({
                    'id': term_id,
                    'reason': '存在冲突记录',
                    'english_term': english_term,
                    'chinese_term': chinese_term
                })
                return False
            
            # 如果是实际执行模式，执行更新
            if not self.dry_run:
                self.cursor.execute(
                    "UPDATE terms SET english_term = ?, chinese_translation = ? WHERE id = ?",
                    (chinese_term, english_term, term_id)
                )
                
            # 记录修复情况
            self.fix_log['fixed_terms'].append({
                'id': term_id,
                'old_english': english_term,
                'old_chinese': chinese_term,
                'new_english': chinese_term,
                'new_chinese': english_term,
                'source_file': source_file
            })
            
            return True
        except sqlite3.Error as e:
            print(f"修复术语ID={term_id}时出错: {e}")
            self.fix_log['error_terms'].append({
                'id': term_id,
                'english_term': english_term,
                'chinese_term': chinese_term,
                'error': str(e)
            })
            return False

    def preview_problems(self, problem_terms, limit=50):
        """预览问题记录"""
        print("\n===== 问题记录预览 (前50条) =====")
        print("ID | 问题类型 | 英文术语 (前30字符)      | 中文术语 (前30字符)     | 建议操作")
        print("---|---------|-------------------------------|-------------------------------|--------")
        
        # 问题类型描述映射
        type_descriptions = {
            'cn_in_en': '中文在英文列',
            'filename_description': '文件名+描述',
            'en_in_cn': '英文在中文列',
            'code_mixed': '代码中英文混合',
            'tech_term_swapped': '技术术语顺序交换'
        }
        
        # 只显示前50条记录
        for term in problem_terms[:limit]:
            term_type = type_descriptions.get(term['problem_type'], term['problem_type'])
            english_trunc = str(term['english'])[:30] if term['english'] else "None"
            chinese_trunc = str(term['chinese'])[:30] if term['chinese'] else "None"
            print(f"{term['id']:3d} | {term_type:9s} | {english_trunc:<30} | {chinese_trunc:<30} | 交换顺序")
        
        if len(problem_terms) > limit:
            print(f"... 还有 {len(problem_terms) - limit} 条记录")
        
        print("==============================\n")

    def run_interactive_fix(self):
        """运行交互式修复流程"""
        print("===== 翻译术语数据库智能交互式修复 =====")
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
            
            # 4. 查找问题记录
            problem_terms = self.find_problem_terms()
            print(f"发现 {len(problem_terms)} 条可能有问题的记录")
            
            # 5. 预览问题记录
            self.preview_problems(problem_terms)
            
            # 6. 询问用户修复选项
            print("请选择修复模式：")
            print("1. 自动修复所有问题记录")
            print("2. 手动逐一确认修复")
            print("3. 仅修复特定类型的问题")
            print("4. 只生成报告，不实际修复")
            
            choice = input("请输入选项 (1-4): ").strip()
            
            # 7. 根据用户选择执行修复
            if choice == '1':
                # 自动修复所有问题记录
                fixed_count = 0
                for term in problem_terms:
                    if self.fix_term(term['id'], term['english'], term['chinese'], term['source']):
                        fixed_count += 1
                        # 每修复10条记录显示一次进度
                        if fixed_count % 10 == 0:
                            print(f"已修复 {fixed_count}/{len(problem_terms)} 条记录...")
                
            elif choice == '2':
                # 手动逐一确认修复
                fixed_count = 0
                for term in problem_terms:
                    # 显示当前记录信息
                    print(f"\n----- 记录ID: {term['id']} -----")
                    print(f"英文术语: {term['english']}")
                    print(f"中文术语: {term['chinese']}")
                    print(f"源文件: {term['source']}")
                    print(f"问题类型: {term['problem_type']}")
                    print(f"建议操作: 交换术语顺序")
                    
                    # 询问用户是否修复
                    action = input("是否修复此记录？(y/n/s跳过所有): ").lower()
                    
                    if action == 's':
                        print("跳过所有剩余记录")
                        break
                    elif action == 'y':
                        if self.fix_term(term['id'], term['english'], term['chinese'], term['source']):
                            fixed_count += 1
                            print(f"已修复，当前修复总数: {fixed_count}")
            
            elif choice == '3':
                # 仅修复特定类型的问题
                # 显示问题类型列表
                type_counts = {}
                for term in problem_terms:
                    type_counts[term['problem_type']] = type_counts.get(term['problem_type'], 0) + 1
                
                print("\n可用的问题类型：")
                for i, (type_name, count) in enumerate(type_counts.items(), 1):
                    print(f"{i}. {type_name}: {count} 条记录")
                
                # 询问用户选择问题类型
                type_choice = input("请输入要修复的问题类型编号 (多个请用逗号分隔): ").strip()
                
                # 解析用户选择
                selected_types = []
                try:
                    for num in type_choice.split(','):
                        idx = int(num.strip()) - 1
                        if 0 <= idx < len(type_counts):
                            selected_types.append(list(type_counts.keys())[idx])
                except ValueError:
                    print("输入无效，将修复所有类型")
                    selected_types = list(type_counts.keys())
                
                # 修复选定类型的问题
                fixed_count = 0
                for term in problem_terms:
                    if term['problem_type'] in selected_types:
                        if self.fix_term(term['id'], term['english'], term['chinese'], term['source']):
                            fixed_count += 1
                            # 每修复5条记录显示一次进度
                            if fixed_count % 5 == 0:
                                print(f"已修复 {fixed_count} 条记录...")
            
            elif choice == '4':
                # 只生成报告，不实际修复
                self.dry_run = True
                fixed_count = 0
                for term in problem_terms:
                    if self.fix_term(term['id'], term['english'], term['chinese'], term['source']):
                        fixed_count += 1
                
                print(f"\n模拟修复完成，将修复 {fixed_count} 条记录（实际未修改数据库）")
            
            else:
                print("无效的选项，退出修复")
                return False
            
            # 8. 生成修复报告
            self.generate_fix_report()
            
            # 9. 更新统计信息
            self.cursor.execute("SELECT COUNT(*) FROM terms")
            final_count = self.cursor.fetchone()[0]
            
            self.fix_log['stats'] = {
                'initial_count': total_terms,
                'final_count': final_count,
                'fixed_count': fixed_count,
                'problem_terms_count': len(problem_terms)
            }
            
            print("\n===== 修复总结 =====")
            print(f"修复前记录数: {total_terms}")
            print(f"修复后记录数: {final_count}")
            print(f"发现问题记录: {len(problem_terms)} 条")
            print(f"成功修复术语: {fixed_count} 条")
            print(f"跳过术语: {len(self.fix_log['skipped_terms'])} 条")
            print(f"修复出错术语: {len(self.fix_log['error_terms'])} 条")
            print(f"修复模式: {'模拟修复' if self.dry_run else '实际修复'}")
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

    def generate_fix_report(self, filename='translation_terms_smart_fix_report.md'):
        """生成修复报告"""
        try:
            with open(filename, 'w', encoding='utf-8') as f:
                f.write(f"# 翻译术语智能修复报告\n\n")
                f.write(f"报告生成时间: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
                f.write(f"修复模式: {'模拟修复' if self.dry_run else '实际修复'}\n\n")
                
                # 统计信息
                f.write("## 修复统计\n\n")
                f.write(f"- 数据库总记录数: {self.fix_log['stats'].get('initial_count', 0)}\n")
                f.write(f"- 发现问题记录: {self.fix_log['stats'].get('problem_terms_count', 0)} 条\n")
                f.write(f"- 成功修复术语: {self.fix_log['stats'].get('fixed_count', 0)} 条\n")
                f.write(f"- 跳过的术语: {len(self.fix_log['skipped_terms'])} 条\n")
                f.write(f"- 修复出错的术语: {len(self.fix_log['error_terms'])} 条\n\n")
                
                # 修复的术语列表
                if self.fix_log['fixed_terms']:
                    f.write("## 修复的术语列表\n\n")
                    f.write("| ID | 原英文术语 | 原中文翻译 | 修复后英文术语 | 修复后中文翻译 | 源文件 |\n")
                    f.write("|---|---|---|---|---|---|\n")
                    
                    # 只显示前100条记录
                    for term in self.fix_log['fixed_terms'][:100]:
                        f.write(f"| {term['id']} | {term['old_english'][:50]} | {term['old_chinese'][:50]} | {term['new_english'][:50]} | {term['new_chinese'][:50]} | {term['source_file']} |\n")
                    
                    if len(self.fix_log['fixed_terms']) > 100:
                        f.write(f"| ... | ... | ... | ... | ... | ... |\n")
                        f.write(f"| 总计 {len(self.fix_log['fixed_terms'])} 条记录 | | | | | |\n")
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
                f.write("2. 对于跳过的记录，建议手动检查确认是否需要修复\n")
                f.write("3. 如果修复效果不理想，可以使用备份文件恢复数据库\n")
            
            file_size = os.path.getsize(filename) / 1024  # KB
            print(f"修复报告已导出到 {filename} ({round(file_size, 2)} KB)")
            return True
        except Exception as e:
            print(f"生成修复报告时出错: {e}")
            return False

if __name__ == "__main__":
    fixer = SmartInteractiveTermFixer()
    success = fixer.run_interactive_fix()
    
    print("\n===== 修复完成 =====")
    
    if success:
        print("智能交互式修复完成！")
        print("详细的修复报告可在 translation_terms_smart_fix_report.md 中查看。")
        print("建议运行 final_verification.py 进行最终验证。")
    else:
        print("智能交互式修复过程中出现问题，请查看上面的详细报告。")