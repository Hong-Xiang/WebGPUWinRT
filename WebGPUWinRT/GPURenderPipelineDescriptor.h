#pragma once
#include "GPURenderPipelineDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPURenderPipelineDescriptor : GPURenderPipelineDescriptorT<GPURenderPipelineDescriptor>
    {
        GPURenderPipelineDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
        winrt::WebGPUWinRT::IGPUPipelineLayout Layout();
        void Layout(winrt::WebGPUWinRT::IGPUPipelineLayout const& value);
    };
}
namespace winrt::WebGPUWinRT::factory_implementation
{
    struct GPURenderPipelineDescriptor : GPURenderPipelineDescriptorT<GPURenderPipelineDescriptor, implementation::GPURenderPipelineDescriptor>
    {
    };
}
