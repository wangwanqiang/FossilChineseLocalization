@echo off
REM Simple demonstration of fossil settings ignore-glob

cls
echo ===== Fossil ignore-glob Demo =====
echo.
echo The correct command to view settings is: fossil settings [SETTING]
echo.
echo Current ignore-glob value:
echo ------------------------------------------
fossil.exe settings --value ignore-glob
echo ------------------------------------------
echo.
echo To set ignore-glob (example):
echo fossil settings ignore-glob "*.o,*.obj,*.exe,*.dll,*.tmp"
echo.
echo To unset ignore-glob:
echo fossil unset ignore-glob
echo.
echo Press any key to exit...
pause > nul