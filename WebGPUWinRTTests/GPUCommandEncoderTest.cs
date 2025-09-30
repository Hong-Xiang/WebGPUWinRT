namespace WebGPUWinRTTests;
using WebGPUWinRT;
using Xunit;
using System.Threading.Tasks;

/// <summary>
/// Tests for GPUCommandEncoder and GPUCommandBuffer
/// </summary>
public class GPUCommandEncoderTest
{
    [Fact]
    public async Task CreateCommandEncoder_ShouldSucceed()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        // Act
        var commandEncoder = device.CreateCommandEncoder();
        
        // Assert
        Assert.NotNull(commandEncoder);
    }

    [Fact]
    public async Task CommandEncoder_ShouldHaveLabel()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        // Act
        var commandEncoder = device.CreateCommandEncoder();
        var label = commandEncoder.Label;
        
        // Assert
        Assert.NotNull(label);
    }

    [Fact]
    public async Task CommandEncoder_Finish_ShouldCreateCommandBuffer()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        var commandEncoder = device.CreateCommandEncoder();
        
        // Act
        var commandBuffer = commandEncoder.Finish();
        
        // Assert
        Assert.NotNull(commandBuffer);
    }

    [Fact]
    public async Task CommandBuffer_ShouldHaveLabel()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        var commandEncoder = device.CreateCommandEncoder();
        
        // Act
        var commandBuffer = commandEncoder.Finish();
        var label = commandBuffer.Label;
        
        // Assert
        Assert.NotNull(label);
    }
}
