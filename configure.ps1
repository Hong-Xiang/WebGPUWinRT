# Configure WebGPUWinRT with WebGPU-native backend using MSVC

Write-Host "Configuring WebGPUWinRT with WebGPU-native backend using MSVC..." -ForegroundColor Green

# Create build directory
if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
}

Set-Location "build"

try {
    # Configure with CMake using WGPU backend and precompiled binaries
    Write-Host "Running CMake configuration..." -ForegroundColor Yellow
    
    cmake .. `
        -DWEBGPU_BACKEND=WGPU `
        -DWEBGPU_BUILD_FROM_SOURCE=OFF `
        -DWEBGPU_LINK_TYPE=SHARED `
        -DCMAKE_BUILD_TYPE=Release
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host ""
        Write-Host "Configuration complete!" -ForegroundColor Green
        Write-Host ""
        Write-Host "To build the project, run:" -ForegroundColor Cyan
        Write-Host "  .\build.ps1" -ForegroundColor White
        Write-Host ""
        Write-Host "Or manually:" -ForegroundColor Cyan
        Write-Host "  cd build" -ForegroundColor White
        Write-Host "  cmake --build . --config Release" -ForegroundColor White
        Write-Host ""
        Write-Host "To run the example after building:" -ForegroundColor Cyan
        Write-Host "  cd build\examples\Release" -ForegroundColor White
        Write-Host "  .\BasicExample.exe" -ForegroundColor White
    } else {
        Write-Host "CMake configuration failed!" -ForegroundColor Red
        exit 1
    }
}
catch {
    Write-Host "Error during configuration: $_" -ForegroundColor Red
    exit 1
}
finally {
    # Return to original directory
    Set-Location ".."
}
