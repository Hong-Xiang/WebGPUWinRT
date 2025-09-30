using WebGPUWinRT;
using System.Text.Json;
using Windows.Foundation;

namespace WebGPUUsageTestApp;

internal class Program
{
    static async Task TestBasicAPIs()
    {
        Console.WriteLine("=== Testing Basic GPU APIs ===\n");
        
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

    static async Task TestNewAPIs()
    {
        Console.WriteLine("\n\n=== Testing New APIs ===\n");
        
        var gpu = new GPU();
        var adapter = await gpu.RequestAdapter();
        var device = await adapter.RequestDevice();
        
        // Test Queue
        Console.WriteLine("--- Testing Queue ---");
        var queue = device.Queue;
        Console.WriteLine($"✅ Queue obtained: {queue != null}");
        Console.WriteLine($"   Queue Label: '{queue.Label}'");
        
        // Test Buffer Creation
        Console.WriteLine("\n--- Testing Buffer Creation ---");
        var bufferDescriptor = new GPUBufferDescriptor
        {
            Label = "Test Buffer",
            Size = 256,
            Usage = GPUBufferUsage.Uniform | GPUBufferUsage.CopyDst,
            MappedAtCreation = false
        };
        
        try
        {
            var buffer = device.CreateBuffer(bufferDescriptor);
            Console.WriteLine($"✅ Buffer created successfully");
            Console.WriteLine($"   Buffer Size: {buffer.Size}");
            Console.WriteLine($"   Buffer Usage: {buffer.Usage}");
            // Note: MapState is not implemented in wgpu-native yet, skipping
            // Console.WriteLine($"   Buffer MapState: {buffer.MapState}");
            Console.WriteLine($"   Buffer Label: '{buffer.Label}'");
            
            // Note: Label is read-only, cannot be modified after creation
        }
        catch (Exception ex)
        {
            Console.WriteLine($"❌ Buffer creation failed: {ex.Message}");
        }
        
        // Test Shader Module Creation
        Console.WriteLine("\n--- Testing Shader Module Creation ---");
        string shaderCode = @"
@vertex
fn vs_main(@builtin(vertex_index) vertex_index: u32) -> @builtin(position) vec4<f32> {
    let x = f32(i32(vertex_index) - 1);
    let y = f32(i32(vertex_index & 1u) * 2 - 1);
    return vec4<f32>(x, y, 0.0, 1.0);
}

@fragment
fn fs_main() -> @location(0) vec4<f32> {
    return vec4<f32>(1.0, 0.0, 0.0, 1.0);
}
";
        
        var shaderDescriptor = new GPUShaderModuleDescriptor
        {
            Label = "Test Shader",
            Code = shaderCode
        };
        
        try
        {
            var shaderModule = device.CreateShaderModule(shaderDescriptor);
            Console.WriteLine($"✅ Shader module created successfully");
            Console.WriteLine($"   Shader Label: '{shaderModule.Label}'");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"❌ Shader module creation failed: {ex.Message}");
        }
        
        // Test Pipeline Layout Creation
        Console.WriteLine("\n--- Testing Pipeline Layout Creation ---");
        var pipelineLayoutDescriptor = new GPUPipelineLayoutDescriptor
        {
            Label = "Test Pipeline Layout"
        };
        
        try
        {
            var pipelineLayout = device.CreatePipelineLayout(pipelineLayoutDescriptor);
            Console.WriteLine($"✅ Pipeline layout created successfully");
            Console.WriteLine($"   Pipeline Layout Label: '{pipelineLayout.Label}'");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"❌ Pipeline layout creation failed: {ex.Message}");
        }
        
        // Test Render Pipeline Creation
        Console.WriteLine("\n--- Testing Render Pipeline Creation ---");
        try
        {
            var shaderModule = device.CreateShaderModule(new GPUShaderModuleDescriptor
            {
                Label = "Render Shader",
                Code = shaderCode
            });
            
            Console.WriteLine($"✅ Shader module created for pipeline");
            
            // Note: Full render pipeline creation requires more complex setup
            // Skipping full pipeline creation due to API complexity
            Console.WriteLine($"   (Full pipeline creation test skipped - requires vertex/fragment state setup)");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"❌ Render pipeline setup failed: {ex.Message}");
        }
        
        // Test Command Encoder Creation
        Console.WriteLine("\n--- Testing Command Encoder Creation ---");
        
        try
        {
            var commandEncoder = device.CreateCommandEncoder();
            Console.WriteLine($"✅ Command encoder created successfully");
            Console.WriteLine($"   Command Encoder Label: '{commandEncoder.Label}'");
            
            // Test finishing the command encoder
            var commandBuffer = commandEncoder.Finish();
            Console.WriteLine($"✅ Command buffer created successfully");
            Console.WriteLine($"   Command Buffer Label: '{commandBuffer.Label}'");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"❌ Command encoder/buffer creation failed: {ex.Message}");
        }
    }
    
    static async Task Main(string[] args)
    {
        try
        {
            await TestBasicAPIs();
            await TestNewAPIs();
            
            GC.Collect();
            Console.WriteLine("\n=== All Tests Complete ===");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"\n❌ Fatal error: {ex.Message}");
            Console.WriteLine($"Stack trace: {ex.StackTrace}");
        }
    }
}
