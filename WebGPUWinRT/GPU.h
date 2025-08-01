#pragma once
#include "GPU.g.h"
#include "webgpu/wgpu.h"
#include "winrt/WebGPUWinRT.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPU : GPUT<GPU>
	{
		GPU();
        winrt::WebGPUWinRT::IGPUAdapter RequestAdapter();

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
