@echo off
for %%s in (*.png) do (
echo %%s
start.exe %%s %%s >>bitmaps.h
)
pause