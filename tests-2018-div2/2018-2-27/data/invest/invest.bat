@echo off
if "%1"=="" goto loop
copy invest%1.in invest.in >nul
echo Problem Test
echo Data %1
time<enter
invest.exe
time<enter
copy invest%1.out invest.ans >nul
fc invest.out invest.ans
del invest.in
del invest.out
del invest.ans
pause
goto quit
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:quit
