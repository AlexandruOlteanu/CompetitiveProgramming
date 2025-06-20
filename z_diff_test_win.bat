@echo off
generate >input.in
main <input.in >output.out
slowMain <input.in >slowMain.out
fc output.out slowMain.out
if errorlevel 1 exit
z_diff_test_win