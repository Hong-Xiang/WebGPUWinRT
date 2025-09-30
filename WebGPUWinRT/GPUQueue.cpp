#include "pch.h"
#include "GPUQueue.h"
#include "GPUCommandBuffer.h"
#include "Interop.h"
#include <iostream>
#include <vector>

namespace winrt::WebGPUWinRT::implementation
{
	GPUQueue::GPUQueue(WGPUQueue handle) : handle(handle) {
		if (handle) {
			wgpuQueueAddRef(handle);
		}
	}
	
	GPUQueue::~GPUQueue() {
		if (handle) {
			wgpuQueueRelease(handle);
			handle = nullptr;
		}
	}

	winrt::hstring GPUQueue::Label() {
		// Labels are not retrievable from native API, return empty for now
		return L"";
	}

	void GPUQueue::Submit(winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::IGPUCommandBuffer> commandBuffers) {
		std::vector<WGPUCommandBuffer> nativeCommandBuffers;
		for (auto commandBuffer : commandBuffers) {
			auto impl = commandBuffer.as<implementation::GPUCommandBuffer>();
			nativeCommandBuffers.push_back(impl->handle);
		}
		
		wgpuQueueSubmit(handle, nativeCommandBuffers.size(), nativeCommandBuffers.data());
	}

	winrt::Windows::Foundation::IAsyncAction GPUQueue::OnSubmittedWorkDone() {
		// Basic implementation - will be completed in Phase 3
		throw winrt::hresult_not_implemented(L"GPUQueue::OnSubmittedWorkDone - Not implemented yet");
	}

	void GPUQueue::WriteBuffer(winrt::WebGPUWinRT::IGPUBuffer buffer, uint64_t bufferOffset, 
							  winrt::Windows::Storage::Streams::IBuffer data, uint64_t dataOffset, uint64_t size) {
		// Basic implementation - will be completed in Phase 3
		throw winrt::hresult_not_implemented(L"GPUQueue::WriteBuffer - Not implemented yet");
	}

	void GPUQueue::WriteTexture(winrt::WebGPUWinRT::IGPUTexture destination, 
							   winrt::Windows::Storage::Streams::IBuffer data, winrt::WebGPUWinRT::GPUExtent3D size) {
		// Basic implementation - will be completed in Phase 3
		throw winrt::hresult_not_implemented(L"GPUQueue::WriteTexture - Not implemented yet");
	}
}
