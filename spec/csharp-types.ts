import type * as webidl from "webidl2";

/**
 * Maps WebIDL primitive types to C# types
 */
export function mapWebIDLTypeToCSharp(
  idlType: webidl.IDLTypeDescription,
  context: 'generic' | 'normal' = 'normal'
): string {
  if (idlType.union) {
    // Check if it's a "T | undefined" pattern (maps to T? in C#)
    const types = idlType.idlType;
    if (types.length === 2) {
      const hasUndefined = types.some(
        (t) =>
          !t.union &&
          t.generic === "" &&
          (t.idlType === "undefined" || t.idlType === "void")
      );
      if (hasUndefined) {
        // Find the non-undefined type
        const nonUndefinedType = types.find(
          (t) =>
            t.union ||
            t.generic !== "" ||
            (t.idlType !== "undefined" && t.idlType !== "void")
        );
        if (nonUndefinedType) {
          return mapWebIDLTypeToCSharp(nonUndefinedType, context) + "?";
        }
      }
    }
    // Other union types - generate as comment for now
    const typeNames = types.map((t) => mapWebIDLTypeToCSharp(t, context));
    return `object /* Union: ${typeNames.join(" | ")} */`;
  }

  // Handle generic types
  if (idlType.generic !== "") {
    switch (idlType.generic) {
      case "sequence":
        return `Sequence<${mapWebIDLTypeToCSharp(idlType.idlType[0], 'generic')}>`;
      case "Promise":
        return `Promise<${mapWebIDLTypeToCSharp(idlType.idlType[0], 'generic')}>`;
      case "FrozenArray":
        return `FrozenArray<${mapWebIDLTypeToCSharp(idlType.idlType[0], 'generic')}>`;
      case "ObservableArray":
        return `ObservableArray<${mapWebIDLTypeToCSharp(idlType.idlType[0], 'generic')}>`;
      case "record":
        return `Record<${mapWebIDLTypeToCSharp(
          idlType.idlType[0], 'generic'
        )}, ${mapWebIDLTypeToCSharp(idlType.idlType[1], 'generic')}>`;
      default:
        return `${(idlType as any).generic}<Unknown>`;
    }
  }

  // Single type
  const baseType = mapPrimitiveType(idlType.idlType as string, context);
  return idlType.nullable ? `${baseType}?` : baseType;
}

/**
 * Maps WebIDL primitive type names to C# type names
 */
function mapPrimitiveType(typeName: string, context: 'generic' | 'normal' = 'normal'): string {
  const typeMap: Record<string, string> = {
    // Integer types
    byte: "sbyte",
    octet: "byte",
    short: "short",
    "unsigned short": "ushort",
    long: "int",
    "unsigned long": "uint",
    "long long": "long",
    "unsigned long long": "ulong",

    // Floating point
    float: "float",
    "unrestricted float": "float",
    double: "double",
    "unrestricted double": "double",

    // Other primitives
    boolean: "bool",
    DOMString: "string",
    ByteString: "string",
    USVString: "string",

    // Special types
    // In generic context, void must be replaced with Undefined
    undefined: context === 'generic' ? "Undefined" : "void",
    void: context === 'generic' ? "Undefined" : "void",
    any: "object",
    object: "object",
    symbol: "object",
    ArrayBuffer: "ArrayBuffer",
    DataView: "DataView",
    Int8Array: "Int8Array",
    Int16Array: "Int16Array",
    Int32Array: "Int32Array",
    Uint8Array: "Uint8Array",
    Uint16Array: "Uint16Array",
    Uint32Array: "Uint32Array",
    Uint8ClampedArray: "Uint8ClampedArray",
    Float32Array: "Float32Array",
    Float64Array: "Float64Array",
    AllowSharedBufferSource: "AllowSharedBufferSource",

    // WebGPU specific
    GPUSize32: "uint",
    GPUSize64: "ulong",
    GPUIntegerCoordinate: "uint",
    GPUIndex32: "uint",
    GPUSignedOffset32: "int",
    GPUFlagsConstant: "uint",
    GPUBufferUsageFlags: "uint",
    GPUMapModeFlags: "uint",
    GPUTextureUsageFlags: "uint",
    GPUShaderStageFlags: "uint",
    GPUColorWriteFlags: "uint",
    GPUPipelineConstantValue: "double",
  };

  return typeMap[typeName] || typeName;
}

/**
 * Escapes C# keywords and invalid identifiers
 */
export function escapeCSharpName(name: string): string {
  const keywords = new Set([
    "abstract",
    "as",
    "base",
    "bool",
    "break",
    "byte",
    "case",
    "catch",
    "char",
    "checked",
    "class",
    "const",
    "continue",
    "decimal",
    "default",
    "delegate",
    "do",
    "double",
    "else",
    "enum",
    "event",
    "explicit",
    "extern",
    "false",
    "finally",
    "fixed",
    "float",
    "for",
    "foreach",
    "goto",
    "if",
    "implicit",
    "in",
    "int",
    "interface",
    "internal",
    "is",
    "lock",
    "long",
    "namespace",
    "new",
    "null",
    "object",
    "operator",
    "out",
    "override",
    "params",
    "private",
    "protected",
    "public",
    "readonly",
    "ref",
    "return",
    "sbyte",
    "sealed",
    "short",
    "sizeof",
    "stackalloc",
    "static",
    "string",
    "struct",
    "switch",
    "this",
    "throw",
    "true",
    "try",
    "typeof",
    "uint",
    "ulong",
    "unchecked",
    "unsafe",
    "ushort",
    "using",
    "virtual",
    "void",
    "volatile",
    "while",
  ]);

  if (keywords.has(name)) {
    return `@${name}`;
  }

  // Replace hyphens with underscores and handle other invalid characters
  let escaped = name.replace(/-/g, "_");

  // If starts with digit, prefix with underscore
  if (/^\d/.test(escaped)) {
    escaped = "_" + escaped;
  }

  return escaped;
}

/**
 * Checks if a WebIDL type needs a [WebIDLNullable] attribute
 */
export function needsNullableAttribute(
  idlType: webidl.IDLTypeDescription
): boolean {
  return idlType.nullable;
}

/**
 * Checks if extended attributes contain specific attribute
 */
export function hasExtendedAttribute(
  extAttrs: webidl.ExtendedAttribute[],
  name: string
): boolean {
  return extAttrs.some((attr) => attr.name === name);
}

/**
 * Gets the value of an extended attribute
 */
export function getExtendedAttributeValue(
  extAttrs: webidl.ExtendedAttribute[],
  name: string
): any {
  const attr = extAttrs.find((a) => a.name === name);
  return attr?.rhs;
}
