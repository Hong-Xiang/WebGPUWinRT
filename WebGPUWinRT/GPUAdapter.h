#pragma once
#include "GPUAdapter.g.h"
#include "GPU.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPUAdapter : GPUAdapterT<GPUAdapter>
	{
		GPUAdapter(const GPU& gpu);

		winrt::WebGPUWinRT::GPUSupportedLimits Limits() const;

		WGPUAdapter handle{};
		WebGPUWinRT::GPU m_gpu{};
		~GPUAdapter();

	private:
		void RequestAdapterInternal();
	};
}
