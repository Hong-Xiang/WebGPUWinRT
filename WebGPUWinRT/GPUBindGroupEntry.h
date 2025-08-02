#pragma once
#include "GPUBindGroupEntry.g.h"

namespace winrt::WebGPUWinRT::implementation
{
    struct GPUBindGroupEntry : GPUBindGroupEntryT<GPUBindGroupEntry>
    {
        GPUBindGroupEntry() = default;

        uint32_t Binding();
        void Binding(uint32_t value);
        winrt::WebGPUWinRT::IGPUBuffer Buffer();
        void Buffer(winrt::WebGPUWinRT::IGPUBuffer const& value);
        winrt::WebGPUWinRT::IGPUSampler Sampler();
        void Sampler(winrt::WebGPUWinRT::IGPUSampler const& value);
        winrt::WebGPUWinRT::IGPUTextureView TextureView();
        void TextureView(winrt::WebGPUWinRT::IGPUTextureView const& value);
    };
}
