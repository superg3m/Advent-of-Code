# This build file has been generated by c_build
if ($PSVersionTable.Platform -eq "Unix") {
    Set-Alias python python3
}

. ./c_build/validate_temp_files.ps1 $MyInvocation.MyCommand.Name

Push-Location  "./c_build"
git fetch origin -q
git reset --hard origin/main -q
git pull -q
Pop-Location

python -B -m c_build_script --build_type "debug"
python -B -m c_build_script --execution_type "DEBUG"
