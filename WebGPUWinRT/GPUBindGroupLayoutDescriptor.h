#pragma once
#include "GPUBindGroupLayoutDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPUBindGroupLayoutDescriptor : GPUBindGroupLayoutDescriptorT<GPUBindGroupLayoutDescriptor>
    {
        GPUBindGroupLayoutDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
        winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUBindGroupLayoutEntry> Entries();
        void Entries(winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUBindGroupLayoutEntry> const& value);
    };
}
namespace winrt::WebGPUWinRT::factory_implementation
{
    struct GPUBindGroupLayoutDescriptor : GPUBindGroupLayoutDescriptorT<GPUBindGroupLayoutDescriptor, implementation::GPUBindGroupLayoutDescriptor>
    {
    };
}
