<#
.SYNOPSIS
Builds Fossil SCM using Visual Studio build tools.

.DESCRIPTION
This script sets up the Visual Studio environment and builds Fossil SCM according to the instructions in BUILD.txt.

.EXAMPLE
PS> .\build_fossil.ps1
Builds Fossil with default settings.

.EXAMPLE
PS> .\build_fossil.ps1 -EnableSSL -EnableJSON
Builds Fossil with SSL and JSON support enabled.

.PARAMETER EnableSSL
Enable SSL support in Fossil.

.PARAMETER EnableJSON
Enable JSON API support in Fossil.

.PARAMETER EnableTCL
Enable TCL integration subsystem.

.PARAMETER EnableTh1Docs
Enable TH1 scripts in embedded documentation.

.PARAMETER EnableTh1Hooks
Enable TH1 hooks for commands and web pages.

.PARAMETER BuildSSL
Build OpenSSL libraries from source.

.PARAMETER BuildZLIB
Build included zlib library (default is enabled).

.PARAMETER DynamicBuild
Link everything except SQLite dynamically.

.PARAMETER Debug
Build with debugging symbols.

.PARAMETER Optimize
Set optimization level (0-3, default is 2).

.PARAMETER Platform
Target platform (x86, x64, etc.).
#>
[CmdletBinding()]
param (
    [switch]$EnableSSL = $false,
    [switch]$EnableJSON = $false,
    [switch]$EnableTCL = $false,
    [switch]$EnableTh1Docs = $false,
    [switch]$EnableTh1Hooks = $false,
    [switch]$BuildSSL = $false,
    [switch]$BuildZLIB = $true,
    [switch]$DynamicBuild = $false,
    [switch]$Debug = $false,
    [int]$Optimize = 2,
    [string]$Platform = "x64"
)

function Find-VsDevCmd {
    # Try to find Visual Studio installation
    $vsPath = "C:\Program Files\Microsoft Visual Studio\2022\Community"
    if (-not (Test-Path $vsPath)) {
        Write-Error "Visual Studio 2022 Community not found at $vsPath"
        Write-Error "Please update the vsPath variable in this script to match your Visual Studio installation"
        exit 1
    }

    # Find vsdevcmd.bat
    $devCmdPath = Join-Path $vsPath "Common7\Tools\vsdevcmd.bat"
    if (-not (Test-Path $devCmdPath)) {
        Write-Error "vsdevcmd.bat not found at $devCmdPath"
        exit 1
    }

    return $devCmdPath
}

function Build-Fossil {
    param (
        [string]$DevCmdPath,
        [string]$TargetPlatform
    )

    # Create build command with options
    $buildOptions = @(
        "/f Makefile.msc",
        "OPTIMIZATIONS=$Optimize",
        "FOSSIL_BUILD_ZLIB=$(if($BuildZLIB) {1} else {0})",
        "FOSSIL_DYNAMIC_BUILD=$(if($DynamicBuild) {1} else {0})",
        "FOSSIL_ENABLE_SSL=$(if($EnableSSL) {1} else {0})",
        "FOSSIL_ENABLE_JSON=$(if($EnableJSON) {1} else {0})",
        "FOSSIL_ENABLE_TCL=$(if($EnableTCL) {1} else {0})",
        "FOSSIL_ENABLE_TH1_DOCS=$(if($EnableTh1Docs) {1} else {0})",
        "FOSSIL_ENABLE_TH1_HOOKS=$(if($EnableTh1Hooks) {1} else {0})",
        "FOSSIL_BUILD_SSL=$(if($BuildSSL) {1} else {0})",
        "DEBUG=$(if($Debug) {1} else {0})",
        "PLATFORM=$TargetPlatform"
    )

    $buildCmd = "nmake $($buildOptions -join ' ')"

    # Get the current script directory
    $scriptDir = Split-Path -Parent $PSCommandPath
    $fossilDir = $scriptDir
    $winDir = Join-Path $fossilDir "Fossil-1205ec86\win"

    # Create a temporary batch file to set up environment and build
    $tempPath = [System.IO.Path]::GetTempPath()
    $tempBatch = Join-Path $tempPath "build_fossil_temp.bat"
    $batchContent = @"
@echo off
call "$DevCmdPath" -arch=$TargetPlatform
cd /d "$winDir"
echo Building Fossil with options: $buildOptions
echo Running: $buildCmd
$buildCmd
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
echo Build completed successfully.
echo Fossil executable should be in the win directory.
"@
    
    $batchContent | Out-File -FilePath $tempBatch -Encoding ASCII

    try {
        # Execute the batch file
        Write-Host "Setting up Visual Studio environment and building Fossil..."
        & cmd.exe /c "$tempBatch"
        if ($LASTEXITCODE -ne 0) {
            Write-Error "Build failed with exit code $LASTEXITCODE"
            exit $LASTEXITCODE
        }
    }
    finally {
        # Clean up temporary file
        if (Test-Path $tempBatch) {
            Remove-Item $tempBatch -Force
        }
    }
}

# Main script
Write-Host "Fossil Build Script"
Write-Host "=================="

# Validate optimization level
if ($Optimize -lt 0 -or $Optimize -gt 3) {
    Write-Error "Invalid optimization level. Must be between 0 and 3."
    exit 1
}

# Display build configuration
Write-Host "Build Configuration:"
Write-Host "--------------------"
Write-Host "Platform: $Platform"
Write-Host "Optimization: $Optimize"
Write-Host "Debug: $Debug"
Write-Host "Build ZLIB: $BuildZLIB"
Write-Host "Dynamic Build: $DynamicBuild"
Write-Host "Enable SSL: $EnableSSL"
Write-Host "Build SSL: $BuildSSL"
Write-Host "Enable JSON: $EnableJSON"
Write-Host "Enable TCL: $EnableTCL"
Write-Host "Enable TH1 Docs: $EnableTh1Docs"
Write-Host "Enable TH1 Hooks: $EnableTh1Hooks"
Write-Host

# Find Visual Studio dev cmd
$devCmdPath = Find-VsDevCmd

# Build Fossil
Build-Fossil -DevCmdPath $devCmdPath -TargetPlatform $Platform

Write-Host "Build process completed."