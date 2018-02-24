@echo off
if "%1"=="" goto loop
copy fld%1.in fld.in >nul
echo Problem Test
echo Data %1
time<enter
fld.exe
time<enter
fc fld.out fld%1.out
del fld.in
del fld.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
