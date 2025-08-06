#include "pch.h"
#include "GPUCommandBuffer.h"
#include "Interop.h"
#include <iostream>

namespace winrt::WebGPUWinRT::implementation
{
	GPUCommandBuffer::GPUCommandBuffer(WGPUCommandBuffer handle) : handle(handle) {
		if (handle) {
			wgpuCommandBufferReference(handle);
		}
	}
	
	GPUCommandBuffer::~GPUCommandBuffer() {
		if (handle) {
			wgpuCommandBufferRelease(handle);
			handle = nullptr;
		}
	}

	winrt::hstring GPUCommandBuffer::Label() {
		// Labels are not retrievable from native API, return empty for now
		return L"";
	}
}
