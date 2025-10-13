@echo off

REM Move to parent folder
cd ..

REM Now all commands run in the parent folder
generator > input.in
professional < input.in > output.out
slowSolution < input.in > slowSolutionOutput.out
fc output.out slowSolutionOutput.out
if errorlevel 1 exit
diff_test
