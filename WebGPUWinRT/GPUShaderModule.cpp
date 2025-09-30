#include "pch.h"
#include "GPUShaderModule.h"
#include "Interop.h"
#include <iostream>

namespace winrt::WebGPUWinRT::implementation
{
	GPUShaderModule::GPUShaderModule(WGPUShaderModule handle) : handle(handle) {
		if (handle) {
			wgpuShaderModuleAddRef(handle);
		}
	}
	
	GPUShaderModule::~GPUShaderModule() {
		if (handle) {
			wgpuShaderModuleRelease(handle);
			handle = nullptr;
		}
	}

	winrt::hstring GPUShaderModule::Label() {
		// Labels are not retrievable from native API, return empty for now
		return L"";
	}

	winrt::Windows::Foundation::IAsyncOperation<winrt::WebGPUWinRT::IGPUCompilationInfo> GPUShaderModule::GetCompilationInfo() {
		// Basic implementation - will be completed later
		throw winrt::hresult_not_implemented(L"GPUShaderModule::GetCompilationInfo - Not implemented yet");
	}
}
