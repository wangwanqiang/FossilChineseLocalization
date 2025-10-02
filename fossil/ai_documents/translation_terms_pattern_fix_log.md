# 翻译术语模式修复日志

修复时间: 2025-10-02 11:36:06
修复完成时间: 2025-10-02 11:36:07

## 修复统计

- 成功修复术语数量: 158
- 跳过的术语数量: 0
- 修复出错的术语数量: 0

## 按类型统计

- 文件名+描述模式: 8 条
- 中文在前、英文在后: 32 条
- 代码片段混合: 118 条

## 修复的术语列表

### 文件名+描述模式

| ID | 原英文术语 | 原中文翻译 | 修复后英文术语 | 修复后中文翻译 |
|---|---|---|---|---|
| 1 | shun.c - 页面标题 | 被回避的制品 | 被回避的制品 | shun.c - 页面标题 |
| 3 | shun.c - 按钮文本 | 查看 | 查看 | shun.c - 按钮文本 |
| 5 | shun.c - 验证状态 | 无效制品 | 无效制品 | shun.c - 验证状态 |
| 9 | setup.c - 页面标题 | 编辑项目Logo和背景 | 编辑项目Logo和背景 | setup.c - 页面标题 |
| 11 | setup.c - 按钮文本 | 更改Logo | 更改Logo | setup.c - 按钮文本 |
| 15 | setup.c - 提示文本 | 注意： | 注意： | setup.c - 提示文本 |
| 17 | alerts.c - 按钮文本 | 刷新 | 刷新 | alerts.c - 按钮文本 |
| 21 | alerts.c - 表单标签 | 管理员电子邮件地址 | 管理员电子邮件地址 | alerts.c - 表单标签 |

### 中文在前、英文在后

| ID | 原英文术语 | 原中文翻译 | 修复后英文术语 | 修复后中文翻译 |
|---|---|---|---|---|
| 2 | 制品 | Artifact(s) | Artifact(s) | 制品 |
| 20 | 规范服务器URL | Canonical Server URL | Canonical Server URL | 规范服务器URL |
| 22 | 仓库昵称 | Repository Nickname | Repository Nickname | 仓库昵称 |
| 26 | 在此目录中存储电子邮件 | Store Emails In This Directory | Store Emails In This Directory | 在此目录中存储电子邮件 |
| 36 | @ 如果此值不为空字符串，则它将成为所有出站通知电子邮件中"List-ID:"头的参数。 | @ (Property: "email-listid")</p> | @ (Property: "email-listid")</p> | @ 如果此值不为空字符串，则它将成为所有出站通知电子邮件中"List-ID:"头的参数。 |
| 40 | @ 如果此值是大于或等于14的整数N，则电子邮件通知订阅 | @ (Property: "email-renew-interval")</p> | @ (Property: "email-renew-interval")</p> | @ 如果此值是大于或等于14的整数N，则电子邮件通知订阅 |
| 56 | /* 不为非设置用户显示 intermap 编辑字段 */ | /* Do not show intermap editing fields to non-setu | /* Do not show intermap editing fields to non-setu | /* 不为非设置用户显示 intermap 编辑字段 */ |
| 63 | > 段落之间用空行分隔。 | > End a line with two or more spaces to force a mi | > End a line with two or more spaces to force a mi | > 段落之间用空行分隔。 |
| 64 | > 1.  **\[显示文本\]\(URL\)** | > 3.  **\[display text\]\(URL 'Title'\)** | > 3.  **\[display text\]\(URL 'Title'\)** | > 1.  **\[显示文本\]\(URL\)** |
| 67 | > 在格式 8 中，URL 成为显示文本。这对于指向 wiki 页面、签入和工单哈希的超链接很有用。 | > hyperlinks that refer to wiki pages and check-in | > hyperlinks that refer to wiki pages and check-in | > 在格式 8 中，URL 成为显示文本。这对于指向 wiki 页面、签入和工单哈希的超链接很有用。 |
| 72 | > 对于文本或代码块： | > For blocks of text or code: | > For blocks of text or code: | > 对于文本或代码块： |
| 73 | > 1. 使用制表符或至少四个空格缩进文本 | > "`language-WORD`" is "pikchr". | > "`language-WORD`" is "pikchr". | > 1. 使用制表符或至少四个空格缩进文本 |
| 74 | > 使用标准皮肤，逐字文本以等宽字体呈现，但这纯粹是一个呈现问题，由皮肤的 CSS 控制。 | > but that is purely a presentation matter, contro | > but that is purely a presentation matter, contro | > 使用标准皮肤，逐字文本以等宽字体呈现，但这纯粹是一个呈现问题，由皮肤的 CSS 控制。 |
| 76 | > 如果第一行后面跟着水平线或空行，则第一行是标题。 | > The first row is a header if followed by a horiz | > The first row is a header if followed by a horiz | > 如果第一行后面跟着水平线或空行，则第一行是标题。 |
| 79 | oval "开始" fit; arrow; box "你好，世界！" fit; arrow; ova | oval "Start" fit; arrow; box "Hello, World!" fit;  | oval "Start" fit; arrow; box "Hello, World!" fit;  | oval "开始" fit; arrow; box "你好，世界！" fit; arrow; ova |
| 80 | > 使用 [Pikchr](https://pikchr.org/home) 进行格式化，结果如下： | > Formatted using [Pikchr](https://pikchr.org/home | > Formatted using [Pikchr](https://pikchr.org/home | > 使用 [Pikchr](https://pikchr.org/home) 进行格式化，结果如下： |
| 83 | > [^标签]: 脚注定义必须从第一列开始。 | >      Definition continues until indentation drop | >      Definition continues until indentation drop | > [^标签]: 脚注定义必须从第一列开始。 |
| 100 | multiple_choice_attribute("重定向到HTTPS", | multiple_choice_attribute("Redirect to HTTPS", | multiple_choice_attribute("Redirect to HTTPS", | multiple_choice_attribute("重定向到HTTPS", |
| 148 | multiple_choice_attribute("每项时间格式", "timeline-date | multiple_choice_attribute("Per-Item Time Format",  | multiple_choice_attribute("Per-Item Time Format",  | multiple_choice_attribute("每项时间格式", "timeline-date |
| 184 | @ 根据Wiki页面名称将Wiki页面与分支、标签、工单或签入关联。当此功能启用时，以"branch | @ check-in, tag or ticket are treated specially wh | @ check-in, tag or ticket are treated specially wh | @ 根据Wiki页面名称将Wiki页面与分支、标签、工单或签入关联。当此功能启用时，以"branch |
| ... | ... | ... | ... | ... |
| 总计 32 条记录 | | | | |

### 代码片段混合

| ID | 原英文术语 | 原中文翻译 | 修复后英文术语 | 修复后中文翻译 |
|---|---|---|---|---|
| 30 | @ (Property: "email-url")</p> | @ <p><b>必填项。</b> | @ <p><b>必填项。</b> | @ (Property: "email-url")</p> |
| 32 | @ (Property: "email-admin")</p> | @ <p>这是系统管理员的电子邮件地址。 | @ <p>这是系统管理员的电子邮件地址。 | @ (Property: "email-admin")</p> |
| 34 | @ can handle bounces. (Property: "email-self")</p> | @ <p><b>必填项。</b> | @ <p><b>必填项。</b> | @ can handle bounces. (Property: "email-self")</p> |
| 38 | @ (Property: "email-subname")</p> | @ <p><b>必填项。</b> | @ <p><b>必填项。</b> | @ (Property: "email-subname")</p> |
| 42 | @ (Property: "email-send-method")</p> | @ <p>如何发送电子邮件。需要以下字段提供辅助信息。 | @ <p>如何发送电子邮件。需要以下字段提供辅助信息。 | @ (Property: "email-send-method")</p> |
| 44 | @ (Property: "email-send-relayhost")</p> | @ <p>当发送方法为"SMTP中继"时，每条电子邮件消息通过SMTP协议（rfc5321） | @ <p>当发送方法为"SMTP中继"时，每条电子邮件消息通过SMTP协议（rfc5321） | @ (Property: "email-send-relayhost")</p> |
| 48 | @ (Property: "email-send-dir")</p> | @ <p>当发送方法为"存储在目录中"时，每条电子邮件消息作为单独的文件存储在此处显示的目录中。 | @ <p>当发送方法为"存储在目录中"时，每条电子邮件消息作为单独的文件存储在此处显示的目录中。 | @ (Property: "email-send-dir")</p> |
| 57 | @ tag field but leave the "Base URL" field blank.< | @ <p>要添加新映射，请填写下面的表单并为标记提供唯一名称。要编辑现有映射，请填写表单并使用现有名 | @ <p>要添加新映射，请填写下面的表单并为标记提供唯一名称。要编辑现有映射，请填写表单并使用现有名 | @ tag field but leave the "Base URL" field blank.< |
| 86 | @ website can present a crippling CPU and bandwidt | @ <p>即使是一个适度的项目，Fossil网站的树结构中也可能有数以十亿计的页面。其中许多页面（例 | @ <p>即使是一个适度的项目，Fossil网站的树结构中也可能有数以十亿计的页面。其中许多页面（例 | @ website can present a crippling CPU and bandwidt |
| 87 | @ defend the site against robots. | @ <p>本页面的设置旨在帮助站点管理员保护站点免受机器人的影响。 | @ <p>本页面的设置旨在帮助站点管理员保护站点免受机器人的影响。 | @ defend the site against robots. |
| 93 | @ (property: anon-cookie-lifespan) | @ <p>匿名登录Cookie的有效分钟数。 | @ <p>匿名登录Cookie的有效分钟数。 | @ (property: anon-cookie-lifespan) |
| 102 | @ of the following are true: | @ <p>启用后，Web访问始终需要密码登录。禁用时，当使用 | @ <p>启用后，Web访问始终需要密码登录。禁用时，当使用 | @ of the following are true: |
| 103 | @ in the CGI script. | @ <li> 此按钮被勾选 | @ <li> 此按钮被勾选 | @ in the CGI script. |
| 108 | @ (Property: "remote_user_ok") | @ <p>启用后，如果REMOTE_USER环境变量设置为有效用户的登录名，且没有其他登录凭据可用， | @ <p>启用后，如果REMOTE_USER环境变量设置为有效用户的登录名，且没有其他登录凭据可用， | @ (Property: "remote_user_ok") |
| 110 | @ (Property: "http_authentication_ok") | @ <p>启用后，允许使用HTTP_AUTHENTICATION环境变量或"Authenticati | @ <p>启用后，允许使用HTTP_AUTHENTICATION环境变量或"Authenticati | @ (Property: "http_authentication_ok") |
| 116 | @ for users who are not logged in. (Property: "req | @ <p>对于未登录用户的编辑操作（追加、创建或编辑wiki或工单，或向wiki或工单添加附件）需要 | @ <p>对于未登录用户的编辑操作（追加、创建或编辑wiki或工单，或向wiki或工单添加附件）需要 | @ for users who are not logged in. (Property: "req |
| 118 | @ "Default privileges" setting below. | @ <p>一组逗号分隔的glob模式，指定无需登录即可访问的页面，使用下方 | @ <p>一组逗号分隔的glob模式，指定无需登录即可访问的页面，使用下方 | @ "Default privileges" setting below. |
| 119 | @ (Property: "public-pages") | @ <p>使用示例：将此字段设置为"/doc/trunk/www/*"，并将 | @ <p>使用示例：将此字段设置为"/doc/trunk/www/*"，并将 | @ (Property: "public-pages") |
| 125 | @ (Property: "auth-sub-email")</p> | @ <p>这是一个逗号分隔的GLOB模式列表，指定 | @ <p>这是一个逗号分隔的GLOB模式列表，指定 | @ (Property: "auth-sub-email")</p> |
| 127 | @ (Property: "default-perms") | @ <p>授予以下用户的权限：<ul><li>使用自行注册程序注册的用户（如果启用），或<li>访问 | @ <p>授予以下用户的权限：<ul><li>使用自行注册程序注册的用户（如果启用），或<li>访问 | @ (Property: "default-perms") |
| ... | ... | ... | ... | ... |
| 总计 118 条记录 | | | | |

