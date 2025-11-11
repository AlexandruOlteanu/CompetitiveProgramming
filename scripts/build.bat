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

REM --- CALCULATE SOURCE FILE SIZE (in KB with 2 decimals) ---
for %%A in ("%SRC%") do set "BYTES=%%~zA"
for /f "usebackq" %%S in (`powershell -NoProfile -Command "[math]::Round(%BYTES% / 1024.0, 2)"`) do set "KBYTES=%%S"

REM --- BUILD COMMAND ---
echo %CYAN%[INFO]%RESET% Building "%SRC%"
echo %YELLOW%[SIZE]%RESET% Source file size: %KBYTES% KB
echo ...

"%GPP%" ^
  -fdiagnostics-color=always ^
  -g ^
  -DActivateDebug ^
  -DActivateTimings ^
  -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wfloat-equal -Wuninitialized ^
  "%SRC%" -o "%FILEDIR%%FILENAME%.exe"

REM --- CHECK RESULT ---
if %errorlevel% neq 0 (
    echo %RED%[ERROR]%RESET% Build failed!
    exit /b %errorlevel%
) else (
    echo %GREEN%[SUCCESS]%RESET% Build succeeded: "%FILEDIR%%FILENAME%.exe"
)

endlocal
