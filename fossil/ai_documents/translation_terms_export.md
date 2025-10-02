# Fossil翻译术语表
生成时间: 2025-10-02 11:19:15

## Unknown

| English Term | Chinese Translation | Context |
|--------------|---------------------|---------|
| "      this repository</a></li>\n",(href("%R/urllist"))); | cgi_printf("  <li>%z访问此仓库的URL列表</a></li>\n",(href("%R/urllist"))); | "      this repository</a></li>\n",(href("%R/urllist"))); -> cgi_printf("  <li>%z访问此仓库的URL列表</a></li>\n",(href("%R/urllist"))); |
| "     very wide, respectively.\n" | "<li> 第一个项是显示在菜单上的文本。\n" | "     very wide, respectively.\n" -> "<li> 第一个项是显示在菜单上的文本。\n" |
| "  <li>%zCollisions on hash prefixes</a></li>\n",(href("%R/stat")),(href("%R/hash-collisions"))); | "  <li>%z哈希前缀冲突</a></li>\n",(href("%R/stat")),(href("%R/hash-collisions"))); | "  <li>%zCollisions on hash prefixes</a></li>\n",(href("%R/stat")),(href("%R/hash-collisions"))); -> "  <li>%z哈希前缀冲突</a></li>\n",(href("%R/stat")),(href("%R/hash-collisions"))); |
| "  <li>%zList of Attachments</a></li>\n" | cgi_printf("  <li>%z近期活动</a></li>\n" | "  <li>%zList of Attachments</a></li>\n" -> cgi_printf("  <li>%z近期活动</a></li>\n" |
| "  <li>%zMarkdown Formatting Rules</a></li>\n",(href("%R/wiki_rules")),(href("%R/md_rules"))); | cgi_printf("  <li>%z维基格式规则</a></li>\n" | "  <li>%zMarkdown Formatting Rules</a></li>\n",(href("%R/wiki_rules")),(href("%R/md_rules"))); -> cgi_printf("  <li>%z维基格式规则</a></li>\n" |
| "  <li>%zUnversioned Files</a>\n",(href("%R/tree")),(href("%R/tree?type=tree&ci=trunk")),(href("%R/tree?type=flat")),(href("%R/fileage?name=trunk")),(href("%R/uvlist"))); | "  <li>%z树状视图,\n" | "  <li>%zUnversioned Files</a>\n",(href("%R/tree")),(href("%R/tree?type=tree&ci=trunk")),(href("%R/tree?type=flat")),(href("%R/fileage?name=trunk")),(href("%R/uvlist"))); -> "  <li>%z树状视图,\n" |
| "  <li>%z标签</a></li>\n" | "  <li>%zLeaf Check-ins</a></li>\n" | "  <li>%zLeaf Check-ins</a></li>\n" -> "  <li>%z标签</a></li>\n" |
| "  <li>%z活动报告</a></li>\n" | "  <li>%zOther timelines</a></li>\n" | "  <li>%zOther timelines</a></li>\n" -> "  <li>%z活动报告</a></li>\n" |
| "  <li>%z近期活动</a></li>\n" | "  <li>%zRecent activity</a></li>\n" | "  <li>%zRecent activity</a></li>\n" -> "  <li>%z近期活动</a></li>\n" |
| "  <li><a href=\"%R/modreq\">Pending Moderation Requests</a></li>\n" | "  <li><a href=\"%R/secaudit0\">安全审计</a></li>\n" | "  <li><a href=\"%R/modreq\">Pending Moderation Requests</a></li>\n" -> "  <li><a href=\"%R/secaudit0\">安全审计</a></li>\n" |
| "(Change this on the <a href=\"setup_settings\">settings</a> page.)</div>\n",(fLogEnabled?"on":"off")); | cgi_printf("<div>管理日志功能处于%s状态。\n" | "(Change this on the <a href=\"setup_settings\">settings</a> page.)</div>\n",(fLogEnabled?"on":"off")); -> cgi_printf("<div>管理日志功能处于%s状态。\n" |
| "(Property: \"auth-sub-email\")</p>\n"); | cgi_printf("<p>这是一个逗号分隔的GLOB模式列表，指定\n" | "(Property: \"auth-sub-email\")</p>\n"); -> cgi_printf("<p>这是一个逗号分隔的GLOB模式列表，指定\n" |
| "(Property: \"chat-timeline-user\")</p>\n" | cgi_printf("<p>如果此设置不为空字符串，则时间线上出现的任何更改都会在聊天室中以提供的用户名进行公告。\n" | "(Property: \"chat-timeline-user\")</p>\n" -> cgi_printf("<p>如果此设置不为空字符串，则时间线上出现的任何更改都会在聊天室中以提供的用户名进行公告。\n" |
| "(Property: \"email-admin\")</p>\n" | cgi_printf("<p>这是系统管理员的电子邮件地址。\n" | "(Property: \"email-admin\")</p>\n" -> cgi_printf("<p>这是系统管理员的电子邮件地址。\n" |
| "(Property: \"email-listid\")</p>\n" | "如果此值不为空字符串，则它将成为所有出站通知电子邮件中\"List-ID:\"头的参数。\n" | "(Property: \"email-listid\")</p>\n" -> "如果此值不为空字符串，则它将成为所有出站通知电子邮件中\"List-ID:\"头的参数。\n" |
| "(Property: \"email-renew-interval\")</p>\n" | "如果此值是大于或等于14的整数N，则电子邮件通知订阅\n" | "(Property: \"email-renew-interval\")</p>\n" -> "如果此值是大于或等于14的整数N，则电子邮件通知订阅\n" |
| "(Property: \"email-send-dir\")</p>\n"); | cgi_printf("<p>当发送方法为\"存储在目录中\"时，每条电子邮件消息作为单独的文件存储在此处显示的目录中。\n" | "(Property: \"email-send-dir\")</p>\n"); -> cgi_printf("<p>当发送方法为\"存储在目录中\"时，每条电子邮件消息作为单独的文件存储在此处显示的目录中。\n" |
| "(Property: \"email-send-method\")</p>\n"); | cgi_printf("<p>如何发送电子邮件。需要以下字段提供辅助信息。\n" | "(Property: \"email-send-method\")</p>\n"); -> cgi_printf("<p>如何发送电子邮件。需要以下字段提供辅助信息。\n" |
| "(Property: \"email-send-relayhost\")</p>\n" | cgi_printf("<p>当发送方法为\"SMTP中继\"时，每条电子邮件消息通过SMTP协议（rfc5321）\n" | "(Property: \"email-send-relayhost\")</p>\n" -> cgi_printf("<p>当发送方法为\"SMTP中继\"时，每条电子邮件消息通过SMTP协议（rfc5321）\n" |
| "(Property: \"email-subname\")</p>\n" | cgi_printf("<p><b>必填项。</b>\n" | "(Property: \"email-subname\")</p>\n" -> cgi_printf("<p><b>必填项。</b>\n" |
| "(Property: \"email-url\")</p>\n" | cgi_printf("<p><b>必填项。</b>\n" | "(Property: \"email-url\")</p>\n" -> cgi_printf("<p><b>必填项。</b>\n" |
| "(Property: \"email-url\")</p>\n" | cgi_printf("<p>这是用于作为服务器访问此仓库的URL。\n" | "(Property: \"email-url\")</p>\n" -> cgi_printf("<p>这是用于作为服务器访问此仓库的URL。\n" |
| "(Property: \"project-description\")</p>\n" | cgi_printf("<p>描述您的项目。这将用于搜索引擎的页面标题、\n" | "(Property: \"project-description\")</p>\n" -> cgi_printf("<p>描述您的项目。这将用于搜索引擎的页面标题、\n" |
| "(Property: \"project-name\")\n" | entry_attribute("项目名称", 60, "project-name", "pn", "", 0); | "(Property: \"project-name\")\n" -> entry_attribute("项目名称", 60, "project-name", "pn", "", 0); |
| "(Property: \"remote_user_ok\")\n" | cgi_printf("<p>启用后，如果REMOTE_USER环境变量设置为有效用户的登录名，且没有其他登录凭据可用，\n" | "(Property: \"remote_user_ok\")\n" -> cgi_printf("<p>启用后，如果REMOTE_USER环境变量设置为有效用户的登录名，且没有其他登录凭据可用，\n" |
| "(Property: \"short-project-name\")\n" | cgi_printf("<p>这用作生成的tarball和ZIP归档名称的前缀。为获得最佳效果，\n" | "(Property: \"short-project-name\")\n" -> cgi_printf("<p>这用作生成的tarball和ZIP归档名称的前缀。为获得最佳效果，\n" |
| "(Property: robot-restrict)\n" | "要禁用机器人限制，请将此设置更改为\"off\"。\n" | "(Property: robot-restrict)\n" -> "要禁用机器人限制，请将此设置更改为\"off\"。\n" |
| "(Property: sitemap-extra)\n" | "<p>默认值为空，意味着没有添加的条目。\n" | "(Property: sitemap-extra)\n" -> "<p>默认值为空，意味着没有添加的条目。\n" |
| "(property: anon-cookie-lifespan)\n"); | cgi_printf("<p>匿名登录Cookie的有效分钟数。\n" | "(property: anon-cookie-lifespan)\n"); -> cgi_printf("<p>匿名登录Cookie的有效分钟数。\n" |
| "(property: anon-cookie-lifespan)\n"); | cgi_printf("<p>匿名登录Cookie有效的分钟数。\n" | "(property: anon-cookie-lifespan)\n"); -> cgi_printf("<p>匿名登录Cookie有效的分钟数。\n" |
| "<label for='cbResetMenu'>Reset menu to default value</label>\n" | "<label for='cbResetMenu'>将菜单重置为默认值</label>\n" | "<label for='cbResetMenu'>Reset menu to default value</label>\n" -> "<label for='cbResetMenu'>将菜单重置为默认值</label>\n" |
| "<li> <b>branch/</b><i>分支名称</i>\n" | "<li> <b>ticket/</b><i>full-ticket-hash</i>\n" | "<li> <b>ticket/</b><i>full-ticket-hash</i>\n" -> "<li> <b>branch/</b><i>分支名称</i>\n" |
| "<li>%zBackground color test</a>\n",(href("%R/test-builtin-files")),(href("%R/mimetype_list")),(href("%R/hash-color-test")),(href("%R/test-bgcolor"))); | cgi_printf("<li>%z内置文件列表</a></li>\n" | "<li>%zBackground color test</a>\n",(href("%R/test-builtin-files")),(href("%R/mimetype_list")),(href("%R/hash-color-test")),(href("%R/test-bgcolor"))); -> cgi_printf("<li>%z内置文件列表</a></li>\n" |
| "<li>%zDelta vs. baseline manifests</a></li>\n" | "<li>%z当天</a></li>\n" | "<li>%zDelta vs. baseline manifests</a></li>\n" -> "<li>%z当天</a></li>\n" |
| "<li>%zPie-Chart generator test</a></li>\n",(href("%R/cookies")),(href("%R/test-captcha")),(href("%R/test-piechart"))); | cgi_printf("<li>%z显示首选项Cookie内容</a></li>\n" | "<li>%zPie-Chart generator test</a></li>\n",(href("%R/cookies")),(href("%R/test-captcha")),(href("%R/test-piechart"))); -> cgi_printf("<li>%z显示首选项Cookie内容</a></li>\n" |
| "<li>%zRepository schema</a></li>\n",(href("%R/test-backlinks")),(href("%R/test-backlink-timeline")),(href("%R/phantoms")),(href("%R/test-warning")),(href("%R/repo_stat1")),(href("%R/repo_schema"))); | cgi_printf("<li>%z反向链接列表</a></li>\n" | "<li>%zRepository schema</a></li>\n",(href("%R/test-backlinks")),(href("%R/test-backlink-timeline")),(href("%R/phantoms")),(href("%R/test-warning")),(href("%R/repo_stat1")),(href("%R/repo_schema"))); -> cgi_printf("<li>%z反向链接列表</a></li>\n" |
| "<li>%zTest Pages</a></li>\n",(href("%R/skins")),(href("%R/sitemap-test"))); | cgi_printf("<li>%z皮肤</a></li>\n" | "<li>%zTest Pages</a></li>\n",(href("%R/skins")),(href("%R/sitemap-test"))); -> cgi_printf("<li>%z皮肤</a></li>\n" |
| "<li>Suggested <a href=\"setup_skinedit?w=0\">CSS</a> changes:\n" | "<b>广告单元说明：</b><ul>\n" | "<li>Suggested <a href=\"setup_skinedit?w=0\">CSS</a> changes:\n" -> "<b>广告单元说明：</b><ul>\n" |
| "<p>(Properties: \"background-image\" and \"background-mimetype\")\n" | "<p>（属性：\"background-image\" 和 \"background-mimetype\"）\n" | "<p>(Properties: \"background-image\" and \"background-mimetype\")\n" -> "<p>（属性：\"background-image\" 和 \"background-mimetype\"）\n" |
| "<p>(Properties: \"icon-image\" and \"icon-mimetype\")\n" | "<p>（属性：\"icon-image\" 和 \"icon-mimetype\"）\n" | "<p>(Properties: \"icon-image\" and \"icon-mimetype\")\n" -> "<p>（属性：\"icon-image\" 和 \"icon-mimetype\"）\n" |
| "<p>(Properties: \"logo-image\" and \"logo-mimetype\")\n" | "<input type=\"submit\" name=\"setlogo\" value=\"更改Logo\">\n" | "<p>(Properties: \"logo-image\" and \"logo-mimetype\")\n" -> "<input type=\"submit\" name=\"setlogo\" value=\"更改Logo\">\n" |
| "<p>(Properties: \"timeline-tslink-info\")\n"); | cgi_printf("<p>屏幕最左侧与每个时间线条目关联的时间戳上的超链接，通常指向另一个\n" | "<p>(Properties: \"timeline-tslink-info\")\n"); -> cgi_printf("<p>屏幕最左侧与每个时间线条目关联的时间戳上的超链接，通常指向另一个\n" |
| "<p>The main menu for the web interface\n" | "<p>Web界面的主菜单\n" | "<p>The main menu for the web interface\n" -> "<p>Web界面的主菜单\n" |
| "<td>Search all wiki, HTML, Markdown, and Text files</tr>\n" | "<td>搜索所有wiki、HTML、Markdown和文本文件</tr>\n" | "<td>Search all wiki, HTML, Markdown, and Text files</tr>\n" -> "<td>搜索所有wiki、HTML、Markdown和文本文件</tr>\n" |
| "<th width=\"60%%\">Message</th>\n" | "<th>时间</th>\n" | "<th width=\"60%%\">Message</th>\n" -> "<th>时间</th>\n" |
| "<tr><td class=\"form_label\" id=\"imbase\">Base&nbsp;URL:</td>\n" | "<tr><td class=\"form_label\" id=\"imbase\">基础 URL：</td>\n" | "<tr><td class=\"form_label\" id=\"imbase\">Base&nbsp;URL:</td>\n" -> "<tr><td class=\"form_label\" id=\"imbase\">基础 URL：</td>\n" |
| "<tr><td class=\"form_label\" id=\"imhash\">Hash-path:</td>\n" | "<tr><td class=\"form_label\" id=\"imhash\">哈希路径：</td>\n" | "<tr><td class=\"form_label\" id=\"imhash\">Hash-path:</td>\n" -> "<tr><td class=\"form_label\" id=\"imhash\">哈希路径：</td>\n" |
| "<tr><td class=\"form_label\" id=\"imtag\">标记：</td>\n" | "<tr><td class=\"form_label\" id=\"imtag\">Tag:</td>\n" | "<tr><td class=\"form_label\" id=\"imtag\">Tag:</td>\n" -> "<tr><td class=\"form_label\" id=\"imtag\">标记：</td>\n" |
| "<tr><td class=\"form_label\" id=\"imwiki\">Wiki-path:</td>\n" | "（当目标是 Fossil 时使用\"<tt>/info/</tt>\"）</td></tr>\n" | "<tr><td class=\"form_label\" id=\"imwiki\">Wiki-path:</td>\n" -> "（当目标是 Fossil 时使用\"<tt>/info/</tt>\"）</td></tr>\n" |
| "Filename suffix to MIME type map</a></li>\n",(href("%R/mimetype_list"))); | "文件名后缀到MIME类型映射</a></li>\n",(href("%R/mimetype_list"))); | "Filename suffix to MIME type map</a></li>\n",(href("%R/mimetype_list"))); -> "文件名后缀到MIME类型映射</a></li>\n",(href("%R/mimetype_list"))); |
| "In all other case, the tag should exactly match the page name.\n" | "\"diff\"标签涵盖所有差异比较页面，如/vdiff、/fdiff和\n" | "In all other case, the tag should exactly match the page name.\n" -> "\"diff\"标签涵盖所有差异比较页面，如/vdiff、/fdiff和\n" |
| "Some examples:\n" | textarea_attribute("文档全局列表", 3, 35, "doc-glob", "dg", "", 0); | "Some examples:\n" -> textarea_attribute("文档全局列表", 3, 35, "doc-glob", "dg", "", 0); |
| "The RHS entries must be built-in webpage names.\n" | "只发生单个别名操作。不可能嵌套别名。右侧(RHS)条目必须是内置网页名称。\n" | "The RHS entries must be built-in webpage names.\n" -> "只发生单个别名操作。不可能嵌套别名。右侧(RHS)条目必须是内置网页名称。\n" |
| "The current interwiki tag map is as follows:\n"); | "当前的跨Wiki标签映射如下：\n"); | "The current interwiki tag map is as follows:\n"); -> "当前的跨Wiki标签映射如下：\n"); |
| "The recommended value for this setting is:\n" | "<p><b>不允许机器人访问这些页面。</b><br>\n" | "The recommended value for this setting is:\n" -> "<p><b>不允许机器人访问这些页面。</b><br>\n" |
| "This is by design.\n" | "只有当没有内置网页与传入URL匹配时，才会检查别名表。\n" | "This is by design.\n" -> "只有当没有内置网页与传入URL匹配时，才会检查别名表。\n" |
| "To change the background image, use the following form:</p>\n",(zBgMime),(zBgMtime),(g.zBaseURL),(g.zBaseURL)); | "<p>所有用户都可以通过以下URL访问背景图像：\n" | "To change the background image, use the following form:</p>\n",(zBgMime),(zBgMtime),(g.zBaseURL),(g.zBaseURL)); -> "<p>所有用户都可以通过以下URL访问背景图像：\n" |
| "To change the icon image, use the following form:</p>\n",(zIconMime),(zIconMtime),(g.zBaseURL),(g.zBaseURL)); | "<p>所有用户都可以通过以下URL访问图标图像：\n" | "To change the icon image, use the following form:</p>\n",(zIconMime),(zIconMtime),(g.zBaseURL),(g.zBaseURL)); -> "<p>所有用户都可以通过以下URL访问图标图像：\n" |
| "To change the logo image, use the following form:</p>\n",(zLogoMime),(zLogoMtime),(g.zBaseURL),(g.zBaseURL)); | "<p>所有用户都可以通过以下URL访问Logo：\n" | "To change the logo image, use the following form:</p>\n",(zLogoMime),(zLogoMtime),(g.zBaseURL),(g.zBaseURL)); -> "<p>所有用户都可以通过以下URL访问Logo：\n" |
| "Zulu) instead of in local time.  On this server, local time is currently\n"); | cgi_printf("<p>显示 UTC 时间（有时也称为格林威治标准时间 (GMT) 或\n" | "Zulu) instead of in local time.  On this server, local time is currently\n"); -> cgi_printf("<p>显示 UTC 时间（有时也称为格林威治标准时间 (GMT) 或\n" |
| "\"Default privileges\" setting below.\n" | cgi_printf("<p>一组逗号分隔的glob模式，指定无需登录即可访问的页面，使用下方\n" | "\"Default privileges\" setting below.\n" -> cgi_printf("<p>一组逗号分隔的glob模式，指定无需登录即可访问的页面，使用下方\n" |
| "a \"?\" if QUERY_STRING exists.  (Property: robot-exception)<br>\n"); | "<p>该模式应匹配已删除SCRIPT_NAME前缀的REQUEST_URI，并在QUERY_STRING存在时\n" | "a \"?\" if QUERY_STRING exists.  (Property: robot-exception)<br>\n"); -> "<p>该模式应匹配已删除SCRIPT_NAME前缀的REQUEST_URI，并在QUERY_STRING存在时\n" |
| "alerts/bloop.wav",  "Bloop", | "alerts/plunk.wav",  "叮咚声", | "alerts/bloop.wav",  "Bloop", -> "alerts/plunk.wav",  "叮咚声", |
| "alerts/bloop.wav",  "Bloop", | "alerts/plunk.wav",  "叮咚声", | "alerts/bloop.wav",  "Bloop", -> "alerts/plunk.wav",  "叮咚声", |
| "anonymous users.  (Property: \"auto-captcha\")</p>\n"); | cgi_printf("<p>启用后，匿名用户的登录屏幕上会出现一个按钮，可自动填写验证码密码。\n" | "anonymous users.  (Property: \"auto-captcha\")</p>\n"); -> cgi_printf("<p>启用后，匿名用户的登录屏幕上会出现一个按钮，可自动填写验证码密码。\n" |
| "can handle bounces. (Property: \"email-self\")</p>\n" | cgi_printf("<p><b>必填项。</b>\n" | "can handle bounces. (Property: \"email-self\")</p>\n" -> cgi_printf("<p><b>必填项。</b>\n" |
| "check-in, tag or ticket are treated specially when this feature is enabled.\n" | "根据Wiki页面名称将Wiki页面与分支、标签、工单或签入关联。当此功能启用时，以\"branch/\"、\"checkin/\"、\n" | "check-in, tag or ticket are treated specially when this feature is enabled.\n" -> "根据Wiki页面名称将Wiki页面与分支、标签、工单或签入关联。当此功能启用时，以\"branch/\"、\"checkin/\"、\n" |
| "converted into the corresponding form on the right-hand side (RHS).\n" | "<p>当传入URL的第一个部分与上方左侧(LHS)的\"别名\"完全匹配时，URL将转换为右侧(RHS)的相应形式。\n" | "converted into the corresponding form on the right-hand side (RHS).\n" -> "<p>当传入URL的第一个部分与上方左侧(LHS)的\"别名\"完全匹配时，URL将转换为右侧(RHS)的相应形式。\n" |
| "defend the site against robots.\n" | "<p>本页面的设置旨在帮助站点管理员保护站点免受机器人的影响。\n" | "defend the site against robots.\n" -> "<p>本页面的设置旨在帮助站点管理员保护站点免受机器人的影响。\n" |
| "document in which to allow unsafe HTML:\n" | cgi_printf("<p>允许在<a href=\"%R/md_rules\">Markdown格式</a>文档中生成\"不安全\"HTML（例如：&lt;script&gt;、&lt;form&gt;等）。\n" | "document in which to allow unsafe HTML:\n" -> cgi_printf("<p>允许在<a href=\"%R/md_rules\">Markdown格式</a>文档中生成\"不安全\"HTML（例如：&lt;script&gt;、&lt;form&gt;等）。\n" |
| "empty string and press \"Apply Changes\".\n" | "<p>要从别名表中删除条目，请将其名称或值更改为空字符串，然后按\"应用更改\"。\n" | "empty string and press \"Apply Changes\".\n" -> "<p>要从别名表中删除条目，请将其名称或值更改为空字符串，然后按\"应用更改\"。\n" |
| "for users who are not logged in. (Property: \"require-captcha\")</p>\n"); | cgi_printf("<p>对于未登录用户的编辑操作（追加、创建或编辑wiki或工单，或向wiki或工单添加附件）需要验证码。\n" | "for users who are not logged in. (Property: \"require-captcha\")</p>\n"); -> cgi_printf("<p>对于未登录用户的编辑操作（追加、创建或编辑wiki或工单，或向wiki或工单添加附件）需要验证码。\n" |
| "in the CGI script.\n" | "<li> 此按钮被勾选\n" | "in the CGI script.\n" -> "<li> 此按钮被勾选\n" |
| "in the incoming URL.\n" | "右侧(RHS)的查询参数会添加到传入URL的查询参数集中。\n" | "in the incoming URL.\n" -> "右侧(RHS)的查询参数会添加到传入URL的查询参数集中。\n" |
| "list of query parameters.\n" | "别名表中的右侧(RHS)条目应该以单个\"/\"开头，后跟路径元素，可选地后跟\"?\"和查询参数列表。\n" | "list of query parameters.\n" -> "别名表中的右侧(RHS)条目应该以单个\"/\"开头，后跟路径元素，可选地后跟\"?\"和查询参数列表。\n" |
| "moderation. (Property: \"modreq-tkt\")\n" | cgi_printf("<p>启用后，任何工单变更都需要工单审核员的批准\n" | "moderation. (Property: \"modreq-tkt\")\n" -> cgi_printf("<p>启用后，任何工单变更都需要工单审核员的批准\n" |
| "moderation. (Property: \"modreq-wiki\")\n" | cgi_printf("<p>启用后，任何Wiki变更都需要Wiki审核员的批准\n" | "moderation. (Property: \"modreq-wiki\")\n" -> cgi_printf("<p>启用后，任何Wiki变更都需要Wiki审核员的批准\n" |
| "modify the interwiki tag map.\n" | cgi_printf("<p>访问 <a href=\"./intermap\">%R/intermap</a> 了解详情或修改跨Wiki标签映射。\n" | "modify the interwiki tag map.\n" -> cgi_printf("<p>访问 <a href=\"./intermap\">%R/intermap</a> 了解详情或修改跨Wiki标签映射。\n" |
| "of the following are true:\n" | "<p>在以下任一情况下，始终需要密码：\n" | "of the following are true:\n" -> "<p>在以下任一情况下，始终需要密码：\n" |
| "of the table above and press \"Apply Changes\".\n",(blob_str(&namelist))); | "<p>要添加新别名，请在上面表格的最后一行填写名称和值，然后按\"应用更改\"。\n",(blob_str(&namelist))); | "of the table above and press \"Apply Changes\".\n",(blob_str(&namelist))); -> "<p>要添加新别名，请在上面表格的最后一行填写名称和值，然后按\"应用更改\"。\n",(blob_str(&namelist))); |
| "on this list. (Property: mainmenu)\n" | "<p>一些自定义皮肤可能不使用此属性。是否使用此属性是由皮肤设计师做出的选择。\n" | "on this list. (Property: mainmenu)\n" -> "<p>一些自定义皮肤可能不使用此属性。是否使用此属性是由皮肤设计师做出的选择。\n" |
| "or %.1f%% of the repository.</p>\n",(search_index_type(0)),(zSize),(100.0*(double)nFts/(double)nTotal)); | cgi_printf("<p>当前使用SQLite FTS%d搜索索引。\n" | "or %.1f%% of the repository.</p>\n",(search_index_type(0)),(zSize),(100.0*(double)nFts/(double)nTotal)); -> cgi_printf("<p>当前使用SQLite FTS%d搜索索引。\n" |
| "readded to the repository by subsequent sync operation.</p>\n" | "<p>要回避制品，请在下方输入框中输入制品哈希值（制品内容的\n" | "readded to the repository by subsequent sync operation.</p>\n" -> "<p>要回避制品，请在下方输入框中输入制品哈希值（制品内容的\n" |
| "separated by spaces and/or commas.\n" | entry_attribute("文档分支", 20, "doc-branch", "db", "trunk", 0); | "separated by spaces and/or commas.\n" -> entry_attribute("文档分支", 20, "doc-branch", "db", "trunk", 0); |
| "single \"/\" followed by a single path element.\n" | "左侧(LHS)仅与传入URL的第一个部分进行比较。因此，别名表中的所有左侧条目都应该以单个\"/\"开头，后跟单个路径元素。\n" | "single \"/\" followed by a single path element.\n" -> "左侧(LHS)仅与传入URL的第一个部分进行比较。因此，别名表中的所有左侧条目都应该以单个\"/\"开头，后跟单个路径元素。\n" |
| "specified in the URL.  For example, if you visit the url:</p>\n" | entry_attribute("索引页", 60, "index-page", "idxpg", "/home", 0); | "specified in the URL.  For example, if you visit the url:</p>\n" -> entry_attribute("索引页", 60, "index-page", "idxpg", "/home", 0); |
| "the value on the incoming URL.\n" | "如果相同的查询参数同时出现在传入URL和别名的右侧(RHS)，则右侧(RHS)的查询参数值会覆盖传入URL上的值。\n" | "the value on the incoming URL.\n" -> "如果相同的查询参数同时出现在传入URL和别名的右侧(RHS)，则右侧(RHS)的查询参数值会覆盖传入URL上的值。\n" |
| "the word \"localauth\" appears in the CGI script.\n" | cgi_printf("<p>启用后，Web访问始终需要密码登录。禁用时，当使用\n" | "the word \"localauth\" appears in the CGI script.\n" -> cgi_printf("<p>启用后，Web访问始终需要密码登录。禁用时，当使用\n" |
| "trigram", "Trigram", | "off",     "无", | "trigram", "Trigram", -> "off",     "无", |
| "trigram", "Trigram", | "off",     "无", | "trigram", "Trigram", -> "off",     "无", |
| "triple defines a new entry:\n" | "<p>此设置应为分为三元组的TCL列表。每个三元组定义一个新条目：\n" | "triple defines a new entry:\n" -> "<p>此设置应为分为三元组的TCL列表。每个三元组定义一个新条目：\n" |
| "two, so be patient after pressing the button.</p>\n" | "<p>点击下方的重建按钮来重建仓库。新被回避的制品\n" | "two, so be patient after pressing the button.</p>\n" -> "<p>点击下方的重建按钮来重建仓库。新被回避的制品\n" |
| "values defines a single main menu item:\n" | "<p>此设置应为TCL列表。每组连续的四个值定义一个主菜单项：\n" | "values defines a single main menu item:\n" -> "<p>此设置应为TCL列表。每组连续的四个值定义一个主菜单项：\n" |
| "website can present a crippling CPU and bandwidth load.\n" | cgi_printf("<p>即使是一个适度的项目，Fossil网站的树结构中也可能有数以十亿计的页面。其中许多页面（例如：差异比较和压缩包）\n" | "website can present a crippling CPU and bandwidth load.\n" -> cgi_printf("<p>即使是一个适度的项目，Fossil网站的树结构中也可能有数以十亿计的页面。其中许多页面（例如：差异比较和压缩包）\n" |
| "will appear on the hamburger menu.\n" | "<p>出现在<a href=\"%R/sitemap\">/sitemap</a>页面上的额外链接，\n" | "will appear on the hamburger menu.\n" -> "<p>出现在<a href=\"%R/sitemap\">/sitemap</a>页面上的额外链接，\n" |
| "with appropriate adjustments to \"width:\" and \"height:\".\n" | "<li>如需测试用的占位广告单元，请复制粘贴以下内容，并适当调整\"width:\"和\"height:\"。\n" | "with appropriate adjustments to \"width:\" and \"height:\".\n" -> "<li>如需测试用的占位广告单元，请复制粘贴以下内容，并适当调整\"width:\"和\"height:\"。\n" |
| "影响<a href=\"%R/search\">/search</a>网页的服务器特定设置。\n" | "<a href=\"%R/search\">/search</a> webpage.\n" | "<a href=\"%R/search\">/search</a> webpage.\n" -> "影响<a href=\"%R/search\">/search</a>网页的服务器特定设置。\n" |
| %s hours ahead of UTC.</p>\n | 比 UTC 早 %s 小时。</p>\n | cgi_printf("%s hours ahead of UTC.</p>\n",(zTmDiff)); -> cgi_printf("比 UTC 早 %s 小时。</p>\n",(zTmDiff)); |
| %s hours behind UTC.</p>\n | 比 UTC 晚 %s 小时。</p>\n | cgi_printf("%s hours behind UTC.</p>\n",(zTmDiff)); -> cgi_printf("比 UTC 晚 %s 小时。</p>\n",(zTmDiff)); |
| '&gt;Demo Ad&lt;/div&gt;\n | '&gt;演示广告&lt;/div&gt;\n | "'&gt;Demo Ad&lt;/div&gt;\n" -> "'&gt;演示广告&lt;/div&gt;\n" |
| (Property: \ | (属性: \ | "(Property: \"localauth\")\n" -> "(属性: \"localauth\")\n" |
| (Property: \ | <p>启用后，允许使用HTTP_AUTHENTICATION环境变量或\ | "(Property: \"http_authentication_ok\")\n" -> cgi_printf("<p>启用后，允许使用HTTP_AUTHENTICATION环境变量或\"Authentication:\" HTTP头来查找用户名和\n" |
| (Property: \ | <p>使用示例：将此字段设置为\ | "(Property: \"public-pages\")\n" -> "<p>使用示例：将此字段设置为\"/doc/trunk/www/*\"，并将\n" |
| (Property: \ | <p>授予以下用户的权限：<ul><li>使用自行注册程序注册的用户（如果启用），或<li>访问由上述public-pages glob模式标识的\ | "(Property: \"default-perms\")\n" -> cgi_printf("<p>授予以下用户的权限：<ul><li>使用自行注册程序注册的用户（如果启用），或<li>访问由上述public-pages glob模式标识的\"公开\"\n" |
| (Property: \ | (属性: \ | "(Property: \"wiki-about\")</p>\n" -> "(属性: \"wiki-about\")</p>\n" |
| (Property: \ | <p>新的聊天内容使用\ | "(Property: \"chat-poll-timeout\")</p>\n" -> cgi_printf("<p>新的聊天内容使用\"长轮询\"技术下载。系统向/chat-poll发送HTTP请求，该请求会阻塞等待新内容到达。\n" |
| (off) | 时:分 | "4", "(off)" -> "0", "时:分", |
| (off) | 时:分 | "4", "(off)" -> "0", "时:分", |
| (use \ | （当目标是 Fossil 时使用\ | "(use \"<tt>/wiki?name=</tt>\" when the target is Fossil)</td></tr>\n" -> "（当目标是 Fossil 时使用\"<tt>/wiki?name=</tt>\"）</td></tr>\n" |
| )</p>\n | 格式，那么每当日期更改时，日期将显示在单独的框中\n | "CSS class \"timelineTime\". (Property: \"timeline-date-format\")</p>\n"); -> cgi_printf("<p>如果选择了 \"HH:MM\" 或 \"HH:MM:SS\" 格式，那么每当日期更改时，日期将显示在单独的框中\n" |
| )</p>\n | 技术下载。系统向/chat-poll发送HTTP请求，该请求会阻塞等待新内容到达。\n | "(Property: \"chat-poll-timeout\")</p>\n" -> cgi_printf("<p>新的聊天内容使用\"长轮询\"技术下载。系统向/chat-poll发送HTTP请求，该请求会阻塞等待新内容到达。\n" |
| )\n | HTTP头来查找用户名和\n | "(Property: \"http_authentication_ok\")\n" -> cgi_printf("<p>启用后，允许使用HTTP_AUTHENTICATION环境变量或\"Authentication:\" HTTP头来查找用户名和\n" |
| )\n | ，并将\n | "(Property: \"public-pages\")\n" -> "<p>使用示例：将此字段设置为\"/doc/trunk/www/*\"，并将\n" |
| )\n | \n | "(Property: \"default-perms\")\n" -> cgi_printf("<p>授予以下用户的权限：<ul><li>使用自行注册程序注册的用户（如果启用），或<li>访问由上述public-pages glob模式标识的\"公开\"\n" |
| )\n | 开头，\n | "<p>(Property: \"index-page\")\n" -> "<p>注意：为避免重定向循环或其他问题，此条目必须以\"/\"开头，\n" |
| *  second-level item | *  顶层列表项 | *  second-level item -> *  顶层列表项 |
| . (Property: \ | 或 \ | "CSS class \"timelineTime\". (Property: \"timeline-date-format\")</p>\n"); -> cgi_printf("<p>如果选择了 \"HH:MM\" 或 \"HH:MM:SS\" 格式，那么每当日期更改时，日期将显示在单独的框中\n" |
| /* Do not show intermap editing fields to non-setup users */ | /* 不为非设置用户显示 intermap 编辑字段 */ | /* Do not show intermap editing fields to non-setup users */ -> /* 不为非设置用户显示 intermap 编辑字段 */ |
| /* Do not show intermap editing fields to non-setup users */ | /* 不为非设置用户显示 intermap 编辑字段 */ | /* Do not show intermap editing fields to non-setup users */ -> /* 不为非设置用户显示 intermap 编辑字段 */ |
| 2 | 0 | "2", "All Pages" -> "0", "关闭", |
| 2 | 0 | "2", "All Pages" -> "0", "关闭", |
| 2)  numbered item | *   无序列表项 | 2)  numbered item -> *   无序列表项 |
| 4 | 0 | "4", "(off)" -> "0", "时:分", |
| 4 | 0 | "4", "(off)" -> "0", "时:分", |
| 53ee9c0188ef2df3ed61fecfde97dee3 | a8391a0f10feae2e39627f3868cf25f5 | #define FOSSIL_BUILD_HASH "53ee9c0188ef2df3ed61fecfde97dee3" -> #define FOSSIL_BUILD_HASH "a8391a0f10feae2e39627f3868cf25f5" |
| 53ee9c0188ef2df3ed61fecfde97dee3 | a8391a0f10feae2e39627f3868cf25f5 | #define FOSSIL_BUILD_HASH "53ee9c0188ef2df3ed61fecfde97dee3" -> #define FOSSIL_BUILD_HASH "a8391a0f10feae2e39627f3868cf25f5" |
| <b>Banner Ad-Unit:</b><br>\n | <b>横幅广告单元：</b><br>\n | cgi_printf("<b>Banner Ad-Unit:</b><br>\n"); -> cgi_printf("<b>横幅广告单元：</b><br>\n"); |
| <b>Right-Column Ad-Unit:</b><br>\n | <b>右侧栏广告单元：</b><br>\n | "<b>Right-Column Ad-Unit:</b><br>\n"); -> "<b>右侧栏广告单元：</b><br>\n"); |
| <h1>Status &ensp; <input type=\ | <h1>状态 &ensp; <input type=\ | "<h1>Status &ensp; <input type=\"submit\"  name=\"submit\" value=\"Refresh\"></h1>\n" -> "<h1>状态 &ensp; <input type=\"submit\"  name=\"submit\" value=\"刷新\"></h1>\n" |
| <hr><p>Shunned Artifacts:</p>\n | <hr><p>已被回避的制品：</p>\n | "<hr><p>Shunned Artifacts:</p>\n" -> "<hr><p>已被回避的制品：</p>\n" |
| <i>no artifacts are shunned on this server</i>\n | <i>此服务器上没有被回避的制品</i>\n | cgi_printf("<i>no artifacts are shunned on this server</i>\n"); -> cgi_printf("<i>此服务器上没有被回避的制品</i>\n"); |
| <li> <b>w</b> &rarr; wiki pages\n | <li> <b>b</b> &rarr; 签入文件、嵌入式文档\n | "<li> <b>w</b> &rarr; wiki pages\n" -> "<li> <b>b</b> &rarr; 签入文件、嵌入式文档\n" |
| <li> Base-URL: <tt>%h</tt>\n | <li> 基础 URL: <tt>%h</tt>\n | "<li> Base-URL: <tt>%h</tt>\n",(db_column_text(&q,0)),(db_column_text(&q,1))); -> "<li> 基础 URL: <tt>%h</tt>\n",(db_column_text(&q,0)),(db_column_text(&q,1))); |
| <p>(Property: \ | <p>(属性: \ | cgi_printf("<p>(Property: \"timeline-utc\")\n"); -> cgi_printf("<p>(属性: \"timeline-utc\")\n"); |
| <p>(Property: \ | <p>注意：为避免重定向循环或其他问题，此条目必须以\ | "<p>(Property: \"index-page\")\n" -> "<p>注意：为避免重定向循环或其他问题，此条目必须以\"/\"开头，\n" |
| <td>Search nothing. (Disables document search).</tr>\n | <td>搜索doc/子文件夹中的所有Markdown文件和所有README.txt\n | "<td>Search nothing. (Disables document search).</tr>\n" -> "<td>搜索doc/子文件夹中的所有Markdown文件和所有README.txt\n" |
| <th>Disabled</th>\n | <th>已禁用</th>\n | cgi_printf("<th>Disabled</th>\n"); -> cgi_printf("<th>已禁用</th>\n"); |
| <tr><th>Alias<th>URI That The Alias Maps Into\n | <tr><th>别名<th>别名映射到的URI\n | "<tr><th>Alias<th>URI That The Alias Maps Into\n"); -> "<tr><th>别名<th>别名映射到的URI\n"); |
| >      Definition continues until indentation drops below that of the 2nd line. | > [^标签]: 脚注定义必须从第一列开始。 | >      Definition continues until indentation drops below that of the 2nd line. -> > [^标签]: 脚注定义必须从第一列开始。 |
| >    document title displayed at the top of the Fossil page. | > 字符 **^** 不是标签的一部分，它是语法的一部分。 | >    document title displayed at the top of the Fossil page. -> > 字符 **^** 不是标签的一部分，它是语法的一部分。 |
| > "`language-WORD`" is "pikchr". | > 1. 使用制表符或至少四个空格缩进文本 | > "`language-WORD`" is "pikchr". -> > 1. 使用制表符或至少四个空格缩进文本 |
| > * **\[label\]:&nbsp;URL&nbsp;(Title)** | > * **\[标签\]:&nbsp;URL** | > * **\[label\]:&nbsp;URL&nbsp;(Title)** -> > * **\[标签\]:&nbsp;URL** |
| > 3.  **\[display text\]\(URL 'Title'\)** | > 1.  **\[显示文本\]\(URL\)** | > 3.  **\[display text\]\(URL 'Title'\)** -> > 1.  **\[显示文本\]\(URL\)** |
| > > Double-indented paragraph | > > 双重缩进的段落 | > > Double-indented paragraph -> > > 双重缩进的段落 |
| > End a line with two or more spaces to force a mid-paragraph line break. | > 段落之间用空行分隔。 | > End a line with two or more spaces to force a mid-paragraph line break. -> > 段落之间用空行分隔。 |
| > For blocks of text or code: | > 对于文本或代码块： | > For blocks of text or code: -> > 对于文本或代码块： |
| > Formatted using [Pikchr](https://pikchr.org/home), resulting in: | > 使用 [Pikchr](https://pikchr.org/home) 进行格式化，结果如下： | > Formatted using [Pikchr](https://pikchr.org/home), resulting in: -> > 使用 [Pikchr](https://pikchr.org/home) 进行格式化，结果如下： |
| > Labels are case-insensitive. | ## 脚注 ## | > Labels are case-insensitive. -> ## 脚注 ## |
| > The first row is a header if followed by a horizontal rule or a blank line. | > 如果第一行后面跟着水平线或空行，则第一行是标题。 | > The first row is a header if followed by a horizontal rule or a blank line. -> > 如果第一行后面跟着水平线或空行，则第一行是标题。 |
| > This paragraph is indented | > 这个段落被缩进了 | > This paragraph is indented -> > 这个段落被缩进了 |
| > body cells are left-aligned. | > 在单元格的左侧、两侧或右侧放置 **:** 分别表示左对齐、居中或右对齐文本。默认情况下，标题和主体单元格都是左对齐的。 | > body cells are left-aligned. -> > 在单元格的左侧、两侧或右侧放置 **:** 分别表示左对齐、居中或右对齐文本。默认情况下，标题和主体单元格都是左对齐的。 |
| > but that is purely a presentation matter, controlled by the skin’s CSS. | > 使用标准皮肤，逐字文本以等宽字体呈现，但这纯粹是一个呈现问题，由皮肤的 CSS 控制。 | > but that is purely a presentation matter, controlled by the skin’s CSS. -> > 使用标准皮肤，逐字文本以等宽字体呈现，但这纯粹是一个呈现问题，由皮肤的 CSS 控制。 |
| > hyperlinks that refer to wiki pages and check-in and ticket hashes. | > 在格式 8 中，URL 成为显示文本。这对于指向 wiki 页面、签入和工单哈希的超链接很有用。 | > hyperlinks that refer to wiki pages and check-in and ticket hashes. -> > 在格式 8 中，URL 成为显示文本。这对于指向 wiki 页面、签入和工单哈希的超链接很有用。 |
| > may be split onto the next line with optional indenting. | > 对于链接格式 5、6 和 7（"引用链接"），URL 在文档的其他地方提供，如下所示。链接格式 6 和 7 重用显示文本作为标签。标签不区分大小写。标题可以分割到下一行，并可选择缩进。 | > may be split onto the next line with optional indenting. -> > 对于链接格式 5、6 和 7（"引用链接"），URL 在文档的其他地方提供，如下所示。链接格式 6 和 7 重用显示文本作为标签。标签不区分大小写。标题可以分割到下一行，并可选择缩进。 |
| > respectively, contains at least one blank cell. | > 最左侧或最右侧的 **\|** 仅在第一列或最后一列（分别）包含至少一个空单元格时才需要。 | > respectively, contains at least one blank cell. -> > 最左侧或最右侧的 **\|** 仅在第一列或最后一列（分别）包含至少一个空单元格时才需要。 |
| ></p>\n | >\n | "<input type=\"submit\" name=\"clrbg\" value=\"Revert To Default\"></p>\n" -> "<input type=\"submit\" name=\"setbg\" value=\"更改背景\">\n" |
| ></p>\n | >\n | "<input type=\"submit\" name=\"clricon\" value=\"Revert To Default\"></p>\n" -> "<input type=\"submit\" name=\"seticon\" value=\"更改图标\">\n" |
| >Artifact(s)<br>\n | >制品<br>\n | cgi_printf("<p class=\"noMoreShun\">Artifact(s)<br>\n"); -> cgi_printf("<p class=\"noMoreShun\">制品<br>\n"); |
| >Artifact(s)<br>\n | >制品<br>\n | cgi_printf("<p class=\"noMoreShun\">Artifact(s)<br>\n"); -> cgi_printf("<p class=\"noMoreShun\">制品<br>\n"); |
| >Artifact(s)<br>\n | >制品<br>\n | cgi_printf("<p class=\"shunned\">Artifact(s)<br>\n"); -> cgi_printf("<p class=\"shunned\">制品<br>\n"); |
| @       this repository</a></li> | @   <li>%z(href("%R/urllist"))访问此仓库的URL列表</a></li> | @       this repository</a></li> -> @   <li>%z(href("%R/urllist"))访问此仓库的URL列表</a></li> |
| @      the entry is omitted.  "*" is always true. | @ <li> 第一个项是/sitemap条目的显示名称 | @      the entry is omitted.  "*" is always true. -> @ <li> 第一个项是/sitemap条目的显示名称 |
| @      very wide, respectively. | @ <li> 第一个项是显示在菜单上的文本。 | @      very wide, respectively. -> @ <li> 第一个项是显示在菜单上的文本。 |
| @     <li>%z(href("%R/pikchrshow"))Pikchr Sandbox</a></li> | @     <li>%z(href("%R/wcontent"))维基页面列表</a></li> | @     <li>%z(href("%R/pikchrshow"))Pikchr Sandbox</a></li> -> @     <li>%z(href("%R/wcontent"))维基页面列表</a></li> |
| @     <li>%z(href("%R/wikisrch"))Wiki Search</a></li> | @     <li>%z(href("%R/wikisrch"))维基搜索</a></li> | @     <li>%z(href("%R/wikisrch"))Wiki Search</a></li> -> @     <li>%z(href("%R/wikisrch"))维基搜索</a></li> |
| @   <li>%z(href("%R/attachlist"))List of Attachments</a></li> | @   <li>%z(href("%R/timeline?y=t"))近期活动</a></li> | @   <li>%z(href("%R/attachlist"))List of Attachments</a></li> -> @   <li>%z(href("%R/timeline?y=t"))近期活动</a></li> |
| @   <li>%z(href("%R/bloblist"))List of Artifacts</a></li> | @   <li>%z(href("%R/bloblist"))制品列表</a></li> | @   <li>%z(href("%R/bloblist"))List of Artifacts</a></li> -> @   <li>%z(href("%R/bloblist"))制品列表</a></li> |
| @   <li>%z(href("%R/fileedit"))On-line File Editor</li> | @   <li>%z(href("%R/fileedit"))在线文件编辑器</li> | @   <li>%z(href("%R/fileedit"))On-line File Editor</li> -> @   <li>%z(href("%R/fileedit"))在线文件编辑器</li> |
| @   <li>%z(href("%R/hash-collisions"))Collisions on hash prefixes</a></li> | @   <li>%z(href("%R/hash-collisions"))哈希前缀冲突</a></li> | @   <li>%z(href("%R/hash-collisions"))Collisions on hash prefixes</a></li> -> @   <li>%z(href("%R/hash-collisions"))哈希前缀冲突</a></li> |
| @   <li>%z(href("%R/leaves"))Leaf Check-ins</a></li> | @   <li>%z(href("%R/taglist"))标签</a></li> | @   <li>%z(href("%R/leaves"))Leaf Check-ins</a></li> -> @   <li>%z(href("%R/taglist"))标签</a></li> |
| @   <li>%z(href("%R/md_rules"))Markdown Formatting Rules</a></li> | @   <li>%z(href("%R/wiki_rules"))维基格式规则</a></li> | @   <li>%z(href("%R/md_rules"))Markdown Formatting Rules</a></li> -> @   <li>%z(href("%R/wiki_rules"))维基格式规则</a></li> |
| @   <li>%z(href("%R/sitemap-timeline"))Other timelines</a></li> | @   <li>%z(href("%R/reports"))活动报告</a></li> | @   <li>%z(href("%R/sitemap-timeline"))Other timelines</a></li> -> @   <li>%z(href("%R/reports"))活动报告</a></li> |
| @   <li>%z(href("%R/test-all-help"))All "help" text on a single page</a></li> | @   <li>%z(href("%R/test-all-help"))所有帮助文本（单页显示）</a></li> | @   <li>%z(href("%R/test-all-help"))All "help" text on a single page</a></li> -> @   <li>%z(href("%R/test-all-help"))所有帮助文本（单页显示）</a></li> |
| @   <li>%z(href("%R/timeline?y=f"))Recent activity</a></li> | @   <li>%z(href("%R/timeline?y=f"))近期活动</a></li> | @   <li>%z(href("%R/timeline?y=f"))Recent activity</a></li> -> @   <li>%z(href("%R/timeline?y=f"))近期活动</a></li> |
| @   <li>%z(href("%R/tktsrch"))Ticket Search</a></li> | @   <li>%z(href("%R/tktsrch"))工单搜索</a></li> | @   <li>%z(href("%R/tktsrch"))Ticket Search</a></li> -> @   <li>%z(href("%R/tktsrch"))工单搜索</a></li> |
| @   <li>%z(href("%R/uvlist"))Unversioned Files</a> | @   <li>%z(href("%R/tree?type=tree&ci=trunk"))树状视图, | @   <li>%z(href("%R/uvlist"))Unversioned Files</a> -> @   <li>%z(href("%R/tree?type=tree&ci=trunk"))树状视图, |
| @   <li><a href="%R/modreq">Pending Moderation Requests</a></li> | @   <li><a href="%R/secaudit0">安全审计</a></li> | @   <li><a href="%R/modreq">Pending Moderation Requests</a></li> -> @   <li><a href="%R/secaudit0">安全审计</a></li> |
| @ "Default privileges" setting below. | @ <p>一组逗号分隔的glob模式，指定无需登录即可访问的页面，使用下方 | @ "Default privileges" setting below. -> @ <p>一组逗号分隔的glob模式，指定无需登录即可访问的页面，使用下方 |
| @ (Change this on the <a href="setup_settings">settings</a> page.)</div> | @ <div>管理日志功能处于%s(fLogEnabled?"开启":"关闭")状态。 | @ (Change this on the <a href="setup_settings">settings</a> page.)</div> -> @ <div>管理日志功能处于%s(fLogEnabled?"开启":"关闭")状态。 |
| @ (Property: "auth-sub-email")</p> | @ <p>这是一个逗号分隔的GLOB模式列表，指定 | @ (Property: "auth-sub-email")</p> -> @ <p>这是一个逗号分隔的GLOB模式列表，指定 |
| @ (Property: "chat-timeline-user")</p> | @ <p>如果此设置不为空字符串，则时间线上出现的任何更改都会在聊天室中以提供的用户名进行公告。 | @ (Property: "chat-timeline-user")</p> -> @ <p>如果此设置不为空字符串，则时间线上出现的任何更改都会在聊天室中以提供的用户名进行公告。 |
| @ (Property: "default-perms") | @ <p>授予以下用户的权限：<ul><li>使用自行注册程序注册的用户（如果启用），或<li>访问由上述public-pages glob模式标识的"公开" | @ (Property: "default-perms") -> @ <p>授予以下用户的权限：<ul><li>使用自行注册程序注册的用户（如果启用），或<li>访问由上述public-pages glob模式标识的"公开" |
| @ (Property: "download-tag") | entry_attribute("下载标签", 20, "download-tag", "dlt", "trunk", 0); | @ (Property: "download-tag") -> entry_attribute("下载标签", 20, "download-tag", "dlt", "trunk", 0); |
| @ (Property: "email-admin")</p> | @ <p>这是系统管理员的电子邮件地址。 | @ (Property: "email-admin")</p> -> @ <p>这是系统管理员的电子邮件地址。 |
| @ (Property: "email-listid")</p> | @ 如果此值不为空字符串，则它将成为所有出站通知电子邮件中"List-ID:"头的参数。 | @ (Property: "email-listid")</p> -> @ 如果此值不为空字符串，则它将成为所有出站通知电子邮件中"List-ID:"头的参数。 |
| @ (Property: "email-renew-interval")</p> | @ 如果此值是大于或等于14的整数N，则电子邮件通知订阅 | @ (Property: "email-renew-interval")</p> -> @ 如果此值是大于或等于14的整数N，则电子邮件通知订阅 |
| @ (Property: "email-send-dir")</p> | @ <p>当发送方法为"存储在目录中"时，每条电子邮件消息作为单独的文件存储在此处显示的目录中。 | @ (Property: "email-send-dir")</p> -> @ <p>当发送方法为"存储在目录中"时，每条电子邮件消息作为单独的文件存储在此处显示的目录中。 |
| @ (Property: "email-send-method")</p> | @ <p>如何发送电子邮件。需要以下字段提供辅助信息。 | @ (Property: "email-send-method")</p> -> @ <p>如何发送电子邮件。需要以下字段提供辅助信息。 |
| @ (Property: "email-send-relayhost")</p> | @ <p>当发送方法为"SMTP中继"时，每条电子邮件消息通过SMTP协议（rfc5321） | @ (Property: "email-send-relayhost")</p> -> @ <p>当发送方法为"SMTP中继"时，每条电子邮件消息通过SMTP协议（rfc5321） |
| @ (Property: "email-subname")</p> | @ <p><b>必填项。</b> | @ (Property: "email-subname")</p> -> @ <p><b>必填项。</b> |
| @ (Property: "email-url")</p> | @ <p><b>必填项。</b> | @ (Property: "email-url")</p> -> @ <p><b>必填项。</b> |
| @ (Property: "http_authentication_ok") | @ <p>启用后，允许使用HTTP_AUTHENTICATION环境变量或"Authentication:" HTTP头来查找用户名和 | @ (Property: "http_authentication_ok") -> @ <p>启用后，允许使用HTTP_AUTHENTICATION环境变量或"Authentication:" HTTP头来查找用户名和 |
| @ (Property: "localauth") | @ (属性: "localauth") | @ (Property: "localauth") -> @ (属性: "localauth") |
| @ (Property: "project-description")</p> | @ <p>描述您的项目。这将用于搜索引擎的页面标题、 | @ (Property: "project-description")</p> -> @ <p>描述您的项目。这将用于搜索引擎的页面标题、 |
| @ (Property: "project-name") | entry_attribute("项目名称", 60, "project-name", "pn", "", 0); | @ (Property: "project-name") -> entry_attribute("项目名称", 60, "project-name", "pn", "", 0); |
| @ (Property: "public-pages") | @ <p>使用示例：将此字段设置为"/doc/trunk/www/*"，并将 | @ (Property: "public-pages") -> @ <p>使用示例：将此字段设置为"/doc/trunk/www/*"，并将 |
| @ (Property: "remote_user_ok") | @ <p>启用后，如果REMOTE_USER环境变量设置为有效用户的登录名，且没有其他登录凭据可用， | @ (Property: "remote_user_ok") -> @ <p>启用后，如果REMOTE_USER环境变量设置为有效用户的登录名，且没有其他登录凭据可用， |
| @ (Property: "short-project-name") | @ <p>这用作生成的tarball和ZIP归档名称的前缀。为获得最佳效果， | @ (Property: "short-project-name") -> @ <p>这用作生成的tarball和ZIP归档名称的前缀。为获得最佳效果， |
| @ (Property: robot-restrict) | @ 要禁用机器人限制，请将此设置更改为"off"。 | @ (Property: robot-restrict) -> @ 要禁用机器人限制，请将此设置更改为"off"。 |
| @ (Property: sitemap-extra) | @ <p>默认值为空，意味着没有添加的条目。 | @ (Property: sitemap-extra) -> @ <p>默认值为空，意味着没有添加的条目。 |
| @ (property: anon-cookie-lifespan) | @ <p>匿名登录Cookie的有效分钟数。 | @ (property: anon-cookie-lifespan) -> @ <p>匿名登录Cookie的有效分钟数。 |
| @ (property: anon-cookie-lifespan) | @ <p>匿名登录Cookie有效的分钟数。 | @ (property: anon-cookie-lifespan) -> @ <p>匿名登录Cookie有效的分钟数。 |
| @ <a href="%R/search">/search</a> webpage. | @ 影响<a href="%R/search">/search</a>网页的服务器特定设置。 | @ <a href="%R/search">/search</a> webpage. -> @ 影响<a href="%R/search">/search</a>网页的服务器特定设置。 |
| @ <b>Warning:</b> Not all artifacts | @ <b>警告：</b> 并非所有制品 | @ <b>Warning:</b> Not all artifacts -> @ <b>警告：</b> 并非所有制品 |
| @ <label for='cbResetMenu'>Reset menu to default value</label> | @ <label for='cbResetMenu'>将菜单重置为默认值</label> | @ <label for='cbResetMenu'>Reset menu to default value</label> -> @ <label for='cbResetMenu'>将菜单重置为默认值</label> |
| @ <li> <b>branch/</b><i>分支名称</i> | @ <li> <b>ticket/</b><i>full-ticket-hash</i> | @ <li> <b>ticket/</b><i>full-ticket-hash</i> -> @ <li> <b>branch/</b><i>分支名称</i> |
| @ <li> Hash-path: <i>NULL</i> | @ <li> 哈希路径: <i>空</i> | @ <li> Hash-path: <i>NULL</i> -> @ <li> 哈希路径: <i>空</i> |
| @ <li> Hash-path: <tt>%h(z)</tt> | @ <li> 哈希路径: <tt>%h(z)</tt> | @ <li> Hash-path: <tt>%h(z)</tt> -> @ <li> 哈希路径: <tt>%h(z)</tt> |
| @ <li> Wiki-path: <i>NULL</i> | @ <li> Wiki 路径: <i>空</i> | @ <li> Wiki-path: <i>NULL</i> -> @ <li> Wiki 路径: <i>空</i> |
| @ <li> Wiki-path: <tt>%h(z)</tt> | @ <li> Wiki 路径: <tt>%h(z)</tt> | @ <li> Wiki-path: <tt>%h(z)</tt> -> @ <li> Wiki 路径: <tt>%h(z)</tt> |
| @ <li>%z(href("%R/alerts"))Email Alerts for %h(g.zLogin)</a></li> | @ <li>%z(href("%R/alerts"))邮件提醒 %h(g.zLogin)</a></li> | @ <li>%z(href("%R/alerts"))Email Alerts for %h(g.zLogin)</a></li> -> @ <li>%z(href("%R/alerts"))邮件提醒 %h(g.zLogin)</a></li> |
| @ <li>%z(href("%R/brlist"))Branches</a> | @ <li>%z(href("%R/brlist"))分支</a> | @ <li>%z(href("%R/brlist"))Branches</a> -> @ <li>%z(href("%R/brlist"))分支</a> |
| @ <li>%z(href("%R/chat"))聊天</a></li> | @ <li>%z(href("%R/chat"))Chat</a></li> | @ <li>%z(href("%R/chat"))Chat</a></li> -> @ <li>%z(href("%R/chat"))聊天</a></li> |
| @ <li>%z(href("%R/ckout"))Checkout Status</a></li> | @ <li>%z(href("%R/ckout"))检出状态</a></li> | @ <li>%z(href("%R/ckout"))Checkout Status</a></li> -> @ <li>%z(href("%R/ckout"))检出状态</a></li> |
| @ <li>%z(href("%R/cookies"))Cookie设置</a></li> | @ <li>%z(href("%R/cookies"))Cookies</a></li> | @ <li>%z(href("%R/cookies"))Cookies</a></li> -> @ <li>%z(href("%R/cookies"))Cookie设置</a></li> |
| @ <li>%z(href("%R/help"))帮助</a> | @ <li>%z(href("%R/help"))Help</a> | @ <li>%z(href("%R/help"))Help</a> -> @ <li>%z(href("%R/help"))帮助</a> |
| @ <li>%z(href("%R/home"))Home Page</a> | @ <li>%z(href("%R/home"))首页</a> | @ <li>%z(href("%R/home"))Home Page</a> -> @ <li>%z(href("%R/home"))首页</a> |
| @ <li>%z(href("%R/login"))登录</a> | @ <li>%z(href("%R/login"))Login</a> | @ <li>%z(href("%R/login"))Login</a> -> @ <li>%z(href("%R/login"))登录</a> |
| @ <li>%z(href("%R/logout"))Change Password for %h(g.zLogin)</a></li> | @ <li>%z(href("%R/logout"))修改密码 %h(g.zLogin)</a></li> | @ <li>%z(href("%R/logout"))Change Password for %h(g.zLogin)</a></li> -> @ <li>%z(href("%R/logout"))修改密码 %h(g.zLogin)</a></li> |
| @ <li>%z(href("%R/logout"))Logout from %h(g.zLogin)</a> | @ <li>%z(href("%R/logout"))退出登录 %h(g.zLogin)</a> | @ <li>%z(href("%R/logout"))Logout from %h(g.zLogin)</a> -> @ <li>%z(href("%R/logout"))退出登录 %h(g.zLogin)</a> |
| @ <li>%z(href("%R/register"))Create a new account</a></li> | @ <li>%z(href("%R/register"))创建新账户</a></li> | @ <li>%z(href("%R/register"))Create a new account</a></li> -> @ <li>%z(href("%R/register"))创建新账户</a></li> |
| @ <li>%z(href("%R/repo_schema"))Repository schema</a></li> | @ <li>%z(href("%R/test-backlinks"))反向链接列表</a></li> | @ <li>%z(href("%R/repo_schema"))Repository schema</a></li> -> @ <li>%z(href("%R/test-backlinks"))反向链接列表</a></li> |
| @ <li>%z(href("%R/reportlist"))Tickets/Bug Reports</a> | @ <li>%z(href("%R/reportlist"))工单/缺陷报告</a> | @ <li>%z(href("%R/reportlist"))Tickets/Bug Reports</a> -> @ <li>%z(href("%R/reportlist"))工单/缺陷报告</a> |
| @ <li>%z(href("%R/search"))搜索</a></li> | @ <li>%z(href("%R/search"))Search</a></li> | @ <li>%z(href("%R/search"))Search</a></li> -> @ <li>%z(href("%R/search"))搜索</a></li> |
| @ <li>%z(href("%R/sitemap"))站点地图</a></li> | @ <li>%z(href("%R/sitemap"))Site Map</a></li> | @ <li>%z(href("%R/sitemap"))Site Map</a></li> -> @ <li>%z(href("%R/sitemap"))站点地图</a></li> |
| @ <li>%z(href("%R/sitemap-test"))Test Pages</a></li> | @ <li>%z(href("%R/skins"))皮肤</a></li> | @ <li>%z(href("%R/sitemap-test"))Test Pages</a></li> -> @ <li>%z(href("%R/skins"))皮肤</a></li> |
| @ <li>%z(href("%R/stat"))Repository Status</a> | @ <li>%z(href("%R/stat"))仓库状态</a> | @ <li>%z(href("%R/stat"))Repository Status</a> -> @ <li>%z(href("%R/stat"))仓库状态</a> |
| @ <li>%z(href("%R/subscribe"))Subscribe to Email Alerts</a></li> | @ <li>%z(href("%R/subscribe"))订阅邮件提醒</a></li> | @ <li>%z(href("%R/subscribe"))Subscribe to Email Alerts</a></li> -> @ <li>%z(href("%R/subscribe"))订阅邮件提醒</a></li> |
| @ <li>%z(href("%R/test-bgcolor"))Background color test</a> | @ <li>%z(href("%R/test-builtin-files"))内置文件列表</a></li> | @ <li>%z(href("%R/test-bgcolor"))Background color test</a> -> @ <li>%z(href("%R/test-builtin-files"))内置文件列表</a></li> |
| @ <li>%z(href("%R/test-env"))CGI Environment Test</a></li> | @ <li>%z(href("%R/test-env"))CGI环境测试</a></li> | @ <li>%z(href("%R/test-env"))CGI Environment Test</a></li> -> @ <li>%z(href("%R/test-env"))CGI环境测试</a></li> |
| @ <li>%z(href("%R/test-piechart"))Pie-Chart generator test</a></li> | @ <li>%z(href("%R/cookies"))显示首选项Cookie内容</a></li> | @ <li>%z(href("%R/test-piechart"))Pie-Chart generator test</a></li> -> @ <li>%z(href("%R/cookies"))显示首选项Cookie内容</a></li> |
| @ <li>%z(href("%R/test-rename-list"))List of file renames</a></li> | @ <li>%z(href("%R/test-rename-list"))文件重命名列表</a></li> | @ <li>%z(href("%R/test-rename-list"))List of file renames</a></li> -> @ <li>%z(href("%R/test-rename-list"))文件重命名列表</a></li> |
| @ <li>%z(href("%R/timeline"))Project Timeline</a> | @ <li>%z(href("%R/timeline"))项目时间线</a> | @ <li>%z(href("%R/timeline"))Project Timeline</a> -> @ <li>%z(href("%R/timeline"))项目时间线</a> |
| @ <li>%z(href("%R/timeline?deltabg"))Delta vs. baseline manifests</a></li> | @ <li>%z(href("%R/timeline?ymd"))当天</a></li> | @ <li>%z(href("%R/timeline?deltabg"))Delta vs. baseline manifests</a></li> -> @ <li>%z(href("%R/timeline?ymd"))当天</a></li> |
| @ <li>%z(href("%R/timewarps"))Timeline of timewarps</a></li> | @ <li>%z(href("%R/timewarps"))时间扭曲时间线</a></li> | @ <li>%z(href("%R/timewarps"))Timeline of timewarps</a></li> -> @ <li>%z(href("%R/timewarps"))时间扭曲时间线</a></li> |
| @ <li>%z(href("%R/tree"))File Browser</a> | @ <li>%z(href("%R/tree"))文件浏览器</a> | @ <li>%z(href("%R/tree"))File Browser</a> -> @ <li>%z(href("%R/tree"))文件浏览器</a> |
| @ <li>%z(href("%R/wikihelp"))Wiki</a> | @ <li>%z(href("%R/wikihelp"))维基</a> | @ <li>%z(href("%R/wikihelp"))Wiki</a> -> @ <li>%z(href("%R/wikihelp"))维基</a> |
| @ <li><a href="%R/setup">Administration Pages</a> | @ <li><a href="%R/setup">管理页面</a> | @ <li><a href="%R/setup">Administration Pages</a> -> @ <li><a href="%R/setup">管理页面</a> |
| @ <li>Suggested <a href="setup_skinedit?w=0">CSS</a> changes: | @ <b>广告单元说明：</b><ul> | @ <li>Suggested <a href="setup_skinedit?w=0">CSS</a> changes: -> @ <b>广告单元说明：</b><ul> |
| @ <p>(Properties: "background-image" and "background-mimetype") | @ <p>（属性："background-image" 和 "background-mimetype"） | @ <p>(Properties: "background-image" and "background-mimetype") -> @ <p>（属性："background-image" 和 "background-mimetype"） |
| @ <p>(Properties: "icon-image" and "icon-mimetype") | @ <p>（属性："icon-image" 和 "icon-mimetype"） | @ <p>(Properties: "icon-image" and "icon-mimetype") -> @ <p>（属性："icon-image" 和 "icon-mimetype"） |
| @ <p>(Properties: "logo-image" and "logo-mimetype") | @ <input type="submit" name="setlogo" value="更改Logo"> | @ <p>(Properties: "logo-image" and "logo-mimetype") -> @ <input type="submit" name="setlogo" value="更改Logo"> |
| @ <p><a href="admin_log?n=%d(limit)&x=%d(limit+ofst)">[较旧]</a></p> | @ <p><a href="admin_log?n=%d(limit)&x=%d(limit+ofst)">[Older]</a></p> | @ <p><a href="admin_log?n=%d(limit)&x=%d(limit+ofst)">[Older]</a></p> -> @ <p><a href="admin_log?n=%d(limit)&x=%d(limit+ofst)">[较旧]</a></p> |
| @ <p><a href="admin_log?n=%d(limit)&x=%d(prevx)">[较新]</a></p> | @ <p><a href="admin_log?n=%d(limit)&x=%d(prevx)">[Newer]</a></p> | @ <p><a href="admin_log?n=%d(limit)&x=%d(prevx)">[Newer]</a></p> -> @ <p><a href="admin_log?n=%d(limit)&x=%d(prevx)">[较新]</a></p> |
| @ <p>The main menu for the web interface | @ <p>Web界面的主菜单 | @ <p>The main menu for the web interface -> @ <p>Web界面的主菜单 |
| @ <td>Search all wiki, HTML, Markdown, and Text files</tr> | @ <td>搜索所有wiki、HTML、Markdown和文本文件</tr> | @ <td>Search all wiki, HTML, Markdown, and Text files</tr> -> @ <td>搜索所有wiki、HTML、Markdown和文本文件</tr> |
| @ <th width="60%%">Message</th> | @ <th>时间</th> | @ <th width="60%%">Message</th> -> @ <th>时间</th> |
| @ <tr><td class="form_label" id="imbase">Base&nbsp;URL:</td> | @ <tr><td class="form_label" id="imbase">基础 URL：</td> | @ <tr><td class="form_label" id="imbase">Base&nbsp;URL:</td> -> @ <tr><td class="form_label" id="imbase">基础 URL：</td> |
| @ <tr><td class="form_label" id="imhash">Hash-path:</td> | @ <tr><td class="form_label" id="imhash">哈希路径：</td> | @ <tr><td class="form_label" id="imhash">Hash-path:</td> -> @ <tr><td class="form_label" id="imhash">哈希路径：</td> |
| @ <tr><td class="form_label" id="imtag">Tag:</td> | @ <tr><td class="form_label" id="imtag">标记：</td> | @ <tr><td class="form_label" id="imtag">Tag:</td> -> @ <tr><td class="form_label" id="imtag">标记：</td> |
| @ <tr><td class="form_label" id="imwiki">Wiki-path:</td> | @ （当目标是 Fossil 时使用"<tt>/info/</tt>"）</td></tr> | @ <tr><td class="form_label" id="imwiki">Wiki-path:</td> -> @ （当目标是 Fossil 时使用"<tt>/info/</tt>"）</td></tr> |
| @ All %i(nOk) artifacts are present and | @ 所有 %i(nOk) 个制品存在且 | @ All %i(nOk) artifacts are present and -> @ 所有 %i(nOk) 个制品存在且 |
| @ Background image file: | @ 背景图像文件： | @ Background image file: -> @ 背景图像文件： |
| @ CSS class "timelineTime". (Property: "timeline-date-format")</p> | @ <p>如果选择了 "HH:MM" 或 "HH:MM:SS" 格式，那么每当日期更改时，日期将显示在单独的框中 | @ CSS class "timelineTime". (Property: "timeline-date-format")</p> -> @ <p>如果选择了 "HH:MM" 或 "HH:MM:SS" 格式，那么每当日期更改时，日期将显示在单独的框中 |
| @ Filename suffix to MIME type map</a></li> | @ 文件名后缀到MIME类型映射</a></li> | @ Filename suffix to MIME type map</a></li> -> @ 文件名后缀到MIME类型映射</a></li> |
| @ Icon image file: | @ 图标图像文件： | @ Icon image file: -> @ 图标图像文件： |
| @ In all other case, the tag should exactly match the page name. | @ "diff"标签涵盖所有差异比较页面，如/vdiff、/fdiff和 | @ In all other case, the tag should exactly match the page name. -> @ "diff"标签涵盖所有差异比较页面，如/vdiff、/fdiff和 |
| @ Logo Image file: | @ Logo图像文件： | @ Logo Image file: -> @ Logo图像文件： |
| @ No mappings are currently defined. | @ 当前没有定义映射。 | @ No mappings are currently defined. -> @ 当前没有定义映射。 |
| @ Some examples: | textarea_attribute("文档全局列表", 3, 35, "doc-glob", "dg", "", 0); | @ Some examples: -> textarea_attribute("文档全局列表", 3, 35, "doc-glob", "dg", "", 0); |
| @ The RHS entries must be built-in webpage names. | @ 只发生单个别名操作。不可能嵌套别名。右侧(RHS)条目必须是内置网页名称。 | @ The RHS entries must be built-in webpage names. -> @ 只发生单个别名操作。不可能嵌套别名。右侧(RHS)条目必须是内置网页名称。 |
| @ The artifact is present and | @ 该制品存在且 | @ The artifact is present and -> @ 该制品存在且 |
| @ The current interwiki tag map is as follows: | @ 为每种应允许不安全HTML的文档类型包含相应字母。例如，仅允许在签入文件中使用不安全HTML， | @ The current interwiki tag map is as follows: -> @ 为每种应允许不安全HTML的文档类型包含相应字母。例如，仅允许在签入文件中使用不安全HTML， |
| @ The current mapping is as follows: | @ 当前映射如下： | @ The current mapping is as follows: -> @ 当前映射如下： |
| @ The recommended value for this setting is: | @ <input type="submit"  name="submit" value="应用更改"></p> | @ The recommended value for this setting is: -> @ <input type="submit"  name="submit" value="应用更改"></p> |
| @ This is by design. | @ 只有当没有内置网页与传入URL匹配时，才会检查别名表。 | @ This is by design. -> @ 只有当没有内置网页与传入URL匹配时，才会检查别名表。 |
| @ To change the background image, use the following form:</p> | @ <p>所有用户都可以通过以下URL访问背景图像： | @ To change the background image, use the following form:</p> -> @ <p>所有用户都可以通过以下URL访问背景图像： |
| @ To change the icon image, use the following form:</p> | @ <p>所有用户都可以通过以下URL访问图标图像： | @ To change the icon image, use the following form:</p> -> @ <p>所有用户都可以通过以下URL访问图标图像： |
| @ To change the logo image, use the following form:</p> | @ <p>所有用户都可以通过以下URL访问Logo： | @ To change the logo image, use the following form:</p> -> @ <p>所有用户都可以通过以下URL访问Logo： |
| @ Zulu) instead of in local time.  On this server, local time is currently | @ <p>显示 UTC 时间（有时也称为格林威治标准时间 (GMT) 或 | @ Zulu) instead of in local time.  On this server, local time is currently -> @ <p>显示 UTC 时间（有时也称为格林威治标准时间 (GMT) 或 |
| @ a "?" if QUERY_STRING exists.  (Property: robot-exception)<br> | @ <p>该模式应匹配已删除SCRIPT_NAME前缀的REQUEST_URI，并在QUERY_STRING存在时 | @ a "?" if QUERY_STRING exists.  (Property: robot-exception)<br> -> @ <p>该模式应匹配已删除SCRIPT_NAME前缀的REQUEST_URI，并在QUERY_STRING存在时 |
| @ anonymous users.  (Property: "auto-captcha")</p> | @ <p>启用后，匿名用户的登录屏幕上会出现一个按钮，可自动填写验证码密码。 | @ anonymous users.  (Property: "auto-captcha")</p> -> @ <p>启用后，匿名用户的登录屏幕上会出现一个按钮，可自动填写验证码密码。 |
| @ can handle bounces. (Property: "email-self")</p> | @ <p><b>必填项。</b> | @ can handle bounces. (Property: "email-self")</p> -> @ <p><b>必填项。</b> |
| @ check-in, tag or ticket are treated specially when this feature is enabled. | @ 根据Wiki页面名称将Wiki页面与分支、标签、工单或签入关联。当此功能启用时，以"branch/"、"checkin/"、 | @ check-in, tag or ticket are treated specially when this feature is enabled. -> @ 根据Wiki页面名称将Wiki页面与分支、标签、工单或签入关联。当此功能启用时，以"branch/"、"checkin/"、 |
| @ converted into the corresponding form on the right-hand side (RHS). | @ <p>当传入URL的第一个部分与上方左侧(LHS)的"别名"完全匹配时，URL将转换为右侧(RHS)的相应形式。 | @ converted into the corresponding form on the right-hand side (RHS). -> @ <p>当传入URL的第一个部分与上方左侧(LHS)的"别名"完全匹配时，URL将转换为右侧(RHS)的相应形式。 |
| @ defend the site against robots. | @ <p>本页面的设置旨在帮助站点管理员保护站点免受机器人的影响。 | @ defend the site against robots. -> @ <p>本页面的设置旨在帮助站点管理员保护站点免受机器人的影响。 |
| @ document in which to allow unsafe HTML: | @ <p>允许在<a href="%R/md_rules">Markdown格式</a>文档中生成"不安全"HTML（例如：&lt;script&gt;、&lt;form&gt;等）。 | @ document in which to allow unsafe HTML: -> @ <p>允许在<a href="%R/md_rules">Markdown格式</a>文档中生成"不安全"HTML（例如：&lt;script&gt;、&lt;form&gt;等）。 |
| @ empty string and press "Apply Changes". | @ <p>要从别名表中删除条目，请将其名称或值更改为空字符串，然后按"应用更改"。 | @ empty string and press "Apply Changes". -> @ <p>要从别名表中删除条目，请将其名称或值更改为空字符串，然后按"应用更改"。 |
| @ for users who are not logged in. (Property: "require-captcha")</p> | @ <p>对于未登录用户的编辑操作（追加、创建或编辑wiki或工单，或向wiki或工单添加附件）需要验证码。 | @ for users who are not logged in. (Property: "require-captcha")</p> -> @ <p>对于未登录用户的编辑操作（追加、创建或编辑wiki或工单，或向wiki或工单添加附件）需要验证码。 |
| @ in Git repositories (Property: "timeline-truncate-at-blank")</p> | @ <p>在时间线显示中，签入评论仅显示到 | @ in Git repositories (Property: "timeline-truncate-at-blank")</p> -> @ <p>在时间线显示中，签入评论仅显示到 |
| @ in the CGI script. | @ <li> 此按钮被勾选 | @ in the CGI script. -> @ <li> 此按钮被勾选 |
| @ in the incoming URL. | @ 右侧(RHS)的查询参数会添加到传入URL的查询参数集中。 | @ in the incoming URL. -> @ 右侧(RHS)的查询参数会添加到传入URL的查询参数集中。 |
| @ list of query parameters. | @ 别名表中的右侧(RHS)条目应该以单个"/"开头，后跟路径元素，可选地后跟"?"和查询参数列表。 | @ list of query parameters. -> @ 别名表中的右侧(RHS)条目应该以单个"/"开头，后跟路径元素，可选地后跟"?"和查询参数列表。 |
| @ moderation. (Property: "modreq-tkt") | @ <p>启用后，任何工单变更都需要工单审核员的批准 | @ moderation. (Property: "modreq-tkt") -> @ <p>启用后，任何工单变更都需要工单审核员的批准 |
| @ moderation. (Property: "modreq-wiki") | @ <p>启用后，任何Wiki变更都需要Wiki审核员的批准 | @ moderation. (Property: "modreq-wiki") -> @ <p>启用后，任何Wiki变更都需要Wiki审核员的批准 |
| @ modify the interwiki tag map. | @ <p>访问 <a href="./intermap">%R/intermap</a> 了解详情或修改跨Wiki标签映射。 | @ modify the interwiki tag map. -> @ <p>访问 <a href="./intermap">%R/intermap</a> 了解详情或修改跨Wiki标签映射。 |
| @ of the following are true: | @ <p>启用后，Web访问始终需要密码登录。禁用时，当使用 | @ of the following are true: -> @ <p>启用后，Web访问始终需要密码登录。禁用时，当使用 |
| @ of the table above and press "Apply Changes". | @ <p>要添加新别名，请在上面表格的最后一行填写名称和值，然后按"应用更改"。 | @ of the table above and press "Apply Changes". -> @ <p>要添加新别名，请在上面表格的最后一行填写名称和值，然后按"应用更改"。 |
| @ on this list. (Property: mainmenu) | @ <p>一些自定义皮肤可能不使用此属性。是否使用此属性是由皮肤设计师做出的选择。 | @ on this list. (Property: mainmenu) -> @ <p>一些自定义皮肤可能不使用此属性。是否使用此属性是由皮肤设计师做出的选择。 |
| @ or %.1f(100.0*(double)nFts/(double)nTotal)%% of the repository.</p> | @ <p>当前使用SQLite FTS%d(search_index_type(0))搜索索引。 | @ or %.1f(100.0*(double)nFts/(double)nTotal)%% of the repository.</p> -> @ <p>当前使用SQLite FTS%d(search_index_type(0))搜索索引。 |
| @ parameter.  (Property: "timeline-default-length")</p> | @ <p>在没有用户显示偏好 cookie 设置或显式 n= 查询参数的情况下，时间线上显示的最大行数。 | @ parameter.  (Property: "timeline-default-length")</p> -> @ <p>在没有用户显示偏好 cookie 设置或显式 n= 查询参数的情况下，时间线上显示的最大行数。 |
| @ readded to the repository by subsequent sync operation.</p> | @ <p>要回避制品，请在下方输入框中输入制品哈希值（制品内容的 | @ readded to the repository by subsequent sync operation.</p> -> @ <p>要回避制品，请在下方输入框中输入制品哈希值（制品内容的 |
| @ separated by spaces and/or commas. | entry_attribute("文档分支", 20, "doc-branch", "db", "trunk", 0); | @ separated by spaces and/or commas. -> entry_attribute("文档分支", 20, "doc-branch", "db", "trunk", 0); |
| @ sight - set the "hidden" tag on such artifacts instead.</p> | @ <p>警告：回避功能仅应用于从仓库中移除不适当的内容。 | @ sight - set the "hidden" tag on such artifacts instead.</p> -> @ <p>警告：回避功能仅应用于从仓库中移除不适当的内容。 |
| @ single "/" followed by a single path element. | @ 左侧(LHS)仅与传入URL的第一个部分进行比较。因此，别名表中的所有左侧条目都应该以单个"/"开头，后跟单个路径元素。 | @ single "/" followed by a single path element. -> @ 左侧(LHS)仅与传入URL的第一个部分进行比较。因此，别名表中的所有左侧条目都应该以单个"/"开头，后跟单个路径元素。 |
| @ specified an alternative.  (Property: "timeline-default-style")</p> | @ <p>默认时间线查看样式，适用于用户未指定替代样式的情况。 | @ specified an alternative.  (Property: "timeline-default-style")</p> -> @ <p>默认时间线查看样式，适用于用户未指定替代样式的情况。 |
| @ specified in the URL.  For example, if you visit the url:</p> | entry_attribute("索引页", 60, "index-page", "idxpg", "/home", 0); | @ specified in the URL.  For example, if you visit the url:</p> -> entry_attribute("索引页", 60, "index-page", "idxpg", "/home", 0); |
| @ tag field but leave the "Base URL" field blank.</p> | @ <p>要添加新映射，请填写下面的表单并为标记提供唯一名称。要编辑现有映射，请填写表单并使用现有名称作为标记。要删除现有映射，请填写标记字段，但将"基础 URL"字段留空。</p> | @ tag field but leave the "Base URL" field blank.</p> -> @ <p>要添加新映射，请填写下面的表单并为标记提供唯一名称。要编辑现有映射，请填写表单并使用现有名称作为标记。要删除现有映射，请填写标记字段，但将"基础 URL"字段留空。</p> |
| @ the value on the incoming URL. | @ 如果相同的查询参数同时出现在传入URL和别名的右侧(RHS)，则右侧(RHS)的查询参数值会覆盖传入URL上的值。 | @ the value on the incoming URL. -> @ 如果相同的查询参数同时出现在传入URL和别名的右侧(RHS)，则右侧(RHS)的查询参数值会覆盖传入URL上的值。 |
| @ triple defines a new entry: | @ <p>此设置应为分为三元组的TCL列表。每个三元组定义一个新条目： | @ triple defines a new entry: -> @ <p>此设置应为分为三元组的TCL列表。每个三元组定义一个新条目： |
| @ two, so be patient after pressing the button.</p> | @ <p>点击下方的重建按钮来重建仓库。新被回避的制品 | @ two, so be patient after pressing the button.</p> -> @ <p>点击下方的重建按钮来重建仓库。新被回避的制品 |
| @ values defines a single main menu item: | @ <p>此设置应为TCL列表。每组连续的四个值定义一个主菜单项： | @ values defines a single main menu item: -> @ <p>此设置应为TCL列表。每组连续的四个值定义一个主菜单项： |
| @ website can present a crippling CPU and bandwidth load. | @ <p>即使是一个适度的项目，Fossil网站的树结构中也可能有数以十亿计的页面。其中许多页面（例如：差异比较和压缩包） | @ website can present a crippling CPU and bandwidth load. -> @ <p>即使是一个适度的项目，Fossil网站的树结构中也可能有数以十亿计的页面。其中许多页面（例如：差异比较和压缩包） |
| @ will appear on the hamburger menu. | @ <p>出现在<a href="%R/sitemap">/sitemap</a>页面上的额外链接， | @ will appear on the hamburger menu. -> @ <p>出现在<a href="%R/sitemap">/sitemap</a>页面上的额外链接， |
| @ with appropriate adjustments to "width:" and "height:". | @ <li>如需测试用的占位广告单元，请复制粘贴以下内容，并适当调整"width:"和"height:"。 | @ with appropriate adjustments to "width:" and "height:". -> @ <li>如需测试用的占位广告单元，请复制粘贴以下内容，并适当调整"width:"和"height:"。 |
| Abbreviated<br>\n | 缩写形式<br>\n | cgi_printf("Abbreviated<br>\n"); -> cgi_printf("缩写形式<br>\n"); |
| Accept | 接受 | @ <input type="submit" name="sub" value="Accept"> -> @ <input type="submit" name="sub" value="接受"> |
| All Pages | 关闭 | "2", "All Pages" -> "0", "关闭", |
| All Pages | 关闭 | "2", "All Pages" -> "0", "关闭", |
| Already shunned<br>\n | 已被回避<br>\n | cgi_printf("Already shunned<br>\n"); -> cgi_printf("已被回避<br>\n"); |
| Apply Changes | 应用更改 | @ <p><input type="submit"  name="submit" value="Apply Changes"></p> -> @ <p><input type="submit"  name="submit" value="应用更改"></p> |
| Apply Changes | 应用更改 | @ <td><input type="submit" name="submit" value="Apply Changes"></td></tr> -> @ <td><input type="submit" name="submit" value="应用更改"></td></tr> |
| Apply Changes | 应用更改 | @ <p><input type="submit"  name="submit" value="Apply Changes"></p> -> @ <p><input type="submit"  name="submit" value="应用更改"></p> |
| Apply Changes | 应用更改 | @ <input type="submit"  name="submit" value="Apply Changes"></p> -> @ <input type="submit"  name="submit" value="应用更改"></p> |
| Apply Changes | 应用更改 | @ <p><input type="submit"  name="submit" value="Apply Changes"></p> -> @ <p><input type="submit"  name="submit" value="应用更改"></p> |
| Apply Changes | 应用更改 | @ <p><input type="submit"  name="submit" value="Apply Changes"></p> -> @ <p><input type="submit"  name="submit" value="应用更改"></p> |
| Apply Changes | 应用更改 | @ <br><input type="submit"  name="submit" value="Apply Changes"> -> @ <br><input type="submit"  name="submit" value="应用更改"> |
| Apply Changes | 应用更改 | @ <input type="submit"  name="submit" value="Apply Changes"></p> -> @ <input type="submit"  name="submit" value="应用更改"></p> |
| Apply Changes | 应用更改 | @ <p><input type="submit"  name="submit" value="Apply Changes"></p> -> @ <p><input type="submit"  name="submit" value="应用更改"></p> |
| Apply Changes | 应用更改 | @ <input type="submit"  name="submit" value="Apply Changes"></p> -> @ <input type="submit"  name="submit" value="应用更改"></p> |
| Apply Changes | 应用更改 | @ <input type="submit"  name="submit" value="Apply Changes"></p> -> @ <input type="submit"  name="submit" value="应用更改"></p> |
| Apply Changes | 应用更改 | @ <p><input type="submit"  name="submit" value="Apply Changes"></p> -> @ <p><input type="submit"  name="submit" value="应用更改"></p> |
| Apply Changes | 应用更改 | @ <p><input type="submit"  name="submit" value="Apply Changes"></p> -> @ <p><input type="submit"  name="submit" value="应用更改"></p> |
| Apply Changes | 应用更改 | @ <p><input type="submit"  name="submit" value="Apply Changes"></p> -> @ <p><input type="submit"  name="submit" value="应用更改"></p> |
| Apply Changes | 应用更改 | @ <input type='submit' name='submit' value="Apply Changes"> -> @ <input type='submit' name='submit' value="应用更改"> |
| Bad artifact<br>\n | 无效制品<br>\n | cgi_printf("Bad artifact<br>\n"); -> cgi_printf("无效制品<br>\n"); |
| CSS class \ | <p>如果选择了 \ | "CSS class \"timelineTime\". (Property: \"timeline-date-format\")</p>\n"); -> cgi_printf("<p>如果选择了 \"HH:MM\" 或 \"HH:MM:SS\" 格式，那么每当日期更改时，日期将显示在单独的框中\n" |
| Create A Full-Text Index | 创建全文索引 | @ <p><input type="submit" name="fts1" value="Create A Full-Text Index"> -> @ <p><input type="submit" name="fts1" value="创建全文索引"> |
| Delete Ad-Unit | 应用更改 | @ <input type="submit" name="clear" value="Delete Ad-Unit"> -> @ <input type="submit" name="submit" value="应用更改"> |
| OK</br>\n | 有效</br>\n | cgi_printf("OK</br>\n"); -> cgi_printf("有效</br>\n"); |
| Rebuild | 重建 | @ <input type="submit" name="rebuild" value="Rebuild"> -> @ <input type="submit" name="rebuild" value="重建"> |
| Refresh | 刷新 | @ <h1>Status &ensp; <input type="submit"  name="submit" value="Refresh"></h1> -> @ <h1>状态 &ensp; <input type="submit"  name="submit" value="刷新"></h1> |
| Revert To Default | 更改背景 | @ <input type="submit" name="clrbg" value="Revert To Default"></p> -> @ <input type="submit" name="setbg" value="更改背景"> |
| Revert To Default | 更改图标 | @ <input type="submit" name="clricon" value="Revert To Default"></p> -> @ <input type="submit" name="seticon" value="更改图标"> |
| Review | 回避 | @ <input type="submit" name="review" value="Review"> -> @ <input type="submit" name="add" value="回避"> |
| Unknown<br>\n | 未知<br>\n | cgi_printf("Unknown<br>\n"); -> cgi_printf("未知<br>\n"); |
| a8391a0f10feae2e39627f3868cf25f5 | 8bd77252cbee2716c7066ae6043ea325 | #define FOSSIL_BUILD_HASH "a8391a0f10feae2e39627f3868cf25f5" -> #define FOSSIL_BUILD_HASH "8bd77252cbee2716c7066ae6043ea325" |
| a8391a0f10feae2e39627f3868cf25f5 | 8bd77252cbee2716c7066ae6043ea325 | #define FOSSIL_BUILD_HASH "a8391a0f10feae2e39627f3868cf25f5" -> #define FOSSIL_BUILD_HASH "8bd77252cbee2716c7066ae6043ea325" |
| and looks like this:</p>\n | 编辑项目Logo和背景 | "and looks like this:</p>\n" -> style_header("编辑项目Logo和背景"); |
| and looks like this:</p>\n | <p>当前背景图像的MIME类型为 <b>%h</b>\n | "and looks like this:</p>\n" -> "<p>当前背景图像的MIME类型为 <b>%h</b>\n" |
| and looks like this:</p>\n | <p>当前图标图像的MIME类型为 <b>%h</b>\n | "and looks like this:</p>\n" -> "<p>当前图标图像的MIME类型为 <b>%h</b>\n" |
| are no longer being shunned.</p>\n | 已不再被回避。</p>\n | cgi_printf("are no longer being shunned.</p>\n"); -> cgi_printf("已不再被回避。</p>\n"); |
| baff9ba0a04a3602c4d01406a9fc1df1 | 53ee9c0188ef2df3ed61fecfde97dee3 | #define FOSSIL_BUILD_HASH "baff9ba0a04a3602c4d01406a9fc1df1" -> #define FOSSIL_BUILD_HASH "53ee9c0188ef2df3ed61fecfde97dee3" |
| baff9ba0a04a3602c4d01406a9fc1df1 | 53ee9c0188ef2df3ed61fecfde97dee3 | #define FOSSIL_BUILD_HASH "baff9ba0a04a3602c4d01406a9fc1df1" -> #define FOSSIL_BUILD_HASH "53ee9c0188ef2df3ed61fecfde97dee3" |
| bottom of this page.</p>\n | <p>被回避的制品不会被推送，也不会在拉取时被接受，并且该制品\n | "bottom of this page.</p>\n" -> cgi_printf("<p>被回避的制品不会被推送，也不会在拉取时被接受，并且该制品\n" |
| can be shunned with its hash above.</p>\n | 可以通过上方的哈希值被回避。</p>\n | cgi_printf("can be shunned with its hash above.</p>\n"); -> cgi_printf("可以通过上方的哈希值被回避。</p>\n"); |
| cgi_printf("    <li>%zWiki Search</a></li>\n",(href("%R/wikisrch"))); | cgi_printf("    <li>%z维基搜索</a></li>\n",(href("%R/wikisrch"))); | cgi_printf("    <li>%zWiki Search</a></li>\n",(href("%R/wikisrch"))); -> cgi_printf("    <li>%z维基搜索</a></li>\n",(href("%R/wikisrch"))); |
| cgi_printf("    <li>%z维基页面列表</a></li>\n" | "    <li>%zPikchr Sandbox</a></li>\n" | "    <li>%zPikchr Sandbox</a></li>\n" -> cgi_printf("    <li>%z维基页面列表</a></li>\n" |
| cgi_printf("  <li>%zAll \"help\" text on a single page</a></li>\n",(href("%R/test-all-help"))); | cgi_printf("  <li>%z所有帮助文本（单页显示）</a></li>\n",(href("%R/test-all-help"))); | cgi_printf("  <li>%zAll \"help\" text on a single page</a></li>\n",(href("%R/test-all-help"))); -> cgi_printf("  <li>%z所有帮助文本（单页显示）</a></li>\n",(href("%R/test-all-help"))); |
| cgi_printf("  <li>%zList of Artifacts</a></li>\n" | cgi_printf("  <li>%z制品列表</a></li>\n" | cgi_printf("  <li>%zList of Artifacts</a></li>\n" -> cgi_printf("  <li>%z制品列表</a></li>\n" |
| cgi_printf("  <li>%zOn-line File Editor</li>\n",(href("%R/fileedit"))); | cgi_printf("  <li>%z在线文件编辑器</li>\n",(href("%R/fileedit"))); | cgi_printf("  <li>%zOn-line File Editor</li>\n",(href("%R/fileedit"))); -> cgi_printf("  <li>%z在线文件编辑器</li>\n",(href("%R/fileedit"))); |
| cgi_printf("  <li>%zTicket Search</a></li>\n",(href("%R/tktsrch"))); | cgi_printf("  <li>%z工单搜索</a></li>\n",(href("%R/tktsrch"))); | cgi_printf("  <li>%zTicket Search</a></li>\n",(href("%R/tktsrch"))); -> cgi_printf("  <li>%z工单搜索</a></li>\n",(href("%R/tktsrch"))); |
| cgi_printf("<b>Warning:</b> Not all artifacts\n"); | cgi_printf("<b>警告：</b> 并非所有制品\n"); | cgi_printf("<b>Warning:</b> Not all artifacts\n"); -> cgi_printf("<b>警告：</b> 并非所有制品\n"); |
| cgi_printf("<li> Hash-path: <i>NULL</i>\n"); | cgi_printf("<li> 哈希路径: <i>空</i>\n"); | cgi_printf("<li> Hash-path: <i>NULL</i>\n"); -> cgi_printf("<li> 哈希路径: <i>空</i>\n"); |
| cgi_printf("<li> Hash-path: <tt>%h</tt>\n",(z)); | cgi_printf("<li> 哈希路径: <tt>%h</tt>\n",(z)); | cgi_printf("<li> Hash-path: <tt>%h</tt>\n",(z)); -> cgi_printf("<li> 哈希路径: <tt>%h</tt>\n",(z)); |
| cgi_printf("<li> Wiki-path: <i>NULL</i>\n"); | cgi_printf("<li> Wiki 路径: <i>空</i>\n"); | cgi_printf("<li> Wiki-path: <i>NULL</i>\n"); -> cgi_printf("<li> Wiki 路径: <i>空</i>\n"); |
| cgi_printf("<li> Wiki-path: <tt>%h</tt>\n",(z)); | cgi_printf("<li> Wiki 路径: <tt>%h</tt>\n",(z)); | cgi_printf("<li> Wiki-path: <tt>%h</tt>\n",(z)); -> cgi_printf("<li> Wiki 路径: <tt>%h</tt>\n",(z)); |
| cgi_printf("<li>%zBranches</a>\n" | cgi_printf("<li>%z分支</a>\n" | cgi_printf("<li>%zBranches</a>\n" -> cgi_printf("<li>%z分支</a>\n" |
| cgi_printf("<li>%zCGI Environment Test</a></li>\n",(href("%R/test-env"))); | cgi_printf("<li>%zCGI环境测试</a></li>\n",(href("%R/test-env"))); | cgi_printf("<li>%zCGI Environment Test</a></li>\n",(href("%R/test-env"))); -> cgi_printf("<li>%zCGI环境测试</a></li>\n",(href("%R/test-env"))); |
| cgi_printf("<li>%zChange Password for %h</a></li>\n",(href("%R/logout")),(g.zLogin)); | cgi_printf("<li>%z修改密码 %h</a></li>\n",(href("%R/logout")),(g.zLogin)); | cgi_printf("<li>%zChange Password for %h</a></li>\n",(href("%R/logout")),(g.zLogin)); -> cgi_printf("<li>%z修改密码 %h</a></li>\n",(href("%R/logout")),(g.zLogin)); |
| cgi_printf("<li>%zCheckout Status</a></li>\n",(href("%R/ckout"))); | cgi_printf("<li>%z检出状态</a></li>\n",(href("%R/ckout"))); | cgi_printf("<li>%zCheckout Status</a></li>\n",(href("%R/ckout"))); -> cgi_printf("<li>%z检出状态</a></li>\n",(href("%R/ckout"))); |
| cgi_printf("<li>%zCookie设置</a></li>\n" | cgi_printf("<li>%zCookies</a></li>\n" | cgi_printf("<li>%zCookies</a></li>\n" -> cgi_printf("<li>%zCookie设置</a></li>\n" |
| cgi_printf("<li>%zCreate a new account</a></li>\n",(href("%R/register"))); | cgi_printf("<li>%z创建新账户</a></li>\n",(href("%R/register"))); | cgi_printf("<li>%zCreate a new account</a></li>\n",(href("%R/register"))); -> cgi_printf("<li>%z创建新账户</a></li>\n",(href("%R/register"))); |
| cgi_printf("<li>%zEmail Alerts for %h</a></li>\n",(href("%R/alerts")),(g.zLogin)); | cgi_printf("<li>%z邮件提醒 %h</a></li>\n",(href("%R/alerts")),(g.zLogin)); | cgi_printf("<li>%zEmail Alerts for %h</a></li>\n",(href("%R/alerts")),(g.zLogin)); -> cgi_printf("<li>%z邮件提醒 %h</a></li>\n",(href("%R/alerts")),(g.zLogin)); |
| cgi_printf("<li>%zFile Browser</a>\n" | cgi_printf("<li>%z文件浏览器</a>\n" | cgi_printf("<li>%zFile Browser</a>\n" -> cgi_printf("<li>%z文件浏览器</a>\n" |
| cgi_printf("<li>%zHome Page</a>\n",(href("%R/home"))); | cgi_printf("<li>%z首页</a>\n",(href("%R/home"))); | cgi_printf("<li>%zHome Page</a>\n",(href("%R/home"))); -> cgi_printf("<li>%z首页</a>\n",(href("%R/home"))); |
| cgi_printf("<li>%zList of file renames</a></li>\n",(href("%R/test-rename-list"))); | cgi_printf("<li>%z文件重命名列表</a></li>\n",(href("%R/test-rename-list"))); | cgi_printf("<li>%zList of file renames</a></li>\n",(href("%R/test-rename-list"))); -> cgi_printf("<li>%z文件重命名列表</a></li>\n",(href("%R/test-rename-list"))); |
| cgi_printf("<li>%zLogin</a>\n" | cgi_printf("<li>%z登录</a>\n" | cgi_printf("<li>%zLogin</a>\n" -> cgi_printf("<li>%z登录</a>\n" |
| cgi_printf("<li>%zLogout from %h</a>\n" | cgi_printf("<li>%z退出登录 %h</a>\n" | cgi_printf("<li>%zLogout from %h</a>\n" -> cgi_printf("<li>%z退出登录 %h</a>\n" |
| cgi_printf("<li>%zProject Timeline</a>\n" | cgi_printf("<li>%z项目时间线</a>\n" | cgi_printf("<li>%zProject Timeline</a>\n" -> cgi_printf("<li>%z项目时间线</a>\n" |
| cgi_printf("<li>%zRepository Status</a>\n" | cgi_printf("<li>%z仓库状态</a>\n" | cgi_printf("<li>%zRepository Status</a>\n" -> cgi_printf("<li>%z仓库状态</a>\n" |
| cgi_printf("<li>%zSearch</a></li>\n",(href("%R/search"))); | cgi_printf("<li>%z搜索</a></li>\n",(href("%R/search"))); | cgi_printf("<li>%zSearch</a></li>\n",(href("%R/search"))); -> cgi_printf("<li>%z搜索</a></li>\n",(href("%R/search"))); |
| cgi_printf("<li>%zSite Map</a></li>\n",(href("%R/sitemap"))); | cgi_printf("<li>%z站点地图</a></li>\n",(href("%R/sitemap"))); | cgi_printf("<li>%zSite Map</a></li>\n",(href("%R/sitemap"))); -> cgi_printf("<li>%z站点地图</a></li>\n",(href("%R/sitemap"))); |
| cgi_printf("<li>%zSubscribe to Email Alerts</a></li>\n",(href("%R/subscribe"))); | cgi_printf("<li>%z订阅邮件提醒</a></li>\n",(href("%R/subscribe"))); | cgi_printf("<li>%zSubscribe to Email Alerts</a></li>\n",(href("%R/subscribe"))); -> cgi_printf("<li>%z订阅邮件提醒</a></li>\n",(href("%R/subscribe"))); |
| cgi_printf("<li>%zTickets/Bug Reports</a>\n" | cgi_printf("<li>%z工单/缺陷报告</a>\n" | cgi_printf("<li>%zTickets/Bug Reports</a>\n" -> cgi_printf("<li>%z工单/缺陷报告</a>\n" |
| cgi_printf("<li>%zTimeline of timewarps</a></li>\n",(href("%R/timewarps"))); | cgi_printf("<li>%z时间扭曲时间线</a></li>\n",(href("%R/timewarps"))); | cgi_printf("<li>%zTimeline of timewarps</a></li>\n",(href("%R/timewarps"))); -> cgi_printf("<li>%z时间扭曲时间线</a></li>\n",(href("%R/timewarps"))); |
| cgi_printf("<li>%z帮助</a>\n" | cgi_printf("<li>%zHelp</a>\n" | cgi_printf("<li>%zHelp</a>\n" -> cgi_printf("<li>%z帮助</a>\n" |
| cgi_printf("<li>%z维基</a>\n" | cgi_printf("<li>%zWiki</a>\n" | cgi_printf("<li>%zWiki</a>\n" -> cgi_printf("<li>%z维基</a>\n" |
| cgi_printf("<li>%z聊天</a></li>\n",(href("%R/chat"))); | cgi_printf("<li>%zChat</a></li>\n",(href("%R/chat"))); | cgi_printf("<li>%zChat</a></li>\n",(href("%R/chat"))); -> cgi_printf("<li>%z聊天</a></li>\n",(href("%R/chat"))); |
| cgi_printf("<li><a href=\"%R/setup\">Administration Pages</a>\n" | cgi_printf("<li><a href=\"%R/setup\">管理页面</a>\n" | cgi_printf("<li><a href=\"%R/setup\">Administration Pages</a>\n" -> cgi_printf("<li><a href=\"%R/setup\">管理页面</a>\n" |
| cgi_printf("<p><a href=\"admin_log?n=%d&x=%d\">[较新]</a></p>\n",(limit),(prevx)); | cgi_printf("<p><a href=\"admin_log?n=%d&x=%d\">[Newer]</a></p>\n",(limit),(prevx)); | cgi_printf("<p><a href=\"admin_log?n=%d&x=%d\">[Newer]</a></p>\n",(limit),(prevx)); -> cgi_printf("<p><a href=\"admin_log?n=%d&x=%d\">[较新]</a></p>\n",(limit),(prevx)); |
| cgi_printf("<p><a href=\"admin_log?n=%d&x=%d\">[较旧]</a></p>\n",(limit),(limit+ofst)); | cgi_printf("<p><a href=\"admin_log?n=%d&x=%d\">[Older]</a></p>\n",(limit),(limit+ofst)); | cgi_printf("<p><a href=\"admin_log?n=%d&x=%d\">[Older]</a></p>\n",(limit),(limit+ofst)); -> cgi_printf("<p><a href=\"admin_log?n=%d&x=%d\">[较旧]</a></p>\n",(limit),(limit+ofst)); |
| cgi_printf("All %i artifacts are present and\n",(nOk)); | cgi_printf("所有 %i 个制品存在且\n",(nOk)); | cgi_printf("All %i artifacts are present and\n",(nOk)); -> cgi_printf("所有 %i 个制品存在且\n",(nOk)); |
| cgi_printf("Background image file:\n" | cgi_printf("背景图像文件：\n" | cgi_printf("Background image file:\n" -> cgi_printf("背景图像文件：\n" |
| cgi_printf("Icon image file:\n" | cgi_printf("图标图像文件：\n" | cgi_printf("Icon image file:\n" -> cgi_printf("图标图像文件：\n" |
| cgi_printf("Logo Image file:\n" | cgi_printf("Logo图像文件：\n" | cgi_printf("Logo Image file:\n" -> cgi_printf("Logo图像文件：\n" |
| cgi_printf("No mappings are currently defined.\n"); | cgi_printf("当前没有定义映射。\n"); | cgi_printf("No mappings are currently defined.\n"); -> cgi_printf("当前没有定义映射。\n"); |
| cgi_printf("The artifact is present and\n"); | cgi_printf("该制品存在且\n"); | cgi_printf("The artifact is present and\n"); -> cgi_printf("该制品存在且\n"); |
| cgi_printf("The current mapping is as follows:\n" | cgi_printf("当前映射如下：\n" | cgi_printf("The current mapping is as follows:\n" -> cgi_printf("当前映射如下：\n" |
| changed on this screen.</p><hr><p>\n | <p>仅显示值与默认值不同的设置。\n | "changed on this screen.</p><hr><p>\n" -> cgi_printf("<p>仅显示值与默认值不同的设置。\n" |
| clear | submit | @ <input type="submit" name="clear" value="Delete Ad-Unit"> -> @ <input type="submit" name="submit" value="应用更改"> |
| clrbg | setbg | @ <input type="submit" name="clrbg" value="Revert To Default"></p> -> @ <input type="submit" name="setbg" value="更改背景"> |
| clricon | seticon | @ <input type="submit" name="clricon" value="Revert To Default"></p> -> @ <input type="submit" name="seticon" value="更改图标"> |
| entry_attribute("Administrator email address", 40, "email-admin", | entry_attribute("管理员电子邮件地址", 40, "email-admin", | entry_attribute("Administrator email address", 40, "email-admin", -> entry_attribute("管理员电子邮件地址", 40, "email-admin", |
| entry_attribute("Administrator email address", 40, "email-admin", | entry_attribute("管理员电子邮件地址", 40, "email-admin", | entry_attribute("Administrator email address", 40, "email-admin", -> entry_attribute("管理员电子邮件地址", 40, "email-admin", |
| entry_attribute("Allow Unsafe HTML In Markdown", 6, | entry_attribute("允许在Markdown中使用不安全HTML", 6, | entry_attribute("Allow Unsafe HTML In Markdown", 6, -> entry_attribute("允许在Markdown中使用不安全HTML", 6, |
| entry_attribute("Allow Unsafe HTML In Markdown", 6, | entry_attribute("允许在Markdown中使用不安全HTML", 6, | entry_attribute("Allow Unsafe HTML In Markdown", 6, -> entry_attribute("允许在Markdown中使用不安全HTML", 6, |
| entry_attribute("Anonymous Login Validity", 11, "anon-cookie-lifespan", | entry_attribute("匿名登录有效期", 11, "anon-cookie-lifespan", | entry_attribute("Anonymous Login Validity", 11, "anon-cookie-lifespan", -> entry_attribute("匿名登录有效期", 11, "anon-cookie-lifespan", |
| entry_attribute("Anonymous Login Validity", 11, "anon-cookie-lifespan", | entry_attribute("匿名登录有效期", 11, "anon-cookie-lifespan", | entry_attribute("Anonymous Login Validity", 11, "anon-cookie-lifespan", -> entry_attribute("匿名登录有效期", 11, "anon-cookie-lifespan", |
| entry_attribute("Anonymous Login Validity", 11, "anon-cookie-lifespan", | entry_attribute("匿名登录有效期", 11, "anon-cookie-lifespan", | entry_attribute("Anonymous Login Validity", 11, "anon-cookie-lifespan", -> entry_attribute("匿名登录有效期", 11, "anon-cookie-lifespan", |
| entry_attribute("Anonymous Login Validity", 11, "anon-cookie-lifespan", | entry_attribute("匿名登录有效期", 11, "anon-cookie-lifespan", | entry_attribute("Anonymous Login Validity", 11, "anon-cookie-lifespan", -> entry_attribute("匿名登录有效期", 11, "anon-cookie-lifespan", |
| entry_attribute("Authorized subscription email addresses", 35, | entry_attribute("授权的订阅电子邮件地址", 35, | entry_attribute("Authorized subscription email addresses", 35, -> entry_attribute("授权的订阅电子邮件地址", 35, |
| entry_attribute("Authorized subscription email addresses", 35, | entry_attribute("授权的订阅电子邮件地址", 35, | entry_attribute("Authorized subscription email addresses", 35, -> entry_attribute("授权的订阅电子邮件地址", 35, |
| entry_attribute("Canonical Server URL", 40, "email-url", | entry_attribute("规范服务器URL", 40, "email-url", | entry_attribute("Canonical Server URL", 40, "email-url", -> entry_attribute("规范服务器URL", 40, "email-url", |
| entry_attribute("Canonical Server URL", 40, "email-url", | entry_attribute("规范服务器URL", 40, "email-url", | entry_attribute("Canonical Server URL", 40, "email-url", -> entry_attribute("规范服务器URL", 40, "email-url", |
| entry_attribute("Canonical Server URL", 40, "email-url", | entry_attribute("规范服务器URL", 40, "email-url", | entry_attribute("Canonical Server URL", 40, "email-url", -> entry_attribute("规范服务器URL", 40, "email-url", |
| entry_attribute("Canonical Server URL", 40, "email-url", | entry_attribute("规范服务器URL", 40, "email-url", | entry_attribute("Canonical Server URL", 40, "email-url", -> entry_attribute("规范服务器URL", 40, "email-url", |
| entry_attribute("Chat Polling Timeout", 10, | entry_attribute("聊天轮询超时时间", 10, | entry_attribute("Chat Polling Timeout", 10, -> entry_attribute("聊天轮询超时时间", 10, |
| entry_attribute("Chat Polling Timeout", 10, | entry_attribute("聊天轮询超时时间", 10, | entry_attribute("Chat Polling Timeout", 10, -> entry_attribute("聊天轮询超时时间", 10, |
| entry_attribute("Chat Timeline Robot Username", 15, | @ <p>新的聊天内容使用"长轮询"技术下载。系统向/chat-poll发送HTTP请求，该请求会阻塞等待新内容到达。 | entry_attribute("Chat Timeline Robot Username", 15, -> @ <p>新的聊天内容使用"长轮询"技术下载。系统向/chat-poll发送HTTP请求，该请求会阻塞等待新内容到达。 |
| entry_attribute("Chat Timeline Robot Username", 15, | entry_attribute("聊天时间线机器人用户名", 15, | entry_attribute("Chat Timeline Robot Username", 15, -> entry_attribute("聊天时间线机器人用户名", 15, |
| entry_attribute("Default Number Of Rows", 6, "timeline-default-length", | entry_attribute("默认行数", 6, "timeline-default-length", | entry_attribute("Default Number Of Rows", 6, "timeline-default-length", -> entry_attribute("默认行数", 6, "timeline-default-length", |
| entry_attribute("Default Number Of Rows", 6, "timeline-default-length", | entry_attribute("默认行数", 6, "timeline-default-length", | entry_attribute("Default Number Of Rows", 6, "timeline-default-length", -> entry_attribute("默认行数", 6, "timeline-default-length", |
| entry_attribute("Default privileges", 10, "default-perms", | entry_attribute("默认权限", 10, "default-perms", | entry_attribute("Default privileges", 10, "default-perms", -> entry_attribute("默认权限", 10, "default-perms", |
| entry_attribute("Default privileges", 10, "default-perms", | entry_attribute("默认权限", 10, "default-perms", | entry_attribute("Default privileges", 10, "default-perms", -> entry_attribute("默认权限", 10, "default-perms", |
| entry_attribute("Download packet limit", 10, "max-download", "mxdwn", | entry_attribute("下载数据包限制", 10, "max-download", "mxdwn", | entry_attribute("Download packet limit", 10, "max-download", "mxdwn", -> entry_attribute("下载数据包限制", 10, "max-download", "mxdwn", |
| entry_attribute("Download packet limit", 10, "max-download", "mxdwn", | entry_attribute("下载数据包限制", 10, "max-download", "mxdwn", | entry_attribute("Download packet limit", 10, "max-download", "mxdwn", -> entry_attribute("下载数据包限制", 10, "max-download", "mxdwn", |
| entry_attribute("Download time limit", 11, "max-download-time", "mxdwnt", | entry_attribute("下载时间限制", 11, "max-download-time", "mxdwnt", | entry_attribute("Download time limit", 11, "max-download-time", "mxdwnt", -> entry_attribute("下载时间限制", 11, "max-download-time", "mxdwnt", |
| entry_attribute("Download time limit", 11, "max-download-time", "mxdwnt", | entry_attribute("下载时间限制", 11, "max-download-time", "mxdwnt", | entry_attribute("Download time limit", 11, "max-download-time", "mxdwnt", -> entry_attribute("下载时间限制", 11, "max-download-time", "mxdwnt", |
| entry_attribute("Initial Chat History Size", 10, | entry_attribute("初始聊天历史记录大小", 10, | entry_attribute("Initial Chat History Size", 10, -> entry_attribute("初始聊天历史记录大小", 10, |
| entry_attribute("Initial Chat History Size", 10, | entry_attribute("初始聊天历史记录大小", 10, | entry_attribute("Initial Chat History Size", 10, -> entry_attribute("初始聊天历史记录大小", 10, |
| entry_attribute("List-ID", 40, "email-listid", | entry_attribute("列表ID", 40, "email-listid", | entry_attribute("List-ID", 40, "email-listid", -> entry_attribute("列表ID", 40, "email-listid", |
| entry_attribute("List-ID", 40, "email-listid", | entry_attribute("列表ID", 40, "email-listid", | entry_attribute("List-ID", 40, "email-listid", -> entry_attribute("列表ID", 40, "email-listid", |
| entry_attribute("Login expiration time", 6, "cookie-expire", "cex", | entry_attribute("登录过期时间", 6, "cookie-expire", "cex", | entry_attribute("Login expiration time", 6, "cookie-expire", "cex", -> entry_attribute("登录过期时间", 6, "cookie-expire", "cex", |
| entry_attribute("Login expiration time", 6, "cookie-expire", "cex", | entry_attribute("登录过期时间", 6, "cookie-expire", "cex", | entry_attribute("Login expiration time", 6, "cookie-expire", "cex", -> entry_attribute("登录过期时间", 6, "cookie-expire", "cex", |
| entry_attribute("Max timeline comment length", 6, | entry_attribute("最大时间线评论长度", 6, | entry_attribute("Max timeline comment length", 6, -> entry_attribute("最大时间线评论长度", 6, |
| entry_attribute("Max timeline comment length", 6, | entry_attribute("最大时间线评论长度", 6, | entry_attribute("Max timeline comment length", 6, -> entry_attribute("最大时间线评论长度", 6, |
| entry_attribute("Maximum Message Age In Days", 10, | entry_attribute("消息最大保留天数", 10, | entry_attribute("Maximum Message Age In Days", 10, -> entry_attribute("消息最大保留天数", 10, |
| entry_attribute("Maximum Message Age In Days", 10, | entry_attribute("消息最大保留天数", 10, | entry_attribute("Maximum Message Age In Days", 10, -> entry_attribute("消息最大保留天数", 10, |
| entry_attribute("Minimum Number Of Historical Messages To Retain", 10, | entry_attribute("保留的历史消息最小数量", 10, | entry_attribute("Minimum Number Of Historical Messages To Retain", 10, -> entry_attribute("保留的历史消息最小数量", 10, |
| entry_attribute("Minimum Number Of Historical Messages To Retain", 10, | entry_attribute("保留的历史消息最小数量", 10, | entry_attribute("Minimum Number Of Historical Messages To Retain", 10, -> entry_attribute("保留的历史消息最小数量", 10, |
| entry_attribute("Pipe Email Text Into This Command", 60, "email-send-command", | @ <p>当发送方法为"存储在数据库中"时，每条电子邮件消息存储在此处指定名称的SQLite数据库文件中。 | entry_attribute("Pipe Email Text Into This Command", 60, "email-send-command", -> @ <p>当发送方法为"存储在数据库中"时，每条电子邮件消息存储在此处指定名称的SQLite数据库文件中。 |
| entry_attribute("Pipe Email Text Into This Command", 60, "email-send-command", | cgi_printf("<p>当发送方法为\"存储在数据库中\"时，每条电子邮件消息存储在此处指定名称的SQLite数据库文件中。\n" | entry_attribute("Pipe Email Text Into This Command", 60, "email-send-command", -> cgi_printf("<p>当发送方法为\"存储在数据库中\"时，每条电子邮件消息存储在此处指定名称的SQLite数据库文件中。\n" |
| entry_attribute("Public pages", 30, "public-pages", | entry_attribute("公开页面", 30, "public-pages", | entry_attribute("Public pages", 30, "public-pages", -> entry_attribute("公开页面", 30, "public-pages", |
| entry_attribute("Public pages", 30, "public-pages", | entry_attribute("公开页面", 30, "public-pages", | entry_attribute("Public pages", 30, "public-pages", -> entry_attribute("公开页面", 30, "public-pages", |
| entry_attribute("Repository Nickname", 16, "email-subname", | entry_attribute("仓库昵称", 16, "email-subname", | entry_attribute("Repository Nickname", 16, "email-subname", -> entry_attribute("仓库昵称", 16, "email-subname", |
| entry_attribute("Repository Nickname", 16, "email-subname", | entry_attribute("仓库昵称", 16, "email-subname", | entry_attribute("Repository Nickname", 16, "email-subname", -> entry_attribute("仓库昵称", 16, "email-subname", |
| entry_attribute("SMTP Relay Host", 60, "email-send-relayhost", | entry_attribute("SMTP中继主机", 60, "email-send-relayhost", | entry_attribute("SMTP Relay Host", 60, "email-send-relayhost", -> entry_attribute("SMTP中继主机", 60, "email-send-relayhost", |
| entry_attribute("SMTP Relay Host", 60, "email-send-relayhost", | entry_attribute("SMTP中继主机", 60, "email-send-relayhost", | entry_attribute("SMTP Relay Host", 60, "email-send-relayhost", -> entry_attribute("SMTP中继主机", 60, "email-send-relayhost", |
| entry_attribute("Server Load Average Limit", 11, "max-loadavg", "mxldavg", | entry_attribute("服务器负载平均限制", 11, "max-loadavg", "mxldavg", | entry_attribute("Server Load Average Limit", 11, "max-loadavg", "mxldavg", -> entry_attribute("服务器负载平均限制", 11, "max-loadavg", "mxldavg", |
| entry_attribute("Server Load Average Limit", 11, "max-loadavg", "mxldavg", | entry_attribute("服务器负载平均限制", 11, "max-loadavg", "mxldavg", | entry_attribute("Server Load Average Limit", 11, "max-loadavg", "mxldavg", -> entry_attribute("服务器负载平均限制", 11, "max-loadavg", "mxldavg", |
| entry_attribute("Server Load Average Limit", 11, "max-loadavg", "mxldavg", | entry_attribute("服务器负载平均限制", 11, "max-loadavg", "mxldavg", | entry_attribute("Server Load Average Limit", 11, "max-loadavg", "mxldavg", -> entry_attribute("服务器负载平均限制", 11, "max-loadavg", "mxldavg", |
| entry_attribute("Server Load Average Limit", 11, "max-loadavg", "mxldavg", | entry_attribute("服务器负载平均限制", 11, "max-loadavg", "mxldavg", | entry_attribute("Server Load Average Limit", 11, "max-loadavg", "mxldavg", -> entry_attribute("服务器负载平均限制", 11, "max-loadavg", "mxldavg", |
| entry_attribute("Store Emails In This Database", 60, "email-send-db", | entry_attribute("在此数据库中存储电子邮件", 60, "email-send-db", | entry_attribute("Store Emails In This Database", 60, "email-send-db", -> entry_attribute("在此数据库中存储电子邮件", 60, "email-send-db", |
| entry_attribute("Store Emails In This Database", 60, "email-send-db", | entry_attribute("在此数据库中存储电子邮件", 60, "email-send-db", | entry_attribute("Store Emails In This Database", 60, "email-send-db", -> entry_attribute("在此数据库中存储电子邮件", 60, "email-send-db", |
| entry_attribute("Store Emails In This Directory", 60, "email-send-dir", | @ <p>当发送方法为"传送到命令"时，这是要运行的命令。 | entry_attribute("Store Emails In This Directory", 60, "email-send-dir", -> @ <p>当发送方法为"传送到命令"时，这是要运行的命令。 |
| entry_attribute("Store Emails In This Directory", 60, "email-send-dir", | cgi_printf("<p>当发送方法为\"传送到命令\"时，这是要运行的命令。\n" | entry_attribute("Store Emails In This Directory", 60, "email-send-dir", -> cgi_printf("<p>当发送方法为\"传送到命令\"时，这是要运行的命令。\n" |
| entry_attribute("Subscription Renewal Interval In Days", 8, | entry_attribute("订阅续订间隔（天）", 8, | entry_attribute("Subscription Renewal Interval In Days", 8, -> entry_attribute("订阅续订间隔（天）", 8, |
| entry_attribute("Subscription Renewal Interval In Days", 8, | entry_attribute("订阅续订间隔（天）", 8, | entry_attribute("Subscription Renewal Interval In Days", 8, -> entry_attribute("订阅续订间隔（天）", 8, |
| entry_attribute("Tarball and ZIP-archive Prefix", 20, "short-project-name", | @ <p>这是用于作为服务器访问此仓库的URL。 | entry_attribute("Tarball and ZIP-archive Prefix", 20, "short-project-name", -> @ <p>这是用于作为服务器访问此仓库的URL。 |
| entry_attribute("Tarball and ZIP-archive Prefix", 20, "short-project-name", | entry_attribute("Tarball和ZIP归档前缀", 20, "short-project-name", | entry_attribute("Tarball and ZIP-archive Prefix", 20, "short-project-name", -> entry_attribute("Tarball和ZIP归档前缀", 20, "short-project-name", |
| entry_attribute("Tooltip close time (milliseconds)", 6, | entry_attribute("工具提示关闭时间 (毫秒)", 6, | entry_attribute("Tooltip close time (milliseconds)", 6, -> entry_attribute("工具提示关闭时间 (毫秒)", 6, |
| entry_attribute("Tooltip close time (milliseconds)", 6, | entry_attribute("工具提示关闭时间 (毫秒)", 6, | entry_attribute("Tooltip close time (milliseconds)", 6, -> entry_attribute("工具提示关闭时间 (毫秒)", 6, |
| entry_attribute("Tooltip dwell time (milliseconds)", 6, | entry_attribute("工具提示停留时间 (毫秒)", 6, | entry_attribute("Tooltip dwell time (milliseconds)", 6, -> entry_attribute("工具提示停留时间 (毫秒)", 6, |
| entry_attribute("Tooltip dwell time (milliseconds)", 6, | entry_attribute("工具提示停留时间 (毫秒)", 6, | entry_attribute("Tooltip dwell time (milliseconds)", 6, -> entry_attribute("工具提示停留时间 (毫秒)", 6, |
| entry_attribute("\"Return-Path\" email address", 20, "email-self", | entry_attribute("\"Return-Path\"电子邮件地址", 20, "email-self", | entry_attribute("\"Return-Path\" email address", 20, "email-self", -> entry_attribute("\"Return-Path\"电子邮件地址", 20, "email-self", |
| entry_attribute("\"Return-Path\" email address", 20, "email-self", | entry_attribute("\"Return-Path\"电子邮件地址", 20, "email-self", | entry_attribute("\"Return-Path\" email address", 20, "email-self", -> entry_attribute("\"Return-Path\"电子邮件地址", 20, "email-self", |
| field blank.</p>\n | 字段留空。</p>\n | "tag field but leave the \"Base URL\" field blank.</p>\n"); -> cgi_printf("<p>要添加新映射，请填写下面的表单并为标记提供唯一名称。要编辑现有映射，请填写表单并使用现有名称作为标记。要删除现有映射，请填写标记字段，但将\"基础 URL\"字段留空。</p>\n"); |
| from <i>Tags</i> to complete Server URLs.\n | Interwiki 映射配置 | "from <i>Tags</i> to complete Server URLs.\n"); -> style_header("Interwiki 映射配置"); |
| from other repositories.</p>\n | 将不再被回避，但它们可能在仓库中不存在。\n | "from other repositories.</p>\n"); -> cgi_printf("将不再被回避，但它们可能在仓库中不存在。\n" |
| index-page | / | @ <p>(Property: "index-page") -> @ <p>注意：为避免重定向循环或其他问题，此条目必须以"/"开头， |
| is rebuilt using the <b>fossil rebuild</b> command-line</p>\n | 已被回避。它们将不再被推送。\n | "is rebuilt using the <b>fossil rebuild</b> command-line</p>\n"); -> cgi_printf("已被回避。它们将不再被推送。\n" |
| larger repositories.</p>\n | <p>SQLite搜索索引已禁用。所有搜索都将进行全文扫描。\n | "larger repositories.</p>\n"); -> cgi_printf("<p>SQLite搜索索引已禁用。所有搜索都将进行全文扫描。\n" |
| like:</p>\n | <p><b>反机器人限制的例外情况</b><br>\n | "like:</p>\n" -> "<p><b>反机器人限制的例外情况</b><br>\n" |
| min-height: <i>height-of-right-column-ad-unit</i>;\n | min-height: <i>右侧栏广告单元高度</i>;\n | "  min-height: <i>height-of-right-column-ad-unit</i>;\n" -> "  min-height: <i>右侧栏广告单元高度</i>;\n" |
| multiple_choice_attribute("Alert sound", | multiple_choice_attribute("提示音", | multiple_choice_attribute("Alert sound", -> multiple_choice_attribute("提示音", |
| multiple_choice_attribute("Alert sound", | multiple_choice_attribute("提示音", | multiple_choice_attribute("Alert sound", -> multiple_choice_attribute("提示音", |
| multiple_choice_attribute("Email Send Method", "email-send-method", "esm", | multiple_choice_attribute("电子邮件发送方法", "email-send-method", "esm", | multiple_choice_attribute("Email Send Method", "email-send-method", "esm", -> multiple_choice_attribute("电子邮件发送方法", "email-send-method", "esm", |
| multiple_choice_attribute("Email Send Method", "email-send-method", "esm", | multiple_choice_attribute("电子邮件发送方法", "email-send-method", "esm", | multiple_choice_attribute("Email Send Method", "email-send-method", "esm", -> multiple_choice_attribute("电子邮件发送方法", "email-send-method", "esm", |
| multiple_choice_attribute("FTS Tokenizer", "search-tokenizer", | multiple_choice_attribute("FTS分词器", "search-tokenizer", | multiple_choice_attribute("FTS Tokenizer", "search-tokenizer", -> multiple_choice_attribute("FTS分词器", "search-tokenizer", |
| multiple_choice_attribute("FTS Tokenizer", "search-tokenizer", | multiple_choice_attribute("FTS分词器", "search-tokenizer", | multiple_choice_attribute("FTS Tokenizer", "search-tokenizer", -> multiple_choice_attribute("FTS分词器", "search-tokenizer", |
| multiple_choice_attribute("Per-Item Time Format", "timeline-date-format", | multiple_choice_attribute("每项时间格式", "timeline-date-format", | multiple_choice_attribute("Per-Item Time Format", "timeline-date-format", -> multiple_choice_attribute("每项时间格式", "timeline-date-format", |
| multiple_choice_attribute("Per-Item Time Format", "timeline-date-format", | multiple_choice_attribute("每项时间格式", "timeline-date-format", | multiple_choice_attribute("Per-Item Time Format", "timeline-date-format", -> multiple_choice_attribute("每项时间格式", "timeline-date-format", |
| multiple_choice_attribute("Redirect to HTTPS", | multiple_choice_attribute("重定向到HTTPS", | multiple_choice_attribute("Redirect to HTTPS", -> multiple_choice_attribute("重定向到HTTPS", |
| multiple_choice_attribute("Redirect to HTTPS", | multiple_choice_attribute("重定向到HTTPS", | multiple_choice_attribute("Redirect to HTTPS", -> multiple_choice_attribute("重定向到HTTPS", |
| multiple_choice_attribute("Style", "timeline-default-style", | multiple_choice_attribute("样式", "timeline-default-style", | multiple_choice_attribute("Style", "timeline-default-style", -> multiple_choice_attribute("样式", "timeline-default-style", |
| multiple_choice_attribute("Style", "timeline-default-style", | multiple_choice_attribute("样式", "timeline-default-style", | multiple_choice_attribute("Style", "timeline-default-style", -> multiple_choice_attribute("样式", "timeline-default-style", |
| onoff_attribute("Allow HTTP_AUTHENTICATION authentication", | onoff_attribute("允许HTTP_AUTHENTICATION认证", | onoff_attribute("Allow HTTP_AUTHENTICATION authentication", -> onoff_attribute("允许HTTP_AUTHENTICATION认证", |
| onoff_attribute("Allow HTTP_AUTHENTICATION authentication", | onoff_attribute("允许HTTP_AUTHENTICATION认证", | onoff_attribute("Allow HTTP_AUTHENTICATION authentication", -> onoff_attribute("允许HTTP_AUTHENTICATION认证", |
| onoff_attribute("Allow REMOTE_USER authentication", | onoff_attribute("允许REMOTE_USER认证", | onoff_attribute("Allow REMOTE_USER authentication", -> onoff_attribute("允许REMOTE_USER认证", |
| onoff_attribute("Allow REMOTE_USER authentication", | onoff_attribute("允许REMOTE_USER认证", | onoff_attribute("Allow REMOTE_USER authentication", -> onoff_attribute("允许REMOTE_USER认证", |
| onoff_attribute("Allow anonymous subscriptions", | onoff_attribute("允许匿名订阅", | onoff_attribute("Allow anonymous subscriptions", -> onoff_attribute("允许匿名订阅", |
| onoff_attribute("Allow anonymous subscriptions", | onoff_attribute("允许匿名订阅", | onoff_attribute("Allow anonymous subscriptions", -> onoff_attribute("允许匿名订阅", |
| onoff_attribute("Allow users to register themselves", | onoff_attribute("允许用户自行注册", | onoff_attribute("Allow users to register themselves", -> onoff_attribute("允许用户自行注册", |
| onoff_attribute("Allow users to register themselves", | onoff_attribute("允许用户自行注册", | onoff_attribute("Allow users to register themselves", -> onoff_attribute("允许用户自行注册", |
| onoff_attribute("Allow users to reset their own passwords", | onoff_attribute("允许用户重置自己的密码", | onoff_attribute("Allow users to reset their own passwords", -> onoff_attribute("允许用户重置自己的密码", |
| onoff_attribute("Allow users to reset their own passwords", | onoff_attribute("允许用户重置自己的密码", | onoff_attribute("Allow users to reset their own passwords", -> onoff_attribute("允许用户重置自己的密码", |
| onoff_attribute("Associate Wiki Pages With Branches, Tags, Tickets, or Checkins", | onoff_attribute("将Wiki页面与分支、标签、工单或签入关联", | onoff_attribute("Associate Wiki Pages With Branches, Tags, Tickets, or Checkins", -> onoff_attribute("将Wiki页面与分支、标签、工单或签入关联", |
| onoff_attribute("Associate Wiki Pages With Branches, Tags, Tickets, or Checkins", | onoff_attribute("将Wiki页面与分支、标签、工单或签入关联", | onoff_attribute("Associate Wiki Pages With Branches, Tags, Tickets, or Checkins", -> onoff_attribute("将Wiki页面与分支、标签、工单或签入关联", |
| onoff_attribute("Break comments at newline characters", | onoff_attribute("在换行符处断开评论", | onoff_attribute("Break comments at newline characters", -> onoff_attribute("在换行符处断开评论", |
| onoff_attribute("Break comments at newline characters", | onoff_attribute("在换行符处断开评论", | onoff_attribute("Break comments at newline characters", -> onoff_attribute("在换行符处断开评论", |
| onoff_attribute("Do not adjust user-selected background colors", | onoff_attribute("不调整用户选择的背景颜色", | onoff_attribute("Do not adjust user-selected background colors", -> onoff_attribute("不调整用户选择的背景颜色", |
| onoff_attribute("Do not adjust user-selected background colors", | onoff_attribute("不调整用户选择的背景颜色", | onoff_attribute("Do not adjust user-selected background colors", -> onoff_attribute("不调整用户选择的背景颜色", |
| onoff_attribute("Email verification required for self-registration", | onoff_attribute("自行注册需要电子邮件验证", | onoff_attribute("Email verification required for self-registration", -> onoff_attribute("自行注册需要电子邮件验证", |
| onoff_attribute("Email verification required for self-registration", | onoff_attribute("自行注册需要电子邮件验证", | onoff_attribute("Email verification required for self-registration", -> onoff_attribute("自行注册需要电子邮件验证", |
| onoff_attribute("Enable /artifact_stats", | onoff_attribute("启用 /artifact_stats", | onoff_attribute("Enable /artifact_stats", -> onoff_attribute("启用 /artifact_stats", |
| onoff_attribute("Enable /artifact_stats", | onoff_attribute("启用 /artifact_stats", | onoff_attribute("Enable /artifact_stats", -> onoff_attribute("启用 /artifact_stats", |
| onoff_attribute("Enable /test-env", | onoff_attribute("启用 /test-env", | onoff_attribute("Enable /test-env", -> onoff_attribute("启用 /test-env", |
| onoff_attribute("Enable /test-env", | onoff_attribute("启用 /test-env", | onoff_attribute("Enable /test-env", -> onoff_attribute("启用 /test-env", |
| onoff_attribute("Moderate ticket changes", | onoff_attribute("审核工单变更", | onoff_attribute("Moderate ticket changes", -> onoff_attribute("审核工单变更", |
| onoff_attribute("Moderate ticket changes", | onoff_attribute("审核工单变更", | onoff_attribute("Moderate ticket changes", -> onoff_attribute("审核工单变更", |
| onoff_attribute("Moderate wiki changes", | onoff_attribute("审核Wiki变更", | onoff_attribute("Moderate wiki changes", -> onoff_attribute("审核Wiki变更", |
| onoff_attribute("Moderate wiki changes", | onoff_attribute("审核Wiki变更", | onoff_attribute("Moderate wiki changes", -> onoff_attribute("审核Wiki变更", |
| onoff_attribute("Omit ads to administrator", | onoff_attribute("向管理员隐藏广告", | onoff_attribute("Omit ads to administrator", -> onoff_attribute("向管理员隐藏广告", |
| onoff_attribute("Omit ads to administrator", | onoff_attribute("向管理员隐藏广告", | onoff_attribute("Omit ads to administrator", -> onoff_attribute("向管理员隐藏广告", |
| onoff_attribute("Omit ads to logged-in users", | onoff_attribute("向已登录用户隐藏广告", | onoff_attribute("Omit ads to logged-in users", -> onoff_attribute("向已登录用户隐藏广告", |
| onoff_attribute("Omit ads to logged-in users", | onoff_attribute("向已登录用户隐藏广告", | onoff_attribute("Omit ads to logged-in users", -> onoff_attribute("向已登录用户隐藏广告", |
| onoff_attribute("Plaintext comments on timelines", | onoff_attribute("时间线上的纯文本评论", | onoff_attribute("Plaintext comments on timelines", -> onoff_attribute("时间线上的纯文本评论", |
| onoff_attribute("Plaintext comments on timelines", | onoff_attribute("时间线上的纯文本评论", | onoff_attribute("Plaintext comments on timelines", -> onoff_attribute("时间线上的纯文本评论", |
| onoff_attribute("Require a CAPTCHA if not logged in", | onoff_attribute("未登录时需要验证码", | onoff_attribute("Require a CAPTCHA if not logged in", -> onoff_attribute("未登录时需要验证码", |
| onoff_attribute("Require a CAPTCHA if not logged in", | onoff_attribute("未登录时需要验证码", | onoff_attribute("Require a CAPTCHA if not logged in", -> onoff_attribute("未登录时需要验证码", |
| onoff_attribute("Require password for local access", | @ <p>当接收到未加密请求时，通过重定向到HTTPS强制使用HTTPS。此功能可以仅对登录页面启用，或对所有页面启用。 | onoff_attribute("Require password for local access", -> @ <p>当接收到未加密请求时，通过重定向到HTTPS强制使用HTTPS。此功能可以仅对登录页面启用，或对所有页面启用。 |
| onoff_attribute("Require password for local access", | onoff_attribute("本地访问需要密码", | onoff_attribute("Require password for local access", -> onoff_attribute("本地访问需要密码", |
| onoff_attribute("Search Built-in Help Text", "search-help", "sh", 0, 0); | onoff_attribute("搜索内置帮助文本", "search-help", "sh", 0, 0); | onoff_attribute("Search Built-in Help Text", "search-help", "sh", 0, 0); -> onoff_attribute("搜索内置帮助文本", "search-help", "sh", 0, 0); |
| onoff_attribute("Search Built-in Help Text", "search-help", "sh", 0, 0); | onoff_attribute("搜索内置帮助文本", "search-help", "sh", 0, 0); | onoff_attribute("Search Built-in Help Text", "search-help", "sh", 0, 0); -> onoff_attribute("搜索内置帮助文本", "search-help", "sh", 0, 0); |
| onoff_attribute("Search Check-in Comments", "search-ci", "sc", 0, 0); | onoff_attribute("搜索签入注释", "search-ci", "sc", 0, 0); | onoff_attribute("Search Check-in Comments", "search-ci", "sc", 0, 0); -> onoff_attribute("搜索签入注释", "search-ci", "sc", 0, 0); |
| onoff_attribute("Search Check-in Comments", "search-ci", "sc", 0, 0); | onoff_attribute("搜索签入注释", "search-ci", "sc", 0, 0); | onoff_attribute("Search Check-in Comments", "search-ci", "sc", 0, 0); -> onoff_attribute("搜索签入注释", "search-ci", "sc", 0, 0); |
| onoff_attribute("Search Documents", "search-doc", "sd", 0, 0); | onoff_attribute("搜索文档", "search-doc", "sd", 0, 0); | onoff_attribute("Search Documents", "search-doc", "sd", 0, 0); -> onoff_attribute("搜索文档", "search-doc", "sd", 0, 0); |
| onoff_attribute("Search Documents", "search-doc", "sd", 0, 0); | onoff_attribute("搜索文档", "search-doc", "sd", 0, 0); | onoff_attribute("Search Documents", "search-doc", "sd", 0, 0); -> onoff_attribute("搜索文档", "search-doc", "sd", 0, 0); |
| onoff_attribute("Search Forum", "search-forum", "sf", 0, 0); | onoff_attribute("搜索论坛", "search-forum", "sf", 0, 0); | onoff_attribute("Search Forum", "search-forum", "sf", 0, 0); -> onoff_attribute("搜索论坛", "search-forum", "sf", 0, 0); |
| onoff_attribute("Search Forum", "search-forum", "sf", 0, 0); | onoff_attribute("搜索论坛", "search-forum", "sf", 0, 0); | onoff_attribute("Search Forum", "search-forum", "sf", 0, 0); -> onoff_attribute("搜索论坛", "search-forum", "sf", 0, 0); |
| onoff_attribute("Search Tech Notes", "search-technote", "se", 0, 0); | onoff_attribute("搜索技术笔记", "search-technote", "se", 0, 0); | onoff_attribute("Search Tech Notes", "search-technote", "se", 0, 0); -> onoff_attribute("搜索技术笔记", "search-technote", "se", 0, 0); |
| onoff_attribute("Search Tech Notes", "search-technote", "se", 0, 0); | onoff_attribute("搜索技术笔记", "search-technote", "se", 0, 0); | onoff_attribute("Search Tech Notes", "search-technote", "se", 0, 0); -> onoff_attribute("搜索技术笔记", "search-technote", "se", 0, 0); |
| onoff_attribute("Search Tickets", "search-tkt", "st", 0, 0); | onoff_attribute("搜索工单", "search-tkt", "st", 0, 0); | onoff_attribute("Search Tickets", "search-tkt", "st", 0, 0); -> onoff_attribute("搜索工单", "search-tkt", "st", 0, 0); |
| onoff_attribute("Search Tickets", "search-tkt", "st", 0, 0); | onoff_attribute("搜索工单", "search-tkt", "st", 0, 0); | onoff_attribute("Search Tickets", "search-tkt", "st", 0, 0); -> onoff_attribute("搜索工单", "search-tkt", "st", 0, 0); |
| onoff_attribute("Search Wiki", "search-wiki", "sw", 0, 0); | onoff_attribute("搜索Wiki", "search-wiki", "sw", 0, 0); | onoff_attribute("Search Wiki", "search-wiki", "sw", 0, 0); -> onoff_attribute("搜索Wiki", "search-wiki", "sw", 0, 0); |
| onoff_attribute("Search Wiki", "search-wiki", "sw", 0, 0); | onoff_attribute("搜索Wiki", "search-wiki", "sw", 0, 0); | onoff_attribute("Search Wiki", "search-wiki", "sw", 0, 0); -> onoff_attribute("搜索Wiki", "search-wiki", "sw", 0, 0); |
| onoff_attribute("Show javascript button to fill in CAPTCHA", | onoff_attribute("显示自动填写验证码的JavaScript按钮", | onoff_attribute("Show javascript button to fill in CAPTCHA", -> onoff_attribute("显示自动填写验证码的JavaScript按钮", |
| onoff_attribute("Show javascript button to fill in CAPTCHA", | onoff_attribute("显示自动填写验证码的JavaScript按钮", | onoff_attribute("Show javascript button to fill in CAPTCHA", -> onoff_attribute("显示自动填写验证码的JavaScript按钮", |
| onoff_attribute("Temporarily disable all ads", | onoff_attribute("临时禁用所有广告", | onoff_attribute("Temporarily disable all ads", -> onoff_attribute("临时禁用所有广告", |
| onoff_attribute("Temporarily disable all ads", | onoff_attribute("临时禁用所有广告", | onoff_attribute("Temporarily disable all ads", -> onoff_attribute("临时禁用所有广告", |
| onoff_attribute("Timestamp hyperlinks to /info", | @ <p><strong>停留时间</strong> 定义了鼠标指针在图表对象上方静止多长时间后才会显示工具提示。<br> | onoff_attribute("Timestamp hyperlinks to /info", -> @ <p><strong>停留时间</strong> 定义了鼠标指针在图表对象上方静止多长时间后才会显示工具提示。<br> |
| onoff_attribute("Timestamp hyperlinks to /info", | onoff_attribute("时间戳超链接到 /info", | onoff_attribute("Timestamp hyperlinks to /info", -> onoff_attribute("时间戳超链接到 /info", |
| onoff_attribute("Truncate comment at first blank line (Git-style)", | onoff_attribute("在第一个空行截断评论 (Git风格)", | onoff_attribute("Truncate comment at first blank line (Git-style)", -> onoff_attribute("在第一个空行截断评论 (Git风格)", |
| onoff_attribute("Truncate comment at first blank line (Git-style)", | onoff_attribute("在第一个空行截断评论 (Git风格)", | onoff_attribute("Truncate comment at first blank line (Git-style)", -> onoff_attribute("在第一个空行截断评论 (Git风格)", |
| onoff_attribute("Use HTML as wiki markup language", | onoff_attribute("使用HTML作为Wiki标记语言", | onoff_attribute("Use HTML as wiki markup language", -> onoff_attribute("使用HTML作为Wiki标记语言", |
| onoff_attribute("Use HTML as wiki markup language", | onoff_attribute("使用HTML作为Wiki标记语言", | onoff_attribute("Use HTML as wiki markup language", -> onoff_attribute("使用HTML作为Wiki标记语言", |
| onoff_attribute("Use Universal Coordinated Time (UTC)", | onoff_attribute("使用协调世界时 (UTC)", | onoff_attribute("Use Universal Coordinated Time (UTC)", -> onoff_attribute("使用协调世界时 (UTC)", |
| onoff_attribute("Use Universal Coordinated Time (UTC)", | onoff_attribute("使用协调世界时 (UTC)", | onoff_attribute("Use Universal Coordinated Time (UTC)", -> onoff_attribute("使用协调世界时 (UTC)", |
| operations.</p>\n | <p>输入先前被回避的制品的UUID，使其重新被仓库接受。\n | "operations.</p>\n" -> "<p>输入先前被回避的制品的UUID，使其重新被仓库接受。\n" |
| or symbolic tags.</p>\n | <p>请注意，您必须输入完整的制品哈希值，而不是缩写\n | "or symbolic tags.</p>\n" -> "<p>请注意，您必须输入完整的制品哈希值，而不是缩写\n" |
| oval "Start" fit; arrow; box "Hello, World!" fit; arrow; oval "Done" fit | oval "开始" fit; arrow; box "你好，世界！" fit; arrow; oval "完成" fit | oval "Start" fit; arrow; box "Hello, World!" fit; arrow; oval "Done" fit -> oval "开始" fit; arrow; box "你好，世界！" fit; arrow; oval "完成" fit |
| oval "Start" fit; arrow; box "Hello, World!" fit; arrow; oval "Done" fit | oval "开始" fit; arrow; box "你好，世界！" fit; arrow; oval "完成" fit | oval "Start" fit; arrow; box "Hello, World!" fit; arrow; oval "Done" fit -> oval "开始" fit; arrow; box "你好，世界！" fit; arrow; oval "完成" fit |
| review | add | @ <input type="submit" name="review" value="Review"> -> @ <input type="submit" name="add" value="回避"> |
| style_header("Access Control Settings"); | style_header("访问控制设置"); | style_header("Access Control Settings"); -> style_header("访问控制设置"); |
| style_header("Access Control Settings"); | style_header("访问控制设置"); | style_header("Access Control Settings"); -> style_header("访问控制设置"); |
| style_header("Chat Configuration"); | style_header("聊天配置"); | style_header("Chat Configuration"); -> style_header("聊天配置"); |
| style_header("Chat Configuration"); | style_header("聊天配置"); | style_header("Chat Configuration"); -> style_header("聊天配置"); |
| style_header("Edit Ad Unit"); | style_header("编辑广告单元"); | style_header("Edit Ad Unit"); -> style_header("编辑广告单元"); |
| style_header("Edit Ad Unit"); | style_header("编辑广告单元"); | style_header("Edit Ad Unit"); -> style_header("编辑广告单元"); |
| style_header("Email Notification Setup"); | style_header("电子邮件通知设置"); | style_header("Email Notification Setup"); -> style_header("电子邮件通知设置"); |
| style_header("Email Notification Setup"); | style_header("电子邮件通知设置"); | style_header("Email Notification Setup"); -> style_header("电子邮件通知设置"); |
| style_header("Moderator For Wiki And Tickets"); | style_header("Wiki和工单审核设置"); | style_header("Moderator For Wiki And Tickets"); -> style_header("Wiki和工单审核设置"); |
| style_header("Moderator For Wiki And Tickets"); | style_header("Wiki和工单审核设置"); | style_header("Moderator For Wiki And Tickets"); -> style_header("Wiki和工单审核设置"); |
| style_header("Robot Defense Settings"); | style_header("机器人防御设置"); | style_header("Robot Defense Settings"); -> style_header("机器人防御设置"); |
| style_header("Robot Defense Settings"); | style_header("机器人防御设置"); | style_header("Robot Defense Settings"); -> style_header("机器人防御设置"); |
| style_header("Search Configuration"); | style_header("搜索配置"); | style_header("Search Configuration"); -> style_header("搜索配置"); |
| style_header("Search Configuration"); | style_header("搜索配置"); | style_header("Search Configuration"); -> style_header("搜索配置"); |
| style_header("Settings"); | style_header("设置"); | style_header("Settings"); -> style_header("设置"); |
| style_header("Settings"); | style_header("设置"); | style_header("Settings"); -> style_header("设置"); |
| style_header("Shunned Artifacts"); | style_header("被回避的制品"); | style_header("Shunned Artifacts"); -> style_header("被回避的制品"); |
| style_header("Shunned Artifacts"); | style_header("被回避的制品"); | style_header("Shunned Artifacts"); -> style_header("被回避的制品"); |
| style_header("Site Map"); | style_header("站点地图"); | style_header("Site Map"); -> style_header("站点地图"); |
| style_header("Site Map"); | style_header("站点地图"); | style_header("Site Map"); -> style_header("站点地图"); |
| style_header("Test Page Map"); | style_header("测试页面地图"); | style_header("Test Page Map"); -> style_header("测试页面地图"); |
| style_header("Test Page Map"); | style_header("测试页面地图"); | style_header("Test Page Map"); -> style_header("测试页面地图"); |
| style_header("Timeline Display Preferences"); | style_header("时间线显示偏好"); | style_header("Timeline Display Preferences"); -> style_header("时间线显示偏好"); |
| style_header("Timeline Display Preferences"); | style_header("时间线显示偏好"); | style_header("Timeline Display Preferences"); -> style_header("时间线显示偏好"); |
| style_header("Timeline Examples"); | style_header("时间线示例"); | style_header("Timeline Examples"); -> style_header("时间线示例"); |
| style_header("Timeline Examples"); | style_header("时间线示例"); | style_header("Timeline Examples"); -> style_header("时间线示例"); |
| style_header("URL Alias Configuration"); | style_header("URL别名配置"); | style_header("URL Alias Configuration"); -> style_header("URL别名配置"); |
| style_header("URL Alias Configuration"); | style_header("URL别名配置"); | style_header("URL Alias Configuration"); -> style_header("URL别名配置"); |
| style_header("WWW Configuration"); | style_header("WWW 配置"); | style_header("WWW Configuration"); -> style_header("WWW 配置"); |
| style_header("WWW Configuration"); | style_header("WWW 配置"); | style_header("WWW Configuration"); -> style_header("WWW 配置"); |
| style_header("Wiki Configuration"); | style_header("Wiki 配置"); | style_header("Wiki Configuration"); -> style_header("Wiki 配置"); |
| style_header("Wiki Configuration"); | style_header("Wiki 配置"); | style_header("Wiki Configuration"); -> style_header("Wiki 配置"); |
| style_submenu_element("All", "%R/setup_settings?all"); | style_submenu_element("全部", "%R/setup_settings?all"); | style_submenu_element("All", "%R/setup_settings?all"); -> style_submenu_element("全部", "%R/setup_settings?all"); |
| style_submenu_element("All", "%R/setup_settings?all"); | style_submenu_element("全部", "%R/setup_settings?all"); | style_submenu_element("All", "%R/setup_settings?all"); -> style_submenu_element("全部", "%R/setup_settings?all"); |
| style_submenu_element("Changes-Only", "%R/setup_settings"); | style_submenu_element("仅显示变更", "%R/setup_settings"); | style_submenu_element("Changes-Only", "%R/setup_settings"); -> style_submenu_element("仅显示变更", "%R/setup_settings"); |
| style_submenu_element("Changes-Only", "%R/setup_settings"); | style_submenu_element("仅显示变更", "%R/setup_settings"); | style_submenu_element("Changes-Only", "%R/setup_settings"); -> style_submenu_element("仅显示变更", "%R/setup_settings"); |
| style_submenu_element("FTS Index Debugging","%R/test-ftsdocs"); | @ <p><input type="submit" name="fts0" value="删除全文索引"> | style_submenu_element("FTS Index Debugging","%R/test-ftsdocs"); -> @ <p><input type="submit" name="fts0" value="删除全文索引"> |
| style_submenu_element("FTS Index Debugging","%R/test-ftsdocs"); | cgi_printf("<p><input type=\"submit\" name=\"fts0\" value=\"删除全文索引\">\n" | style_submenu_element("FTS Index Debugging","%R/test-ftsdocs"); -> cgi_printf("<p><input type=\"submit\" name=\"fts0\" value=\"删除全文索引\">\n" |
| style_submenu_element("Log-Menu", "setup-logmenu"); | style_header("管理日志"); | style_submenu_element("Log-Menu", "setup-logmenu"); -> style_header("管理日志"); |
| style_submenu_element("Log-Menu", "setup-logmenu"); | style_header("管理日志"); | style_submenu_element("Log-Menu", "setup-logmenu"); -> style_header("管理日志"); |
| tag field but leave the \ | <p>要添加新映射，请填写下面的表单并为标记提供唯一名称。要编辑现有映射，请填写表单并使用现有名称作为标记。要删除现有映射，请填写标记字段，但将\ | "tag field but leave the \"Base URL\" field blank.</p>\n"); -> cgi_printf("<p>要添加新映射，请填写下面的表单并为标记提供唯一名称。要编辑现有映射，请填写表单并使用现有名称作为标记。要删除现有映射，请填写标记字段，但将\"基础 URL\"字段留空。</p>\n"); |
| textarea_attribute("Custom Sitemap Entries", 8, 80, | textarea_attribute("自定义站点地图条目", 8, 80, | textarea_attribute("Custom Sitemap Entries", 8, 80, -> textarea_attribute("自定义站点地图条目", 8, 80, |
| textarea_attribute("Custom Sitemap Entries", 8, 80, | textarea_attribute("自定义站点地图条目", 8, 80, | textarea_attribute("Custom Sitemap Entries", 8, 80, -> textarea_attribute("自定义站点地图条目", 8, 80, |
| textarea_attribute("Main Menu", 12, 80, | textarea_attribute("主菜单", 12, 80, | textarea_attribute("Main Menu", 12, 80, -> textarea_attribute("主菜单", 12, 80, |
| textarea_attribute("Main Menu", 12, 80, | textarea_attribute("主菜单", 12, 80, | textarea_attribute("Main Menu", 12, 80, -> textarea_attribute("主菜单", 12, 80, |
| textarea_attribute("Project Description", 3, 80, | textarea_attribute("项目描述", 3, 80, | textarea_attribute("Project Description", 3, 80, -> textarea_attribute("项目描述", 3, 80, |
| textarea_attribute("Project Description", 3, 80, | textarea_attribute("项目描述", 3, 80, | textarea_attribute("Project Description", 3, 80, -> textarea_attribute("项目描述", 3, 80, |
| the display.</p>\n | 与 UTC 相同，因此此设置在显示中不会有任何区别。</p>\n | "the display.</p>\n"); -> cgi_printf("与 UTC 相同，因此此设置在显示中不会有任何区别。</p>\n"); |
| when the target is Fossil)</td></tr>\n | ）</td></tr>\n | "(use \"<tt>/wiki?name=</tt>\" when the target is Fossil)</td></tr>\n" -> "（当目标是 Fossil 时使用\"<tt>/wiki?name=</tt>\"）</td></tr>\n" |
| \| Header 1     \| Header 2    \| Header 3      \| | \| 标题 1     \| 标题 2    \| 标题 3      \| | \| Header 1     \| Header 2    \| Header 3      \| -> \| 标题 1     \| 标题 2    \| 标题 3      \| |

## summary

| English Term | Chinese Translation | Context |
|--------------|---------------------|---------|
| Abbreviated | 缩写形式 |  |
| Accept | 接受 |  |
| Already shunned | 已被回避 |  |
| Artifact(s) | 制品 |  |
| Canonical Server URL | 规范服务器URL |  |
| Disabled | 已禁用 |  |
| Email Notification Setup | 电子邮件通知设置 |  |
| Icon image file | 图标图像文件 |  |
| Repository Nickname | 仓库昵称 |  |
| Revert To Default | 恢复默认 |  |
| SMTP Relay Host | SMTP中继主机 |  |
| Store Emails In This Directory | 在此目录中存储电子邮件 |  |
| The current project logo | 当前项目Logo |  |
| 刷新 | alerts.c - 按钮文本 |  |
| 将电子邮件文本传送到此命令 | alerts.c - 表单标签 |  |
| 应用更改 | alerts.c - 按钮文本 |  |
| 无效制品 | shun.c - 验证状态 |  |
| 更改Logo | setup.c - 按钮文本 |  |
| 更改背景 | setup.c - 按钮文本 |  |
| 有效 | shun.c - 验证状态 |  |
| 查看 | shun.c - 按钮文本 |  |
| 注意： | setup.c - 提示文本 |  |
| 电子邮件发送方法 | alerts.c - 表单标签 |  |
| 管理员电子邮件地址 | alerts.c - 表单标签 |  |
| 编辑项目Logo和背景 | setup.c - 页面标题 |  |
| 被回避的制品 | shun.c - 页面标题 |  |

