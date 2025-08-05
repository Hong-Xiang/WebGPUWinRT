#include "pch.h"
#include "Interop.h"
#include <codecvt>

namespace interop {

	std::string interop::to(WGPUStringView wgpu_string_view)
	{
		if (wgpu_string_view.length == WGPU_STRLEN) {
			return std::string(wgpu_string_view.data);
		}
		else {
			return std::string(wgpu_string_view.data, wgpu_string_view.length);
		}
	} // namespace interop

	winrt::WebGPUWinRT::GPUFeature interop::to(WGPUFeatureName feature)
	{
		// although currently the enum values are the same, we may change it in the future,
		// thus we use a explicit switch table here
		switch (feature) {
		case WGPUFeatureName_Undefined:
			return winrt::WebGPUWinRT::GPUFeature::Undefined;
		case WGPUFeatureName_DepthClipControl:
			return winrt::WebGPUWinRT::GPUFeature::DepthClipControl;
		case WGPUFeatureName_Depth32FloatStencil8:
			return winrt::WebGPUWinRT::GPUFeature::Depth32FloatStencil8;
		case WGPUFeatureName_TimestampQuery:
			return winrt::WebGPUWinRT::GPUFeature::TimestampQuery;
		case WGPUFeatureName_TextureCompressionBC:
			return winrt::WebGPUWinRT::GPUFeature::TextureCompressionBC;
		case WGPUFeatureName_TextureCompressionBCSliced3D:
			return winrt::WebGPUWinRT::GPUFeature::TextureCompressionBCSliced3D;
		case WGPUFeatureName_TextureCompressionETC2:
			return winrt::WebGPUWinRT::GPUFeature::TextureCompressionETC2;
		case WGPUFeatureName_TextureCompressionASTC:
			return winrt::WebGPUWinRT::GPUFeature::TextureCompressionASTC;
		case WGPUFeatureName_TextureCompressionASTCSliced3D:
			return winrt::WebGPUWinRT::GPUFeature::TextureCompressionASTCSliced3D;
		case WGPUFeatureName_IndirectFirstInstance:
			return winrt::WebGPUWinRT::GPUFeature::IndirectFirstInstance;
		case WGPUFeatureName_ShaderF16:
			return winrt::WebGPUWinRT::GPUFeature::ShaderF16;
		case WGPUFeatureName_RG11B10UfloatRenderable:
			return winrt::WebGPUWinRT::GPUFeature::RG11B10UfloatRenderable;
		case WGPUFeatureName_BGRA8UnormStorage:
			return winrt::WebGPUWinRT::GPUFeature::BGRA8UnormStorage;
		case WGPUFeatureName_Float32Filterable:
			return winrt::WebGPUWinRT::GPUFeature::Float32Filterable;
		case WGPUFeatureName_Float32Blendable:
			return winrt::WebGPUWinRT::GPUFeature::Float32Blendable;
		case WGPUFeatureName_ClipDistances:
			return winrt::WebGPUWinRT::GPUFeature::ClipDistances;
		case WGPUFeatureName_DualSourceBlending:
			return winrt::WebGPUWinRT::GPUFeature::DualSourceBlending;
		default:
			// force cast for unknown values
			return (winrt::WebGPUWinRT::GPUFeature)feature;
		}
	}

	winrt::WebGPUWinRT::GPUSupportedLimits interop::to(WGPULimits limits)
	{
		auto result = winrt::WebGPUWinRT::GPUSupportedLimits{
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


	winrt::WebGPUWinRT::GPUAdapterInfo interop::to(WGPUAdapterInfo info)
	{
		return winrt::WebGPUWinRT::GPUAdapterInfo{
			.Vendor = winrt::to_hstring(to(info.vendor)),
			.Architecture = winrt::to_hstring(to(info.architecture)),
			.Device = winrt::to_hstring(to(info.device)),
			.Description = winrt::to_hstring(to(info.description)),
		};
	}

	WGPUPowerPreference from(winrt::WebGPUWinRT::GPUPowerPreference powerPreference)
	{
		switch (powerPreference) {
		case winrt::WebGPUWinRT::GPUPowerPreference::LowPower:
			return WGPUPowerPreference_LowPower;
		case winrt::WebGPUWinRT::GPUPowerPreference::HighPerformance:
			return WGPUPowerPreference_HighPerformance;
		default:
			return WGPUPowerPreference_HighPerformance;
		}
	}

	WGPUBackendType from(winrt::WebGPUWinRT::GPUBackendType backendType)
	{
		switch (backendType) {
		case winrt::WebGPUWinRT::GPUBackendType::D3D12:
			return WGPUBackendType_D3D12;
		case winrt::WebGPUWinRT::GPUBackendType::Metal:
			return WGPUBackendType_Metal;
		case winrt::WebGPUWinRT::GPUBackendType::Vulkan:
			return WGPUBackendType_Vulkan;
		default:
			return WGPUBackendType_D3D12;
		}
	}

	WGPUStringView from(winrt::hstring str)
	{
		auto s8 = winrt::to_string(str);
		auto result = WGPUStringView{};
		result.data = s8.c_str();
		result.length = s8.length();
		return result;
	}

	WGPUDeviceDescriptor from(winrt::WebGPUWinRT::GPUDeviceDescriptor descriptor)
	{
		auto result = WGPUDeviceDescriptor{
			.label = from(descriptor.Label()),
		};
		return result;
	}

	WGPURequestAdapterOptions from(winrt::WebGPUWinRT::GPURequestAdapterOptions options) {
		auto result = WGPURequestAdapterOptions{};
		// TODO: mapping options
		result.backendType = from(options.BackendType);
		result.powerPreference = from(options.PowerPreference);
		result.featureLevel = WGPUFeatureLevel_Core;
		return result;
	}
}
