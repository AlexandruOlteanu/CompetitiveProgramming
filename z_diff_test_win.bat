@echo off
generate >input.in
main <input.in >output.out
second <input.in >second_output.out
fc output.out second_output.out
if errorlevel 1 exit
z_diff_test_win