#include "pch.h"
#include "GPUDeviceDescriptor.h"
#include "GPUDeviceDescriptor.g.cpp"

namespace winrt::WebGPUWinRT::implementation
{
    hstring GPUDeviceDescriptor::Label()
    {
        throw hresult_not_implemented();
    }
    void GPUDeviceDescriptor::Label(hstring const& value)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUFeature> GPUDeviceDescriptor::RequiredFeatures()
    {
        throw hresult_not_implemented();
    }
    void GPUDeviceDescriptor::RequiredFeatures(winrt::Windows::Foundation::Collections::IVectorView<winrt::WebGPUWinRT::GPUFeature> const& value)
    {
        throw hresult_not_implemented();
    }
    winrt::WebGPUWinRT::GPUQueueDescriptor GPUDeviceDescriptor::DefaultQueue()
    {
        throw hresult_not_implemented();
    }
    void GPUDeviceDescriptor::DefaultQueue(winrt::WebGPUWinRT::GPUQueueDescriptor const& value)
    {
        throw hresult_not_implemented();
    }
}
