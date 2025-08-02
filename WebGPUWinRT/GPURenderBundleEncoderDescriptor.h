#pragma once
#include "GPURenderBundleEncoderDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPURenderBundleEncoderDescriptor : GPURenderBundleEncoderDescriptorT<GPURenderBundleEncoderDescriptor>
    {
        GPURenderBundleEncoderDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
        winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUTextureFormat> ColorFormats();
        void ColorFormats(winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUTextureFormat> const& value);
        winrt::WebGPUWinRT::GPUTextureFormat DepthStencilFormat();
        void DepthStencilFormat(winrt::WebGPUWinRT::GPUTextureFormat const& value);
        uint32_t SampleCount();
        void SampleCount(uint32_t value);
        bool DepthReadOnly();
        void DepthReadOnly(bool value);
        bool StencilReadOnly();
        void StencilReadOnly(bool value);
    };
}
