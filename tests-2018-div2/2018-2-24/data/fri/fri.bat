@echo off
if "%1"=="" goto loop
copy fri%1.in fri.in >nul
echo Problem Test
echo Data %1
time<enter
fri
time<enter
fc fri.out fri%1.out
del fri.in
del fri.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
