#include "WebGPUWinRT/WebGPUDevice.h"
#include <iostream>

int main() {
    std::cout << "WebGPU WinRT Basic Example" << std::endl;

    // Create and initialize WebGPU device
    WebGPUWinRT::WebGPUDevice webgpuDevice;
    
    if (!webgpuDevice.Initialize()) {
        std::cerr << "Failed to initialize WebGPU device!" << std::endl;
        return -1;
    }

    // Get device info
    auto device = webgpuDevice.GetDevice();
    if (device) {
        std::cout << "WebGPU device is ready!" << std::endl;
        
        // You can now use the device for WebGPU operations
        // For example, create buffers, textures, render pipelines, etc.
    }

    std::cout << "Example completed successfully!" << std::endl;
    return 0;
}
