# Clean WebGPUWinRT build artifacts

Write-Host "Cleaning WebGPUWinRT build artifacts..." -ForegroundColor Green

$pathsToClean = @(
    "build",
    "out"
)

foreach ($path in $pathsToClean) {
    if (Test-Path $path) {
        Write-Host "Removing: $path" -ForegroundColor Yellow
        try {
            Remove-Item -Path $path -Recurse -Force
            Write-Host "Successfully removed: $path" -ForegroundColor Green
        }
        catch {
            Write-Host "Failed to remove $path : $_" -ForegroundColor Red
        }
    } else {
        Write-Host "Path not found (already clean): $path" -ForegroundColor Gray
    }
}

Write-Host ""
Write-Host "Clean complete!" -ForegroundColor Green
Write-Host "To rebuild the project, run:" -ForegroundColor Cyan
Write-Host "  .\configure.ps1" -ForegroundColor White
Write-Host "  .\build.ps1" -ForegroundColor White
