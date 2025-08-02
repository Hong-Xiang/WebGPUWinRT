#pragma once
#include "GPURenderPassDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPURenderPassDescriptor : GPURenderPassDescriptorT<GPURenderPassDescriptor>
    {
        GPURenderPassDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
        winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPURenderPassColorAttachment> ColorAttachments();
        void ColorAttachments(winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPURenderPassColorAttachment> const& value);
        winrt::WebGPUWinRT::GPURenderPassDepthStencilAttachment DepthStencilAttachment();
        void DepthStencilAttachment(winrt::WebGPUWinRT::GPURenderPassDepthStencilAttachment const& value);
        winrt::WebGPUWinRT::IGPUQuerySet OcclusionQuerySet();
        void OcclusionQuerySet(winrt::WebGPUWinRT::IGPUQuerySet const& value);
        uint64_t MaxDrawCount();
        void MaxDrawCount(uint64_t value);
    };
}
namespace winrt::WebGPUWinRT::factory_implementation
{
    struct GPURenderPassDescriptor : GPURenderPassDescriptorT<GPURenderPassDescriptor, implementation::GPURenderPassDescriptor>
    {
    };
}
