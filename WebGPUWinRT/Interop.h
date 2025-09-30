#pragma once
#include <string>
#include <winrt/Windows.Foundation.h>
#include <future>
#include <wil/resource.h>
#include <iostream>

namespace interop {
	std::string to(WGPUStringView wgpu_string_view);
	winrt::WebGPUWinRT::GPUFeature to(WGPUFeatureName feature);
	winrt::WebGPUWinRT::GPUSupportedLimits to(WGPULimits limits);
	winrt::WebGPUWinRT::GPUAdapterInfo to(WGPUAdapterInfo limits);

	WGPURequestAdapterOptions from(winrt::WebGPUWinRT::GPURequestAdapterOptions options);
	WGPUDeviceDescriptor from(winrt::WebGPUWinRT::GPUDeviceDescriptor descriptor);
	WGPUBackendType from(winrt::WebGPUWinRT::GPUBackendType backendType);
	WGPUPowerPreference from(winrt::WebGPUWinRT::GPUPowerPreference powerPreference);
	WGPUStringView from(winrt::hstring str);
	WGPUStringView from(const std::string& str);
	WGPUIndexFormat from(winrt::WebGPUWinRT::GPUIndexFormat format);
	WGPUShaderModuleDescriptor from(winrt::WebGPUWinRT::GPUShaderModuleDescriptor descriptor);
	WGPUBufferDescriptor from(winrt::WebGPUWinRT::GPUBufferDescriptor descriptor);
	WGPUPipelineLayoutDescriptor from(winrt::WebGPUWinRT::GPUPipelineLayoutDescriptor descriptor);
	WGPURenderPipelineDescriptor from(winrt::WebGPUWinRT::GPURenderPipelineDescriptor descriptor);
	WGPURenderPassDescriptor from(winrt::WebGPUWinRT::GPURenderPassDescriptor descriptor);
	WGPUCommandBufferDescriptor from(winrt::WebGPUWinRT::GPUCommandBufferDescriptor descriptor);
	WGPUVertexState from(winrt::WebGPUWinRT::GPUVertexState state);
	WGPUFragmentState from(winrt::WebGPUWinRT::GPUFragmentState state);
	WGPUPrimitiveState from(winrt::WebGPUWinRT::GPUPrimitiveState state);
	WGPUBufferUsage from(winrt::WebGPUWinRT::GPUBufferUsage usage);

	template<typename T>
	winrt::Windows::Foundation::IAsyncOperation<typename T::result> from_async(
		typename T::handle source,
		typename T::option option) {
		struct CallbackData {
			typename T::data result{ nullptr };
			std::string errorMessage;
			wil::shared_event ready{ wil::EventOptions::ManualReset };
		};
		auto data = std::make_shared<CallbackData>();
		auto callback = [](typename T::status status, typename T::data adapter, WGPUStringView message, void* userdata, void*) {
			auto* data = static_cast<CallbackData*>(userdata);
			if (status == 1)
			{
				std::cout << "Got adapter g " << std::endl;
				data->result = adapter;
			}
			else
			{
				data->errorMessage = interop::to(message);
			}
			data->ready.SetEvent();
			};

		T::api(source, &option, { .callback = callback, .userdata1 = data.get() });

		co_await winrt::resume_on_signal(data->ready.get());

		if (data->result == nullptr)
		{
			auto error_message = winrt::to_hstring(data->errorMessage);
			throw winrt::hresult_error(E_FAIL, error_message);
		}
		else {
			co_return T::to(data->result);
		}

	};
} // namespace interop
