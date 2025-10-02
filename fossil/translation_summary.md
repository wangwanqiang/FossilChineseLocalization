# Fossil 界面翻译工作总结

本文档总结了 Fossil 代码库中关键文件的中文界面翻译工作，包括 shun.c、setup.c 和 alerts.c。这些翻译旨在使中文用户能够更直观地理解和使用 Fossil 版本控制系统的界面功能。

## 已完成的翻译工作

### 1. shun.c（被回避制品管理界面）

翻译了整个被回避制品管理界面，包括：
- 页面标题和操作状态消息
- 制品验证状态文本
- 核心功能说明和警告文本
- 表单按钮和操作指南
- 被回避制品列表显示文本

### 2. setup.c（项目Logo和背景设置界面）

翻译了项目Logo和背景设置界面，包括：
- 页面标题和说明文本
- 图像上传表单和按钮文本
- 属性说明和链接文本
- 各种图像类型（Logo、背景、图标）的描述文本

### 3. alerts.c（电子邮件通知设置界面）

翻译了电子邮件通知设置界面，包括：
- 页面标题和操作按钮
- 配置项标签和描述文本
- 状态显示文本
- 必填项提示和建议值说明

## 翻译术语对照表

| 英文词条 | 中文词条 | 使用界面 |
|---------|---------|---------|
| Shunned Artifacts | 被回避的制品 | shun.c - 页面标题 |
| Artifact(s) | 制品 | shun.c - 状态消息 |
| Shun | 回避 | shun.c - 按钮文本 |
| Review | 查看 | shun.c - 按钮文本 |
| Accept | 接受 | shun.c - 按钮文本 |
| Rebuild | 重建 | shun.c - 按钮文本 |
| Bad artifact | 无效制品 | shun.c - 验证状态 |
| Already shunned | 已被回避 | shun.c - 验证状态 |
| Unknown | 未知 | shun.c - 验证状态 |
| OK | 有效 | shun.c - 验证状态 |
| Abbreviated | 缩写形式 | shun.c - 验证状态 |
| Warning: | 警告： | shun.c - 状态总结 |
| Edit Project Logo And Background | 编辑项目Logo和背景 | setup.c - 页面标题 |
| The current project logo | 当前项目Logo | setup.c - 描述文本 |
| Logo Image file | Logo图像文件 | setup.c - 表单标签 |
| Change Logo | 更改Logo | setup.c - 按钮文本 |
| Revert To Default | 恢复默认 | setup.c - 按钮文本 |
| Background image file | 背景图像文件 | setup.c - 表单标签 |
| Change Background | 更改背景 | setup.c - 按钮文本 |
| Icon image file | 图标图像文件 | setup.c - 表单标签 |
| Change Icon | 更改图标 | setup.c - 按钮文本 |
| Note: | 注意： | setup.c - 提示文本 |
| Email Notification Setup | 电子邮件通知设置 | alerts.c - 页面标题 |
| Status | 状态 | alerts.c - 标题 |
| Refresh | 刷新 | alerts.c - 按钮文本 |
| Disabled | 已禁用 | alerts.c - 状态文本 |
| Configuration | 配置 | alerts.c - 标题 |
| Apply Changes | 应用更改 | alerts.c - 按钮文本 |
| Canonical Server URL | 规范服务器URL | alerts.c - 表单标签 |
| Required. | 必填项。 | alerts.c - 提示文本 |
| Administrator email address | 管理员电子邮件地址 | alerts.c - 表单标签 |
| Repository Nickname | 仓库昵称 | alerts.c - 表单标签 |
| Subscription Renewal Interval In Days | 订阅续订间隔（天） | alerts.c - 表单标签 |
| Email Send Method | 电子邮件发送方法 | alerts.c - 表单标签 |
| SMTP Relay Host | SMTP中继主机 | alerts.c - 表单标签 |
| Store Emails In This Database | 在此数据库中存储电子邮件 | alerts.c - 表单标签 |
| Pipe Email Text Into This Command | 将电子邮件文本传送到此命令 | alerts.c - 表单标签 |
| Store Emails In This Directory | 在此目录中存储电子邮件 | alerts.c - 表单标签 |
| Interwiki Map Configuration | 跨维基地图配置 | interwiki.c - 页面标题 |

## 翻译原则和注意事项

1. **保持技术准确性**：所有技术术语和专业词汇都保持了原有的准确性，确保翻译不会导致功能理解偏差。

2. **中文表达自然**：在保持准确性的前提下，尽量使中文表达流畅自然，符合中文用户的阅读习惯。

3. **保持一致性**：对于相同或相似的术语，在不同文件和界面中保持了统一的翻译。