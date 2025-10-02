
# Fossil翻译术语管理工具

这个工具用于管理Fossil代码库的英文-中文翻译术语，方便翻译工作的持续性和一致性。

## 文件说明

- **translation_terms_manager.py**: 主要的术语管理工具，包含完整的数据库操作功能
- **translation_terms.db**: SQLite数据库文件，存储所有翻译术语
- **translation_terms_export.md**: 导出的Markdown格式术语表
- **demo_terms_usage.py**: 使用示例脚本，展示工具的基本操作

## 功能特性

1. **术语管理**：添加、更新、搜索翻译术语
2. **自动导入**：从补丁文件和摘要文件自动提取术语
3. **统计分析**：查看术语数量和分布情况
4. **导出功能**：导出为Markdown格式，便于查看和分享

## 使用方法

### 初始化数据库

首次使用时，运行主脚本初始化数据库并导入现有术语：

```
python translation_terms_manager.py
```

### 日常操作

运行示例脚本查看基本操作：

```
python demo_terms_usage.py
```

### 添加新术语

可以通过修改translation_terms_manager.py添加新的术语，或扩展功能实现批量导入。

### 导出术语表

术语表会自动导出为Markdown格式，可直接用于文档或翻译参考。

## 扩展建议

1. 添加GUI界面，方便非技术人员使用
2. 实现批量导入/导出功能，支持CSV、Excel等格式
3. 添加术语冲突检测和建议功能
4. 集成到翻译工作流程中，实现自动更新

