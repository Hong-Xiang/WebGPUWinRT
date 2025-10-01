// See https://aka.ms/new-console-template for more information
using System.IO;
using CppAst;

if (args.Length == 0)
{
    Console.WriteLine("Usage: cppast-test <header-file-path>");
    return 1;
}

var filePath = args[0];
Console.WriteLine($"Parsing C++ header file: {filePath}");
Console.WriteLine();

if (!File.Exists(filePath))
{
    Console.WriteLine($"Error: File not found: {filePath}");
    return 1;
}

// Parse the C++ file
var options = new CppParserOptions
{
    ParseMacros = true,
    ParseComments = false,
};

var compilation = CppParser.ParseFile(filePath, options);

// Check for errors
if (compilation.HasErrors)
{
    Console.WriteLine("Parsing errors:");
    foreach (var message in compilation.Diagnostics.Messages)
    {
        if (message.Type == CppLogMessageType.Error)
        {
            Console.WriteLine($"  [ERROR] {message}");
        }
        else if (message.Type == CppLogMessageType.Warning)
        {
            Console.WriteLine($"  [WARNING] {message}");
        }
    }
    Console.WriteLine();
}

// Dump the parsed content
Console.WriteLine("=== Compilation Summary ===");
Console.WriteLine($"Macros: {compilation.Macros.Count}");
Console.WriteLine($"Enums: {compilation.Enums.Count}");
Console.WriteLine($"Classes: {compilation.Classes.Count}");
Console.WriteLine($"Functions: {compilation.Functions.Count}");
Console.WriteLine($"Typedefs: {compilation.Typedefs.Count}");
Console.WriteLine();

// Dump Macros
if (compilation.Macros.Count > 0)
{
    Console.WriteLine("=== MACROS ===");
    foreach (var macro in compilation.Macros)
    {
        Console.WriteLine($"  {macro.Name} = {macro.Value}");
    }
    Console.WriteLine();
}

// Dump Enums
if (compilation.Enums.Count > 0)
{
    Console.WriteLine("=== ENUMS ===");
    foreach (var enumType in compilation.Enums)
    {
        Console.WriteLine($"  enum {enumType.Name}");
        foreach (var item in enumType.Items)
        {
            Console.WriteLine($"    {item.Name} = {item.Value}");
        }
        Console.WriteLine();
    }
}

// Dump Typedefs
if (compilation.Typedefs.Count > 0)
{
    Console.WriteLine("=== TYPEDEFS ===");
    foreach (var typedef in compilation.Typedefs)
    {
        Console.WriteLine($"  typedef {typedef.ElementType} {typedef.Name}");
    }
    Console.WriteLine();
}

// Dump Structs/Classes
if (compilation.Classes.Count > 0)
{
    Console.WriteLine("=== STRUCTS/CLASSES ===");
    foreach (var classType in compilation.Classes)
    {
        Console.WriteLine($"  {classType.ClassKind} {classType.Name} (Size: {classType.SizeOf} bytes)");
        
        // Dump fields
        if (classType.Fields.Count > 0)
        {
            Console.WriteLine("    Fields:");
            foreach (var field in classType.Fields)
            {
                Console.WriteLine($"      {field.Type} {field.Name} (Offset: {field.Offset})");
            }
        }
        
        // Dump methods
        if (classType.Functions.Count > 0)
        {
            Console.WriteLine("    Methods:");
            foreach (var method in classType.Functions)
            {
                var parameters = string.Join(", ", method.Parameters.Select(p => $"{p.Type} {p.Name}"));
                Console.WriteLine($"      {method.ReturnType} {method.Name}({parameters})");
            }
        }
        
        Console.WriteLine();
    }
}

// Dump Functions
if (compilation.Functions.Count > 0)
{
    Console.WriteLine("=== FUNCTIONS ===");
    foreach (var function in compilation.Functions)
    {
        var parameters = string.Join(", ", function.Parameters.Select(p => $"{p.Type} {p.Name}"));
        Console.WriteLine($"  {function.ReturnType} {function.Name}({parameters})");
    }
    Console.WriteLine();
}

Console.WriteLine("=== Parsing Complete ===");
return 0;



