namespace WebGPUWinRTTests;
using WebGPUWinRT;
using Xunit;
using System.Threading.Tasks;

/// <summary>
/// Tests for GPUPipelineLayout creation
/// </summary>
public class GPUPipelineLayoutTest
{
    [Fact]
    public async Task CreatePipelineLayout_WithEmptyDescriptor_ShouldSucceed()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        var descriptor = new GPUPipelineLayoutDescriptor
        {
            Label = "Test Pipeline Layout"
        };
        
        // Act
        var pipelineLayout = device.CreatePipelineLayout(descriptor);
        
        // Assert
        Assert.NotNull(pipelineLayout);
    }

    [Fact]
    public async Task PipelineLayout_ShouldHaveLabel()
    {
        // Arrange
        var device = await TestHelper.GetDeviceAsync();
        
        var descriptor = new GPUPipelineLayoutDescriptor
        {
            Label = "My Pipeline Layout"
        };
        
        // Act
        var pipelineLayout = device.CreatePipelineLayout(descriptor);
        
        // Assert
        Assert.NotNull(pipelineLayout.Label);
    }
}
