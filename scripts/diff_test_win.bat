@echo off

REM Move to parent folder
cd ..

REM Now all commands run in the parent folder
generate > input.in
main < input.in > output.out
slowMain < input.in > slowMain.out
fc output.out slowMain.out
if errorlevel 1 exit
z_diff_test_win
