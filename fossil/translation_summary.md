# Fossil 界面翻译工作总结

本文档总结了 Fossil 代码库中四个关键文件的中文界面翻译工作，包括 shun.c、sitemap.c、cache.c 和 setup.c。这些翻译旨在使中文用户能够更直观地理解和使用 Fossil 版本控制系统的界面功能。

## 已完成的翻译工作

### 1. shun.c（被回避制品管理界面）

翻译了整个被回避制品管理界面，包括：
- 页面标题和操作状态消息
- 制品验证状态文本
- 核心功能说明和警告文本
- 表单按钮和操作指南
- 被回避制品列表显示文本

### 2. sitemap.c（站点地图界面）

翻译了整个站点地图界面，包括：
- 页面标题（站点地图、测试页面地图、时间线示例）
- 所有导航链接文本
- 菜单条目和子菜单条目
- 测试页面和时间线示例中的各种链接

### 3. cache.c（网页缓存管理界面）

翻译了整个网页缓存管理界面，包括：
- 页面标题和操作按钮
- 缓存条目属性显示文本
- 缓存说明和配置指南
- 错误页面文本

### 4. setup.c（管理设置界面）

翻译了管理设置相关界面，包括：
- 服务器管理页面标题和配置错误警告
- 设备检查相关警告信息
- 错误日志配置描述和使用说明
- 原始TH1命令页面的标题、警告文本、标签和按钮

## 翻译术语对照表

| 英文词条 | 中文词条 | 使用界面 |
|---------|---------|---------|
| Shunned Artifacts | 被回避的制品 | shun.c - 页面标题 |
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
| Site Map | 站点地图 | sitemap.c - 页面标题 |
| Home Page | 首页 | sitemap.c - 导航链接 |
| File Browser | 文件浏览器 | sitemap.c - 导航链接 |
| Project Timeline | 项目时间线 | sitemap.c - 导航链接 |
| Branches | 分支 | sitemap.c - 导航链接 |
| Search | 搜索 | sitemap.c - 导航链接 |
| Chat | 聊天 | sitemap.c - 导航链接 |
| Tickets/Bug Reports | 工单/缺陷报告 | sitemap.c - 导航链接 |
| Wiki | 维基 | sitemap.c - 导航链接 |
| Login | 登录 | sitemap.c - 导航链接 |
| Logout | 退出登录 | sitemap.c - 导航链接 |
| Create a new account | 创建新账户 | sitemap.c - 导航链接 |
| Repository Status | 仓库状态 | sitemap.c - 导航链接 |
| Help | 帮助 | sitemap.c - 导航链接 |
| Administration Pages | 管理页面 | sitemap.c - 导航链接 |
| Test Pages | 测试页面 | sitemap.c - 导航链接 |
| Web Cache Status | 网页缓存状态 | cache.c - 页面标题 |
| Refresh | 刷新 | cache.c - 按钮文本 |
| Current Cache Entries | 当前缓存条目 | cache.c - 标题 |
| size | 大小 | cache.c - 缓存属性 |
| hit-count | 命中次数 | cache.c - 缓存属性 |
| last-access | 最后访问 | cache.c - 缓存属性 |
| checkin info | 检出信息 | cache.c - 链接文本 |
| About The Web-Cache | 关于网页缓存 | cache.c - 标题 |
| Enable | 启用 | cache.c - 按钮文本 |
| Clear the cache | 清除缓存 | cache.c - 按钮文本 |
| Cache Download Error | 缓存下载错误 | cache.c - 错误页面标题 |
| Server Administration | 服务器管理 | setup.c - 页面标题 |
| Configuration Error | 配置错误 | setup.c - 警告文本 |
| HTML header | HTML 头部 | setup.c - 链接文本 |
| WARNING | 警告 | setup.c - 警告文本 |
| Error Log | 错误日志 | setup.c - 菜单项 |
| Disabled | 已禁用 | setup.c - 状态文本 |
| filename | 文件名 | setup.c - 占位文本 |
| option | 参数 | setup.c - 描述文本 |
| Raw TH1 Commands | 原始TH1命令 | setup.c - 页面标题 |
| Caution | 警告 | setup.c - 提示文本 |
| Run TH1 | 运行TH1 | setup.c - 按钮文本 |

## 翻译原则和注意事项

1. **保持技术准确性**：所有技术术语和专业词汇都保持了原有的准确性，确保翻译不会导致功能理解偏差。

2. **中文表达自然**：在保持准确性的前提下，尽量使中文表达流畅自然，符合中文用户的阅读习惯。

3. **保持一致性**：对于相同或相似的术语，在不同文件和界面中保持了统一的翻译。

4. **保留必要的英文元素**：对于一些特定的技术标记和代码相关的引用，保留了英文原文，以确保系统功能不受影响。

5. **适配中文界面**：调整了部分语句结构，使其更适合中文界面的显示和阅读。

通过这些翻译工作，Fossil 的核心管理界面现在能够为中文用户提供更友好、更易理解的使用体验。