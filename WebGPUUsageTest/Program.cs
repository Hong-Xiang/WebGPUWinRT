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
        await TaskTest();
        GC.Collect();
        Console.WriteLine("Hello, World!");
    }



    private static AsyncLocal<string> _asyncLocal = new AsyncLocal<string>();

    public static async Task TaskTest()
    {
        _asyncLocal.Value = "main";

        var tasks = new List<Task>();
        for (int i = 0; i < 3; i++)
        {
            int taskNum = i;
            tasks.Add(Task.Run(async () =>
            {
                Console.WriteLine($"Task {taskNum}: initial value is '{_asyncLocal.Value}'");
                _asyncLocal.Value = $"task {taskNum}";
                Console.WriteLine($"Task {taskNum}: new value is '{_asyncLocal.Value}'");
                await Task.Delay(100);
                Console.WriteLine($"Task {taskNum}: value after delay is '{_asyncLocal.Value}'");
            }));
        }

        await Task.WhenAll(tasks);

        Console.WriteLine($"Main: final value is '{_asyncLocal.Value}'");
    }
}
