#pragma once
#include "webgpu/wgpu.h"
#include "winrt/WebGPUWinRT.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPUCommandBuffer : implements<GPUCommandBuffer, winrt::WebGPUWinRT::IGPUCommandBuffer>
	{
		GPUCommandBuffer(WGPUCommandBuffer handle);
		~GPUCommandBuffer();
		WGPUCommandBuffer handle{ nullptr };
		
		// Properties
		winrt::hstring Label();
	};
}
