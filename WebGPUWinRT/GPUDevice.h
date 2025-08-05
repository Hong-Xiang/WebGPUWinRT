#pragma once
#include "webgpu/wgpu.h"
#include "winrt/WebGPUWinRT.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPUDevice : implements<GPUDevice, winrt::WebGPUWinRT::IGPUDevice, winrt::Windows::Foundation::IClosable>
	{
		GPUDevice(WGPUDevice handle);
		~GPUDevice();
		void Close();
		WGPUDevice handle{ nullptr };
		winrt::hstring Label();
		GPUSupportedLimits Limits();
	private:
		bool m_isClosed{ false };
	};
}

