#pragma once
#include "GPURenderPassDepthStencilAttachment.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPURenderPassDepthStencilAttachment : GPURenderPassDepthStencilAttachmentT<GPURenderPassDepthStencilAttachment>
    {
        GPURenderPassDepthStencilAttachment() = default;

        winrt::WebGPUWinRT::IGPUTextureView View();
        void View(winrt::WebGPUWinRT::IGPUTextureView const& value);
        winrt::WebGPUWinRT::GPULoadOp DepthLoadOp();
        void DepthLoadOp(winrt::WebGPUWinRT::GPULoadOp const& value);
        winrt::WebGPUWinRT::GPUStoreOp DepthStoreOp();
        void DepthStoreOp(winrt::WebGPUWinRT::GPUStoreOp const& value);
        float DepthClearValue();
        void DepthClearValue(float value);
        winrt::WebGPUWinRT::GPULoadOp StencilLoadOp();
        void StencilLoadOp(winrt::WebGPUWinRT::GPULoadOp const& value);
        winrt::WebGPUWinRT::GPUStoreOp StencilStoreOp();
        void StencilStoreOp(winrt::WebGPUWinRT::GPUStoreOp const& value);
        uint32_t StencilClearValue();
        void StencilClearValue(uint32_t value);
        bool DepthReadOnly();
        void DepthReadOnly(bool value);
        bool StencilReadOnly();
        void StencilReadOnly(bool value);
    };
}
namespace winrt::WebGPUWinRT::factory_implementation
{
    struct GPURenderPassDepthStencilAttachment : GPURenderPassDepthStencilAttachmentT<GPURenderPassDepthStencilAttachment, implementation::GPURenderPassDepthStencilAttachment>
    {
    };
}
