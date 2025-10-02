#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
翻译术语数据库最终验证工具
此工具全面检查修复后的数据库状态，确认所有术语顺序问题都已解决。
"""

import sqlite3
import os
import re
from datetime import datetime

class FinalDatabaseVerifier:
    def __init__(self, db_path='translation_terms.db'):
        self.db_path = db_path
        self.conn = None
        self.cursor = None

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
            self.conn.close()
            print("数据库连接已关闭")

    def is_definitely_chinese(self, text):
        """判断文本是否主要是中文"""
        if not text:
            return False
        text_str = str(text)
        # 检查是否包含中文字符
        if not re.search(r'[\u4e00-\u9fa5]', text_str):
            return False
        # 计算中文字符的比例
        chinese_count = len(re.findall(r'[\u4e00-\u9fa5]', text_str))
        total_count = len(text_str.strip())
        # 如果中文比例超过30%，则认为是中文
        return total_count > 0 and (chinese_count / total_count) > 0.3

    def is_definitely_english(self, text):
        """判断文本是否主要是英文"""
        if not text:
            return False
        text_str = str(text)
        # 如果包含中文，则不是英文
        if re.search(r'[\u4e00-\u9fa5]', text_str):
            return False
        # 英文文本通常包含字母
        return bool(re.search(r'[a-zA-Z]', text_str))

    def get_database_stats(self):
        """获取数据库基本统计信息"""
        try:
            # 获取总记录数
            self.cursor.execute("SELECT COUNT(*) FROM terms")
            total_terms = self.cursor.fetchone()[0]
            
            # 获取源文件分布
            self.cursor.execute("SELECT source_file, COUNT(*) as count FROM terms GROUP BY source_file ORDER BY count DESC")
            source_distribution = self.cursor.fetchall()
            
            # 检查是否存在空记录
            self.cursor.execute("SELECT COUNT(*) FROM terms WHERE english_term IS NULL OR english_term = ''")
            empty_english = self.cursor.fetchone()[0]
            
            self.cursor.execute("SELECT COUNT(*) FROM terms WHERE chinese_translation IS NULL OR chinese_translation = ''")
            empty_chinese = self.cursor.fetchone()[0]
            
            return {
                'total_terms': total_terms,
                'source_distribution': source_distribution,
                'empty_english': empty_english,
                'empty_chinese': empty_chinese
            }
        except sqlite3.Error as e:
            print(f"获取数据库统计信息时出错: {e}")
            return None

    def check_term_order(self):
        """检查术语顺序是否正确"""
        try:
            # 获取所有记录
            self.cursor.execute("SELECT id, english_term, chinese_translation FROM terms")
            all_terms = self.cursor.fetchall()
            
            # 检查顺序问题
            order_problems = []
            for term in all_terms:
                term_id, english, chinese = term
                
                # 检查条件：英文主要是中文，或者中文不主要是中文
                english_is_chinese = self.is_definitely_chinese(english)
                chinese_not_chinese = not self.is_definitely_chinese(chinese)
                
                if english_is_chinese or chinese_not_chinese:
                    order_problems.append({
                        'id': term_id,
                        'english': english,
                        'chinese': chinese
                    })
            
            return order_problems
        except sqlite3.Error as e:
            print(f"检查术语顺序时出错: {e}")
            return []

    def check_duplicate_terms(self):
        """检查是否有重复的术语记录"""
        try:
            # 检查英文术语+源文件的重复
            self.cursor.execute("""
                SELECT english_term, source_file, COUNT(*) as count 
                FROM terms 
                WHERE english_term IS NOT NULL AND english_term != '' 
                GROUP BY english_term, source_file 
                HAVING count > 1
                ORDER BY count DESC
            """)
            duplicate_terms = self.cursor.fetchall()
            
            return duplicate_terms
        except sqlite3.Error as e:
            print(f"检查重复术语时出错: {e}")
            return []

    def get_sample_terms(self, limit=20):
        """获取随机样本记录"""
        try:
            self.cursor.execute("""
                SELECT id, english_term, chinese_translation, source_file 
                FROM terms 
                ORDER BY RANDOM() 
                LIMIT ?
            """, (limit,))
            sample_terms = self.cursor.fetchall()
            
            return sample_terms
        except sqlite3.Error as e:
            print(f"获取样本记录时出错: {e}")
            return []

    def check_export_files(self):
        """检查导出文件是否存在且有效"""
        export_files = [
            'translation_terms_export.md',
            'translation_terms_export_fixed.md',
            'translation_terms_fix_log.md'
        ]
        
        file_info = []
        for file_path in export_files:
            if os.path.exists(file_path):
                file_size = os.path.getsize(file_path) / 1024  # KB
                file_info.append({
                    'name': file_path,
                    'exists': True,
                    'size_kb': round(file_size, 2)
                })
            else:
                file_info.append({
                    'name': file_path,
                    'exists': False,
                    'size_kb': 0
                })
        
        return file_info

    def run_complete_verification(self):
        """运行完整的数据库验证"""
        print("===== 翻译术语数据库最终验证 =====")
        print(f"验证时间: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        
        # 1. 连接数据库
        if not self.connect_db():
            print("验证失败：无法连接数据库")
            return False
        
        try:
            # 2. 获取数据库统计信息
            stats = self.get_database_stats()
            if stats:
                print("\n----- 数据库基本统计 -----\n")
                print(f"总术语数: {stats['total_terms']}")
                print(f"英文术语为空: {stats['empty_english']}")
                print(f"中文翻译为空: {stats['empty_chinese']}")
                
                print("\n源文件分布:")
                for source, count in stats['source_distribution'][:10]:  # 显示前10个源文件
                    source_str = str(source) if source else "Unknown"
                    print(f"  {source_str}: {count} 条")
                if len(stats['source_distribution']) > 10:
                    print(f"  ... 还有 {len(stats['source_distribution']) - 10} 个源文件")
            
            # 3. 检查术语顺序
            order_problems = self.check_term_order()
            print("\n----- 术语顺序检查 -----\n")
            print(f"发现顺序问题记录数: {len(order_problems)}")
            
            # 如果有问题，显示前5条
            if order_problems:
                print("\n顺序问题记录示例 (前5条):")
                print("ID | English Term (前30字符)      | Chinese Term (前30字符)")
                print("---|-------------------------------|-------------------------------")
                
                for problem in order_problems[:5]:
                    english_trunc = str(problem['english'])[:30] if problem['english'] else "None"
                    chinese_trunc = str(problem['chinese'])[:30] if problem['chinese'] else "None"
                    print(f"{problem['id']:2d} | {english_trunc:<30} | {chinese_trunc:<30}")
            else:
                print("✓ 恭喜！没有发现术语顺序问题。")
            
            # 4. 检查重复术语
            duplicate_terms = self.check_duplicate_terms()
            print("\n----- 重复术语检查 -----\n")
            print(f"发现重复术语组数量: {len(duplicate_terms)}")
            
            if duplicate_terms:
                print("\n重复术语组示例 (前5组):")
                print("英文术语 | 源文件 | 重复次数")
                print("---------|--------|--------")
                
                for english, source, count in duplicate_terms[:5]:
                    source_str = str(source) if source else "Unknown"
                    english_trunc = str(english)[:20]
                    print(f"{english_trunc:<9} | {source_str:<6} | {count}")
            else:
                print("✓ 没有发现重复的术语记录。")
            
            # 5. 显示随机样本
            sample_terms = self.get_sample_terms(10)
            print("\n----- 随机样本记录 -----\n")
            print("ID | English Term (前30字符)      | Chinese Term (前30字符)     | Source")
            print("---|-------------------------------|-------------------------------|-------")
            
            for term in sample_terms:
                term_id, english, chinese, source = term
                english_trunc = str(english)[:30] if english else "None"
                chinese_trunc = str(chinese)[:30] if chinese else "None"
                source_trunc = str(source)[:10] if source else "Unknown"
                print(f"{term_id:2d} | {english_trunc:<30} | {chinese_trunc:<30} | {source_trunc}")
            
            # 6. 检查导出文件
            export_files_info = self.check_export_files()
            print("\n----- 导出文件检查 -----\n")
            for file_info in export_files_info:
                status = "✓ 存在" if file_info['exists'] else "✗ 不存在"
                size_info = f" ({file_info['size_kb']} KB)" if file_info['exists'] else ""
                print(f"{file_info['name']}: {status}{size_info}")
            
            # 7. 总结
            print("\n===== 验证总结 =====")
            if not order_problems:
                print("✓ 数据库术语顺序验证通过！所有术语的英文和中文顺序正确。")
            else:
                print(f"⚠ 数据库仍存在 {len(order_problems)} 条术语顺序问题，建议进一步修复。")
            
            # 检查是否有空记录
            if stats and (stats['empty_english'] > 0 or stats['empty_chinese'] > 0):
                print(f"⚠ 注意：数据库中有 {stats['empty_english']} 条英文术语为空，{stats['empty_chinese']} 条中文翻译为空。")
            
            # 检查是否有重复记录
            if duplicate_terms:
                print(f"⚠ 注意：数据库中存在 {len(duplicate_terms)} 组重复的术语记录。")
            
            print("====================")
            
            return len(order_problems) == 0
            
        except Exception as e:
            print(f"验证过程中发生错误: {e}")
            import traceback
            traceback.print_exc()
            return False
        finally:
            # 关闭数据库连接
            self.close_db()

if __name__ == "__main__":
    verifier = FinalDatabaseVerifier()
    success = verifier.run_complete_verification()
    
    print("\n===== 验证完成 =====")
    
    # 根据验证结果显示不同的消息
    if success:
        print("数据库验证成功！所有术语顺序问题已解决。")
        print("您可以使用 translation_terms_export_fixed.md 文件作为最终的术语表。")
        print("详细的修复记录可在 translation_terms_fix_log.md 中查看。")
    else:
        print("数据库验证未完全通过，请查看上面的详细报告。")
        print("建议进一步分析和修复剩余问题。")