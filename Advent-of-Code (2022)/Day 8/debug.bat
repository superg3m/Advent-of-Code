@echo off
if not exist .\Build\AOC_Day8.sln (
    if not exist .\Build\AOC_Day8.exe (
        powershell -nologo -command "Write-Host 'ERROR: check if exe exists and re-build' -ForegroundColor Red"
    ) else (
        devenv .\Build\AOC_Day8.exe
    )
) else (
    devenv .\Build\AOC_Day8.sln
)
