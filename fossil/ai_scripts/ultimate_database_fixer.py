#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Fossil 翻译术语数据库终极修复工具
特别优化了术语顺序判断逻辑，确保英文和中文术语完全正确对应
"""

import os
import re
import sqlite3
import datetime
import argparse
import time

class UltimateTranslationTermsManager:
    def __init__(self, db_path='translation_terms.db'):
        self.db_path = db_path
        self.conn = None
        self.cursor = None
        self.backup_suffix = datetime.datetime.now().strftime('%Y%m%d_%H%M%S')
    
    def connect(self):
        """连接到数据库"""
        try:
            self.conn = sqlite3.connect(self.db_path)
            self.cursor = self.conn.cursor()
            self.create_table()
            return True
        except sqlite3.Error as e:
            print(f"数据库连接错误: {e}")
            return False
    
    def create_table(self):
        """创建术语表"""
        try:
            self.cursor.execute('''
                CREATE TABLE IF NOT EXISTS terms (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    english_term TEXT NOT NULL,
                    chinese_translation TEXT NOT NULL,
                    source_file TEXT,
                    context TEXT,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    UNIQUE(english_term, source_file)
                )
            ''')
            self.conn.commit()
        except sqlite3.Error as e:
            print(f"创建表错误: {e}")
    
    def backup_database(self):
        """备份数据库"""
        if os.path.exists(self.db_path):
            backup_path = f"{self.db_path}.backup_{self.backup_suffix}"
            try:
                # 使用文件复制方式备份，更可靠
                with open(self.db_path, 'rb') as src, open(backup_path, 'wb') as dst:
                    dst.write(src.read())
                print(f"数据库备份成功: {backup_path}")
                return backup_path
            except Exception as e:
                print(f"数据库备份失败: {e}")
                return None
        else:
            print("数据库文件不存在，跳过备份")
            return None
    
    def rebuild_database(self):
        """重建数据库"""
        # 备份现有数据库
        backup_path = self.backup_database()
        
        # 删除旧数据库
        if os.path.exists(self.db_path):
            try:
                os.remove(self.db_path)
                print(f"已删除旧数据库文件: {self.db_path}")
            except Exception as e:
                print(f"删除旧数据库文件失败: {e}")
                return False
        
        # 连接新数据库
        if not self.connect():
            return False
        
        return True
    
    def is_definitely_chinese(self, text):
        """更精确地检测文本是否为中文"""
        if not text or not isinstance(text, str):
            return False
        
        # 移除非文本内容
        text = re.sub(r'[\s\-\.\,\:\;\(\)\[\]\{\}"\'\`]', '', text)
        if not text:
            return False
        
        # 检测中文字符
        chinese_chars = re.findall(r'[\u4e00-\u9fff]', text)
        # 严格标准：如果有中文字符，或者非英文字符占比超过30%
        if chinese_chars or len([c for c in text if not (c.isascii() and c.isalpha())]) / len(text) > 0.3:
            return True
        
        # 排除一些特定的非英文模式
        # 1. 包含文件路径信息的
        if re.search(r'\.c\s*-\s*', text):
            return True
        # 2. 包含中文常见词汇
        chinese_words = ['页面标题', '按钮文本', '验证状态', '提示文本', '表单标签']
        for word in chinese_words:
            if word in text:
                return True
        
        return False
    
    def is_definitely_english(self, text):
        """更精确地检测文本是否为英文"""
        if not text or not isinstance(text, str):
            return False
        
        # 移除非文本内容
        text = re.sub(r'[\s\-\.\,\:\;\(\)\[\]\{\}"\'\`]', '', text)
        if not text:
            return False
        
        # 英文单词占比超过90%
        english_chars = re.findall(r'[a-zA-Z]', text)
        if len(english_chars) / len(text) > 0.9:
            return True
        
        # 一些特定的英文模式
        # 1. 常见的技术术语或UI元素名称
        common_terms = ['administrator', 'email', 'address', 'button', 'label', 'title', 'header', 'footer',
                        'menu', 'option', 'setting', 'configuration', 'file', 'directory', 'path',
                        'project', 'repository', 'branch', 'commit', 'push', 'pull', 'merge',
                        'login', 'logout', 'user', 'password', 'permission', 'access', 'denied',
                        'error', 'warning', 'success', 'info', 'debug', 'log', 'message']
        for term in common_terms:
            if term.lower() in text.lower():
                return True
        
        # 2. 包含明显的英文语法结构（如冠词、介词等）
        english_patterns = [r'\bthe\b', r'\ba\b', r'\ban\b', r'\band\b', r'\bor\b', 
                            r'\bof\b', r'\bto\b', r'\bfor\b', r'\bin\b', r'\bon\b']
        for pattern in english_patterns:
            if re.search(pattern, text.lower()):
                return True
        
        return False
    
    def swap_terms_precisely(self, term1, term2):
        """更精确地判断并交换术语顺序"""
        # 基本情况：如果有一个明显是中文，另一个明显是英文，就交换
        if self.is_definitely_chinese(term1) and self.is_definitely_english(term2):
            return term2, term1
        elif self.is_definitely_chinese(term2) and self.is_definitely_english(term1):
            return term1, term2
        
        # 其他情况，使用更复杂的判断
        # 检查术语长度、字符类型分布等
        term1_has_chinese = bool(re.search(r'[\u4e00-\u9fff]', str(term1)))
        term2_has_chinese = bool(re.search(r'[\u4e00-\u9fff]', str(term2)))
        
        # 如果一个有中文，另一个没有，就交换
        if term1_has_chinese and not term2_has_chinese:
            return term2, term1
        elif term2_has_chinese and not term1_has_chinese:
            return term1, term2
        
        # 如果两个都有中文，可能是术语对中的注释或说明，保持原样
        # 或者根据其他规则判断
        return term1, term2
    
    def add_term(self, english_term, chinese_translation, source_file=None, context=None):
        """添加或更新术语，使用更精确的术语顺序判断"""
        # 确保输入是字符串
        english_term = str(english_term).strip() if english_term is not None else ''
        chinese_translation = str(chinese_translation).strip() if chinese_translation is not None else ''
        
        # 跳过空记录
        if not english_term or not chinese_translation:
            return False
        
        # 跳过无效的表头记录
        if (english_term in ['英文词条', '---------'] or 
            chinese_translation in ['中文词条', '---------'] or
            english_term == chinese_translation):
            return False
        
        # 更精确地纠正术语顺序
        english_term, chinese_translation = self.swap_terms_precisely(english_term, chinese_translation)
        
        try:
            # 使用INSERT OR REPLACE来处理重复记录
            self.cursor.execute('''
                INSERT OR REPLACE INTO terms 
                (english_term, chinese_translation, source_file, context)
                VALUES (?, ?, ?, ?)
            ''', (english_term, chinese_translation, source_file, context))
            self.conn.commit()
            return True
        except sqlite3.Error as e:
            print(f"添加术语错误: {e}")
            return False
    
    def add_terms_from_summary(self, summary_file):
        """从摘要文件导入术语"""
        if not os.path.exists(summary_file):
            print(f"摘要文件不存在: {summary_file}")
            return 0
        
        added_count = 0
        try:
            with open(summary_file, 'r', encoding='utf-8') as f:
                content = f.read()
                
                # 提取Markdown表格中的术语对
                # 匹配表格行，忽略表头
                term_pattern = re.compile(r'\|\s*([^|]+?)\s*\|\s*([^|]+?)\s*\|', re.MULTILINE)
                matches = term_pattern.findall(content)
                
                for match in matches:
                    term1, term2 = match
                    # 跳过表头行
                    if term1.strip() in ['英文词条', 'English Term'] and term2.strip() in ['中文词条', 'Chinese Term']:
                        continue
                    # 跳过分隔线
                    if term1.strip() == '---------':
                        continue
                    
                    if self.add_term(term1, term2, 'summary'):
                        added_count += 1
            
            return added_count
        except Exception as e:
            print(f"从摘要文件导入术语错误: {e}")
            return 0
    
    def add_terms_from_patch(self, patch_file):
        """从补丁文件导入术语"""
        if not os.path.exists(patch_file):
            print(f"补丁文件不存在: {patch_file}")
            return 0
        
        added_count = 0
        try:
            with open(patch_file, 'r', encoding='utf-8') as f:
                content = f.read()
                
                # 从文件名提取source_file信息
                source_file = self.get_source_file_from_patch_name(patch_file)
                
                # 提取+和-行中的术语对，优化了提取逻辑
                lines = content.split('\n')
                for i, line in enumerate(lines):
                    if line.startswith('+') and i > 0 and lines[i-1].startswith('-'):
                        # 找到对应的-行和+行
                        old_text = lines[i-1][1:].strip()
                        new_text = line[1:].strip()
                        
                        # 尝试更智能地提取术语对
                        term_pairs = self.extract_term_pairs_enhanced(old_text, new_text, source_file)
                        for term1, term2 in term_pairs:
                            if self.add_term(term1, term2, source_file, f"{old_text} -> {new_text}"):
                                added_count += 1
            
            return added_count
        except Exception as e:
            print(f"从补丁文件导入术语错误: {e}")
            return 0
    
    def get_source_file_from_patch_name(self, patch_file):
        """从补丁文件名推断源文件"""
        patch_name = os.path.basename(patch_file)
        
        # 常见文件映射规则
        if 'shun' in patch_name.lower():
            return 'shun.c'
        elif 'alert' in patch_name.lower():
            return 'alerts.c'
        elif 'setup' in patch_name.lower():
            return 'setup.c'
        elif 'interwiki' in patch_name.lower():
            return 'interwiki.c'
        else:
            return None
    
    def extract_term_pairs_enhanced(self, old_text, new_text, source_file=None):
        """增强版术语对提取逻辑"""
        term_pairs = []
        
        # 如果旧文本和新文本明显不同
        if old_text and new_text and old_text != new_text:
            # 1. 简单情况：一个是英文，一个是中文
            if self.is_definitely_chinese(new_text) and self.is_definitely_english(old_text):
                term_pairs.append((old_text, new_text))
            elif self.is_definitely_chinese(old_text) and self.is_definitely_english(new_text):
                term_pairs.append((new_text, old_text))
            # 2. 更复杂的情况：尝试提取文本中的术语
            else:
                # 查找可能的术语边界
                # 例如，提取引号中的内容
                quotes_pattern = re.compile(r'"(.*?)"')
                old_quotes = quotes_pattern.findall(old_text)
                new_quotes = quotes_pattern.findall(new_text)
                
                # 如果两边都有引号内容，且数量相同，尝试匹配
                if len(old_quotes) == len(new_quotes) and len(old_quotes) > 0:
                    for oq, nq in zip(old_quotes, new_quotes):
                        if oq != nq:
                            term_pairs.append((oq, nq))
                
        return term_pairs
    
    def export_terms(self, export_file='translation_terms_export.md'):
        """导出术语表为Markdown格式"""
        try:
            # 查询所有有效的术语，按源文件和英文术语排序
            self.cursor.execute('''
                SELECT english_term, chinese_translation, source_file, context 
                FROM terms 
                WHERE english_term NOT IN ('英文词条', '---------') 
                AND chinese_translation NOT IN ('中文词条', '---------') 
                ORDER BY source_file, english_term
            ''')
            terms = self.cursor.fetchall()
            
            with open(export_file, 'w', encoding='utf-8') as f:
                # 写入标题和生成时间
                f.write(f"# Fossil翻译术语表\n")
                f.write(f"生成时间: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n")
                
                # 按源文件分组
                terms_by_file = {}
                for term in terms:
                    source_file = term[2] or 'Unknown'
                    if source_file not in terms_by_file:
                        terms_by_file[source_file] = []
                    terms_by_file[source_file].append(term)
                
                # 逐个源文件写入
                for source_file in sorted(terms_by_file.keys()):
                    f.write(f"## {source_file}\n\n")
                    # 写入表格头
                    f.write("| English Term | Chinese Translation | Context |\n")
                    f.write("|--------------|---------------------|---------|\n")
                    # 写入术语行
                    for term in terms_by_file[source_file]:
                        english, chinese, _, context = term
                        # 转义管道符
                        english = english.replace('|', '\\|')
                        chinese = chinese.replace('|', '\\|')
                        context = context.replace('|', '\\|') if context else ''
                        f.write(f"| {english} | {chinese} | {context} |\n")
                    f.write("\n")
            
            print(f"术语表已导出到: {export_file}")
            return len(terms)
        except Exception as e:
            print(f"导出术语表错误: {e}")
            return 0
    
    def get_stats(self):
        """获取数据库统计信息"""
        stats = {
            'total_count': 0,
            'by_source': {}
        }
        
        try:
            # 总记录数
            self.cursor.execute('''
                SELECT COUNT(*) FROM terms 
                WHERE english_term NOT IN ('英文词条', '---------') 
                AND chinese_translation NOT IN ('中文词条', '---------')
            ''')
            stats['total_count'] = self.cursor.fetchone()[0]
            
            # 按源文件分布
            self.cursor.execute('''
                SELECT source_file, COUNT(*) 
                FROM terms 
                WHERE english_term NOT IN ('英文词条', '---------') 
                AND chinese_translation NOT IN ('中文词条', '---------')
                GROUP BY source_file 
                ORDER BY COUNT(*) DESC
            ''')
            for row in self.cursor.fetchall():
                source_file = row[0] or 'Unknown'
                stats['by_source'][source_file] = row[1]
            
        except sqlite3.Error as e:
            print(f"获取统计信息错误: {e}")
        
        return stats
    
    def close(self):
        """关闭数据库连接"""
        if self.conn:
            self.conn.close()
            print("数据库连接已关闭")


def main():
    # 解析命令行参数
    parser = argparse.ArgumentParser(description='Fossil翻译术语数据库终极修复工具')
    parser.add_argument('--rebuild', action='store_true', help='重建数据库')
    parser.add_argument('--export', action='store_true', help='导出术语表')
    parser.add_argument('--summary', default='translation_summary.md', help='翻译摘要文件路径')
    parser.add_argument('--patch-dir', default='translation_patches_clean', help='补丁文件目录')
    args = parser.parse_args()
    
    # 创建管理器实例
    manager = UltimateTranslationTermsManager()
    
    try:
        # 重建数据库模式
        if args.rebuild:
            print("===== 开始重建数据库 =====")
            if not manager.rebuild_database():
                print("数据库重建失败")
                return 1
        else:
            # 直接连接数据库
            if not manager.connect():
                print("数据库连接失败")
                return 1
        
        # 导入术语
        if args.rebuild:
            # 从摘要文件导入
            print(f"\n从 {args.summary} 导入术语...")
            summary_count = manager.add_terms_from_summary(args.summary)
            print(f"从摘要文件导入: {summary_count} 个术语")
            
            # 从补丁文件导入
            if os.path.exists(args.patch_dir):
                print(f"\n从 {args.patch_dir} 目录中的补丁文件导入术语...")
                patch_count = 0
                patch_files = [f for f in os.listdir(args.patch_dir) if f.endswith('.patch')]
                for patch_file in sorted(patch_files):
                    full_path = os.path.join(args.patch_dir, patch_file)
                    print(f"处理文件: {patch_file}")
                    patch_count += manager.add_terms_from_patch(full_path)
                print(f"从补丁文件导入: {patch_count} 个术语")
            else:
                print(f"补丁文件目录不存在: {args.patch_dir}")
                patch_count = 0
            
            print(f"\n===== 导入完成 =====")
            print(f"总共导入: {summary_count + patch_count} 个术语")
        
        # 显示统计信息
        print("\n数据库统计信息:")
        stats = manager.get_stats()
        print(f"总术语数: {stats['total_count']}")
        if stats['by_source']:
            print("按文件分布:")
            for source_file, count in stats['by_source'].items():
                print(f"  {source_file}: {count} 个术语")
        
        # 导出术语表
        if args.export:
            manager.export_terms()
        
        print("\n操作完成！")
        return 0
        
    finally:
        # 确保关闭数据库连接
        manager.close()


if __name__ == '__main__':
    exit_code = main()
    # 添加一点延迟，确保所有输出都能显示
    time.sleep(0.5)
    exit(exit_code)