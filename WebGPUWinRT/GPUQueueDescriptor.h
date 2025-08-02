#pragma once
#include "GPUQueueDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPUQueueDescriptor : GPUQueueDescriptorT<GPUQueueDescriptor>
    {
        GPUQueueDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
    };
}
