@echo off
setlocal ENABLEDELAYEDEXPANSION

REM --- Color Configuration ---
set "RED=[31m"
set "GREEN=[32m"
set "YELLOW=[33m"
set "RESET=[0m"

REM --- Check Parameters ---
if "%~1" == "" (
    echo %RED%[ERROR]%RESET% No executable name provided.
    exit /b 1
)

REM Extract just the filename (e.g., "main") in case a path was passed
set "EXE_NAME=%~n1.exe"

REM --- PATH SETUP ---
REM Move to the parent directory (project root) where input/output lives
cd ..

set "EXE_PATH=.\executables\%EXE_NAME%"
set "inputName=input.in"
set "outputName=output.out"
set "maxBytes=10485760"
set "limitExceeded=0"

REM Verify the executable exists in the new location
if not exist "%EXE_PATH%" (
    echo %RED%[ERROR]%RESET% Executable not found at: %EXE_PATH%
    exit /b 1
)

REM Delete previous output if it exists
if exist "%outputName%" del "%outputName%"

REM --- Execution ---
echo %YELLOW%[INFO]%RESET% Running %EXE_NAME% from /executables...
start "" /b "%EXE_PATH%" < "%inputName%" > "%outputName%" 2>&1

:LOOP
REM Check if process is still running
tasklist /FI "IMAGENAME eq %EXE_NAME%" 2>NUL | find /I "%EXE_NAME%" >NUL
set "running=%errorlevel%"

REM Monitor file size
if exist "%outputName%" (
    for %%A in ("%outputName%") do set "size=%%~zA"
    
    if !size! GTR %maxBytes% (
        set "limitExceeded=1"
        echo %RED%[LIMIT EXCEEDED]%RESET% Output exceeded 10MB. Killing process...
        taskkill /F /T /IM "%EXE_NAME%" >nul 2>&1
        timeout /t 1 /nobreak >nul
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
    echo=
    type "%outputName%"
    echo=
    echo=
    echo %GREEN%[SUCCESS]%RESET% Program finished successfully.
)

echo %GREEN%[INFO]%RESET% Output saved to: "%cd%\%outputName%"

REM Return to scripts folder
cd scripts
exit /b 0