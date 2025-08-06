#include "pch.h"
#include "GPUDevice.h"
#include "GPUQueue.h"
#include "GPUBuffer.h"
#include "GPUShaderModule.h"
#include "GPUPipelineLayout.h"
#include "GPURenderPipeline.h"
#include "GPUCommandEncoder.h"
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

	winrt::WebGPUWinRT::IGPUQueue GPUDevice::Queue() {
		if (!m_queue) {
			WGPUQueue nativeQueue = wgpuDeviceGetQueue(handle);
			if (nativeQueue) {
				m_queue = winrt::make<implementation::GPUQueue>(nativeQueue);
			}
		}
		return m_queue;
	}

	winrt::WebGPUWinRT::IGPUBuffer GPUDevice::CreateBuffer(winrt::WebGPUWinRT::GPUBufferDescriptor descriptor) {
		WGPUBufferDescriptor nativeDesc = interop::from(descriptor);
		WGPUBuffer nativeBuffer = wgpuDeviceCreateBuffer(handle, &nativeDesc);
		if (!nativeBuffer) {
			throw winrt::hresult_error(E_FAIL, L"Failed to create buffer");
		}
		return winrt::make<implementation::GPUBuffer>(nativeBuffer);
	}

	winrt::WebGPUWinRT::IGPUShaderModule GPUDevice::CreateShaderModule(winrt::WebGPUWinRT::GPUShaderModuleDescriptor descriptor) {
		WGPUShaderModuleDescriptor nativeDesc = interop::from(descriptor);
		WGPUShaderModule nativeModule = wgpuDeviceCreateShaderModule(handle, &nativeDesc);
		if (!nativeModule) {
			throw winrt::hresult_error(E_FAIL, L"Failed to create shader module");
		}
		return winrt::make<implementation::GPUShaderModule>(nativeModule);
	}

	winrt::WebGPUWinRT::IGPUPipelineLayout GPUDevice::CreatePipelineLayout(winrt::WebGPUWinRT::GPUPipelineLayoutDescriptor descriptor) {
		WGPUPipelineLayoutDescriptor nativeDesc = interop::from(descriptor);
		WGPUPipelineLayout nativeLayout = wgpuDeviceCreatePipelineLayout(handle, &nativeDesc);
		if (!nativeLayout) {
			throw winrt::hresult_error(E_FAIL, L"Failed to create pipeline layout");
		}
		return winrt::make<implementation::GPUPipelineLayout>(nativeLayout);
	}

	winrt::WebGPUWinRT::IGPURenderPipeline GPUDevice::CreateRenderPipeline(winrt::WebGPUWinRT::GPURenderPipelineDescriptor descriptor) {
		WGPURenderPipelineDescriptor nativeDesc = interop::from(descriptor);
		WGPURenderPipeline nativePipeline = wgpuDeviceCreateRenderPipeline(handle, &nativeDesc);
		if (!nativePipeline) {
			throw winrt::hresult_error(E_FAIL, L"Failed to create render pipeline");
		}
		return winrt::make<implementation::GPURenderPipeline>(nativePipeline);
	}

	winrt::WebGPUWinRT::IGPUCommandEncoder GPUDevice::CreateCommandEncoder() {
		WGPUCommandEncoder nativeEncoder = wgpuDeviceCreateCommandEncoder(handle, nullptr);
		if (!nativeEncoder) {
			throw winrt::hresult_error(E_FAIL, L"Failed to create command encoder");
		}
		return winrt::make<implementation::GPUCommandEncoder>(nativeEncoder);
	}
}