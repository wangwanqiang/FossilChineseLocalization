@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\vsdevcmd.bat" -arch=x64
cd /d "C:\source\fossil_depot\fossil\Fossil-1205ec86\win"
nmake /f Makefile.msc OPTIMIZATIONS=2 FOSSIL_BUILD_ZLIB=1 DEBUG=0 FOSSIL_ENABLE_TH1_HOOKS=1 FOSSIL_ENABLE_TH1_DOCS=1
pause