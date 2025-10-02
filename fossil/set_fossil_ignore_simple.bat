@echo off
REM Simple script to set Fossil ignore-glob configuration

REM Set path to fossil.exe
set FOSSIL_EXE=bin\fossil.exe

REM Check if fossil.exe exists
if not exist %FOSSIL_EXE% (
echo Error: fossil.exe not found in bin directory.
pause
exit /b 1
)

REM Set ignore patterns for Fossil
echo Setting fossil ignore-glob configuration...
%FOSSIL_EXE% settings ignore-glob "*.o,*.obj,*.exe,*.dll,*.pdb,*.ilk,*.suo,*.ncb,*.user,*.cache,*.bak,*.tmp,*.temp,*.old,*.log,*.err,ai_backups/*"

if %ERRORLEVEL% equ 0 (
echo Success: fossil ignore-glob configuration has been set!
echo Common binary and temporary files will be ignored.
) else (
echo Failed: Could not set fossil ignore-glob configuration!
)

echo.
echo To commit changes quickly, use this command:
echo %FOSSIL_EXE% add . && %FOSSIL_EXE% commit -m "Your commit message"
echo.

pause