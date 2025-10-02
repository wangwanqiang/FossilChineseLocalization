#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
翻译术语数据库终极修复工具
此工具针对之前修复后仍存在的问题，提供更智能的术语顺序检测和修复机制。
"""

import sqlite3
import os
import re
from datetime import datetime
import json

class UltimateTermFixer:
    def __init__(self, db_path='translation_terms.db'):
        self.db_path = db_path
        self.conn = None
        self.cursor = None
        self.fix_log = {
            'started_at': datetime.now().strftime('%Y-%m-%d %H:%M:%S'),
            'fixed_terms': [],
            'skipped_terms': [],
            'duplicate_terms': [],
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

    def is_definitely_chinese(self, text):
        """改进的中文检测逻辑，更智能地判断文本是否主要是中文"""
        if not text:
            return False
        
        text_str = str(text).strip()
        if not text_str:
            return False
        
        # 排除HTML标签、代码和特殊格式
        if self.is_code_or_html(text_str):
            return False
        
        # 检查是否包含中文字符
        if not re.search(r'[\u4e00-\u9fa5]', text_str):
            return False
        
        # 计算中文字符的比例和数量
        chinese_count = len(re.findall(r'[\u4e00-\u9fa5]', text_str))
        total_count = len(text_str)
        
        # 如果中文比例超过30%，或者有3个以上中文字符，认为是中文
        return (chinese_count / total_count > 0.3) or (chinese_count >= 3)

    def is_definitely_english(self, text):
        """改进的英文检测逻辑，更智能地判断文本是否主要是英文"""
        if not text:
            return False
        
        text_str = str(text).strip()
        if not text_str:
            return False
        
        # 排除HTML标签、代码和特殊格式
        if self.is_code_or_html(text_str):
            return False
        
        # 如果包含中文字符，则不是英文
        if re.search(r'[\u4e00-\u9fa5]', text_str):
            return False
        
        # 英文文本通常包含字母或常见技术词汇
        return bool(re.search(r'[a-zA-Z]', text_str)) or self.is_tech_english(text_str)

    def is_code_or_html(self, text):
        """检查文本是否为代码或HTML"""
        text_str = str(text)
        # 常见的代码或HTML特征
        code_patterns = [
            r'<[^>]+>',  # HTML标签
            r'\b\w+\s*\([^)]*\)',  # 函数调用
            r'\b[a-zA-Z_]\w*\s*=',  # 变量赋值
            r'\bif\s*\(|else|for\s*\(|while\s*\(',  # 控制结构
            r'\\x[0-9a-fA-F]{2}',  # 转义字符
            r'\b\d+\s*[a-zA-Z]',  # 数字+字母
        ]
        
        for pattern in code_patterns:
            if re.search(pattern, text_str):
                return True
        
        # 检查代码关键字
        code_keywords = ['entry_attribute', 'onoff_attribute', 'textarea_attribute', 'cgi_printf']
        for keyword in code_keywords:
            if keyword in text_str:
                return True
        
        return False

    def is_tech_english(self, text):
        """检查文本是否为技术英文术语"""
        text_str = str(text).lower()
        # 常见的技术英文词汇
        tech_terms = [
            'url', 'http', 'https', 'api', 'json', 'xml', 'html', 'css', 'js',
            'user', 'admin', 'password', 'login', 'logout', 'server', 'client',
            'database', 'table', 'column', 'row', 'index', 'query', 'select',
            'insert', 'update', 'delete', 'where', 'and', 'or', 'true', 'false'
        ]
        
        # 技术文件扩展名
        extensions = ['.c', '.h', '.py', '.js', '.css', '.html', '.md', '.txt']
        
        # 检查是否包含技术术语或扩展名
        for term in tech_terms:
            if term in text_str:
                return True
        
        for ext in extensions:
            if ext in text_str:
                return True
        
        return False

    def identify_order_problem(self, english_term, chinese_term):
        """智能识别术语顺序问题"""
        # 将None转换为空字符串
        english_term = str(english_term) if english_term is not None else ''
        chinese_term = str(chinese_term) if chinese_term is not None else ''
        
        # 情况1: 英文字段包含明显的中文，中文字段不包含明显的中文
        en_is_cn = self.is_definitely_chinese(english_term)
        cn_not_cn = not self.is_definitely_chinese(chinese_term)
        
        # 情况2: 英文字段不包含明显的英文，中文字段包含明显的英文
        en_not_en = not self.is_definitely_english(english_term)
        cn_is_en = self.is_definitely_english(chinese_term)
        
        # 情况3: 英文字段是技术术语或文件名，而中文字段是描述性文本
        en_is_tech = self.is_tech_english(english_term) or self.is_code_or_html(english_term)
        cn_is_desc = self.is_definitely_chinese(chinese_term) and not self.is_code_or_html(chinese_term)
        
        # 情况4: 特殊模式检测（如 'xxx.c - 描述' 格式）
        if re.search(r'\.c\s*-', english_term) and self.is_definitely_chinese(chinese_term):
            return False  # 正确的顺序
        if re.search(r'\.c\s*-', chinese_term) and self.is_definitely_chinese(english_term):
            return True   # 需要交换
        
        # 综合判断 - 修复隐式行连接问题
        return ((en_is_cn and cn_not_cn) or \
                (en_not_en and cn_is_en) or \
                (en_is_tech and cn_is_desc))

    def find_duplicate_terms(self):
        """查找重复的术语记录"""
        try:
            # 查找重复的英文术语+源文件组合
            self.cursor.execute("""
                SELECT english_term, source_file, GROUP_CONCAT(id) as ids, COUNT(*) as count 
                FROM terms 
                GROUP BY english_term, source_file 
                HAVING count > 1
            """)
            duplicates = self.cursor.fetchall()
            
            duplicate_list = []
            for eng, src, ids_str, count in duplicates:
                ids = list(map(int, ids_str.split(',')))
                duplicate_list.append({
                    'english_term': eng,
                    'source_file': src,
                    'ids': ids,
                    'count': count
                })
            
            return duplicate_list
        except sqlite3.Error as e:
            print(f"查找重复术语时出错: {e}")
            return []

    def get_all_terms(self):
        """获取所有术语记录"""
        try:
            self.cursor.execute("""
                SELECT id, english_term, chinese_translation, source_file 
                FROM terms 
                ORDER BY id
            """)
            return self.cursor.fetchall()
        except sqlite3.Error as e:
            print(f"获取所有术语时出错: {e}")
            return []

    def fix_term_order(self, term_id, english_term, chinese_term, source_file):
        """修复术语顺序"""
        try:
            # 先检查是否存在冲突
            self.cursor.execute(
                "SELECT id FROM terms WHERE english_term = ? AND source_file = ?", 
                (chinese_term, source_file)
            )
            existing_id = self.cursor.fetchone()
            
            if existing_id:
                # 如果存在冲突，先删除原记录，再插入新记录
                # 但保留一条记录以避免数据丢失
                if existing_id[0] != term_id:
                    print(f"发现冲突记录: ID={term_id} 与 ID={existing_id[0]}，保留后者")
                    self.fix_log['skipped_terms'].append({
                        'id': term_id,
                        'reason': '冲突记录，已存在相同的英文术语+源文件组合',
                        'english_term': english_term,
                        'chinese_term': chinese_term
                    })
                    # 删除当前记录
                    self.cursor.execute("DELETE FROM terms WHERE id = ?", (term_id,))
                    return False
                else:
                    # 如果是同一条记录，则直接更新
                    self.cursor.execute(
                        "UPDATE terms SET english_term = ?, chinese_translation = ? WHERE id = ?",
                        (chinese_term, english_term, term_id)
                    )
            else:
                # 没有冲突，直接更新
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

    def handle_duplicate_terms(self):
        """处理重复的术语记录"""
        duplicates = self.find_duplicate_terms()
        if not duplicates:
            print("没有发现重复的术语记录")
            return
        
        print(f"发现 {len(duplicates)} 组重复的术语记录")
        
        for duplicate in duplicates:
            # 保留最新的记录，删除旧记录
            # 或者根据具体情况决定保留哪一条
            if len(duplicate['ids']) > 1:
                # 保留第一个记录，删除其他记录
                keep_id = duplicate['ids'][0]
                delete_ids = duplicate['ids'][1:]
                
                for del_id in delete_ids:
                    try:
                        self.cursor.execute("DELETE FROM terms WHERE id = ?", (del_id,))
                        self.fix_log['duplicate_terms'].append({
                            'deleted_id': del_id,
                            'kept_id': keep_id,
                            'english_term': duplicate['english_term'],
                            'source_file': duplicate['source_file']
                        })
                    except sqlite3.Error as e:
                        print(f"删除重复记录ID={del_id}时出错: {e}")
                        self.fix_log['error_terms'].append({
                            'id': del_id,
                            'error': f"删除重复记录时出错: {str(e)}"
                        })

    def export_terms(self, filename='translation_terms_export_final.md'):
        """导出修复后的术语表"""
        try:
            self.cursor.execute(
                "SELECT english_term, chinese_translation, source_file FROM terms ORDER BY english_term"
            )
            terms = self.cursor.fetchall()
            
            with open(filename, 'w', encoding='utf-8') as f:
                f.write("# 翻译术语表\n\n")
                f.write("| 英文术语 | 中文翻译 | 源文件 |\n")
                f.write("|---------|---------|--------|\n")
                
                for term in terms:
                    english = str(term[0]) if term[0] is not None else ''
                    chinese = str(term[1]) if term[1] is not None else ''
                    source = str(term[2]) if term[2] is not None else 'Unknown'
                    
                    # 转义Markdown特殊字符
                    english = english.replace('|', '\\|').replace('\n', '<br>')
                    chinese = chinese.replace('|', '\\|').replace('\n', '<br>')
                    
                    f.write(f"| {english} | {chinese} | {source} |\n")
            
            file_size = os.path.getsize(filename) / 1024  # KB
            print(f"术语表已导出到 {filename} ({round(file_size, 2)} KB)")
            return True
        except Exception as e:
            print(f"导出术语表时出错: {e}")
            return False

    def save_fix_log(self, filename='translation_terms_final_fix_log.md'):
        """保存修复日志"""
        try:
            with open(filename, 'w', encoding='utf-8') as f:
                f.write(f"# 翻译术语修复日志\n\n")
                f.write(f"修复时间: {self.fix_log['started_at']}\n")
                f.write(f"修复完成时间: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n")
                
                # 统计信息
                f.write("## 修复统计\n\n")
                f.write(f"- 成功修复术语数量: {len(self.fix_log['fixed_terms'])}\n")
                f.write(f"- 跳过的术语数量: {len(self.fix_log['skipped_terms'])}\n")
                f.write(f"- 处理的重复术语数量: {len(self.fix_log['duplicate_terms'])}\n")
                f.write(f"- 修复出错的术语数量: {len(self.fix_log['error_terms'])}\n\n")
                
                # 修复的术语列表
                if self.fix_log['fixed_terms']:
                    f.write("## 修复的术语列表\n\n")
                    f.write("| ID | 原英文术语 | 原中文翻译 | 修复后英文术语 | 修复后中文翻译 | 源文件 |\n")
                    f.write("|---|---|---|---|---|---|\n")
                    
                    # 只显示前50条记录
                    for term in self.fix_log['fixed_terms'][:50]:
                        f.write(f"| {term['id']} | {term['old_english'][:50]} | {term['old_chinese'][:50]} | {term['new_english'][:50]} | {term['new_chinese'][:50]} | {term['source_file']} |\n")
                    
                    if len(self.fix_log['fixed_terms']) > 50:
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
                    f.write("| ID | 错误信息 |\n")
                    f.write("|---|---|\n")
                    
                    for term in self.fix_log['error_terms']:
                        f.write(f"| {term['id']} | {term['error'][:100]} |\n")
                    f.write("\n")
            
            file_size = os.path.getsize(filename) / 1024  # KB
            print(f"修复日志已导出到 {filename} ({round(file_size, 2)} KB)")
            return True
        except Exception as e:
            print(f"保存修复日志时出错: {e}")
            return False

    def create_backup(self):
        """创建数据库备份"""
        backup_time = datetime.now().strftime('%Y%m%d_%H%M%S')
        backup_path = f'translation_terms.db.backup_{backup_time}'
        
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

    def run_full_fix(self):
        """运行完整的修复流程"""
        print("===== 翻译术语数据库终极修复 =====")
        print(f"修复开始时间: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        
        # 1. 创建数据库备份
        if not self.create_backup():
            print("警告: 无法创建数据库备份，但仍继续修复过程")
        
        # 2. 连接数据库
        if not self.connect_db():
            print("修复失败：无法连接数据库")
            return False
        
        try:
            # 3. 获取数据库统计信息
            self.cursor.execute("SELECT COUNT(*) FROM terms")
            total_terms = self.cursor.fetchone()[0]
            print(f"数据库总记录数: {total_terms}")
            
            # 4. 获取所有术语记录
            terms = self.get_all_terms()
            print(f"获取到 {len(terms)} 条术语记录")
            
            # 5. 修复术语顺序
            fixed_count = 0
            for term in terms:
                term_id, english, chinese, source_file = term
                
                # 智能识别是否需要修复
                if self.identify_order_problem(english, chinese):
                    if self.fix_term_order(term_id, english, chinese, source_file):
                        fixed_count += 1
                        # 每修复10条记录显示一次进度
                        if fixed_count % 10 == 0:
                            print(f"已修复 {fixed_count} 条记录...")
            
            print(f"术语顺序修复完成，共修复 {fixed_count} 条记录")
            
            # 6. 处理重复术语
            self.handle_duplicate_terms()
            
            # 7. 导出修复后的术语表
            self.export_terms()
            
            # 8. 保存修复日志
            self.save_fix_log()
            
            # 9. 更新统计信息
            self.cursor.execute("SELECT COUNT(*) FROM terms")
            final_count = self.cursor.fetchone()[0]
            
            self.fix_log['stats'] = {
                'initial_count': total_terms,
                'final_count': final_count,
                'fixed_count': fixed_count,
                'duplicate_count': len(self.find_duplicate_terms())
            }
            
            print("\n===== 修复总结 =====")
            print(f"修复前记录数: {total_terms}")
            print(f"修复后记录数: {final_count}")
            print(f"成功修复术语: {fixed_count} 条")
            print(f"跳过术语: {len(self.fix_log['skipped_terms'])} 条")
            print(f"处理重复术语: {len(self.fix_log['duplicate_terms'])} 条")
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

if __name__ == "__main__":
    fixer = UltimateTermFixer()
    success = fixer.run_full_fix()
    
    print("\n===== 修复完成 =====")
    
    if success:
        print("数据库修复成功！")
        print("您可以使用 translation_terms_export_final.md 文件作为最终的术语表。")
        print("详细的修复记录可在 translation_terms_final_fix_log.md 中查看。")
        print("建议运行 final_verification.py 进行最终验证。")
    else:
        print("数据库修复过程中出现问题，请查看上面的详细报告。")