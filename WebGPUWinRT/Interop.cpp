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

	WGPUIndexFormat from(winrt::WebGPUWinRT::GPUIndexFormat format) {
		switch (format) {
		case winrt::WebGPUWinRT::GPUIndexFormat::Uint16:
			return WGPUIndexFormat_Uint16;
		case winrt::WebGPUWinRT::GPUIndexFormat::Uint32:
			return WGPUIndexFormat_Uint32;
		default:
			return WGPUIndexFormat_Uint16;
		}
	}

	WGPUShaderModuleDescriptor from(winrt::WebGPUWinRT::GPUShaderModuleDescriptor descriptor) {
		auto labelStr = winrt::to_string(descriptor.Label);
		auto codeStr = winrt::to_string(descriptor.Code);

		auto result = WGPUShaderModuleDescriptor{};
		result.label = labelStr.c_str();

		// Create WGSL descriptor
		WGPUShaderSourceWGSL wgslDesc{};
		wgslDesc.chain.sType = WGPUSType_ShaderSourceWGSL;
		wgslDesc.code = { .data = codeStr.c_str(), .length = codeStr.length() };
		result.nextInChain = reinterpret_cast<WGPUChainedStruct*>(&wgslDesc);

		return result;
	}

	WGPUBufferDescriptor from(winrt::WebGPUWinRT::GPUBufferDescriptor descriptor) {
		auto labelStr = winrt::to_string(descriptor.Label);
		auto result = WGPUBufferDescriptor{};
		result.label = labelStr.c_str();
		result.size = descriptor.Size;
		result.usage = from(descriptor.Usage);
		result.mappedAtCreation = descriptor.MappedAtCreation;
		return result;
	}

	WGPUPipelineLayoutDescriptor from(winrt::WebGPUWinRT::GPUPipelineLayoutDescriptor descriptor) {
		auto labelStr = winrt::to_string(descriptor.Label());
		auto result = WGPUPipelineLayoutDescriptor{};
		result.label = labelStr.c_str();

		// For Hello Triangle, we'll start with empty bind group layouts
		result.bindGroupLayoutCount = 0;
		result.bindGroupLayouts = nullptr;

		return result;
	}
	WGPUBufferUsage from(winrt::WebGPUWinRT::GPUBufferUsage usage) {
		return static_cast<WGPUBufferUsage>(usage);
	}

	WGPURenderPipelineDescriptor from(winrt::WebGPUWinRT::GPURenderPipelineDescriptor descriptor) {
		auto labelStr = winrt::to_string(descriptor.Label());
		auto result = WGPURenderPipelineDescriptor{};
		result.label = labelStr.c_str();

		// Convert layout
		if (descriptor.Layout()) {
			auto layoutImpl = descriptor.Layout().as<implementation::GPUPipelineLayout>();
			result.layout = layoutImpl->handle;
		}

		// Convert vertex state
		result.vertex = from(descriptor.Vertex());

		// Convert primitive state
		result.primitive = from(descriptor.Primitive());

		// Convert fragment state  
		auto fragmentState = from(descriptor.Fragment());
		result.fragment = &fragmentState;

		return result;
	}

	WGPUVertexState from(winrt::WebGPUWinRT::GPUVertexState state) {
		auto entryPointStr = winrt::to_string(state.EntryPoint);
		auto result = WGPUVertexState{};
		result.entryPoint = entryPointStr.c_str();

		if (state.Module) {
			auto moduleImpl = state.Module.get_self<implementation::GPUShaderModule>();
			result.module = moduleImpl->handle;
		}

		// Buffers will be added later
		result.bufferCount = 0;
		result.buffers = nullptr;

		return result;
	}

	WGPUFragmentState from(winrt::WebGPUWinRT::GPUFragmentState state) {
		auto entryPointStr = winrt::to_string(state.EntryPoint);
		auto result = WGPUFragmentState{};
		result.entryPoint = entryPointStr.c_str();

		if (state.Module) {
			auto moduleImpl = state.Module.as<implementation::GPUShaderModule>();
			result.module = moduleImpl->handle;
		}

		// Targets will be added later
		result.targetCount = 0;
		result.targets = nullptr;

		return result;
	}

	WGPUPrimitiveState from(winrt::WebGPUWinRT::GPUPrimitiveState state) {
		auto result = WGPUPrimitiveState{};

		// Convert topology
		switch (state.Topology) {
		case winrt::WebGPUWinRT::GPUPrimitiveTopology::PointList:
			result.topology = WGPUPrimitiveTopology_PointList;
			break;
		case winrt::WebGPUWinRT::GPUPrimitiveTopology::LineList:
			result.topology = WGPUPrimitiveTopology_LineList;
			break;
		case winrt::WebGPUWinRT::GPUPrimitiveTopology::LineStrip:
			result.topology = WGPUPrimitiveTopology_LineStrip;
			break;
		case winrt::WebGPUWinRT::GPUPrimitiveTopology::TriangleList:
			result.topology = WGPUPrimitiveTopology_TriangleList;
			break;
		case winrt::WebGPUWinRT::GPUPrimitiveTopology::TriangleStrip:
			result.topology = WGPUPrimitiveTopology_TriangleStrip;
			break;
		default:
			result.topology = WGPUPrimitiveTopology_TriangleList;
		}

		// Convert front face
		switch (state.FrontFace) {
		case winrt::WebGPUWinRT::GPUFrontFace::CCW:
			result.frontFace = WGPUFrontFace_CCW;
			break;
		case winrt::WebGPUWinRT::GPUFrontFace::CW:
			result.frontFace = WGPUFrontFace_CW;
			break;
		default:
			result.frontFace = WGPUFrontFace_CCW;
		}

		// Convert cull mode
		switch (state.CullMode) {
		case winrt::WebGPUWinRT::GPUCullMode::None:
			result.cullMode = WGPUCullMode_None;
			break;
		case winrt::WebGPUWinRT::GPUCullMode::Front:
			result.cullMode = WGPUCullMode_Front;
			break;
		case winrt::WebGPUWinRT::GPUCullMode::Back:
			result.cullMode = WGPUCullMode_Back;
			break;
		default:
			result.cullMode = WGPUCullMode_None;
		}

		result.unclippedDepth = state.UnclippedDepth;

		return result;
	}

	WGPURenderPassDescriptor from(winrt::WebGPUWinRT::GPURenderPassDescriptor descriptor) {
		auto labelStr = winrt::to_string(descriptor.Label());
		auto result = WGPURenderPassDescriptor{};
		result.label = labelStr.c_str();

		// Basic implementation - will be completed when we have proper color attachments
		// For now, just return empty descriptor
		result.colorAttachmentCount = 0;
		result.colorAttachments = nullptr;
		result.depthStencilAttachment = nullptr;

		return result;
	}

	WGPUCommandBufferDescriptor from(winrt::WebGPUWinRT::GPUCommandBufferDescriptor descriptor) {
		auto result = WGPUCommandBufferDescriptor{};
		auto labelStr = winrt::to_string(descriptor.Label);
		result.label = labelStr.c_str();
		return result;
	}
}
