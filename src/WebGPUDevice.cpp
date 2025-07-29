#define WEBGPU_CPP_IMPLEMENTATION
#include "WebGPUWinRT/WebGPUDevice.h"

#include <iostream>
#include <cassert>

namespace WebGPUWinRT {

	WebGPUDevice::WebGPUDevice() = default;

	WebGPUDevice::~WebGPUDevice() {
		if (device_) {
			device_.release();
		}
		if (adapter_) {
			adapter_.release();
		}
		if (instance_) {
			instance_.release();
		}
	}

	bool WebGPUDevice::Initialize() {
		if (initialized_) {
			return true;
		}

		if (!CreateInstance()) {
			std::cerr << "Failed to create WebGPU instance" << std::endl;
			return false;
		}

		if (!RequestAdapter()) {
			std::cerr << "Failed to request WebGPU adapter" << std::endl;
			return false;
		}

		if (!RequestDevice()) {
			std::cerr << "Failed to request WebGPU device" << std::endl;
			return false;
		}

		initialized_ = true;
		std::cout << "WebGPU device initialized successfully" << std::endl;
		return true;
	}

	bool WebGPUDevice::CreateInstance() {
		wgpu::InstanceDescriptor instanceDesc = {};
		instance_ = wgpu::createInstance(instanceDesc);
		return instance_ != nullptr;
	}

	bool WebGPUDevice::RequestAdapter() {
		wgpu::RequestAdapterOptions adapterOpts = {};
		adapterOpts.powerPreference = wgpu::PowerPreference::HighPerformance;

		// In a real application, you would use async callbacks
		// For simplicity, this is a synchronous approach
		struct AdapterData {
			wgpu::Adapter adapter = nullptr;
			bool requestEnded = false;
		} adapterData;

		auto onAdapterRequestEnded = [](wgpu::RequestAdapterStatus status,
			wgpu::Adapter adapter,
			wgpu::StringView message,
			void* pUserData) {
				AdapterData& data = *reinterpret_cast<AdapterData*>(pUserData);
				if (status == wgpu::RequestAdapterStatus::Success) {
					data.adapter = adapter;
				}
				else {
					std::cerr << "Could not get WebGPU adapter: " << message.data << std::endl;
				}
				data.requestEnded = true;
			};


		adapter_ = instance_.requestAdapter(adapterOpts);

		//// Simple polling loop (in production, use proper async handling)
		//while (!adapterData.requestEnded) {
		//	instance_.processEvents();
		//}

		//adapter_ = adapterData.adapter;
		return adapter_ != nullptr;
	}

	bool WebGPUDevice::RequestDevice() {
		wgpu::DeviceDescriptor deviceDesc = {};

		deviceDesc.label = wgpu::StringView::StringView("WebGPUWinRT Device");

		struct DeviceData {
			wgpu::Device device = nullptr;
			bool requestEnded = false;
		} deviceData;

		auto onDeviceRequestEnded = [](wgpu::RequestDeviceStatus status,
			wgpu::Device device,
			wgpu::StringView message,
			void* pUserData) {
				DeviceData& data = *reinterpret_cast<DeviceData*>(pUserData);
				if (status == wgpu::RequestDeviceStatus::Success) {
					data.device = device;
				}
				else {
					std::cerr << "Could not get WebGPU device: " << message.data << std::endl;
				}
				data.requestEnded = true;
			};

		device_ = adapter_.requestDevice(deviceDesc);

		//// Simple polling loop (in production, use proper async handling)
		//while (!deviceData.requestEnded) {
		//	instance_.processEvents();
		//}

		//device_ = deviceData.device;
		return device_ != nullptr;
	}

} // namespace WebGPUWinRT
