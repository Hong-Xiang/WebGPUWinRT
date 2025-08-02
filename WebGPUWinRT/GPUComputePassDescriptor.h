#pragma once
#include "GPUComputePassDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPUComputePassDescriptor : GPUComputePassDescriptorT<GPUComputePassDescriptor>
    {
        GPUComputePassDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
    };
}
