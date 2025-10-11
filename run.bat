@echo off
REM ==========================================================
REM  run.bat — runs your compiled C++ program with input.in
REM ==========================================================

setlocal

REM Change to the folder containing this script
cd /d "%~dp0"

REM Run the executable (auto-detects same name as .cpp)
REM Example: if you compiled test.cpp -> test.exe
set "exeName=test.exe"

if not exist "%exeName%" (
    echo [Error] "%exeName%" not found!
    echo Make sure it’s compiled and in the same folder as run.bat.
    pause
    exit /b 1
)

if not exist "input.in" (
    echo [Error] "input.in" not found!
    pause
    exit /b 1
)

"%exeName%" < "input.in"
