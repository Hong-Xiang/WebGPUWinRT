#include "pch.h"
#include "GPUAdapter.h"
#include <iostream>
#include "Interop.h"
#include "GPUDevice.h"
#include "GPUDeviceDescriptor.h"


namespace winrt::WebGPUWinRT::implementation
{
	using namespace winrt;

	GPUAdapter::GPUAdapter(WGPUAdapter handle) : handle(handle) {
	}

	winrt::Windows::Foundation::Collections::IVectorView<WebGPUWinRT::GPUFeature> GPUAdapter::Features() const {
		struct SupportedFeaturesWrapper {
			WGPUSupportedFeatures data;
			~SupportedFeaturesWrapper() {
				wgpuSupportedFeaturesFreeMembers(data);
			}
		};
		// TODO: unique_ptr wrapper?
		SupportedFeaturesWrapper featuresWrapper{ };
		wgpuAdapterGetFeatures(handle, &featuresWrapper.data);
		std::vector<winrt::WebGPUWinRT::GPUFeature> features{ featuresWrapper.data.featureCount };
		for (auto i = 0; i < featuresWrapper.data.featureCount; i++) {
			features[i] = interop::to(featuresWrapper.data.features[i]);
		}
		return single_threaded_vector(std::move(features)).GetView();
	}

	winrt::WebGPUWinRT::GPUAdapterInfo GPUAdapter::Info() const {
		WGPUAdapterInfo info = {};
		wgpuAdapterGetInfo(handle, &info);
		return interop::to(info);
	}

	winrt::Windows::Foundation::IAsyncOperation<winrt::WebGPUWinRT::IGPUDevice> GPUAdapter::RequestDevice() {
		std::cout << "RequestDevice" << std::endl;
		//throw hresult_not_implemented();
		return RequestDevice(make<winrt::WebGPUWinRT::implementation::GPUDeviceDescriptor>());
	}
	struct RequestDeviceTrait {
		using handle = WGPUAdapter;
		using option = WGPUDeviceDescriptor;
		using status = WGPURequestDeviceStatus;
		using data = WGPUDevice;
		using result = winrt::WebGPUWinRT::IGPUDevice;
		static void api(handle h, option* o, WGPURequestDeviceCallbackInfo c) {
			wgpuAdapterRequestDevice(h, o, c);
		};
		static result to(data d) {
			return make<implementation::GPUDevice>(d);
		}
	};

	winrt::Windows::Foundation::IAsyncOperation<winrt::WebGPUWinRT::IGPUDevice> GPUAdapter::RequestDevice(winrt::WebGPUWinRT::GPUDeviceDescriptor descriptor) {
		std::cout << "RequestDevice with option" << std::endl;
		return interop::from_async<RequestDeviceTrait>(handle, interop::from(descriptor));
	}



	winrt::WebGPUWinRT::GPUSupportedLimits GPUAdapter::Limits() const
	{
		WGPULimits limits{};
		wgpuAdapterGetLimits(handle, &limits);
		return interop::to(limits);
	}

	GPUAdapter::~GPUAdapter()
	{
		if (handle)
		{
			wgpuAdapterRelease(handle);
		}
	}
}
