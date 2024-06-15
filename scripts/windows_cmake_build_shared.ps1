# Set the build directory path
$directoryPath = "build"

# Set the expected location of cmake executable
$cmakeDir = "$directoryPath/cmake/cmake-3.28.3-windows-x86_64/bin"
$cmakePath = Join-Path -Path $cmakeDir -ChildPath "cmake.exe"

# Check if CMake has been downloaded and use that.
if (Test-Path $cmakePath)
{
    # Start building all targets.
    & $cmakePath --build $directoryPath --target all
}
else
{
    # If CMake can't be found alert user.
    Write-Host "CMake not found in $cmakePath. Please ensure CMake has been downloaded and extracted correctly."
}