# Set the build directory path
$buildDirectory = "build"

# Navigate inside the build directory.
Set-Location -Path $buildDirectory

# Set the expected location of cpack executable
$ctestDir = "cmake/cmake-3.28.3-windows-x86_64/bin"
$cpackPath = Join-Path -Path $ctestDir -ChildPath "cpack.exe"

# Check if CPack has been downloaded and use that.
if (Test-Path $cpackPath)
{
    # Run CPack with verbose mode on.
    & $cpackPath -V
}
else
{
    # If CPack can't be found alert user.
    Write-Host "CPack not found in $cpackPath. Please ensure CPack has been downloaded and extracted correctly"
}