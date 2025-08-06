#pragma once
#include "webgpu/wgpu.h"
#include "winrt/WebGPUWinRT.h"
#include "winrt/Windows.Foundation.Collections.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPUDevice : implements<GPUDevice, winrt::WebGPUWinRT::IGPUDevice, winrt::Windows::Foundation::IClosable>
	{
		GPUDevice(WGPUDevice handle);
		~GPUDevice();
		void Close();
		WGPUDevice handle{ nullptr };
		
		// Properties
		winrt::hstring Label();
		winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUFeature> Features();
		GPUSupportedLimits Limits();
		GPUAdapterInfo AdapterInfo();
		winrt::WebGPUWinRT::IGPUQueue Queue();
		
		// Resource creation methods
		winrt::WebGPUWinRT::IGPUBuffer CreateBuffer(winrt::WebGPUWinRT::GPUBufferDescriptor descriptor);
		winrt::WebGPUWinRT::IGPUShaderModule CreateShaderModule(winrt::WebGPUWinRT::GPUShaderModuleDescriptor descriptor);
		winrt::WebGPUWinRT::IGPUPipelineLayout CreatePipelineLayout(winrt::WebGPUWinRT::GPUPipelineLayoutDescriptor descriptor);
		winrt::WebGPUWinRT::IGPURenderPipeline CreateRenderPipeline(winrt::WebGPUWinRT::GPURenderPipelineDescriptor descriptor);
		winrt::WebGPUWinRT::IGPUCommandEncoder CreateCommandEncoder();
		
	private:
		bool m_isClosed{ false };
		winrt::WebGPUWinRT::IGPUQueue m_queue{ nullptr };
	};
}

