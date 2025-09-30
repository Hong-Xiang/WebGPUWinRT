namespace WebGPUWinRTTests;
using WebGPUWinRT;
using Xunit;
using System.Threading.Tasks;

/// <summary>
/// Tests for GPUQueue functionality
/// </summary>
public class GPUQueueTest
{
    [Fact]
    public async Task Device_ShouldHaveQueue()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        // Act
        var queue = device.Queue;
        
        // Assert
        Assert.NotNull(queue);
    }

    [Fact]
    public async Task Queue_ShouldHaveLabel()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        // Act
        var queue = device.Queue;
        var label = queue.Label;
        
        // Assert
        Assert.NotNull(label);
        // Label might be empty string by default
    }
}
