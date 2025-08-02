#include "pch.h"
#include "GPUAdapter.h"
#include <iostream>
#include "Interop.h"


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
		throw hresult_not_implemented();
	}

	winrt::Windows::Foundation::IAsyncOperation<winrt::WebGPUWinRT::IGPUDevice> GPUAdapter::RequestDevice(winrt::WebGPUWinRT::GPUDeviceDescriptor descriptor) {
		throw hresult_not_implemented();
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
