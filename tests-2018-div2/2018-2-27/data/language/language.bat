@echo off
if "%1"=="" goto loop
copy language%1.in language.in >nul
echo Problem Test
echo Data %1
time<enter
language.exe
time<enter
copy language%1.out language.ans >nul
checkl
type check.txt
del language.in
del language.out
del language.ans
pause
goto quit
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:quit
