#pragma once
#include "webgpu/wgpu.h"
#include "winrt/WebGPUWinRT.h"
#include "winrt/Windows.Foundation.Collections.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPUCommandEncoder : implements<GPUCommandEncoder, winrt::WebGPUWinRT::IGPUCommandEncoder>
	{
		GPUCommandEncoder(WGPUCommandEncoder handle);
		~GPUCommandEncoder();
		WGPUCommandEncoder handle{ nullptr };
		
		// Properties
		winrt::hstring Label();
		
		// Methods
		winrt::WebGPUWinRT::IGPUComputePassEncoder BeginComputePass();
		winrt::WebGPUWinRT::IGPUComputePassEncoder BeginComputePassWithDescriptor(winrt::WebGPUWinRT::GPUComputePassDescriptor descriptor);
		winrt::WebGPUWinRT::IGPURenderPassEncoder BeginRenderPass(winrt::WebGPUWinRT::GPURenderPassDescriptor descriptor);
		
		void CopyBufferToBuffer(winrt::WebGPUWinRT::IGPUBuffer source, uint64_t sourceOffset, 
							   winrt::WebGPUWinRT::IGPUBuffer destination, uint64_t destinationOffset, uint64_t size);
		void CopyBufferToTexture(winrt::WebGPUWinRT::IGPUBuffer source, winrt::WebGPUWinRT::IGPUTexture destination, 
								winrt::WebGPUWinRT::GPUExtent3D copySize);
		void CopyTextureToBuffer(winrt::WebGPUWinRT::IGPUTexture source, winrt::WebGPUWinRT::IGPUBuffer destination, 
								winrt::WebGPUWinRT::GPUExtent3D copySize);
		void CopyTextureToTexture(winrt::WebGPUWinRT::IGPUTexture source, winrt::WebGPUWinRT::IGPUTexture destination, 
								 winrt::WebGPUWinRT::GPUExtent3D copySize);
		void ResolveQuerySet(winrt::WebGPUWinRT::IGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, 
							winrt::WebGPUWinRT::IGPUBuffer destination, uint64_t destinationOffset);
		
		winrt::WebGPUWinRT::IGPUCommandBuffer Finish();
		winrt::WebGPUWinRT::IGPUCommandBuffer FinishWithDescriptor(winrt::WebGPUWinRT::GPUCommandBufferDescriptor descriptor);
	};
}
