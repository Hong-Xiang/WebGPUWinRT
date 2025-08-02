#pragma once
#include "GPUComputePipelineDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPUComputePipelineDescriptor : GPUComputePipelineDescriptorT<GPUComputePipelineDescriptor>
    {
        GPUComputePipelineDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
        winrt::WebGPUWinRT::IGPUPipelineLayout Layout();
        void Layout(winrt::WebGPUWinRT::IGPUPipelineLayout const& value);
        hstring EntryPoint();
        void EntryPoint(hstring const& value);
        winrt::WebGPUWinRT::IGPUShaderModule Module();
        void Module(winrt::WebGPUWinRT::IGPUShaderModule const& value);
    };
}
namespace winrt::WebGPUWinRT::factory_implementation
{
    struct GPUComputePipelineDescriptor : GPUComputePipelineDescriptorT<GPUComputePipelineDescriptor, implementation::GPUComputePipelineDescriptor>
    {
    };
}
