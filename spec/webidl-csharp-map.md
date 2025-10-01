# Rules to Map WebIDL to CSharp

## Type Mapping

- webidl interface type should map to csharp interface
- webidl dictionary type should map to csharp class
- webidl typedef to single type should map to csharp type alias (using)
- webidl typedef to union type should map to csharp abstract class (for union) and sub type (for cases)
- webidl mixin should be map to csharp inheritance, webidl interface mixins should always be valid, but since csharp class only support single inheritance, webidl dictionary mixins might not be support if more than one dictionary is mixed in, a csharp comment should be leave to indicate this
- webidl integer enums should be map to csharp enum, with correct values
- webidl string enums should be map to csharp enum, with correct names, and no predefined values, with a `[WebIDLStringEnum]` attribute
- enum names should be escaped to valid csharp name, if changed should add a `[WebIDLName("<original-name>")]` attribute
- webidl primitive types should be properly mapped to csharp primitive types, with same signedness and size (e.g. `unsigned long long` should be mapped to `UInt64` or `ulong`)
- webidl nullable types should be mapped to csharp nullable types (e.g. `long?`), with a `[WebIDLNullable]` attribute
- webidl `T or undefined` union type should be mapped to csharp nullable types (e.g. `T?`), with a `[WebIDLOrUndefined]` attribute
- some special webidl `or` type may not support, should be noted in the csharp code using comment
- methods returning `undefined` should be mapped to csharp `void`
- to preserve maximum information, sequence, promise etc generic types has been defined in csharp, thus should be used directly for mapping
- special webidl interface with `setlike<t>` or `maplike<t>` should be mapped to csharp `interface <interface-name> : setlike<T>` or `interface <interface-name> : maplike<K, V>` respectively

