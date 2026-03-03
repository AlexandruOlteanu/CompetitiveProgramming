@echo off
setlocal ENABLEDELAYEDEXPANSION

REM --- Color Configuration ---
set "RED=[31m"
set "GREEN=[32m"
set "YELLOW=[33m"
set "RESET=[0m"

REM --- Check Parameters ---
if "%~1" == "" (
    echo %RED%[ERROR]%RESET% No executable path provided.
    exit /b 1
)

for %%F in ("%~1") do (
    set "exeName=%%~nF.exe"
    set "fileDir=%%~dpF"
)

set "inputName=input.in"
set "outputName=output.out"
set "maxBytes=10485760"
set "limitExceeded=0"

cd /d "%fileDir%"

REM Delete previous output if it exists
if exist "%outputName%" del "%outputName%"

REM --- Execution ---
echo %YELLOW%[INFO]%RESET% Running %exeName%...
start "" /b "%exeName%" < "%inputName%" > "%outputName%" 2>&1

:LOOP
REM Check if process is still running
tasklist /FI "IMAGENAME eq %exeName%" 2>NUL | find /I "%exeName%" >NUL
set "running=%errorlevel%"

REM Monitor file size
if exist "%outputName%" (
    for %%A in ("%outputName%") do set "size=%%~zA"
    
    if !size! GTR %maxBytes% (
        set "limitExceeded=1"
        echo %RED%[LIMIT EXCEEDED]%RESET% Output exceeded 10MB. Killing process...
        taskkill /F /IM "%exeName%" >nul 2>&1
        goto TRUNCATE_FINISH
    )
)

if %running%==0 (
    timeout /t 1 /nobreak >nul
    goto LOOP
)

:TRUNCATE_FINISH
REM --- Final Truncation ---
if exist "%outputName%" (
    for %%A in ("%outputName%") do set "finalSize=%%~zA"
    if !finalSize! GTR %maxBytes% (
        set "limitExceeded=1"
        REM Truncate the file to exactly 10MB using PowerShell
        powershell -Command "$f=[System.IO.File]::OpenWrite('%outputName%'); $f.SetLength(%maxBytes%); $f.Close()"
    )
)

REM --- Intelligent Display Logic ---
echo=
if "%limitExceeded%"=="1" (
    echo %RED%[WARNING]%RESET% Output file was truncated to exactly 10MB.
    echo %RED%[INFO]%RESET% Console display skipped to prevent terminal lag.
) else (
    echo %YELLOW%--- Program Output ---%RESET%
    type "%outputName%"
    echo=
    echo %YELLOW%----------------------%RESET%
    echo %GREEN%[SUCCESS]%RESET% Program finished normally.
)

echo %GREEN%[INFO]%RESET% Final output saved to: "%outputName%"
exit /b 0