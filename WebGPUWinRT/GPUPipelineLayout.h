#pragma once
#include "webgpu/wgpu.h"
#include "winrt/WebGPUWinRT.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPUPipelineLayout : implements<GPUPipelineLayout, winrt::WebGPUWinRT::IGPUPipelineLayout>
	{
		GPUPipelineLayout(WGPUPipelineLayout handle);
		~GPUPipelineLayout();
		WGPUPipelineLayout handle{ nullptr };
		
		// Properties
		winrt::hstring Label();
	};
}
