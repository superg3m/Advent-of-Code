@echo off

if exist ./Build/Output.exe (
    if NOT [%1] EQU [] (
        if [%1] EQU [-debug] (
            call gdb "./Build/Output.exe"
        ) 
    ) else (
        call "./Build/Output.exe"
    )
) else (
    powershell -nologo -command "Write-Host 'ERROR: check if exe exists and re-build' -ForegroundColor Red"
)
