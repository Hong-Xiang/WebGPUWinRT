#include "pch.h"
#include "GPUPipelineLayout.h"
#include "Interop.h"
#include <iostream>

namespace winrt::WebGPUWinRT::implementation
{
	GPUPipelineLayout::GPUPipelineLayout(WGPUPipelineLayout handle) : handle(handle) {
		if (handle) {
			wgpuPipelineLayoutAddRef(handle);
		}
	}
	
	GPUPipelineLayout::~GPUPipelineLayout() {
		if (handle) {
			wgpuPipelineLayoutRelease(handle);
			handle = nullptr;
		}
	}

	winrt::hstring GPUPipelineLayout::Label() {
		// Labels are not retrievable from native API, return empty for now
		return L"";
	}
}
