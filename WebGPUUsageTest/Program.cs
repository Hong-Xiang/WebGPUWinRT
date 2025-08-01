using WebGPUWinRT;
using System.Text.Json;

namespace WebGPUUsageTest;

internal class Program
{
    static void Foo()
    {
        var gpu = new GPU();
        var adaptor = gpu.RequestAdapter();
        var limits = adaptor.Limits;
        Console.WriteLine($"maxBindGroups: {limits.maxBindingsPerBindGroup}");
        var option = new JsonSerializerOptions(JsonSerializerOptions.Default);
        option.IncludeFields = true;
        Console.WriteLine(JsonSerializer.Serialize(limits, option));
        foreach (var feature in adaptor.Features)
        {
            Console.WriteLine($"{feature} : {Enum.GetName(feature)}");
        }
    }
    static void Main(string[] args)
    {
        Foo();
        GC.Collect();
        Console.WriteLine("Hello, World!");
    }
}
