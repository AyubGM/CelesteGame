@echo off
echo --- Starting Build Process ---

cmake -S . -B build

cmake --build build --config Debug

echo.
echo --- Build Finished ---
pause