@echo off
if "%1"=="" goto loop
copy d%1.in d.in >nul
echo Problem Test
echo Data %1
time<enter
d.exe
time<enter
copy d%1.out d.ans >nul
fc d.out d.ans
del d.in
del d.out
del d.ans
pause
goto quit
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:quit
