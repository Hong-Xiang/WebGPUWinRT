#pragma once
#include "GPUCommandBufferDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPUCommandBufferDescriptor : GPUCommandBufferDescriptorT<GPUCommandBufferDescriptor>
    {
        GPUCommandBufferDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
    };
}
