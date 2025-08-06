#pragma once
#include "webgpu/wgpu.h"
#include "winrt/WebGPUWinRT.h"
#include "winrt/Windows.Foundation.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPUShaderModule : implements<GPUShaderModule, winrt::WebGPUWinRT::IGPUShaderModule>
	{
		GPUShaderModule(WGPUShaderModule handle);
		~GPUShaderModule();
		WGPUShaderModule handle{ nullptr };
		
		// Properties
		winrt::hstring Label();
		
		// Methods
		winrt::Windows::Foundation::IAsyncOperation<winrt::WebGPUWinRT::IGPUCompilationInfo> GetCompilationInfo();
	};
}
