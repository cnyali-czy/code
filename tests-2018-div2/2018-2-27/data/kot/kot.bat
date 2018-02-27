@echo off
if "%1"=="" goto loop
copy kot%1.in kot.in >nul
echo Problem Test
echo Data %1
time<enter
kot.exe
time<enter
copy kot%1.out kot.ans >nul
fc kot.out kot.ans
del kot.in
del kot.out
del kot.ans
pause
goto quit
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:quit
