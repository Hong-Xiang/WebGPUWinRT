#include "pch.h"
#include "Interop.h"

std::string interop::to_string(WGPUStringView wgpu_string_view)
{
	if (wgpu_string_view.length == WGPU_STRLEN) {
		return std::string(wgpu_string_view.data);
	}
	else {
		return std::string(wgpu_string_view.data, wgpu_string_view.length);
	}
} // namespace interop
