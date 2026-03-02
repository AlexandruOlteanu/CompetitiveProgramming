@echo off
REM ==========================================================
REM run.bat — runs the compiled C++ program with input.in
REM Writes to output.out, stops if >10MB
REM Redirects stderr -> stdout for debugging
REM ==========================================================

setlocal ENABLEDELAYEDEXPANSION

set "RED=[31m"
set "GREEN=[32m"
set "YELLOW=[33m"
set "RESET=[0m"

REM --- Check parameter ---
if "%~1"=="" (
    echo %RED%[ERROR]%RESET% No executable path provided.
    exit /b 1
)

for %%F in ("%~1") do (
    set "exeName=%%~nF.exe"
    set "fileDir=%%~dpF"
)

set "inputName=input.in"
set "outputName=output.out"
set "maxBytes=10485760"   REM 10 MB

cd /d "%fileDir%"

REM --- Check file existence ---
if not exist "%exeName%" (
    echo %RED%[ERROR]%RESET% "%exeName%" not found!
    exit /b 1
)

if not exist "%inputName%" (
    echo %RED%[ERROR]%RESET% "%inputName%" not found!
    exit /b 1
)

if exist "%outputName%" del "%outputName%"

REM --- Run program asynchronously ---
start "" /b "%exeName%" < "%inputName%" > "%outputName%" 2>&1

ping 127.0.0.1 -n 2 > nul
echo %YELLOW%[INFO]%RESET% Running with 10MB output limit...

REM --- Monitor output file size ---
:LOOP
if exist "%outputName%" (
    for %%A in ("%outputName%") do set "size=%%~zA"

    if !size! GTR %maxBytes% (
        echo %RED%[ERROR]%RESET% Output exceeded 10 MB. Stopping program...
        taskkill /F /IM "%exeName%" > nul 2>&1
        echo %RED%[ERROR]%RESET% Program terminated due to excessive output.
        exit /b 1
    )
)

REM Check if program is still running
tasklist /FI "IMAGENAME eq %exeName%" | find /I "%exeName%" > nul
if %errorlevel%==0 (
    goto LOOP
)

REM --- Final output ---
for %%A in ("%outputName%") do set "finalSize=%%~zA"

echo=
type "%outputName%"
echo=
echo=
echo %GREEN%[SUCCESS]%RESET% Program finished successfully!
echo %GREEN%[INFO]%RESET% Output saved to "%outputName%"
exit /b 0