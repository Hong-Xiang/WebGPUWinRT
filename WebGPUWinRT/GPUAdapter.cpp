#include "pch.h"
#include "GPUAdapter.h"
#include <iostream>
#include "Interop.h"


namespace winrt::WebGPUWinRT::implementation
{
	using namespace winrt;

	GPUAdapter::GPUAdapter(const implementation::GPU& gpu) : m_gpu(gpu), handle(nullptr) {
		WGPURequestAdapterOptions adapterOpts = {};
		adapterOpts.nextInChain = nullptr;

		struct UserData {
			WGPUAdapter adapter = nullptr;
			bool requestEnded = false;
		};
		UserData userData{};

		auto onAdapterRequestEnded = [](WGPURequestAdapterStatus status, WGPUAdapter adapter, WGPUStringView message, void* pUserData, void* _) {
			UserData& userData = *reinterpret_cast<UserData*>(pUserData);
			if (status == WGPURequestAdapterStatus_Success) {
				userData.adapter = adapter;
			}
			else {
				std::cout << "Could not get WebGPU adapter: " << interop::to_string(message) << std::endl;
			}
			userData.requestEnded = true;
			};

		wgpuInstanceRequestAdapter(
			gpu.handle,
			&adapterOpts,
			{
				.callback = onAdapterRequestEnded,
				.userdata1 = &userData,
			}
			);

		while (!userData.requestEnded) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		handle = userData.adapter;
		if (handle == nullptr) {
			throw std::runtime_error("Failed to get GPUAdapter");
		}
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


	winrt::WebGPUWinRT::GPUSupportedLimits GPUAdapter::Limits() const
	{
		WGPUAdapterInfo info = {};
		wgpuAdapterGetInfo(handle, &info);

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
