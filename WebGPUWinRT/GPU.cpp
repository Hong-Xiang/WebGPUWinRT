#include "pch.h"
#include "GPU.h"
#include "GPU.g.cpp"
#include <iostream>
#include "Interop.h"
#include "GPUAdapter.h"
#include <winrt/Windows.Foundation.h>
#include <future>


namespace winrt::WebGPUWinRT::implementation
{
	GPU::GPU()
	{
		WGPUInstanceDescriptor desc = {};
		handle = wgpuCreateInstance(&desc);
	}

	winrt::Windows::Foundation::IAsyncOperation<winrt::WebGPUWinRT::IGPUAdapter> GPU::RequestAdapter()
	{
		WGPURequestAdapterOptions adapterOpts = {};
		adapterOpts.nextInChain = nullptr;
		//winrt::

		//struct UserData {
		//	WGPUAdapter adapter = nullptr;
		//	bool requestEnded = false;
		//};
		//auto userData{ std::make_shared<UserData>() };

		auto promise = std::make_shared<std::promise<WGPUAdapter>>();

		auto callback = [](WGPURequestAdapterStatus status, WGPUAdapter adapter, WGPUStringView message, void* userdata, void* _) {
			auto p = static_cast<std::promise<WGPUAdapter>*>(userdata);
			if (status == WGPURequestAdapterStatus_Success)
			{
				std::cout << "Got adapter in async using resume background" << std::endl;
				p->set_value(adapter);
			}
			else
			{
				p->set_exception(std::make_exception_ptr(std::runtime_error(interop::to(message))));
			}
			};

		wgpuInstanceRequestAdapter(handle, &adapterOpts, {
			.callback = callback,
			.userdata1 = promise.get(),
			});

		// TODO: use correct async implementation
		co_await winrt::resume_background();
		auto result = promise->get_future().get();
		co_return make<implementation::GPUAdapter>(result);
	}

	winrt::Windows::Foundation::IAsyncOperation<winrt::WebGPUWinRT::IGPUAdapter> GPU::RequestAdapter(winrt::WebGPUWinRT::GPURequestAdapterOptions options)
	{
		throw hresult_not_implemented();
	}


	GPU::~GPU()
	{
		if (handle)
		{
			wgpuInstanceRelease(handle);
		}
	}
}
