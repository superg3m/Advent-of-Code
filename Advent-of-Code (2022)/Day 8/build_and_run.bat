@echo off

SET CURRENTDIR="%cd%"

rem Set compiler options
if not exist .\build (
	mkdir .\build
) else (
	del /S /F /Q .\build
)
if not exist .\CKit (
	echo "missing CKit"
    git clone https://github.com/superg3m/CKit.git
) else (
	pushd .\Ckit
	git stash
	git stash drop
	git pull
	popd
)

pushd .\CKit
Powershell.exe -executionpolicy remotesigned -File ./build.ps1
popd

pushd .\build
cl /std:c11 /Fe:"AOC_Day8.exe" /Zi "..\Source\*.c" "..\CKit\build_cl\CKit.lib" "User32.lib">> "..\compilation_errors.txt" 2>nul
popd

call normalize_path.bat

pushd .\Source
"..\build\AOC_Day8.exe"
popd





