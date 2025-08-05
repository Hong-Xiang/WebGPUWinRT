#include "pch.h"
#include "GPUDevice.h"
#include "Interop.h"
#include <iostream>
#include <vector>

namespace winrt::WebGPUWinRT::implementation
{
	GPUDevice::GPUDevice(WGPUDevice handle) : handle(handle) {
	}
	void GPUDevice::Close() {
		std::cout << "Close device" << std::endl;
		if (m_isClosed) {
			return;
		}
		if (handle)
		{
			std::cout << "Close device disposing" << std::endl;
			wgpuDeviceRelease(handle);
			handle = nullptr;
		}
	}
	GPUDevice::~GPUDevice() {
		std::cout << "Deconstructor device" << std::endl;
		if (handle)
		{
			std::cout << "Releasing device" << std::endl;
			wgpuDeviceRelease(handle);
			handle = nullptr;
		}
	}

	winrt::hstring GPUDevice::Label() {
		// Labels are not retrievable from native API, return empty for now
		return L"";
	}

	winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUFeature> GPUDevice::Features() {
		struct SupportedFeaturesWrapper {
			WGPUSupportedFeatures data;
			~SupportedFeaturesWrapper() {
				wgpuSupportedFeaturesFreeMembers(data);
			}
		};
		
		SupportedFeaturesWrapper featuresWrapper{};
		wgpuDeviceGetFeatures(handle, &featuresWrapper.data);
		
		std::vector<winrt::WebGPUWinRT::GPUFeature> features{ featuresWrapper.data.featureCount };
		for (auto i = 0; i < featuresWrapper.data.featureCount; i++) {
			features[i] = interop::to(featuresWrapper.data.features[i]);
		}
		
		return winrt::single_threaded_vector(std::move(features)).GetView();
	}

	GPUSupportedLimits GPUDevice::Limits() {
		WGPULimits limits = {};
		wgpuDeviceGetLimits(handle, &limits);
		return interop::to(limits);
	}

	GPUAdapterInfo GPUDevice::AdapterInfo() {
		// TODO: wgpuDeviceGetAdapterInfo is not implemented in wgpu-native yet
		// Return a default/empty adapter info for now
		throw winrt::hresult_not_implemented(L"GPUDevice::AdapterInfo - wgpuDeviceGetAdapterInfo not implemented in native library");
	}
}