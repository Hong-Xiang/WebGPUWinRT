#pragma once
#include "webgpu/wgpu.h"
#include "winrt/WebGPUWinRT.h"
#include "winrt/Windows.Foundation.Collections.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPURenderPassEncoder : implements<GPURenderPassEncoder, winrt::WebGPUWinRT::IGPURenderPassEncoder>
	{
		GPURenderPassEncoder(WGPURenderPassEncoder handle);
		~GPURenderPassEncoder();
		WGPURenderPassEncoder handle{ nullptr };
		
		// Properties
		winrt::hstring Label();
		
		// Methods
		void SetPipeline(winrt::WebGPUWinRT::IGPURenderPipeline pipeline);
		void SetBindGroup(uint32_t index, winrt::WebGPUWinRT::IGPUBindGroup bindGroup);
		void SetBindGroupWithOffsets(uint32_t index, winrt::WebGPUWinRT::IGPUBindGroup bindGroup, 
									winrt::Windows::Foundation::Collections::IVectorView<uint32_t> dynamicOffsets);
		
		void SetVertexBuffer(uint32_t slot, winrt::WebGPUWinRT::IGPUBuffer buffer, uint64_t offset, uint64_t size);
		void SetIndexBuffer(winrt::WebGPUWinRT::IGPUBuffer buffer, winrt::WebGPUWinRT::GPUIndexFormat format, 
						   uint64_t offset, uint64_t size);
		
		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
		void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, 
						int32_t baseVertex, uint32_t firstInstance);
		void DrawIndirect(winrt::WebGPUWinRT::IGPUBuffer indirectBuffer, uint64_t indirectOffset);
		void DrawIndexedIndirect(winrt::WebGPUWinRT::IGPUBuffer indirectBuffer, uint64_t indirectOffset);
		
		void End();
	};
}
