# Fossil SCM Commit Tools Documentation

This document provides information about the convenience tools for managing code commits in the Fossil version control system.

## Available Tools

### 1. set_fossil_ignore_simple.bat

**Purpose**: Used to set Fossil's ignore-glob configuration, defining which files should be ignored and not included in version control.

**Features**: 
- Checks if fossil.exe exists in the bin directory
- Sets common binary files, temporary files, log files, IDE configuration files, etc. as ignore patterns
- Provides quick commit command examples

**Usage**: Double-click to run and automatically set the ignore-glob configuration.

**Ignored File Types**: 
```
*.o,*.obj,*.exe,*.dll,*.pdb,*.ilk,*.suo,*.ncb,*.user,*.cache,*.bak,*.tmp,*.temp,*.old,*.log,*.err
```

### 2. quick_commit.bat (Version 1.2)

**Purpose**: Provides a quick way to add all changes and commit to the Fossil repository.

**Features**: 
- Checks if fossil.exe exists in the bin directory
- Verifies if a commit message parameter is provided
- Sets the working directory to the script's location
- Shows status before commit
- Adds all changes to version control
- Executes the commit operation
- Shows status after commit
- Provides a tip for pushing to a remote repository

**Usage**: 
```
quick_commit.bat "your commit message"
```

**Example**: 
```
quick_commit.bat "Fixed homepage layout issue"
```

### 3. start_fossil_ui.bat (Version 1.3)

**Purpose**: Conveniently starts Fossil's built-in web interface for repository management.

**Features**: 
- Checks if fossil.exe exists in the bin directory
- Sets the working directory to the script's location
- Uses default port (8080) but allows customization
- Displays access information and usage instructions
- Starts the Fossil UI server
- Provides helpful error messages and suggestions when startup fails (e.g., port conflicts)
- Correct repository file path configuration

**Usage**: 
```
start_fossil_ui.bat [port]
```

**Examples**: 
```
start_fossil_ui.bat            # Start with default settings (port 8080)
start_fossil_ui.bat 8888       # Start on port 8888
```

To access the UI, open a web browser and navigate to http://localhost:8080 (or the custom port you specified). Press Ctrl+C to stop the server.

**Note**: 
- Version 1.2 includes better error handling for common startup issues like port conflicts.
- Version 1.3 fixes the repository path to correctly point to the fossil.fossil file in the parent directory, ensuring proper display of all commit records in timeline.

## Binary-Glob Configuration

To avoid warnings when committing binary files, the system has been configured with binary-glob settings, including the following file types:

```
*.exe,*.dll,*.zip,*.tar,*.gz,*.7z,*.pdf,*.png,*.jpg,*.gif,*.bmp,*.ico,*.doc,*.docx,*.xls,*.xlsx,*.ppt,*.pptx,*.pk
```

This configuration tells Fossil to treat these files as binary files, avoiding warning messages during commits.

## Viewing and Modifying Configurations

To view the current ignore-glob or binary-glob configuration, you can use the following commands:

```
bin\fossil.exe setting ignore-glob
```

```
bin\fossil.exe setting binary-glob
```

To modify these configurations, you can directly run the corresponding setting commands:

```
bin\fossil.exe setting ignore-glob "your ignore pattern list"
```

```
bin\fossil.exe setting binary-glob "your binary file pattern list"
```

## Notes

1. Ensure fossil.exe is located in the bin directory and is executable
2. Commit messages should be concise and clearly describe the main changes in the commit
3. Before committing, it is recommended to check the status (fossil status) to ensure only necessary files are committed
4. If you need to push to a remote repository, use `bin\fossil.exe push` after committing
5. If you encounter permission issues, run the scripts as an administrator

## Usage Tips

- Regularly run `set_fossil_ignore_simple.bat` to ensure the ignore-glob configuration is up to date
- For frequent small updates, use `quick_commit.bat` to simplify the commit process
- For important code changes, it is recommended to run `fossil diff` first to view the specific changes
- You can add these scripts to the system PATH for use from any location