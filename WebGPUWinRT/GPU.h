#pragma once
#include "GPU.g.h"
#include "webgpu/wgpu.h"
#include "winrt/WebGPUWinRT.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPU : GPUT<GPU>
	{
		GPU();
		winrt::Windows::Foundation::IAsyncOperation<winrt::WebGPUWinRT::IGPUAdapter> RequestAdapter();
		winrt::Windows::Foundation::IAsyncOperation<winrt::WebGPUWinRT::IGPUAdapter> RequestAdapter(winrt::WebGPUWinRT::GPURequestAdapterOptions options);

		WGPUInstance handle{};
		~GPU();
	};
}
namespace winrt::WebGPUWinRT::factory_implementation
{
	struct GPU : GPUT<GPU, implementation::GPU>
	{
	};
}
