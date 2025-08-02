#pragma once
#include "GPUExternalTextureDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPUExternalTextureDescriptor : GPUExternalTextureDescriptorT<GPUExternalTextureDescriptor>
    {
        GPUExternalTextureDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
    };
}
