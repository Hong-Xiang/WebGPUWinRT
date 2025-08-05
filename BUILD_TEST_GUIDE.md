# WebGPU WinRT Development Commands

Essential build/test commands for WebGPU WinRT development cycle.

## Quick Development Loop

### Build (iterative development)
```powershell
& "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\amd64\MSBuild.exe" WebGPUWinRTTests\WebGPUWinRTTests.csproj -p:Platform=x64 -p:Configuration=Debug -v:minimal
```

### Test
```powershell
& "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\Common7\IDE\CommonExtensions\Microsoft\TestWindow\vstest.console.exe" "D:\WebGPUWinRT\build\x64\Debug\WebGPUWinRTTests\bin\WebGPUWinRTTests.dll" --Platform:x64
```

### Build + Test (one command)
```powershell
& "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\amd64\MSBuild.exe" WebGPUWinRTTests\WebGPUWinRTTests.csproj -p:Platform=x64 -p:Configuration=Debug -v:minimal && & "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\Common7\IDE\CommonExtensions\Microsoft\TestWindow\vstest.console.exe" "D:\WebGPUWinRT\build\x64\Debug\WebGPUWinRTTests\bin\WebGPUWinRTTests.dll" --Platform:x64
```

## Clean Build (when needed)
```powershell
& "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\amd64\MSBuild.exe" WebGPUWinRTTests\WebGPUWinRTTests.csproj -p:Platform=x64 -p:Configuration=Debug -t:Clean
```

## Build C++ Only
```powershell
& "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\amd64\MSBuild.exe" WebGPUWinRT\WebGPUWinRT.vcxproj -p:Platform=x64 -p:Configuration=Debug
```

## Notes
- All commands run from WebGPUWinRT root directory
- Dependencies auto-copy via project configuration
- Use PowerShell terminal
