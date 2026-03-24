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

REM --- PATH SETUP ---
REM %~dp0 gaseste folderul exact in care se afla acest script (ex: C:\...\scripts\)
set "SCRIPTS_DIR=%~dp0"

REM Calculam calea catre folderul radacina (un nivel mai sus)
for %%I in ("%SCRIPTS_DIR%..") do set "ROOT_DIR=%%~fI"

REM Extragem doar numele fara extensie si ii adaugam fortat .exe
set "EXE_NAME=%~n1.exe"
set "EXE_PATH=%ROOT_DIR%\executables\%EXE_NAME%"
set "inputName=%ROOT_DIR%\input.in"
set "outputName=%ROOT_DIR%\output.out"

set "maxBytes=10485760"
set "limitExceeded=0"

REM --- Context & Preparation ---
REM Schimbam folderul curent in radacina proiectului
cd /d "%ROOT_DIR%"

REM Verificam daca executabilul exista
if not exist "%EXE_PATH%" (
    echo %RED%[ERROR]%RESET% Executable not found at: "%EXE_PATH%"
    exit /b 1
)

REM Stergem vechiul output daca exista
if exist "%outputName%" del /Q "%outputName%"

REM Daca nu exista fisierul de input, cream unul gol pentru a preveni erori la redirectionare
if not exist "%inputName%" type nul > "%inputName%"

REM --- Execution ---
echo %YELLOW%[INFO]%RESET% Running %EXE_NAME% ...
REM Am adaugat cmd /c pentru ca redirectarea ( < si > ) sa functioneze mai fiabil in background
start "" /b cmd /c ""%EXE_PATH%" < "%inputName%" > "%outputName%" 2>&1"

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

echo %GREEN%[INFO]%RESET% Output saved to: "%outputName%"

REM Ne intoarcem in folderul scripts la final
cd /d "%SCRIPTS_DIR%"
exit /b 0