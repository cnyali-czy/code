@echo off
if "%1"=="" goto loop
copy tv%1.in tv.in >nul
echo Problem Test
echo Data %1
time<enter
tv
time<enter
fc tv.out tv%1.out
del tv.in
del tv.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
