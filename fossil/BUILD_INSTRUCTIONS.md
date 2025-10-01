# Fossil SCM Build Instructions for Windows

This document provides detailed instructions for building Fossil SCM on Windows using Visual Studio 2022 build tools.

## Prerequisites

1. **Visual Studio 2022** (Community Edition or higher) with C++ development tools installed
2. **PowerShell** (version 5.1 or higher)
3. **Fossil Source Code** (included in this repository at `Fossil`)

## Build Options

Fossil can be built with various options enabled or disabled. The key options include:

- **SSL Support**: Enable HTTPS functionality
- **JSON API**: Enable JSON API support
- **TCL Integration**: Enable TCL scripting support
- **TH1 Hooks**: Enable TH1 script hooks for commands and web pages
- **Optimization Level**: Control compiler optimization settings
- **Debug Build**: Include debugging symbols

## Using the Build Script

A PowerShell script `build_fossil.ps1` has been provided to simplify the build process. This script will:

1. Locate your Visual Studio installation
2. Set up the build environment using the Visual Studio Developer Command Prompt
3. Build Fossil with your specified options

### Basic Build

To perform a basic build with default settings:

```powershell
# Open PowerShell as Administrator (required for environment setup)
cd c:\source\fossil_depot\fossil
.uild_fossil.ps1
```

### Custom Build Options

You can specify various parameters to customize the build:

```powershell
# Build with SSL and JSON support
.uild_fossil.ps1 -EnableSSL -EnableJSON

# Build with debugging symbols and lower optimization
.uild_fossil.ps1 -Debug -Optimize 1

# Build for x86 platform
.uild_fossil.ps1 -Platform x86

# All available options
.uild_fossil.ps1 -EnableSSL -EnableJSON -EnableTCL -EnableTh1Hooks -Debug -Optimize 2 -Platform x64
```

## Manual Build Process

If you prefer to build manually without the script:

1. **Open the Visual Studio Developer Command Prompt**
   - For x64 builds: Use "Developer Command Prompt for VS 2022"
   - For x86 builds: Use "Developer Command Prompt for VS 2022" and run `vcvars32.bat`

2. **Navigate to the Fossil Windows build directory**
   ```cmd
   cd c:\source\fossil_depot\fossil\Fossil\win
   ```

3. **Run the build command with your desired options**
   ```cmd
   nmake /f Makefile.msc OPTIMIZATIONS=2 DEBUG=0 FOSSIL_ENABLE_SSL=0
   ```

## Build Output

After a successful build, you will find the `fossil.exe` executable in the `win` directory:
`c:\source\fossil_depot\fossil\Fossil\win\fossil.exe`

## Troubleshooting

### Common Build Issues

1. **Visual Studio not found**
   - If the script can't find your Visual Studio installation, edit the `vsPath` variable in `build_fossil.ps1` to match your actual installation path.

2. **Missing compiler or build tools**
   - Ensure you have the "Desktop development with C++" workload installed in Visual Studio.

3. **SSL build errors**
   - If enabling SSL support, you may need to have Perl installed for OpenSSL build scripts.
   - Set the `PERLDIR` environment variable if Perl is not in your PATH.

4. **Permission issues**
   - Run PowerShell as Administrator to ensure proper environment setup.

## Additional Resources

- For more detailed information about the Fossil build process, refer to the official documentation at:
  http://fossil-scm.org/home/doc/trunk/www/makefile.wiki

- The `BUILD.txt` file in the Fossil source directory contains additional build instructions and options.