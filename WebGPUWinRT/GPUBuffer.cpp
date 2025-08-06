#include "pch.h"
#include "GPUBuffer.h"
#include "Interop.h"
#include <iostream>

namespace winrt::WebGPUWinRT::implementation
{
	GPUBuffer::GPUBuffer(WGPUBuffer handle) : handle(handle) {
		if (handle) {
			wgpuBufferReference(handle);
			m_size = wgpuBufferGetSize(handle);
			m_usage = static_cast<winrt::WebGPUWinRT::GPUBufferUsage>(wgpuBufferGetUsage(handle));
		}
	}
	
	GPUBuffer::~GPUBuffer() {
		if (handle) {
			wgpuBufferRelease(handle);
			handle = nullptr;
		}
	}

	void GPUBuffer::Close() {
		if (m_isClosed) {
			return;
		}
		if (handle) {
			wgpuBufferRelease(handle);
			handle = nullptr;
		}
		m_isClosed = true;
	}

	winrt::hstring GPUBuffer::Label() {
		// Labels are not retrievable from native API, return empty for now
		return L"";
	}

	uint64_t GPUBuffer::Size() {
		return m_size;
	}

	winrt::WebGPUWinRT::GPUBufferUsage GPUBuffer::Usage() {
		return m_usage;
	}

	winrt::WebGPUWinRT::GPUBufferMapState GPUBuffer::MapState() {
		WGPUBufferMapState state = wgpuBufferGetMapState(handle);
		switch (state) {
		case WGPUBufferMapState_Unmapped:
			return winrt::WebGPUWinRT::GPUBufferMapState::Unmapped;
		case WGPUBufferMapState_Pending:
			return winrt::WebGPUWinRT::GPUBufferMapState::Pending;
		case WGPUBufferMapState_Mapped:
			return winrt::WebGPUWinRT::GPUBufferMapState::Mapped;
		default:
			return winrt::WebGPUWinRT::GPUBufferMapState::Unmapped;
		}
	}

	winrt::Windows::Foundation::IAsyncAction GPUBuffer::MapAsync(uint32_t mode, uint64_t offset, uint64_t size) {
		// Basic implementation - will be completed later
		throw winrt::hresult_not_implemented(L"GPUBuffer::MapAsync - Not implemented yet");
	}

	winrt::Windows::Storage::Streams::IBuffer GPUBuffer::GetMappedRange(uint64_t offset, uint64_t size) {
		// Basic implementation - will be completed later
		throw winrt::hresult_not_implemented(L"GPUBuffer::GetMappedRange - Not implemented yet");
	}

	void GPUBuffer::Unmap() {
		if (handle) {
			wgpuBufferUnmap(handle);
		}
	}
}
