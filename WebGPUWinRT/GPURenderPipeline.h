#pragma once
#include "webgpu/wgpu.h"
#include "winrt/WebGPUWinRT.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPURenderPipeline : implements<GPURenderPipeline, winrt::WebGPUWinRT::IGPURenderPipeline>
	{
		GPURenderPipeline(WGPURenderPipeline handle);
		~GPURenderPipeline();
		WGPURenderPipeline handle{ nullptr };
		
		// Properties
		winrt::hstring Label();
		
		// Methods
		winrt::WebGPUWinRT::IGPUBindGroupLayout GetBindGroupLayout(uint32_t index);
	};
}
