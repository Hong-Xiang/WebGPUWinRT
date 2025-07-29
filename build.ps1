# Build WebGPUWinRT project

Write-Host "Building WebGPUWinRT..." -ForegroundColor Green

# Check if build directory exists
if (-not (Test-Path "build")) {
    Write-Host "Build directory not found. Please run configure.ps1 first." -ForegroundColor Red
    Write-Host "Run: .\configure.ps1" -ForegroundColor Yellow
    exit 1
}

Set-Location "build"

try {
    Write-Host "Building project with CMake..." -ForegroundColor Yellow
    
    cmake --build . --config Release
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host ""
        Write-Host "Build complete!" -ForegroundColor Green
        Write-Host ""
        Write-Host "To run the example:" -ForegroundColor Cyan
        Write-Host "  cd build\examples\Release" -ForegroundColor White
        Write-Host "  .\BasicExample.exe" -ForegroundColor White
        Write-Host ""
        Write-Host "Or use the run script:" -ForegroundColor Cyan
        Write-Host "  .\run-example.ps1" -ForegroundColor White
    } else {
        Write-Host "Build failed!" -ForegroundColor Red
        exit 1
    }
}
catch {
    Write-Host "Error during build: $_" -ForegroundColor Red
    exit 1
}
finally {
    # Return to original directory
    Set-Location ".."
}
