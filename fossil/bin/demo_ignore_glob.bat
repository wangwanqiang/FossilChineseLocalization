@echo off
REM 演示如何正确使用fossil settings命令来管理ignore-glob配置

REM 清屏
cls

REM 显示欢迎信息
echo ===== Fossil ignore-glob 配置演示 =====
echo.

REM 解释之前命令失败的原因
echo 【重要说明】：
echo 之前尝试使用的 "fossil config get ignore-glob" 命令格式错误。
echo 在Fossil中，查看和设置配置的正确命令是 "fossil settings" 而不是 "fossil config get"。
echo.

REM 演示查看ignore-glob当前值
echo 1. 查看当前ignore-glob设置（没有设置时显示为空）：
echo ------------------------------------------
fossil.exe settings --value ignore-glob
echo ------------------------------------------
echo.

REM 演示设置ignore-glob
echo 2. 设置ignore-glob示例（不会实际修改，仅展示命令格式）：
echo ------------------------------------------
echo 要设置忽略的文件模式，可以使用类似这样的命令：
echo fossil.exe settings ignore-glob "*.o,*.obj,*.exe,*.dll,*.pdb,*.ilk,*.suo,*.ncb,*.user,*.bak,*.tmp,.gitignore,.svn,__pycache__"
echo ------------------------------------------
echo.

REM 演示如何清除设置
echo 3. 清除ignore-glob设置：
echo ------------------------------------------
echo 要清除当前设置，可以使用：
echo fossil.exe unset ignore-glob
echo ------------------------------------------
echo.

REM 显示更多帮助信息
echo 4. 查看完整settings命令帮助：
echo ------------------------------------------
echo 要获取更多帮助，请运行：
echo fossil.exe help settings
echo ------------------------------------------
echo.

REM 提示按任意键退出
echo 按任意键退出演示...
pause > nul