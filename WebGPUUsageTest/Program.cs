using WebGPUWinRT;
using System.Text.Json;

namespace WebGPUUsageTest;

internal class Program
{
    static async Task Foo()
    {
        var gpu = new GPU();
        var adaptor = await gpu.RequestAdapter();
        var limits = adaptor.Limits;
        Console.WriteLine($"maxBindGroups: {limits.maxBindingsPerBindGroup}");
        var option = new JsonSerializerOptions(JsonSerializerOptions.Default)
        {
            IncludeFields = true
        };
        Console.WriteLine(JsonSerializer.Serialize(limits, option));
        foreach (var feature in adaptor.Features)
        {
            Console.WriteLine($"{feature} : {Enum.GetName(feature)}");
        }
    }
    static async Task Main(string[] args)
    {
        await Foo();
        GC.Collect();
        Console.WriteLine("Hello, World!");
    }
}
