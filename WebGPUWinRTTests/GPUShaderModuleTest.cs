namespace WebGPUWinRTTests;
using WebGPUWinRT;
using Xunit;
using System.Threading.Tasks;

/// <summary>
/// Tests for GPUShaderModule creation
/// </summary>
public class GPUShaderModuleTest
{
    [Fact(Skip = "Shader module creation crashes in wgpu-native with current WGSL code")]
    public async Task CreateShaderModule_WithValidWGSL_ShouldSucceed()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        var descriptor = new GPUShaderModuleDescriptor
        {
            Label = "Test Shader",
            Code = TestHelper.SimpleShaderCode
        };
        
        // Act
        var shaderModule = device.CreateShaderModule(descriptor);
        
        // Assert
        Assert.NotNull(shaderModule);
    }

    [Fact(Skip = "Shader module creation crashes in wgpu-native with current WGSL code")]
    public async Task ShaderModule_ShouldHaveLabel()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        var descriptor = new GPUShaderModuleDescriptor
        {
            Label = "My Shader Module",
            Code = TestHelper.SimpleShaderCode
        };
        
        // Act
        var shaderModule = device.CreateShaderModule(descriptor);
        
        // Assert
        Assert.NotNull(shaderModule.Label);
    }
}
