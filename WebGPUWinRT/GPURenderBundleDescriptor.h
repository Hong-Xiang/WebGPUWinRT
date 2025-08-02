#pragma once
#include "GPURenderBundleDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPURenderBundleDescriptor : GPURenderBundleDescriptorT<GPURenderBundleDescriptor>
    {
        GPURenderBundleDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
    };
}
