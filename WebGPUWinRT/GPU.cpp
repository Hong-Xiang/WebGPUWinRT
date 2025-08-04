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
		WGPURequestAdapterOptions adapterOpts = {};
		adapterOpts.nextInChain = nullptr;
		//winrt::

		//struct UserData {
		//	WGPUAdapter adapter = nullptr;
		//	bool requestEnded = false;
		//};
		//auto userData{ std::make_shared<UserData>() };

		struct CallbackData {
			WGPUAdapter adapter{ nullptr };
			std::string errorMessage;

			// Create a manual-reset event using WIL.
			// This is the direct replacement for:
			// CreateEvent(nullptr, TRUE, FALSE, nullptr)
			wil::shared_event ready{ wil::EventOptions::ManualReset };
		};
		auto data = std::make_shared<CallbackData>();


		//if (data.status != 0)
		//{
		//	winrt::throw_hresult(E_FAIL, winrt::to_hstring(data.errorMessage));
		//}

		//co_return data.resultObject;

		//auto promise = std::make_shared<std::promise<WGPUAdapter>>();

		auto callback = [](WGPURequestAdapterStatus status, WGPUAdapter adapter, WGPUStringView message, void* userdata, void* _) {
			auto* data = static_cast<CallbackData*>(userdata);

			auto p = static_cast<std::promise<WGPUAdapter>*>(userdata);
			if (status == WGPURequestAdapterStatus_Success)
			{
				std::cout << "Got adapter in async using resume background using event" << std::endl;
				data->adapter = adapter;
			}
			else
			{
				data->errorMessage = interop::to(message);
			}
			data->ready.SetEvent();
			};

		wgpuInstanceRequestAdapter(handle, &adapterOpts, {
			.callback = callback,
			.userdata1 = data.get(),
			});

		co_await winrt::resume_on_signal(data->ready.get());

		if (data->adapter == nullptr)
		{
			auto error_message = winrt::to_hstring(data->errorMessage);
			throw winrt::hresult_error(E_FAIL, error_message);
		}
		else {
			co_return make<implementation::GPUAdapter>(data->adapter);
		}
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
