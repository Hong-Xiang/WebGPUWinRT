namespace WebGPUWinRTTests;
using WebGPUWinRT;
using Xunit;
using System.Linq;
using System.Threading.Tasks;

/// <summary>
/// Tests for basic GPU, Adapter, and Device initialization
/// </summary>
public class GPUAPITest
{
    [Fact]
    public void CreateGPU_ShouldSucceed()
    {
        // Arrange & Act
        var gpu = TestHelper.CreateGPU();
        
        // Assert
        Assert.NotNull(gpu);
    }

    [Fact]
    public async Task RequestAdapter_ShouldReturnAdapter()
    {
        // Arrange & Act
        var adapter = await TestHelper.GetAdapterAsync();
        
        // Assert
        Assert.NotNull(adapter);
    }

    [Fact]
    public async Task Adapter_ShouldHaveFeatures()
    {
        // Arrange
        var adapter = await TestHelper.GetAdapterAsync();
        
        // Act
        var features = adapter.Features;
        
        // Assert
        Assert.NotNull(features);
        // Adapter should have at least some features
        Assert.True(features.Count > 0, "Adapter should have at least one feature");
    }

    [Fact]
    public async Task Adapter_ShouldHaveLimits()
    {
        // Arrange
        var adapter = await TestHelper.GetAdapterAsync();
        
        // Act
        var limits = adapter.Limits;
        
        // Assert
        Assert.NotNull(limits);
        Assert.True(limits.maxBindingsPerBindGroup > 0, "maxBindingsPerBindGroup should be greater than 0");
    }

    [Fact]
    public async Task RequestDevice_ShouldReturnDevice()
    {
        // Arrange & Act
        var device = await TestHelper.GetDeviceAsync();
        
        // Assert
        Assert.NotNull(device);
    }

    [Fact]
    public async Task Device_ShouldHaveLimits()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        // Act
        var limits = device.Limits;
        
        // Assert
        Assert.NotNull(limits);
        Assert.True(limits.maxBindGroups > 0, "maxBindGroups should be greater than 0");
    }

    [Fact]
    public async Task Device_ShouldHaveFeatures()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        // Act
        var features = device.Features;
        
        // Assert
        Assert.NotNull(features);
        // Note: Device features might be empty if no features were requested
    }
}
