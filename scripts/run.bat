@echo off
REM ==========================================================
REM run.bat — runs the compiled C++ program with input.in
REM Automatically detects executable based on current file
REM ==========================================================

REM --- ANSI color codes (Windows 10+ terminals support this) ---
set "RED=[31m"
set "GREEN=[32m"
set "YELLOW=[33m"
set "RESET=[0m"

REM --- Expect the active file path as argument ---
if "%~1"=="" (
    echo %RED%[ERROR]%RESET% No source file path provided.
    echo Please run this from VS Code with the file path argument.
    exit /b 1
)

REM --- Extract base filename (without extension) ---
for %%F in ("%~1") do (
    set "exeName=%%~nF.exe"
    set "fileDir=%%~dpF"
)

REM --- Input file name ---
set "inputName=input.in"

REM --- Change to the source file's directory ---
cd /d "%fileDir%"

REM --- Check if executable exists ---
if not exist "%exeName%" (
    echo %RED%[ERROR]%RESET% "%exeName%" not found!
    echo Make sure it's compiled first.
    exit /b 1
)

REM --- Check if input.in exists ---
if not exist "%inputName%" (
    echo %RED%[ERROR]%RESET% "%inputName%" not found!
    exit /b 1
)

REM --- Run program with input.in ---
"%exeName%" < "%inputName%"

REM --- Print a message after execution ---
echo.
echo %GREEN%[INFO]%RESET% "%exeName%" finished running.
echo.