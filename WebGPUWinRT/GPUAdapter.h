#pragma once
#include "GPU.h"
#include "winrt/WebGPUWinRT.h"
#include "winrt/Windows.Foundation.Collections.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPUAdapter : implements<GPUAdapter, winrt::WebGPUWinRT::IGPUAdapter>
	{
		GPUAdapter(const GPU& gpu);

		winrt::WebGPUWinRT::GPUSupportedLimits Limits() const;

		winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUFeature> Features() const;

		WGPUAdapter handle{};
		WebGPUWinRT::GPU m_gpu{};
		~GPUAdapter();
	};
}
