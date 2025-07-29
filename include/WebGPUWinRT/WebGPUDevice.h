#pragma once

#include <webgpu/webgpu.hpp>
#include <memory>
#include <string>

namespace WebGPUWinRT {

    /**
     * @brief Main WebGPU wrapper class for WinRT integration
     */
    class WebGPUDevice {
    public:
        WebGPUDevice();
        ~WebGPUDevice();

        /**
         * @brief Initialize the WebGPU device
         * @return true if initialization was successful
         */
        bool Initialize();

        /**
         * @brief Get the underlying WebGPU device
         * @return WebGPU device instance
         */
        wgpu::Device GetDevice() const { return device_; }

        /**
         * @brief Get the WebGPU instance
         * @return WebGPU instance
         */
        wgpu::Instance GetInstance() const { return instance_; }

        /**
         * @brief Check if the device is initialized
         * @return true if device is ready to use
         */
        bool IsInitialized() const { return initialized_; }

    private:
        wgpu::Instance instance_;
        wgpu::Device device_;
        wgpu::Adapter adapter_;
        bool initialized_ = false;

        bool CreateInstance();
        bool RequestAdapter();
        bool RequestDevice();
    };

} // namespace WebGPUWinRT
