#pragma once
#include "GPURenderPassColorAttachment.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPURenderPassColorAttachment : GPURenderPassColorAttachmentT<GPURenderPassColorAttachment>
    {
        GPURenderPassColorAttachment() = default;

        winrt::WebGPUWinRT::IGPUTextureView View();
        void View(winrt::WebGPUWinRT::IGPUTextureView const& value);
        uint32_t DepthSlice();
        void DepthSlice(uint32_t value);
        winrt::WebGPUWinRT::IGPUTextureView ResolveTarget();
        void ResolveTarget(winrt::WebGPUWinRT::IGPUTextureView const& value);
        winrt::WebGPUWinRT::GPULoadOp LoadOp();
        void LoadOp(winrt::WebGPUWinRT::GPULoadOp const& value);
        winrt::WebGPUWinRT::GPUStoreOp StoreOp();
        void StoreOp(winrt::WebGPUWinRT::GPUStoreOp const& value);
        winrt::WebGPUWinRT::GPUColor ClearValue();
        void ClearValue(winrt::WebGPUWinRT::GPUColor const& value);
    };
}
namespace winrt::WebGPUWinRT::factory_implementation
{
    struct GPURenderPassColorAttachment : GPURenderPassColorAttachmentT<GPURenderPassColorAttachment, implementation::GPURenderPassColorAttachment>
    {
    };
}
