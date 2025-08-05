#include "pch.h"
#include "GPUDevice.h"
#include "Interop.h"
#include <iostream>

namespace winrt::WebGPUWinRT::implementation
{
	GPUDevice::GPUDevice(WGPUDevice handle) : handle(handle) {
	}
	void GPUDevice::Close() {
		std::cout << "Close device" << std::endl;
		if (m_isClosed) {
			return;
		}
		if (handle)
		{
			std::cout << "Close device disposing" << std::endl;
			wgpuDeviceRelease(handle);
			handle = nullptr;
		}
	}
	GPUDevice::~GPUDevice() {
		std::cout << "Deconstructor device" << std::endl;
		if (handle)
		{
			std::cout << "Releasing device" << std::endl;
			wgpuDeviceRelease(handle);
			handle = nullptr;
		}
	}

	GPUSupportedLimits GPUDevice::Limits() {
		WGPULimits limits = {};
		wgpuDeviceGetLimits(handle, &limits);
		return interop::to(limits);
	}
}