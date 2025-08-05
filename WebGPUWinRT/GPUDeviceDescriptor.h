#pragma once
#include "GPUDeviceDescriptor.g.h"

namespace winrt::WebGPUWinRT::implementation
{
	struct GPUDeviceDescriptor : GPUDeviceDescriptorT<GPUDeviceDescriptor>
	{
		GPUDeviceDescriptor() = default;

		hstring Label();
		void Label(hstring const& value);
		winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUFeature> RequiredFeatures();
		void RequiredFeatures(winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUFeature> const& value);
		winrt::WebGPUWinRT::GPUQueueDescriptor DefaultQueue();
		void DefaultQueue(winrt::WebGPUWinRT::GPUQueueDescriptor const& value);

		hstring m_label{};
	};
}
