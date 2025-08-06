#include "pch.h"
#include "GPURenderPassEncoder.h"
#include "GPURenderPipeline.h"
#include "GPUBuffer.h"
#include "Interop.h"
#include <iostream>

namespace winrt::WebGPUWinRT::implementation
{
	GPURenderPassEncoder::GPURenderPassEncoder(WGPURenderPassEncoder handle) : handle(handle) {
		if (handle) {
			wgpuRenderPassEncoderReference(handle);
		}
	}
	
	GPURenderPassEncoder::~GPURenderPassEncoder() {
		if (handle) {
			wgpuRenderPassEncoderRelease(handle);
			handle = nullptr;
		}
	}

	winrt::hstring GPURenderPassEncoder::Label() {
		// Labels are not retrievable from native API, return empty for now
		return L"";
	}

	void GPURenderPassEncoder::SetPipeline(winrt::WebGPUWinRT::IGPURenderPipeline pipeline) {
		auto pipelineImpl = pipeline.as<implementation::GPURenderPipeline>();
		wgpuRenderPassEncoderSetPipeline(handle, pipelineImpl->handle);
	}

	void GPURenderPassEncoder::SetBindGroup(uint32_t index, winrt::WebGPUWinRT::IGPUBindGroup bindGroup) {
		// Basic implementation - will be completed when bind groups are implemented
		throw winrt::hresult_not_implemented(L"GPURenderPassEncoder::SetBindGroup - Not implemented yet");
	}

	void GPURenderPassEncoder::SetBindGroupWithOffsets(uint32_t index, winrt::WebGPUWinRT::IGPUBindGroup bindGroup, 
													   winrt::Windows::Foundation::Collections::IVectorView<uint32_t> dynamicOffsets) {
		// Basic implementation - will be completed when bind groups are implemented
		throw winrt::hresult_not_implemented(L"GPURenderPassEncoder::SetBindGroupWithOffsets - Not implemented yet");
	}

	void GPURenderPassEncoder::SetVertexBuffer(uint32_t slot, winrt::WebGPUWinRT::IGPUBuffer buffer, uint64_t offset, uint64_t size) {
		auto bufferImpl = buffer.as<implementation::GPUBuffer>();
		wgpuRenderPassEncoderSetVertexBuffer(handle, slot, bufferImpl->handle, offset, size);
	}

	void GPURenderPassEncoder::SetIndexBuffer(winrt::WebGPUWinRT::IGPUBuffer buffer, winrt::WebGPUWinRT::GPUIndexFormat format, 
											  uint64_t offset, uint64_t size) {
		auto bufferImpl = buffer.as<implementation::GPUBuffer>();
		WGPUIndexFormat nativeFormat = interop::from(format);
		wgpuRenderPassEncoderSetIndexBuffer(handle, bufferImpl->handle, nativeFormat, offset, size);
	}

	void GPURenderPassEncoder::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
		wgpuRenderPassEncoderDraw(handle, vertexCount, instanceCount, firstVertex, firstInstance);
	}

	void GPURenderPassEncoder::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, 
										   int32_t baseVertex, uint32_t firstInstance) {
		wgpuRenderPassEncoderDrawIndexed(handle, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
	}

	void GPURenderPassEncoder::DrawIndirect(winrt::WebGPUWinRT::IGPUBuffer indirectBuffer, uint64_t indirectOffset) {
		auto bufferImpl = indirectBuffer.as<implementation::GPUBuffer>();
		wgpuRenderPassEncoderDrawIndirect(handle, bufferImpl->handle, indirectOffset);
	}

	void GPURenderPassEncoder::DrawIndexedIndirect(winrt::WebGPUWinRT::IGPUBuffer indirectBuffer, uint64_t indirectOffset) {
		auto bufferImpl = indirectBuffer.as<implementation::GPUBuffer>();
		wgpuRenderPassEncoderDrawIndexedIndirect(handle, bufferImpl->handle, indirectOffset);
	}

	void GPURenderPassEncoder::End() {
		wgpuRenderPassEncoderEnd(handle);
	}
}
