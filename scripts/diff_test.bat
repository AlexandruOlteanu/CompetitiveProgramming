@echo off
setlocal

REM --- PATH CONFIGURATION ---
REM Assuming this script is in /scripts and exes are in /executables
set "EXEDIR=..\executables"

REM Move to parent folder to keep input/output files there
cd ..

REM --- RUN TESTS ---
REM We call the executables from the new subfolder
"%EXEDIR%\generator.exe" > input.in
"%EXEDIR%\professional.exe" < input.in > output.out
"%EXEDIR%\slowSolution.exe" < input.in > slowSolutionOutput.out

REM --- COMPARE ---
fc output.out slowSolutionOutput.out
if errorlevel 1 (
    echo [DIFF] Files differ!
    cd .\scripts
    exit /b 1
)

REM --- CLEANUP / RETURN ---
echo [SUCCESS] No differences found.
cd .\scripts
call diff_test.bat

endlocal