# Set the build directory path
$buildDirectory = "build"

# Navigate inside the build directory.
Set-Location -Path $buildDirectory

# Set the expected location of ctest executable
$ctestDir = "cmake/cmake-3.28.3-windows-x86_64/bin"
$ctestPath = Join-Path -Path $ctestDir -ChildPath "ctest.exe"

# Check if CTest has been downloaded and use that.
if (Test-Path $ctestPath)
{
    # Run CTest with verbose mode on.
    & $ctestPath -V
}
else
{
    # If CTest can't be found alert user.
    Write-Host "CTest not found in $ctestPath. Please ensure CTest has been downloaded and extracted correctly"
}