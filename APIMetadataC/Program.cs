using System.Reflection;

namespace APIMetadataC
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var t = typeof(APIMetadataP.TestHandle);
            foreach (var m in t.GetMethods(BindingFlags.DeclaredOnly | BindingFlags.Public | BindingFlags.Static | BindingFlags.Instance))
            {
                Console.WriteLine($"{m.Name} {m.ReturnType.Name}");
            }

            var ns = typeof(APIMetadataP.NS);
            foreach(var n in ns.GetMembers())
            {
                Console.WriteLine(n.Name);
            }
        }
    }
}
