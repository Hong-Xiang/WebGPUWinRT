#pragma once
#include "GPUPipelineLayoutDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPUPipelineLayoutDescriptor : GPUPipelineLayoutDescriptorT<GPUPipelineLayoutDescriptor>
    {
        GPUPipelineLayoutDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
        winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::IGPUBindGroupLayout> BindGroupLayouts();
        void BindGroupLayouts(winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::IGPUBindGroupLayout> const& value);
    };
}
namespace winrt::WebGPUWinRT::factory_implementation
{
    struct GPUPipelineLayoutDescriptor : GPUPipelineLayoutDescriptorT<GPUPipelineLayoutDescriptor, implementation::GPUPipelineLayoutDescriptor>
    {
    };
}
