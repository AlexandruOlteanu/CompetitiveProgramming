@echo off
REM ==========================================================
REM build.bat — build the currently open C++ file with colors
REM ==========================================================

setlocal ENABLEDELAYEDEXPANSION

REM --- CONFIGURE G++ PATH ---
set "GPP=C:\msys64\ucrt64\bin\g++.exe"

REM --- ANSI COLOR CODES (for VS Code / modern CMD) ---
set "RED=[31m"
set "GREEN=[32m"
set "YELLOW=[33m"
set "CYAN=[36m"
set "RESET=[0m"

REM --- EXPECT FILE PATH FROM ARGUMENT ---
if "%~1"=="" (
    echo %RED%[ERROR]%RESET% No file path provided.
    echo Please run this from VS Code with the file path argument.
    exit /b 1
)

set "SRC=%~1"

REM --- EXTRACT FILE INFO ---
for %%F in ("%SRC%") do (
    set "FILENAME=%%~nF"
    set "FILEDIR=%%~dpF"
)

REM --- BUILD COMMAND ---
echo %CYAN%[INFO]%RESET% Building "%SRC%" ...
"%GPP%" -fdiagnostics-color=always -g -DDebugMode "%SRC%" -o "%FILEDIR%%FILENAME%.exe"

REM --- CHECK RESULT ---
if %errorlevel% neq 0 (
    echo %RED%[ERROR]%RESET% Build failed!
    exit /b %errorlevel%
) else (
    echo %GREEN%[SUCCESS]%RESET% Build succeeded: "%FILEDIR%%FILENAME%.exe"
)

endlocal
