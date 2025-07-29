# Run the WebGPUWinRT basic example

Write-Host "Running WebGPUWinRT Basic Example..." -ForegroundColor Green

# Check if the example executable exists
$examplePath = "build\examples\Release\BasicExample.exe"

if (-not (Test-Path $examplePath)) {
    Write-Host "Example executable not found at: $examplePath" -ForegroundColor Red
    Write-Host ""
    Write-Host "Please build the project first:" -ForegroundColor Yellow
    Write-Host "  .\configure.ps1" -ForegroundColor White
    Write-Host "  .\build.ps1" -ForegroundColor White
    exit 1
}

try {
    Write-Host "Executing example..." -ForegroundColor Yellow
    Write-Host "----------------------------------------" -ForegroundColor Gray
    
    # Run the example
    & $examplePath
    
    Write-Host "----------------------------------------" -ForegroundColor Gray
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Example completed successfully!" -ForegroundColor Green
    } else {
        Write-Host "Example execution failed with exit code: $LASTEXITCODE" -ForegroundColor Red
        exit $LASTEXITCODE
    }
}
catch {
    Write-Host "Error running example: $_" -ForegroundColor Red
    exit 1
}
