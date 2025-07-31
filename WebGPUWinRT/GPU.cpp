#include "pch.h"
#include "GPU.h"
#include "GPU.g.cpp"
#include <iostream>
#include "GPUAdapter.h"

namespace winrt::WebGPUWinRT::implementation
{
	GPU::GPU()
	{
		WGPUInstanceDescriptor desc = {};
		handle = wgpuCreateInstance(&desc);
	}

	winrt::WebGPUWinRT::GPUAdapter GPU::RequestAdapter()
	{
		return make<implementation::GPUAdapter>(*this);
	}

	GPU::~GPU()
	{
		if (handle)
		{
			wgpuInstanceRelease(handle);
		}
	}
}
