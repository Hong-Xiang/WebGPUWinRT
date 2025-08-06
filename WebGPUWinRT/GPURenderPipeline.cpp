#include "pch.h"
#include "GPURenderPipeline.h"
#include "Interop.h"
#include <iostream>

namespace winrt::WebGPUWinRT::implementation
{
	GPURenderPipeline::GPURenderPipeline(WGPURenderPipeline handle) : handle(handle) {
		if (handle) {
			wgpuRenderPipelineReference(handle);
		}
	}
	
	GPURenderPipeline::~GPURenderPipeline() {
		if (handle) {
			wgpuRenderPipelineRelease(handle);
			handle = nullptr;
		}
	}

	winrt::hstring GPURenderPipeline::Label() {
		// Labels are not retrievable from native API, return empty for now
		return L"";
	}

	winrt::WebGPUWinRT::IGPUBindGroupLayout GPURenderPipeline::GetBindGroupLayout(uint32_t index) {
		// Basic implementation - will be completed later when bind groups are implemented
		throw winrt::hresult_not_implemented(L"GPURenderPipeline::GetBindGroupLayout - Not implemented yet");
	}
}
