#pragma once
#include "webgpu/wgpu.h"
#include "winrt/WebGPUWinRT.h"
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.Storage.Streams.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPUBuffer : implements<GPUBuffer, winrt::WebGPUWinRT::IGPUBuffer, winrt::Windows::Foundation::IClosable>
	{
		GPUBuffer(WGPUBuffer handle);
		~GPUBuffer();
		void Close();
		WGPUBuffer handle{ nullptr };
		
		// Properties
		winrt::hstring Label();
		uint64_t Size();
		winrt::WebGPUWinRT::GPUBufferUsage Usage();
		winrt::WebGPUWinRT::GPUBufferMapState MapState();
		
		// Methods
		winrt::Windows::Foundation::IAsyncAction MapAsync(uint32_t mode, uint64_t offset, uint64_t size);
		winrt::Windows::Storage::Streams::IBuffer GetMappedRange(uint64_t offset, uint64_t size);
		void Unmap();
		
	private:
		bool m_isClosed{ false };
		uint64_t m_size{ 0 };
		winrt::WebGPUWinRT::GPUBufferUsage m_usage{ static_cast<winrt::WebGPUWinRT::GPUBufferUsage>(0) };
	};
}
