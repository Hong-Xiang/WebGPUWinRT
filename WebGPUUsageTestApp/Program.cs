using WebGPUWinRT;
using System.Text.Json;

namespace WebGPUUsageTestApp;

internal class Program
{
    static async Task Foo()
    {
        var gpu = new GPU();
        var adaptor = await gpu.RequestAdapter();
        var limits = adaptor.Limits;
        Console.WriteLine($"Adapter maxBindGroups: {limits.maxBindingsPerBindGroup}");
        var option = new JsonSerializerOptions(JsonSerializerOptions.Default)
        {
            IncludeFields = true
        };
        Console.WriteLine("Adapter Features:");
        foreach (var feature in adaptor.Features)
        {
            Console.WriteLine($"  {feature} : {Enum.GetName(feature)}");
        }
        
        var device = await adaptor.RequestDevice();
        Console.WriteLine($"\nDevice Limits: {JsonSerializer.Serialize(device.Limits, option)}");
        
        // Test new Device properties
        Console.WriteLine("\n=== Testing New Device Properties ===");
        
        Console.WriteLine("Device Features:");
        foreach (var feature in device.Features)
        {
            Console.WriteLine($"  {feature} : {Enum.GetName(feature)}");
        }
        
        // Console.WriteLine($"Device AdapterInfo: {JsonSerializer.Serialize(device.AdapterInfo, option)}");
        Console.WriteLine("Device AdapterInfo: [SKIPPED - not implemented in native library]");
        
        // Compare adapter vs device features
        Console.WriteLine("\n=== Feature Comparison ===");
        Console.WriteLine($"Adapter feature count: {adaptor.Features.Count}");
        Console.WriteLine($"Device feature count: {device.Features.Count}");
        
        var adapterFeatureSet = new HashSet<WebGPUWinRT.GPUFeature>(adaptor.Features);
        var deviceFeatureSet = new HashSet<WebGPUWinRT.GPUFeature>(device.Features);
        var onlyInAdapter = adapterFeatureSet.Except(deviceFeatureSet);
        var onlyInDevice = deviceFeatureSet.Except(adapterFeatureSet);
        
        if (onlyInAdapter.Any())
        {
            Console.WriteLine("Features only in adapter:");
            foreach (var feature in onlyInAdapter)
            {
                Console.WriteLine($"  {feature}");
            }
        }
        
        if (onlyInDevice.Any())
        {
            Console.WriteLine("Features only in device:");
            foreach (var feature in onlyInDevice)
            {
                Console.WriteLine($"  {feature}");
            }
        }
        
        if (!onlyInAdapter.Any() && !onlyInDevice.Any())
        {
            Console.WriteLine("✅ Device and Adapter feature sets match!");
        }
    }
    static async Task Main(string[] args)
    {
        await Foo();
        GC.Collect();
        Console.WriteLine("\n=== Test Complete ===");
    }
}
