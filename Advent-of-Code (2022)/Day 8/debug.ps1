$executableFilePath = "./build/AOC_day8.exe"

if (!(Test-Path -Path $executableFilePath)) {
    Write-Host "ERROR: Can't find exe, building..." -ForegroundColor Red
    & "./build_and_run.bat"
    & "raddbg" $executableFilePath
} else {
    & "raddbg" $executableFilePath
}