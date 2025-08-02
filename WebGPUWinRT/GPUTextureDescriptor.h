#pragma once
#include "GPUTextureDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPUTextureDescriptor : GPUTextureDescriptorT<GPUTextureDescriptor>
    {
        GPUTextureDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
        winrt::WebGPUWinRT::GPUExtent3D Size();
        void Size(winrt::WebGPUWinRT::GPUExtent3D const& value);
        uint32_t MipLevelCount();
        void MipLevelCount(uint32_t value);
        uint32_t SampleCount();
        void SampleCount(uint32_t value);
        winrt::WebGPUWinRT::GPUTextureDimension Dimension();
        void Dimension(winrt::WebGPUWinRT::GPUTextureDimension const& value);
        winrt::WebGPUWinRT::GPUTextureFormat Format();
        void Format(winrt::WebGPUWinRT::GPUTextureFormat const& value);
        uint32_t Usage();
        void Usage(uint32_t value);
        winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUTextureFormat> ViewFormats();
        void ViewFormats(winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUTextureFormat> const& value);
    };
}
