#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
检查数据库结构的优化脚本
"""

import os
import sqlite3
import logging
from typing import List, Tuple

# 配置日志
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def check_file_exists(file_path: str) -> bool:
    """检查文件是否存在"""
    exists = os.path.exists(file_path)
    logging.info(f"数据库文件 '{file_path}' 是否存在: {exists}")
    if exists:
        logging.info(f"文件大小: {os.path.getsize(file_path)} 字节")
    return exists

def list_tables(cursor: sqlite3.Cursor) -> List[str]:
    """列出数据库中的所有表"""
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table'")
    return [table[0] for table in cursor.fetchall()]

def describe_table(cursor: sqlite3.Cursor, table_name: str) -> None:
    """描述表结构和内容"""
    logging.info(f"- 表名: {table_name}")
    cursor.execute(f"PRAGMA table_info({table_name})")
    columns = cursor.fetchall()
    logging.info("  表结构:")
    for col in columns:
        logging.info(f"  - {col[1]} ({col[2]})")
    
    cursor.execute(f"SELECT COUNT(*) FROM {table_name}")
    count = cursor.fetchone()[0]
    logging.info(f"  记录数: {count}")
    
    if count > 0:
        logging.info("  前3条记录示例:")
        cursor.execute(f"SELECT * FROM {table_name} LIMIT 3")
        for i, row in enumerate(cursor.fetchall()):
            logging.info(f"  - 记录 {i+1}: {row}")

def check_database(db_path: str) -> None:
    """检查数据库结构"""
    try:
        with sqlite3.connect(db_path) as conn:
            cursor = conn.cursor()
            tables = list_tables(cursor)
            if tables:
                logging.info("\n数据库中的表:")
                for table_name in tables:
                    describe_table(cursor, table_name)
            else:
                logging.info("数据库中没有表")
    except sqlite3.Error as e:
        logging.error(f"数据库错误: {e}")

def find_other_db_files(directory: str) -> List[str]:
    """查找目录下的其他数据库文件"""
    return [f for f in os.listdir(directory) if f.endswith('.db')]

def main() -> None:
    db_path = 'translation_terms.db'
    if check_file_exists(db_path):
        check_database(db_path)
    
    logging.info("\n检查当前目录下是否有其他可能的数据库文件:")
    db_files = find_other_db_files('.')
    if db_files:
        for f in db_files:
            logging.info(f"- {f}")
    else:
        logging.info("没有找到其他数据库文件")

if __name__ == '__main__':
    main()