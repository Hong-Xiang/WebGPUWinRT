# Rules to Map WebIDL to CSharp

## Type Mapping

### Basic Types

- **WebIDL interface** → C# `interface`
- **WebIDL dictionary** → C# `class`
- **WebIDL interface mixin** → C# `interface` (emitted as a separate interface that can be inherited)
- **WebIDL enum (string-based)** → C# `enum` with `[WebIDLStringEnum]` attribute and no predefined values
- **WebIDL enum (integer-based)** → C# `enum` with correct integer values
- **WebIDL namespace** → C# `public static class` with namespace constants as `public const` fields
- **WebIDL callback** → C# `delegate`
- **WebIDL callback interface** → C# `interface` with `[WebIDLCallbackInterface]` attribute

### Type Aliases and Unions

- **WebIDL typedef to single type** → C# `using` type alias at the top of the file (after namespace declaration)
- **WebIDL typedef to union type** → C# abstract class with `[WebIDLUnion(typeof(T1), typeof(T2), ...)]` attribute containing all union type arguments
- **WebIDL union types in properties/parameters** → C# `object` with comment `/* Union: T1 | T2 */` and `[WebIDLUnion(typeof(T1), typeof(T2), ...)]` attribute containing all union type arguments

### Special Union Handling

- **WebIDL `T or undefined`** → C# nullable type `T?` with `[WebIDLOrUndefined]` attribute
- **WebIDL nullable type `T?`** → C# nullable type `T?` with `[WebIDLNullable]` attribute
- **WebIDL `void` return type** → C# `void`
- **WebIDL `void` in generic type arguments** → C# `Undefined` struct (defined in WebIDL namespace)

### Generic and Collection Types

- **WebIDL `sequence<T>`** → C# `Sequence<T>` (helper class defined in WebIDL namespace)
- **WebIDL `Promise<T>`** → C# `Promise<T>` (helper class defined in WebIDL namespace)
- **WebIDL `FrozenArray<T>`** → C# `FrozenArray<T>` (helper class defined in WebIDL namespace)
- **WebIDL `ObservableArray<T>`** → C# `ObservableArray<T>` (helper class defined in WebIDL namespace)
- **WebIDL `record<K, V>`** → C# `Record<K, V>` (helper class defined in WebIDL namespace)

### Primitive Type Mapping

- **WebIDL primitive types** → C# primitive types with same signedness and size:
  - `byte` → `sbyte`
  - `octet` → `byte`
  - `short` → `short`
  - `unsigned short` → `ushort`
  - `long` → `int`
  - `unsigned long` → `uint`
  - `long long` → `long`
  - `unsigned long long` → `ulong`
  - `float` → `float`
  - `double` → `double`
  - `boolean` → `bool`
  - `DOMString`, `ByteString`, `USVString` → `string`
  - `undefined` → `void` (or `Undefined` in generic contexts)
  - `any`, `object` → `object`

### Special Interface Declarations

- **WebIDL `setlike<T>`** → C# interface inheritance `: setlike<T>` with `[WebIDLReadonlySetlike]` attribute if readonly
- **WebIDL `maplike<K, V>`** → C# interface inheritance `: maplike<K, V>` with `[WebIDLReadonlyMaplike]` attribute if readonly
- **WebIDL `iterable<T>` or `iterable<K, V>`** → C# comment `// iterable<T>` (not fully representable in type system)

## Member Mapping

### Interface Members

- **WebIDL readonly attribute** → C# property with only `get;` accessor
- **WebIDL read-write attribute** → C# property with `get; set;` accessors
- **WebIDL operation (method)** → C# method with same signature
- **WebIDL static operation** → C# `static` method
- **WebIDL const** → C# `public const` field

### Dictionary Members

- **WebIDL dictionary field** → C# property with `get; set;` accessors
- **WebIDL required dictionary field** → C# property with `required` keyword (C# 11+)
- **WebIDL dictionary field with default value** → C# property with `= defaultValue` initializer
  - Enum defaults use enum type prefix: `MyEnum.value`
  - Primitive defaults use literal values: `0`, `true`, `"string"`
  - Object/dictionary defaults use `default` with `[WebIDLNewObjectDefaultValue]` attribute
  - Sequence/array defaults use `default`
- **WebIDL dictionary inheritance** → C# class inheritance `: BaseClass`

### Method Parameters

- **WebIDL required parameter** → C# parameter without default
- **WebIDL optional parameter** → C# nullable parameter `T?` with `= default`
- **WebIDL parameter with default value** → C# parameter with `= defaultValue`
- **WebIDL variadic parameter** → C# `params` array parameter

## Extended Attributes Mapping

All WebIDL extended attributes are mapped to C# attributes with `WebIDL` prefix:

- **`[Exposed=(Window, Worker)]`** → `[WebIDLExposed("Window", "Worker")]`
- **`[SecureContext]`** → `[WebIDLSecureContext]`
- **`[Serializable]`** → `[WebIDLSerializable]`
- **`[NewObject]`** → `[WebIDLNewObject]` (on methods that return new objects)
- **`[AllowShared]`** → `[WebIDLAllowShared]` (on parameters)
- **`[Clamp]`** → `[WebIDLClamp]` (on parameters)
- **`[EnforceRange]`** → `[WebIDLEnforceRange]` (on parameters and typedefs)

## Naming and Escaping

- **Enum values with special characters** (e.g., `"2d"`, `"depth-only"`) → Valid C# identifier with `[WebIDLName("original-name")]` attribute
  - Hyphens `-` are replaced with underscores `_`
  - Leading digits get underscore prefix: `"2d"` → `_2d`
  - Original casing is preserved where possible
- **C# reserved keywords** → Escaped with `@` prefix (e.g., `@object`, `@event`)
- **WebIDL names changed for C#** → `[WebIDLName("original-name")]` attribute added

## File Structure

The generated C# file has the following structure:

1. **Type alias usings** (from typedef) - at the very top
2. **Namespace usings** (`using System;`, `using WebIDL;`) - after type aliases
3. **File header comment** with generation timestamp
4. **File-scoped namespace** declaration (`namespace WebGPU;`)
5. **Type definitions** (interfaces, classes, enums, delegates, static classes)

## Recoverability via Reflection

The mapping preserves maximum information so that the original WebIDL structure can be reconstructed via C# reflection:

- ✅ **Type structure** - interfaces, classes, enums, inheritance
- ✅ **Member signatures** - methods, properties, parameters with types
- ✅ **Extended attributes** - via `[WebIDL*]` attributes
- ✅ **Default values** - via property initializers and parameter defaults
- ✅ **Required fields** - via `required` keyword
- ✅ **Readonly members** - via `get;` only accessors
- ✅ **Union types** - via `[WebIDLUnion(typeof(T1), typeof(T2), ...)]` attribute with full type list and comment
- ✅ **Nullable/optional** - via `?` and `[WebIDLNullable]`/`[WebIDLOrUndefined]` attributes
- ✅ **String enums** - via `[WebIDLStringEnum]` attribute
- ✅ **Name mappings** - via `[WebIDLName]` attribute
- ✅ **Special interfaces** - via `setlike<T>`, `maplike<K,V>` inheritance and readonly attributes
- ⚠️ **Method overloads** - WebIDL allows same name with different signatures; C# uses different names or native overloading

## External Type Handling

Some types are defined outside the WebGPU spec (e.g., in HTML/CSS specs) but are referenced:

- **`PredefinedColorSpace`** - Defined in WebIDL namespace, defaults use enum syntax
- **`EventTarget`**, `Event`, `DOMException` - Defined in WebIDL namespace as placeholder interfaces
- **TypedArrays** (`Uint8Array`, etc.) - Defined in WebIDL namespace as placeholder interfaces
- **DOM types** (`HTMLVideoElement`, etc.) - Considered external, may need additional mapping

## Notes and Limitations

- **C# single inheritance limitation**: If a dictionary would need multiple base classes, only one can be inherited; others must be noted in comments
- **Union types**: Full C# representation of arbitrary union types is limited; marked with attribute and comment
- **Iterables**: Not fully representable in C# type system; documented via comment
- **Constructor attributes**: Currently represented as comments in generated interface
- **Method overloads**: WebIDL allows multiple operations with the same name; C# may need different method names or use overloading rules

