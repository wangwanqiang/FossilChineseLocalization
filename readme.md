# Fossil 中文本地化项目

## 项目简介

Fossil 中文本地化项目旨在为 Fossil 版本控制系统提供完整的中文翻译和本地化支持。通过本项目，中文用户可以更方便地使用 Fossil 的各项功能。

## 主要特性

本项目的核心目标是提供高质量的中文翻译：

- **完整性**：确保 Fossil 的所有功能都有对应的中文翻译
- **准确性**：翻译内容经过专业人员审核，确保术语和表达的准确
- **一致性**：保持翻译风格和术语在整个项目中的一致
- **易用性**：优化中文用户的使用体验

## 项目结构

本项目包含以下主要组件：

- `Fossil/`：Fossil 源代码的主要目录
  - `src/`：核心源代码文件
  - `skins/`：Web 界面的主题样式
  - `www/`：Web 界面资源和文档
  - `test/`：测试用例和验证脚本
- `_FOSSIL_`：本地仓库数据
- `locale/`：翻译文件和本地化资源

## 快速开始

### 获取源代码

本仓库包含了 Fossil 的完整源代码。您可以直接使用这些代码构建 Fossil 可执行文件。

### 构建指南

#### Unix/Linux/macOS 平台

```bash
cd Fossil
./configure
make
```

#### Windows 平台

使用 Visual Studio 或 MinGW 编译：

```bash
cd Fossil
nmake /f Makefile.msc
```

### 基本使用示例

创建新仓库：
```bash
fossil new project.fossil
```

打开仓库：
```bash
mkdir project
cd project
fossil open ../project.fossil
```

添加和提交文件：
```bash
fossil add *.c *.h
fossil commit -m "Initial commit"
```

启动 Web 界面：
```bash
fossil ui
```

## 学习资源

- **内置帮助**：运行 `fossil help` 获取命令行帮助
- **Web 文档**：启动 Web 界面后可以访问完整文档
- **官方网站**：[https://fossil-scm.org/](https://fossil-scm.org/)
- **文档目录**：项目中的 `www/` 目录包含详细文档

## 贡献指南

Fossil 是一个开源项目，欢迎社区贡献：

1. 报告问题：通过问题跟踪系统提交 bug 报告
2. 提交改进：通过补丁或合并请求提供代码改进
3. 完善文档：帮助改进和翻译文档
4. 参与讨论：加入邮件列表或论坛讨论


## 联系与支持

- 官方网站：[https://fossil-scm.org/](https://fossil-scm.org/)
- 邮件列表：fossil-users@lists.fossil-scm.org
- 问题跟踪：通过 Fossil 内置的问题跟踪系统

## 关于本仓库

本仓库包含 Fossil 版本控制系统的源代码和相关资源，可用于构建和使用 Fossil 进行项目管理。如果您想了解更多关于 Fossil 的信息，请访问官方网站获取完整文档和社区支持。

本说明文档由AI自动生成，请认真确认其内容的真实性。

## 备忘

当前网络地址：http://fossil.wanqiang.wang/
