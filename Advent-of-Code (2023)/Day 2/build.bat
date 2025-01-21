@echo off
powershell -nologo -command "Write-Host 'running build.bat...' -ForegroundColor Green"
if not exist .\Build (
    mkdir .\Build"
)
pushd .\Build
if NOT [%1] EQU [] (
    if [%1] EQU [-g++] (
        gcc -std=c++20  ../*.c -o Output -lOle32 -lWinmm
    ) else (
        powershell -nologo -command "Write-Host 'Wrong Command' -ForegroundColor Red"
    )
) else (
    cl /std:c++20 /Fe: Output.exe /Zi ..\Source\*.c Ole32.lib Winmm.lib user32.lib gdi32.lib ole32.lib
)
popd