#pragma once
#include <string>

namespace interop {
	std::string to(WGPUStringView wgpu_string_view);
	winrt::WebGPUWinRT::GPUFeature to(WGPUFeatureName feature);
	winrt::WebGPUWinRT::GPUSupportedLimits to(WGPULimits limits);
	winrt::WebGPUWinRT::GPUAdapterInfo to(WGPUAdapterInfo limits);
} // namespace interop
