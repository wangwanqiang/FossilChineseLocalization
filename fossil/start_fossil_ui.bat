REM Script to start Fossil Web UI
REM Author: Trae AI
REM Version: 1.3
REM Purpose: Conveniently start Fossil's built-in web interface
REM Update: Fixed repository path to point to correct fossil.fossil file

REM Set path to fossil.exe
set FOSSIL_EXE=bin\fossil.exe

REM Check if fossil.exe exists
if not exist %FOSSIL_EXE% (
    echo Error: Cannot find fossil.exe. Make sure %FOSSIL_EXE% exists.
    pause
    exit /b 1
)

REM Set path to the actual repository file (in parent directory)
set REPOSITORY_FILE=..\fossil.fossil

REM Check if repository file exists
if not exist %REPOSITORY_FILE% (
    echo Error: Cannot find repository file at %REPOSITORY_FILE%
    pause
    exit /b 1
)

REM Default parameters
set PORT=8081

REM Optional: Use port from command line arguments
if not "%~1"=="" set PORT=%~1

REM Display start information
cls
echo ==================================================
echo          Starting Fossil Web UI
echo ==================================================
echo Repository: %REPOSITORY_FILE%
echo Access URL: http://localhost:%PORT%
echo.
echo Options:
echo   - Press Ctrl+C to stop the server
echo   - To use a different port: %~nx0 8888
echo.
echo ==================================================
echo.

REM Start Fossil UI with specified parameters and repository file
%FOSSIL_EXE% ui %REPOSITORY_FILE% --port %PORT%

REM Check if startup failed
if %ERRORLEVEL% NEQ 0 (
    echo.
echo Error: Failed to start Fossil Web UI. Possible reasons:
    echo 1. Port %PORT% is already in use by another application
    echo 2. You don't have permission to use port %PORT%
    echo.
echo Suggestions:
    echo - Try using a different port: %~nx0 8888
    echo - Close any application that might be using port %PORT%
    echo - Run this script as Administrator if it's a permission issue
    echo.
)

REM If exited, show completion message
echo.
echo Fossil Web UI has been stopped.
pause