# WebGPUWinRT
A WinRT Wrapper over WebGPU Native

## Overview
This project provides a C++ library that wraps WebGPU native functionality for use in Windows applications, specifically targeting WinRT integration.

## Prerequisites
- Visual Studio 2019 or later (with MSVC compiler)
- CMake 3.15 or later
- Git (for submodules)
- PowerShell 5.0 or later

### PowerShell Execution Policy
If you encounter issues running PowerShell scripts, you may need to adjust the execution policy:
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```
This allows local scripts to run while maintaining security for remote scripts.

## Building

### Quick Start (Windows)
1. Clone the repository with submodules:
   ```cmd
   git clone --recursive https://github.com/your-username/WebGPUWinRT.git
   cd WebGPUWinRT
   ```

2. Run the configuration script:
   ```powershell
   .\configure.ps1
   ```

3. Build the project:
   ```powershell
   .\build.ps1
   ```

4. Run the example:
   ```powershell
   .\run-example.ps1
   ```

### Manual Build
If you prefer manual configuration:

```cmd
mkdir build
cd build
cmake .. -DWEBGPU_BACKEND=WGPU -DWEBGPU_BUILD_FROM_SOURCE=OFF -DWEBGPU_LINK_TYPE=SHARED
cmake --build . --config Release
```

## Configuration Options

The project uses WebGPU-distribution which provides several configuration options:

- `WEBGPU_BACKEND`: Choose the WebGPU implementation
  - `WGPU` (default for native): Uses wgpu-native (Rust-based)
  - `DAWN`: Uses Google's Dawn implementation
  
- `WEBGPU_BUILD_FROM_SOURCE`: Whether to build from source
  - `OFF` (recommended): Downloads precompiled binaries
  - `ON`: Builds from source (requires additional dependencies)
  
- `WEBGPU_LINK_TYPE`: Linking type
  - `SHARED` (default): Dynamic linking
  - `STATIC`: Static linking

## Project Structure
```
WebGPUWinRT/
├── include/WebGPUWinRT/     # Public headers
├── src/                     # Implementation files
├── examples/                # Example applications
├── WebGPU-distribution/     # WebGPU implementation (submodule)
├── CMakeLists.txt          # Main CMake configuration
├── configure.ps1           # Windows configuration script
├── build.ps1              # Windows build script
├── run-example.ps1         # Windows example runner script
└── clean.ps1              # Windows clean script
```

## Usage

Include the main header in your code:
```cpp
#include "WebGPUWinRT/WebGPUDevice.h"

// Create and initialize WebGPU device
WebGPUWinRT::WebGPUDevice device;
if (device.Initialize()) {
    // Use the device for WebGPU operations
    auto webgpuDevice = device.GetDevice();
    // ... your WebGPU code here
}
```

## Dependencies
- [WebGPU-distribution](https://github.com/eliemichel/WebGPU-distribution): Unified WebGPU implementation
- WebGPU native headers and implementation (automatically fetched)
