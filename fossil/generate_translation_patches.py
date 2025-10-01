#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
生成翻译相关的补丁文件，排除二进制文件

该脚本用于从git仓库中提取翻译相关的提交，并生成不包含二进制文件的补丁
"""

import os
import subprocess
import re

# 设置工作目录
work_dir = r"c:\source\fossil_depot\fossil"

# 设置输出目录
output_dir = os.path.join(work_dir, "translation_patches_clean")

# 创建输出目录（如果不存在）
if not os.path.exists(output_dir):
    os.makedirs(output_dir)
    print(f"创建输出目录: {output_dir}")

# 检查是否在git仓库中
def is_git_repo():
    try:
        subprocess.run(["git", "rev-parse", "--is-inside-work-tree"], 
                      cwd=work_dir, check=True, 
                      stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return True
    except subprocess.CalledProcessError:
        return False

# 获取所有翻译相关的提交
def get_translation_commits():
    try:
        result = subprocess.run(["git", "log", "--grep=翻译", "--format=%H"], 
                              cwd=work_dir, check=True, 
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        commits = result.stdout.decode('utf-8').strip().split('\n')
        return commits
    except Exception as e:
        print(f"获取翻译提交时出错: {str(e)}")
        return []

# 生成单个补丁文件
def generate_patch(commit_hash, patch_number):
    patch_file = os.path.join(output_dir, f"{patch_number:04d}-translation.patch")
    
    try:
        # 获取提交的完整diff
        result = subprocess.run(["git", "diff", f"{commit_hash}^..{commit_hash}"], 
                              cwd=work_dir, check=True, 
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        diff_content = result.stdout.decode('utf-8', errors='replace')
        
        # 过滤二进制文件
        filtered_lines = []
        skip_binary_section = False
        
        for line in diff_content.split('\n'):
            line_with_newline = line + '\n'
            
            # 检查是否开始一个二进制文件比较部分
            if '.exe' in line and line.startswith('diff --git'):
                skip_binary_section = True
                continue
            elif line.startswith('diff --git'):
                # 新的diff部分开始，重置跳过标志
                skip_binary_section = False
                filtered_lines.append(line_with_newline)
            elif skip_binary_section:
                # 跳过二进制文件内容
                continue
            elif line.startswith('Binary files '):
                # 跳过二进制文件标记行
                continue
            elif '.exe' in line:
                # 跳过任何包含.exe的行
                continue
            else:
                # 添加非二进制内容
                filtered_lines.append(line_with_newline)
        
        # 保存过滤后的补丁文件
        with open(patch_file, 'w', encoding='utf-8') as f:
            f.writelines(filtered_lines)
        
        print(f"已生成补丁文件: {patch_file}")
        return True
    except Exception as e:
        print(f"生成补丁文件时出错 ({commit_hash}): {str(e)}")
        return False

# 主函数
def main():
    if not is_git_repo():
        print(f"错误: {work_dir} 不是git仓库")
        exit(1)
    
    # 获取翻译提交
    commits = get_translation_commits()
    
    if not commits:
        print("没有找到与翻译相关的提交")
        exit(1)
    
    print(f"找到 {len(commits)} 个翻译相关的提交")
    
    # 生成补丁文件
    success_count = 0
    for i, commit in enumerate(reversed(commits)):  # 按时间顺序生成补丁
        if generate_patch(commit, i+1):
            success_count += 1
    
    print(f"\n补丁生成完成！")
    print(f"成功生成 {success_count} 个补丁文件")
    print(f"补丁文件保存在: {output_dir}")

if __name__ == "__main__":
    main()