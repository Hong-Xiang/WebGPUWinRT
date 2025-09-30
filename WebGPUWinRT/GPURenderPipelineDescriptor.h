#pragma once
#include "GPURenderPipelineDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPURenderPipelineDescriptor : GPURenderPipelineDescriptorT<GPURenderPipelineDescriptor>
    {
        GPURenderPipelineDescriptor() = default;

        hstring Label();
        void Label(hstring const& value);
        winrt::WebGPUWinRT::IGPUPipelineLayout Layout();
        void Layout(winrt::WebGPUWinRT::IGPUPipelineLayout const& value);
        winrt::WebGPUWinRT::GPUVertexState Vertex();
        void Vertex(winrt::WebGPUWinRT::GPUVertexState const& value);
        winrt::WebGPUWinRT::GPUPrimitiveState Primitive();
        void Primitive(winrt::WebGPUWinRT::GPUPrimitiveState const& value);
        winrt::WebGPUWinRT::GPUFragmentState Fragment();
        void Fragment(winrt::WebGPUWinRT::GPUFragmentState const& value);
    };
}
namespace winrt::WebGPUWinRT::factory_implementation
{
    struct GPURenderPipelineDescriptor : GPURenderPipelineDescriptorT<GPURenderPipelineDescriptor, implementation::GPURenderPipelineDescriptor>
    {
    };
}
