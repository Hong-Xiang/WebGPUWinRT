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
		
	private:
		bool m_isClosed{ false };
	};
}

