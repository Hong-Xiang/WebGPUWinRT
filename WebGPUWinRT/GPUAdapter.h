#pragma once
#include "GPU.h"
#include "winrt/WebGPUWinRT.h"
#include "winrt/Windows.Foundation.Collections.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPUAdapter : implements<GPUAdapter, winrt::WebGPUWinRT::IGPUAdapter>
	{
		GPUAdapter(WGPUAdapter handle);

		winrt::WebGPUWinRT::GPUSupportedLimits Limits() const;
		winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUFeature> Features() const;
		winrt::WebGPUWinRT::GPUAdapterInfo Info() const;

		winrt::Windows::Foundation::IAsyncOperation<winrt::WebGPUWinRT::IGPUDevice> RequestDevice();
		winrt::Windows::Foundation::IAsyncOperation<winrt::WebGPUWinRT::IGPUDevice> RequestDevice(winrt::WebGPUWinRT::GPUDeviceDescriptor descriptor);

		WGPUAdapter handle{};
		WebGPUWinRT::GPU m_gpu{};
		~GPUAdapter();
	};
}
