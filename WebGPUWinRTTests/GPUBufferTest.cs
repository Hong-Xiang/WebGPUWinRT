namespace WebGPUWinRTTests;
using WebGPUWinRT;
using Xunit;
using System.Threading.Tasks;

/// <summary>
/// Tests for GPUBuffer creation and properties
/// </summary>
public class GPUBufferTest
{
    [Fact]
    public async Task CreateBuffer_WithValidDescriptor_ShouldSucceed()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        var descriptor = new GPUBufferDescriptor
        {
            Label = "Test Buffer",
            Size = 256,
            Usage = GPUBufferUsage.Uniform | GPUBufferUsage.CopyDst,
            MappedAtCreation = false
        };
        
        // Act
        var buffer = device.CreateBuffer(descriptor);
        
        // Assert
        Assert.NotNull(buffer);
    }

    [Fact]
    public async Task Buffer_ShouldHaveCorrectSize()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        var descriptor = new GPUBufferDescriptor
        {
            Label = "Test Buffer",
            Size = 512,
            Usage = GPUBufferUsage.Uniform,
            MappedAtCreation = false
        };
        
        // Act
        var buffer = device.CreateBuffer(descriptor);
        
        // Assert
        Assert.Equal(512UL, buffer.Size);
    }

    [Fact]
    public async Task Buffer_ShouldHaveCorrectUsage()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        var expectedUsage = GPUBufferUsage.Storage | GPUBufferUsage.CopyDst;
        var descriptor = new GPUBufferDescriptor
        {
            Label = "Test Buffer",
            Size = 256,
            Usage = expectedUsage,
            MappedAtCreation = false
        };
        
        // Act
        var buffer = device.CreateBuffer(descriptor);
        
        // Assert
        Assert.Equal(expectedUsage, buffer.Usage);
    }

    [Fact]
    public async Task Buffer_ShouldHaveLabel()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        var descriptor = new GPUBufferDescriptor
        {
            Label = "My Test Buffer",
            Size = 256,
            Usage = GPUBufferUsage.Uniform,
            MappedAtCreation = false
        };
        
        // Act
        var buffer = device.CreateBuffer(descriptor);
        
        // Assert
        Assert.NotNull(buffer.Label);
    }

    // Note: MapState test is skipped because it's not implemented in wgpu-native yet
    [Fact(Skip = "MapState is not implemented in wgpu-native")]
    public async Task Buffer_MapState_ShouldBeUnmapped()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        var descriptor = new GPUBufferDescriptor
        {
            Label = "Test Buffer",
            Size = 256,
            Usage = GPUBufferUsage.Uniform,
            MappedAtCreation = false
        };
        
        // Act
        var buffer = device.CreateBuffer(descriptor);
        
        // Assert
        Assert.Equal(GPUBufferMapState.Unmapped, buffer.MapState);
    }
}
