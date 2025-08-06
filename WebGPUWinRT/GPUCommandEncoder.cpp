#include "pch.h"
#include "GPUCommandEncoder.h"
#include "GPURenderPassEncoder.h"
#include "GPUCommandBuffer.h"
#include "Interop.h"
#include <iostream>

namespace winrt::WebGPUWinRT::implementation
{
	GPUCommandEncoder::GPUCommandEncoder(WGPUCommandEncoder handle) : handle(handle) {
		if (handle) {
			wgpuCommandEncoderReference(handle);
		}
	}
	
	GPUCommandEncoder::~GPUCommandEncoder() {
		if (handle) {
			wgpuCommandEncoderRelease(handle);
			handle = nullptr;
		}
	}

	winrt::hstring GPUCommandEncoder::Label() {
		// Labels are not retrievable from native API, return empty for now
		return L"";
	}

	winrt::WebGPUWinRT::IGPUComputePassEncoder GPUCommandEncoder::BeginComputePass() {
		// Basic implementation - will be completed later
		throw winrt::hresult_not_implemented(L"GPUCommandEncoder::BeginComputePass - Not implemented yet");
	}

	winrt::WebGPUWinRT::IGPUComputePassEncoder GPUCommandEncoder::BeginComputePassWithDescriptor(winrt::WebGPUWinRT::GPUComputePassDescriptor descriptor) {
		// Basic implementation - will be completed later
		throw winrt::hresult_not_implemented(L"GPUCommandEncoder::BeginComputePassWithDescriptor - Not implemented yet");
	}

	winrt::WebGPUWinRT::IGPURenderPassEncoder GPUCommandEncoder::BeginRenderPass(winrt::WebGPUWinRT::GPURenderPassDescriptor descriptor) {
		// Convert descriptor to native
		WGPURenderPassDescriptor nativeDesc = interop::from(descriptor);
		
		WGPURenderPassEncoder nativeEncoder = wgpuCommandEncoderBeginRenderPass(handle, &nativeDesc);
		if (!nativeEncoder) {
			throw winrt::hresult_error(E_FAIL, L"Failed to begin render pass");
		}
		
		return winrt::make<implementation::GPURenderPassEncoder>(nativeEncoder);
	}

	void GPUCommandEncoder::CopyBufferToBuffer(winrt::WebGPUWinRT::IGPUBuffer source, uint64_t sourceOffset, 
											  winrt::WebGPUWinRT::IGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
		// Basic implementation - will be completed later
		throw winrt::hresult_not_implemented(L"GPUCommandEncoder::CopyBufferToBuffer - Not implemented yet");
	}

	void GPUCommandEncoder::CopyBufferToTexture(winrt::WebGPUWinRT::IGPUBuffer source, winrt::WebGPUWinRT::IGPUTexture destination, 
											   winrt::WebGPUWinRT::GPUExtent3D copySize) {
		// Basic implementation - will be completed later
		throw winrt::hresult_not_implemented(L"GPUCommandEncoder::CopyBufferToTexture - Not implemented yet");
	}

	void GPUCommandEncoder::CopyTextureToBuffer(winrt::WebGPUWinRT::IGPUTexture source, winrt::WebGPUWinRT::IGPUBuffer destination, 
											   winrt::WebGPUWinRT::GPUExtent3D copySize) {
		// Basic implementation - will be completed later
		throw winrt::hresult_not_implemented(L"GPUCommandEncoder::CopyTextureToBuffer - Not implemented yet");
	}

	void GPUCommandEncoder::CopyTextureToTexture(winrt::WebGPUWinRT::IGPUTexture source, winrt::WebGPUWinRT::IGPUTexture destination, 
												winrt::WebGPUWinRT::GPUExtent3D copySize) {
		// Basic implementation - will be completed later
		throw winrt::hresult_not_implemented(L"GPUCommandEncoder::CopyTextureToTexture - Not implemented yet");
	}

	void GPUCommandEncoder::ResolveQuerySet(winrt::WebGPUWinRT::IGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, 
										   winrt::WebGPUWinRT::IGPUBuffer destination, uint64_t destinationOffset) {
		// Basic implementation - will be completed later
		throw winrt::hresult_not_implemented(L"GPUCommandEncoder::ResolveQuerySet - Not implemented yet");
	}

	winrt::WebGPUWinRT::IGPUCommandBuffer GPUCommandEncoder::Finish() {
		WGPUCommandBuffer nativeCommandBuffer = wgpuCommandEncoderFinish(handle, nullptr);
		if (!nativeCommandBuffer) {
			throw winrt::hresult_error(E_FAIL, L"Failed to finish command encoder");
		}
		
		return winrt::make<implementation::GPUCommandBuffer>(nativeCommandBuffer);
	}

	winrt::WebGPUWinRT::IGPUCommandBuffer GPUCommandEncoder::FinishWithDescriptor(winrt::WebGPUWinRT::GPUCommandBufferDescriptor descriptor) {
		WGPUCommandBufferDescriptor nativeDesc = interop::from(descriptor);
		WGPUCommandBuffer nativeCommandBuffer = wgpuCommandEncoderFinish(handle, &nativeDesc);
		if (!nativeCommandBuffer) {
			throw winrt::hresult_error(E_FAIL, L"Failed to finish command encoder");
		}
		
		return winrt::make<implementation::GPUCommandBuffer>(nativeCommandBuffer);
	}
}
