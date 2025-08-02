#pragma once
#include "GPUBindGroupDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPUBindGroupDescriptor : GPUBindGroupDescriptorT<GPUBindGroupDescriptor>
    {
        GPUBindGroupDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
        winrt::WebGPUWinRT::IGPUBindGroupLayout Layout();
        void Layout(winrt::WebGPUWinRT::IGPUBindGroupLayout const& value);
        winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUBindGroupEntry> Entries();
        void Entries(winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUBindGroupEntry> const& value);
    };
}
namespace winrt::WebGPUWinRT::factory_implementation
{
    struct GPUBindGroupDescriptor : GPUBindGroupDescriptorT<GPUBindGroupDescriptor, implementation::GPUBindGroupDescriptor>
    {
    };
}
