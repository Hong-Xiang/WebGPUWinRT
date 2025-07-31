namespace WebGPUWinRT.Projection;

public class TestClass
{
    public static void Foo()
    {
        var gpu = new GPU();
        var adaptor = gpu.RequestAdapter();
        var limits = adaptor.Limits;
        Console.WriteLine($"maxBindGroups: {limits.maxBindingsPerBindGroup}");
    }
}
