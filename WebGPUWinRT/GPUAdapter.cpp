#include "pch.h"
#include "GPUAdapter.h"
#include "GPUAdapter.g.cpp"
#include <iostream>
#include "Interop.h"

namespace winrt::WebGPUWinRT::implementation
{
	GPUAdapter::GPUAdapter(const implementation::GPU& gpu) : m_gpu(gpu), handle(nullptr) {
		RequestAdapterInternal();
	}

	void GPUAdapter::RequestAdapterInternal() {
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
			winrt::get_self<implementation::GPU>(m_gpu)->handle,
			&adapterOpts,
			{
				.callback = onAdapterRequestEnded,
				.userdata1 = &userData,
			}
			);

		// Wait for the request to complete (blocking)
		while (!userData.requestEnded) {
			// You might want to add a timeout or use a different synchronization mechanism
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		handle = userData.adapter;
		if (handle == nullptr) {
			throw std::runtime_error("Failed to get GPUAdapter");
		}
	}


	winrt::WebGPUWinRT::GPUSupportedLimits GPUAdapter::Limits() const
	{
		WGPULimits limits{};
		wgpuAdapterGetLimits(handle, &limits);
		auto result = GPUSupportedLimits{
			.maxTextureDimension1D = limits.maxTextureDimension1D,
			.maxTextureDimension2D = limits.maxTextureDimension2D,
			.maxTextureDimension3D = limits.maxTextureDimension3D,
			.maxTextureArrayLayers = limits.maxTextureArrayLayers,
			.maxBindGroups = limits.maxBindGroups,
			.maxBindGroupsPlusVertexBuffers = limits.maxBindGroupsPlusVertexBuffers,
			.maxBindingsPerBindGroup = limits.maxBindingsPerBindGroup,
			.maxDynamicUniformBuffersPerPipelineLayout = limits.maxDynamicUniformBuffersPerPipelineLayout,
			.maxDynamicStorageBuffersPerPipelineLayout = limits.maxDynamicStorageBuffersPerPipelineLayout,
			.maxSampledTexturesPerShaderStage = limits.maxSampledTexturesPerShaderStage,
			.maxSamplersPerShaderStage = limits.maxSamplersPerShaderStage,
			.maxStorageBuffersPerShaderStage = limits.maxStorageBuffersPerShaderStage,
			.maxStorageTexturesPerShaderStage = limits.maxStorageTexturesPerShaderStage,
			.maxUniformBuffersPerShaderStage = limits.maxUniformBuffersPerShaderStage,
			.maxUniformBufferBindingSize = limits.maxUniformBufferBindingSize,
			.maxStorageBufferBindingSize = limits.maxStorageBufferBindingSize,
			.minUniformBufferOffsetAlignment = limits.minUniformBufferOffsetAlignment,
			.minStorageBufferOffsetAlignment = limits.minStorageBufferOffsetAlignment,
			.maxVertexBuffers = limits.maxVertexBuffers,
			.maxBufferSize = limits.maxBufferSize,
			.maxVertexAttributes = limits.maxVertexAttributes,
			.maxVertexBufferArrayStride = limits.maxVertexBufferArrayStride,
			.maxInterStageShaderVariables = limits.maxInterStageShaderVariables,
			.maxColorAttachments = limits.maxColorAttachments,
			.maxColorAttachmentBytesPerSample = limits.maxColorAttachmentBytesPerSample,
			.maxComputeWorkgroupStorageSize = limits.maxComputeWorkgroupStorageSize,
			.maxComputeInvocationsPerWorkgroup = limits.maxComputeInvocationsPerWorkgroup,
			.maxComputeWorkgroupSizeX = limits.maxComputeWorkgroupSizeX,
			.maxComputeWorkgroupSizeY = limits.maxComputeWorkgroupSizeY,
			.maxComputeWorkgroupSizeZ = limits.maxComputeWorkgroupSizeZ,
			.maxComputeWorkgroupsPerDimension = limits.maxComputeWorkgroupsPerDimension,
		};
		return result;
	}

	GPUAdapter::~GPUAdapter()
	{
		if (handle)
		{
			wgpuAdapterRelease(handle);
		}
	}
}
