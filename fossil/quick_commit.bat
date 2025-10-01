@echo off
REM Quick commit script for Fossil SCM
REM Author: Trae AI
REM Version: 1.2
REM Update: Fixed encoding issues by using English messages

REM Set path to fossil.exe
set FOSSIL_EXE=bin\fossil.exe

REM Check if fossil.exe exists
if not exist %FOSSIL_EXE% (
    echo Error: Cannot find fossil.exe. Make sure %FOSSIL_EXE% exists.
    pause
    exit /b 1
)

REM Check if commit message is provided
if "%~1"=="" (
    echo Usage: %0 "commit message"
    echo Example: %0 "Fix login page CSS issue"
    pause
    exit /b 1
)

REM Set working directory to script location
cd /d %~dp0

REM Show current status
%FOSSIL_EXE% status

REM Add all changes
%FOSSIL_EXE% add .

REM Commit changes
%FOSSIL_EXE% commit -m "%~1"

REM Show status after commit
%FOSSIL_EXE% status

REM Operation completed

echo Commit operation completed!
echo Note: To push changes to remote repository, use command: %FOSSIL_EXE% push

REM Wait for user input
pause