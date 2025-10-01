<#
.SYNOPSIS
A simplified script to build Fossil SCM using Visual Studio 2022 build tools.

.DESCRIPTION
This script provides a straightforward way to build Fossil SCM on Windows without complex parameter handling.

.EXAMPLE
PS> .\simple_build_fossil.ps1
Builds Fossil with default settings.
#>

# Configuration options
$vsPath = "C:\Program Files\Microsoft Visual Studio\2022\Community"
$devCmdPath = Join-Path $vsPath "Common7\Tools\vsdevcmd.bat"
$platform = "x64"
$optimize = 2

# Check if Visual Studio is installed
if (-not (Test-Path $vsPath)) {
    Write-Host "Visual Studio 2022 Community not found at $vsPath" -ForegroundColor Red
    Write-Host "Please update the vsPath variable in this script to match your Visual Studio installation" -ForegroundColor Yellow
    exit 1
}

# Check if vsdevcmd.bat exists
if (-not (Test-Path $devCmdPath)) {
    Write-Host "vsdevcmd.bat not found at $devCmdPath" -ForegroundColor Red
    exit 1
}

# Get the current script directory
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$fossilDir = $scriptDir
$winDir = Join-Path $fossilDir "Fossil-1205ec86\win"

# Create a temporary batch file to set up environment and build
$tempPath = [System.IO.Path]::GetTempPath()
$tempBatch = Join-Path $tempPath "build_fossil_temp.bat"

# Build command with basic options including base directory
$bPath = "$fossilDir"
$buildOptions = "/f Makefile.msc B=`"$bPath`" OPTIMIZATIONS=$optimize FOSSIL_BUILD_ZLIB=1 DEBUG=0 PLATFORM=$platform FOSSIL_ENABLE_TH1_HOOKS=1 FOSSIL_ENABLE_TH1_DOCS=1"
$buildCmd = "nmake $buildOptions"

# Write the batch file content
$batchContent = @"
@echo off
call "$devCmdPath" -arch=$platform
cd /d "$winDir"
echo Building Fossil with options: $buildOptions
echo Running: $buildCmd
$buildCmd
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
echo Build completed successfully.
echo Fossil executable should be in the win directory.
"@

$batchContent | Out-File -FilePath $tempBatch -Encoding ASCII

# Execute the build process
try {
    Write-Host "Setting up Visual Studio environment and building Fossil..."
    & cmd.exe /c "$tempBatch"
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Build failed with exit code $LASTEXITCODE" -ForegroundColor Red
        exit $LASTEXITCODE
    }
    else {
        Write-Host "Fossil build completed successfully!" -ForegroundColor Green
        Write-Host "The executable can be found at: $winDir\fossil.exe" -ForegroundColor Cyan
    }
} catch {
    Write-Host "An error occurred during the build process: $($_.Exception.Message)" -ForegroundColor Red
} finally {
    # Clean up temporary file
    if (Test-Path $tempBatch) {
        Remove-Item $tempBatch -Force
    }
}