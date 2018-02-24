@echo off
if "%1"=="" goto loop
copy chicken%1.in chicken.in >nul
echo Problem Test
echo Data %1
time<enter
chicken
time<enter
fc chicken.out chicken%1.out
del chicken.in
del chicken.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
