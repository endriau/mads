# Set the directory path
$directoryPath = "build"

# Remove build directory if it already exists.
if (Test-Path -Path $directoryPath)
{
    Remove-Item -Path "build" -Recurse -Force -Confirm:$false
}

# Create a new empty build directory.
New-Item -ItemType Directory -Force -Path $directoryPath

$cmakeZipUrl = "https://github.com/Kitware/CMake/releases/download/v3.28.3/cmake-3.28.3-windows-x86_64.zip"

# Set the URL of the portable cmake zip file, replace with the actual URL
$ninjaZipUrl = "https://github.com/ninja-build/ninja/releases/download/v1.10.0/ninja-win.zip"

# Set the destination paths
$cmakeDestinationPath = Join-Path -Path $directoryPath -ChildPath "cmake.zip"
$ninjaDestinationPath = Join-Path -Path $directoryPath -ChildPath "ninja-win.zip"

# Download the files
Invoke-WebRequest -Uri $cmakeZipUrl -OutFile $cmakeDestinationPath
Invoke-WebRequest -Uri $ninjaZipUrl -OutFile $ninjaDestinationPath

# Set the extraction locations
$cmakeExtractionPath = Join-Path -Path $directoryPath -ChildPath "cmake"
$ninjaExtractionPath = Join-Path -Path $directoryPath -ChildPath "."

# Extract the files
Expand-Archive -Path $cmakeDestinationPath -DestinationPath $cmakeExtractionPath
Expand-Archive -Path $ninjaDestinationPath -DestinationPath $ninjaExtractionPath

# Configure project with cmake
# Assuming that the cmake executable is directly in the extracted directory
$cmakePath = Join-Path -Path $cmakeExtractionPath -ChildPath "cmake-3.28.3-windows-x86_64/bin/cmake.exe"
$cmakePath = $cmakePath.Replace("\","/") # Convert to forward slashes

& $cmakePath -B build -S . -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DCMAKE_MAKE_PROGRAM="$PWD/$directoryPath/ninja"