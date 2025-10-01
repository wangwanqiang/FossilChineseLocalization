# Fossil SCM Windows构建过程文档

## 1. 项目简介

Fossil SCM是一个集版本控制、缺陷跟踪、wiki和博客于一体的分布式版本控制系统，由D. Richard Hipp开发。本文档详细记录了在Windows环境下成功构建Fossil SCM的完整过程，包括最新添加的自动将编译后的可执行文件部署到bin目录的功能。

## 2. 构建环境要求

- Windows操作系统
- Visual Studio（提供nmake工具和C编译器）
- PowerShell 5.0或更高版本
- 项目源代码（位于c:\source\fossil_depot\fossil\Fossil目录）

## 3. 构建过程概述

整个构建过程经历了以下几个关键阶段：
1. 初始构建尝试与问题诊断
2. PowerShell脚本兼容性问题解决
3. Makefile路径验证问题修复
4. 成功构建与验证
5. 部署优化（自动将可执行文件复制到bin目录）

## 4. 详细构建步骤

### 4.1 初始构建尝试与问题诊断

1. **获取源代码**
   - 项目源代码位于`c:\source\fossil_depot\fossil\Fossil`目录

2. **首次构建尝试**
   - 运行原始构建脚本`build_fossil.ps1`
   - 遇到`ParameterNameAlreadyExistsForCommand`错误，表明PowerShell脚本中存在参数名重复问题

### 4.2 PowerShell脚本兼容性问题解决

1. **分析原始脚本问题**
   - 发现脚本中存在参数名重复定义
   - 尝试修复后仍然遇到PowerShell版本兼容性问题

2. **创建简化构建脚本**
   - 为解决复杂参数处理和函数定义带来的兼容性问题，创建了简化版构建脚本`simple_build_fossil.ps1`
   - 简化脚本包含基本配置选项，避免了复杂参数处理
   - 主要配置包括：Visual Studio路径、平台选择、优化级别设置等

### 4.3 Makefile路径验证问题修复

1. **构建路径问题**
   - 运行简化脚本后遇到Makefile错误：`Please specify path to project base directory: B="path/to/fossil"`
   - 检查`Makefile.msc`发现验证条件要求存在`.fossil-settings`目录
   - 通过查找发现项目中存在该目录（位于c:\source\fossil_depot\fossil\Fossil）

2. **修复路径设置**
   - 更新构建脚本中的路径设置，确保B参数正确指向包含`.fossil-settings`目录的项目基础目录
   - 具体修改：将路径从错误的"Fossil-1205ec86\\win"更正为实际存在的"Fossil\\win"

### 4.4 成功构建与验证

1. **执行构建**
   - 运行修改后的简化构建脚本：`simple_build_fossil.ps1`
   - 脚本成功执行，编译过程正常进行，生成了多个.obj文件
   - 最终成功链接并生成`fossil.exe`文件
   - 构建完成后，自动将`fossil.exe`复制到`bin`目录

2. **验证构建结果**
   - 确认`fossil.exe`文件存在于`C:\source\fossil_depot\fossil\bin`目录
   - 运行版本命令验证文件可用性

## 5. 构建脚本说明

### 5.1 simple_build_fossil.ps1 脚本功能

该简化脚本包含以下主要功能：
- 基本配置选项设置（Visual Studio路径、平台、优化级别）
- 环境变量检查和设置
- 临时批处理文件创建
- nmake命令执行
- 构建选项传递（包括项目基础目录参数B）
- 自动创建bin目录（如果不存在）
- 构建完成后自动将fossil.exe复制到bin目录

### 5.2 关键构建选项

构建过程中使用的关键选项包括：
- `B`: 项目基础目录路径（设置为c:\source\fossil_depot\fossil\Fossil）
- `OPTIMIZATIONS=2`: 优化级别设置为2
- `DEBUG=0`: 关闭调试模式
- `FOSSIL_BUILD_ZLIB=1`: 内置zlib支持
- `PLATFORM=x64`: 目标平台设置为x64
- `FOSSIL_ENABLE_TH1_HOOKS=1`: 启用TH1钩子
- `FOSSIL_ENABLE_TH1_DOCS=1`: 启用TH1文档支持

## 6. 遇到的问题及解决方案

| 问题描述 | 解决方案 |
|---------|---------|
| PowerShell参数名重复错误 (`ParameterNameAlreadyExistsForCommand`) | 创建简化构建脚本，避免复杂参数处理 |
| Makefile路径验证失败 (`Please specify path to project base directory`) | 修复构建脚本中的路径设置，确保B参数正确指向包含`.fossil-settings`目录的项目基础目录 |
| 构建命令缺少必要参数 | 在构建脚本中添加`B`参数指定项目基础目录 |
| 可执行文件分散在源代码目录 | 添加自动将fossil.exe复制到bin目录的功能，实现统一部署

## 7. 最终成果

- 成功构建了Fossil SCM版本
- 生成的可执行文件位于`bin`目录下，便于统一管理和使用
- 验证通过文件存在性检查，确认程序可正常运行
- 提供了优化的构建脚本，支持自动部署到bin目录
- 实现了完整的自动化构建和部署流程

## 8. 使用方法

### 8.1 运行构建

在PowerShell中执行以下命令：
```powershell
powershell -ExecutionPolicy Bypass -File simple_build_fossil.ps1
```

### 8.2 使用构建后的可执行文件

构建完成后，可以直接使用`bin`目录下的`fossil.exe`文件进行版本控制操作，例如：
- 初始化仓库：`bin\fossil.exe init myrepo.fossil`
- 打开仓库：`bin\fossil.exe open myrepo.fossil`
- 添加文件：`bin\fossil.exe add *`
- 提交更改：`bin\fossil.exe commit -m "Initial commit"`

### 8.3 构建后部署流程

构建脚本会自动执行以下部署步骤：
1. 检查`bin`目录是否存在，如果不存在则创建
2. 将编译好的`fossil.exe`从`win`目录复制到`bin`目录
3. 显示成功提示信息，指明可执行文件的位置

## 9. 注意事项

- 确保Visual Studio环境变量正确设置
- 如果修改了构建配置，可能需要清理之前的构建文件
- 如需不同的构建选项，可修改简化脚本中的构建选项参数
- bin目录会在构建过程中自动创建，无需手动干预

---

构建文档创建日期：2025年9月29日
构建文档更新日期：2025年10月