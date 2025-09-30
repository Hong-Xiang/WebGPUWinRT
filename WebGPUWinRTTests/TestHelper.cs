namespace WebGPUWinRTTests;
using WebGPUWinRT;
using System.Threading.Tasks;

/// <summary>
/// Helper class for common test setup operations
/// </summary>
public static class TestHelper
{
    /// <summary>
    /// Creates and returns a GPU instance
    /// </summary>
    public static GPU CreateGPU()
    {
        return new GPU();
    }

    /// <summary>
    /// Creates a GPU and requests an adapter
    /// </summary>
    public static async Task<IGPUAdapter> GetAdapterAsync()
    {
        var gpu = CreateGPU();
        return await gpu.RequestAdapter();
    }

    /// <summary>
    /// Creates a GPU, requests an adapter, and requests a device
    /// </summary>
    public static async Task<IGPUDevice> GetDeviceAsync()
    {
        var adapter = await GetAdapterAsync();
        return await adapter.RequestDevice();
    }

    /// <summary>
    /// Simple vertex and fragment shader for testing
    /// </summary>
    public static string SimpleShaderCode => @"
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
}
