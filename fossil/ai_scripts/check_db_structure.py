#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
检查数据库结构的简单脚本
"""

import os
import sqlite3

def main():
    # 检查文件是否存在
    db_path = 'translation_terms.db'
    print(f"数据库文件 '{db_path}' 是否存在: {os.path.exists(db_path)}")
    
    if os.path.exists(db_path):
        print(f"文件大小: {os.path.getsize(db_path)} 字节")
        
        # 连接数据库并检查表
        try:
            conn = sqlite3.connect(db_path)
            cursor = conn.cursor()
            
            print("\n数据库中的表:")
            cursor.execute("SELECT name FROM sqlite_master WHERE type='table'")
            tables = cursor.fetchall()
            
            if tables:
                for table in tables:
                    table_name = table[0]
                    print(f"- 表名: {table_name}")
                    
                    # 查看表结构
                    print(f"  表结构:")
                    cursor.execute(f"PRAGMA table_info({table_name})")
                    columns = cursor.fetchall()
                    for col in columns:
                        print(f"  - {col[1]} ({col[2]})")
                    
                    # 查看记录数
                    cursor.execute(f"SELECT COUNT(*) FROM {table_name}")
                    count = cursor.fetchone()[0]
                    print(f"  记录数: {count}")
                    
                    # 查看前3条记录（如果有）
                    if count > 0:
                        print(f"  前3条记录示例:")
                        cursor.execute(f"SELECT * FROM {table_name} LIMIT 3")
                        for i, row in enumerate(cursor.fetchall()):
                            print(f"  - 记录 {i+1}: {row}")
            else:
                print("数据库中没有表")
                
        except sqlite3.Error as e:
            print(f"数据库错误: {e}")
        finally:
            conn.close()
    
    # 检查是否有其他可能的数据库文件
    print("\n检查当前目录下是否有其他可能的数据库文件:")
    db_files = [f for f in os.listdir('.') if f.endswith('.db')]
    if db_files:
        for f in db_files:
            print(f"- {f}")
    else:
        print("没有找到其他数据库文件")

if __name__ == '__main__':
    main()