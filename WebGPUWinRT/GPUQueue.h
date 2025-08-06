#pragma once
#include "webgpu/wgpu.h"
#include "winrt/WebGPUWinRT.h"
#include "winrt/Windows.Foundation.Collections.h"
#include "winrt/Windows.Storage.Streams.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPUQueue : implements<GPUQueue, winrt::WebGPUWinRT::IGPUQueue>
	{
		GPUQueue(WGPUQueue handle);
		~GPUQueue();
		WGPUQueue handle{ nullptr };
		
		// Properties
		winrt::hstring Label();
		
		// Methods
		void Submit(winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::IGPUCommandBuffer> commandBuffers);
		winrt::Windows::Foundation::IAsyncAction OnSubmittedWorkDone();
		void WriteBuffer(winrt::WebGPUWinRT::IGPUBuffer buffer, uint64_t bufferOffset, 
						winrt::Windows::Storage::Streams::IBuffer data, uint64_t dataOffset, uint64_t size);
		void WriteTexture(winrt::WebGPUWinRT::IGPUTexture destination, 
						 winrt::Windows::Storage::Streams::IBuffer data, winrt::WebGPUWinRT::GPUExtent3D size);
	};
}
