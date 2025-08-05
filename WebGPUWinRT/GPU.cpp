#include "pch.h"
#include "GPU.h"
#include "GPU.g.cpp"
#include <iostream>
#include "Interop.h"
#include "GPUAdapter.h"
#include <winrt/Windows.Foundation.h>
#include <future>
#include <wil\resource.h>

namespace winrt::WebGPUWinRT::implementation
{
	GPU::GPU()
	{
		WGPUInstanceDescriptor desc = {};
		handle = wgpuCreateInstance(&desc);
	}

	winrt::Windows::Foundation::IAsyncOperation<winrt::WebGPUWinRT::IGPUAdapter> GPU::RequestAdapter()
	{
		winrt::WebGPUWinRT::GPURequestAdapterOptions options{};
		return	RequestAdapter(options);
	}

	winrt::Windows::Foundation::IAsyncOperation<winrt::WebGPUWinRT::IGPUAdapter> GPU::RequestAdapter(winrt::WebGPUWinRT::GPURequestAdapterOptions options)
	{
		struct RequestAdapterTrait {
			using handle = WGPUInstance;
			using option = WGPURequestAdapterOptions;
			using data = WGPUAdapter;
			using status = WGPURequestAdapterStatus;
			using result = winrt::WebGPUWinRT::IGPUAdapter;
			static void api(handle h, option* o, WGPURequestAdapterCallbackInfo c) {
				wgpuInstanceRequestAdapter(h, o, c);
			};
			static result to(data d) {
				return make<implementation::GPUAdapter>(d);
			}
		};


		co_return co_await interop::from_async<RequestAdapterTrait>(handle, interop::from(options));
	}

	GPU::~GPU()
	{
		if (handle)
		{
			wgpuInstanceRelease(handle);
		}
	}
}
