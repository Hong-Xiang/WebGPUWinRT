import type * as webidl from "webidl2";
import { BaseIDLVisitor, visitType, visitMember } from "./visitors";
import {
  CSharpCodeBuilder,
  buildMethodSignature,
  buildPropertySignature,
} from "./csharp-codegen";
import {
  mapWebIDLTypeToCSharp,
  escapeCSharpName,
  needsNullableAttribute,
} from "./csharp-types";

/**
 * Context for tracking mixin relationships and includes
 */
export class TranslationContext {
  /** Map of interface name to mixins it includes */
  includesMap = new Map<string, string[]>();

  /** Map of mixin name to its definition */
  mixins = new Map<string, webidl.InterfaceMixinType>();

  /** All root types for lookup */
  rootTypes = new Map<string, webidl.IDLRootType>();

  addInclude(target: string, mixin: string): void {
    if (!this.includesMap.has(target)) {
      this.includesMap.set(target, []);
    }
    this.includesMap.get(target)!.push(mixin);
  }

  addMixin(name: string, mixin: webidl.InterfaceMixinType): void {
    this.mixins.set(name, mixin);
  }

  addRootType(node: webidl.IDLRootType): void {
    if ("name" in node && node.name) {
      this.rootTypes.set(node.name, node);
    }
  }

  getMixinsForInterface(name: string): string[] {
    return this.includesMap.get(name) || [];
  }
}

/**
 * Visitor that translates WebIDL to C# code
 */
export class WebIDLToCSharpVisitor extends BaseIDLVisitor<void> {
  private emitted = new Set<string>();

  constructor(
    private context: TranslationContext,
    private builder: CSharpCodeBuilder
  ) {
    super();
  }

  protected defaultVisit(_node: any): void {
    // No-op
  }

  /**
   * Visits an interface and generates C# interface code
   */
  visitInterface(node: webidl.InterfaceType): void {
    if (this.emitted.has(node.name)) return;
    this.emitted.add(node.name);

    this.builder.addLine();

    // Add XML documentation if available
    this.builder.addXmlDoc(`Interface: ${node.name}`);

    // Add extended attributes as C# attributes
    this.addExtendedAttributesAsCSharp(node.extAttrs);

    // Build interface declaration
    const modifiers = ["public"];
    let declaration = `${modifiers.join(" ")} interface ${escapeCSharpName(
      node.name
    )}`;

    // Add inheritance
    const baseTypes: string[] = [];
    if (node.inheritance) {
      baseTypes.push(escapeCSharpName(node.inheritance));
    }

    // Add mixins
    const mixins = this.context.getMixinsForInterface(node.name);
    mixins.forEach((mixin) => {
      baseTypes.push(escapeCSharpName(mixin));
      this.builder.addComment(`Includes mixin: ${mixin}`);
    });

    if (baseTypes.length > 0) {
      declaration += ` : ${baseTypes.join(", ")}`;
    }

    this.builder.addLine(declaration);
    this.builder.openBrace();

    // Process members
    node.members.forEach((member) => {
      const memberCode = this.visitInterfaceMember(member);
      if (memberCode) {
        this.builder.addLine(memberCode);
      }
    });

    this.builder.closeBrace();

    return this.builder.toString();
  }

  /**
   * Visits a dictionary and generates C# class code
   */
  visitDictionary(node: webidl.DictionaryType): void {
    if (this.emitted.has(node.name)) return;
    this.emitted.add(node.name);

    this.builder.addLine();

    // Add XML documentation
    this.builder.addXmlDoc(`Dictionary: ${node.name}`);

    // Add extended attributes
    this.addExtendedAttributesAsCSharp(node.extAttrs);

    // Build class declaration
    const modifiers = ["public"];
    let declaration = `${modifiers.join(" ")} class ${escapeCSharpName(
      node.name
    )}`;

    // Add inheritance
    if (node.inheritance) {
      declaration += ` : ${escapeCSharpName(node.inheritance)}`;
    }

    this.builder.addLine(declaration);
    this.builder.openBrace();

    // Process fields as properties
    node.members.forEach((field) => {
      const fieldCode = this.visitField(field);
      if (fieldCode) {
        this.builder.addLine(fieldCode);
      }
    });

    this.builder.closeBrace();
  }

  /**
   * Visits an enum and generates C# enum code
   */
  visitEnum(node: webidl.EnumType): void {
    if (this.emitted.has(node.name)) return;
    this.emitted.add(node.name);

    this.builder.addLine();

    // Check if it's a string enum (all WebIDL enums are string enums)
    this.builder.addXmlDoc(`Enum: ${node.name}`);
    this.builder.addAttribute("WebIDLStringEnum");

    this.builder.addLine(`public enum ${escapeCSharpName(node.name)}`);
    this.builder.openBrace();

    // Add enum values
    node.values.forEach((value, index) => {
      const enumName = this.convertEnumValueToName(value.value);
      const escapedName = escapeCSharpName(enumName);

      // Add attribute if name was changed
      if (escapedName !== value.value) {
        this.builder.addAttribute("WebIDLName", [`"${value.value}"`]);
      }

      const comma = index < node.values.length - 1 ? "," : "";
      this.builder.addLine(`${escapedName}${comma}`);
    });

    this.builder.closeBrace();
  }

  /**
   * Visits a typedef and generates C# using directive or class
   */
  visitTypedef(node: webidl.TypedefType): void {
    if (this.emitted.has(node.name)) return;
    this.emitted.add(node.name);

    const targetType = mapWebIDLTypeToCSharp(node.idlType);

    // Check if it's a union type
    if (node.idlType.union) {
      // Generate an abstract class for union types
      this.builder.addLine();
      this.builder.addXmlDoc(`Union typedef: ${node.name}`);
      this.builder.addAttribute("WebIDLUnion");
      this.builder.addLine(
        `public abstract class ${escapeCSharpName(node.name)}`
      );
      this.builder.openBrace();
      this.builder.addComment("Union type members would be generated here");
      this.builder.closeBrace();
    } else {
      // Simple type alias - use C# using directive at the top
      this.builder.addUsing(
        `using ${escapeCSharpName(node.name)} = ${targetType};`
      );
    }
  }

  /**
   * Visits a callback and generates C# delegate
   */
  visitCallback(node: webidl.CallbackType): void {
    if (this.emitted.has(node.name)) return;
    this.emitted.add(node.name);

    this.builder.addLine();

    this.builder.addXmlDoc(`Callback: ${node.name}`);

    const returnType = mapWebIDLTypeToCSharp(node.idlType);
    const parameters = node.arguments.map((arg) => {
      const type = mapWebIDLTypeToCSharp(arg.idlType);
      const name = escapeCSharpName(arg.name);
      return `${type} ${name}`;
    });

    this.builder.addLine(
      `public delegate ${returnType} ${escapeCSharpName(
        node.name
      )}(${parameters.join(", ")});`
    );
  }

  /**
   * Visits a namespace and generates C# static class
   */
  visitNamespace(node: webidl.NamespaceType): void {
    if (this.emitted.has(node.name)) return;
    this.emitted.add(node.name);

    this.builder.addLine();

    this.builder.addXmlDoc(`Namespace: ${node.name}`);

    this.builder.addLine(`public static class ${escapeCSharpName(node.name)}`);
    this.builder.openBrace();

    // Process members
    node.members.forEach((member) => {
      if (member.type === "operation") {
        const methodCode = this.generateOperation(member, true);
        if (methodCode) {
          this.builder.addLine(methodCode);
        }
      } else if (member.type === "attribute") {
        const propCode = this.generateAttribute(member, true);
        if (propCode) {
          this.builder.addLine(propCode);
        }
      }
    });

    this.builder.closeBrace();
  }

  /**
   * Visits an includes statement (handled in context building)
   */
  visitIncludes(_node: webidl.IncludesType): void {
    // Includes are handled in the context building phase
  }

  /**
   * Visits an interface mixin (stored for later use)
   */
  visitInterfaceMixin(node: webidl.InterfaceMixinType): void {
    if (this.emitted.has(node.name)) return;
    this.emitted.add(node.name);

    this.builder.addLine();

    // Add XML documentation
    this.builder.addXmlDoc(`Interface Mixin: ${node.name}`);

    // Add extended attributes
    this.addExtendedAttributesAsCSharp(node.extAttrs);

    // Emit as interface
    this.builder.addLine(`public interface ${escapeCSharpName(node.name)}`);
    this.builder.openBrace();

    // Process members
    node.members.forEach((member) => {
      const memberCode = this.visitInterfaceMember(member);
      if (memberCode) {
        this.builder.addLine(memberCode);
      }
    });

    this.builder.closeBrace();
  }

  /**
   * Visits a callback interface
   */
  visitCallbackInterface(node: webidl.CallbackInterfaceType): void {
    if (this.emitted.has(node.name)) return;
    this.emitted.add(node.name);

    this.builder.addLine();

    this.builder.addXmlDoc(`Callback Interface: ${node.name}`);
    this.builder.addAttribute("WebIDLCallbackInterface");

    this.builder.addLine(`public interface ${escapeCSharpName(node.name)}`);
    this.builder.openBrace();

    node.members.forEach((member) => {
      const memberCode = this.visitInterfaceMember(member);
      if (memberCode) {
        this.builder.addLine(memberCode);
      }
    });

    this.builder.closeBrace();
  }

  // Helper methods

  private visitInterfaceMember(member: webidl.IDLInterfaceMemberType): string {
    switch (member.type) {
      case "attribute":
        return this.generateAttribute(member, false);
      case "operation":
        return this.generateOperation(member, false);
      case "const":
        return this.generateConstant(member);
      case "constructor":
        return this.generateConstructor(member);
      case "iterable":
      case "maplike":
      case "setlike":
        return this.generateDeclaration(member);
      default:
        return `// Unsupported member type: ${(member as any).type}`;
    }
  }

  private generateAttribute(
    attr: webidl.AttributeMemberType,
    isStatic: boolean
  ): string {
    const type = mapWebIDLTypeToCSharp(attr.idlType);
    const name = escapeCSharpName(attr.name);
    const modifiers: string[] = [];
    if (isStatic) {
      modifiers.push("static");
    }
    const getter = attr.readonly ? "get;" : "get; set;";
    let result = "";
    if (needsNullableAttribute(attr.idlType)) {
      result += `[WebIDLNullable]\n`;
    }
    result += buildPropertySignature({
      modifiers,
      type,
      name,
      getter,
      isInterface: true,
    });
    return result;
  }

  private generateOperation(
    op: webidl.OperationMemberType,
    isStatic: boolean
  ): string {
    const returnType = op.idlType ? mapWebIDLTypeToCSharp(op.idlType) : "void";
    const name = op.name ? escapeCSharpName(op.name) : "UnnamedOperation";
    const modifiers: string[] = [];

    if (isStatic || op.special === "static") {
      modifiers.push("static");
    }

    let hasDefaultParam = false;
    const parameters = op.arguments.map((arg) => {
      let paramType = mapWebIDLTypeToCSharp(arg.idlType);
      let defaultValue: string | undefined = undefined;
      
      if (arg.default) {
        defaultValue = this.formatDefaultValue(arg.default, arg.idlType);
        hasDefaultParam = true;
      } else if (arg.optional) {
        // Optional parameters should be nullable
        if (!paramType.endsWith('?')) {
          paramType += '?';
        }
        // If a previous parameter had a default value, this needs = default
        if (hasDefaultParam) {
          defaultValue = 'default';
        }
      }
      
      return {
        type: paramType,
        name: escapeCSharpName(arg.name),
        defaultValue,
      };
    });

    return (
      buildMethodSignature({
        modifiers,
        returnType,
        name,
        parameters,
      }) + ";"
    );
  }

  private generateConstant(constant: webidl.ConstantMemberType): string {
    const type = mapWebIDLTypeToCSharp(constant.idlType);
    const name = escapeCSharpName(constant.name);
    const value = this.formatConstantValue(constant.value);

    return `public const ${type} ${name} = ${value};`;
  }

  private generateConstructor(_ctor: webidl.ConstructorMemberType): string {
    // Constructors in interfaces are represented as attributes
    return "// [Constructor] attribute";
  }

  private generateDeclaration(decl: webidl.DeclarationMemberType): string {
    if (decl.type === "iterable") {
      const types = decl.idlType.map((t) => mapWebIDLTypeToCSharp(t));
      return `// Iterable<${types.join(", ")}>`;
    } else if (decl.type === "maplike") {
      const [keyType, valueType] = decl.idlType.map((t) =>
        mapWebIDLTypeToCSharp(t)
      );
      return `// : IMaplike<${keyType}, ${valueType}>`;
    } else if (decl.type === "setlike") {
      const type = mapWebIDLTypeToCSharp(decl.idlType[0]);
      return `// : ISetlike<${type}>`;
    }
    return "";
  }

  private generateField(field: webidl.FieldType): string {
    const type = mapWebIDLTypeToCSharp(field.idlType);
    const name = escapeCSharpName(field.name);
    let result = "";
    if (needsNullableAttribute(field.idlType)) {
      result += "[WebIDLNullable]\n";
    }
    if (field.default && this.needsNewObjectDefaultAttribute(field.default)) {
      result += "[WebIDLNewObjectDefaultValue]\n";
    }
    const defaultValue = field.default
      ? this.formatDefaultValue(field.default, field.idlType)
      : undefined;
    result += buildPropertySignature({
      modifiers: ["public"],
      type,
      name,
      getter: "get;",
      setter: "set;",
      defaultValue,
      required: field.required,
    });
    return result;
  }

  visitField(field: webidl.FieldType): string {
    return this.generateField(field);
  }

  private addExtendedAttributesAsCSharp(
    extAttrs: webidl.ExtendedAttribute[]
  ): void {
    extAttrs.forEach((attr) => {
      if (attr.name === "Exposed" || attr.name === "SecureContext") {
        this.builder.addAttribute(`WebIDL${attr.name}`);
      }
    });
  }

  private convertEnumValueToName(value: string): string {
    // Only replace '-' with '_', keep original casing
    return escapeCSharpName(value.replace(/-/g, "_"));
  }

  private formatDefaultValue(value: webidl.ValueDescription, fieldType?: webidl.IDLTypeDescription): string {
    switch (value.type) {
      case "string":
        // Check if the field type is an enum
        if (fieldType && !fieldType.generic && !fieldType.union && typeof fieldType.idlType === 'string') {
          // Try to find if this is an enum type
          const typeName = fieldType.idlType;
          const rootType = this.context.rootTypes.get(typeName);
          
          // List of known external enum types (defined in WebIDL namespace)
          const externalEnums = ['PredefinedColorSpace'];
          
          if ((rootType && rootType.type === 'enum') || externalEnums.includes(typeName)) {
            // It's an enum, use EnumType.value format
            const enumValueName = this.convertEnumValueToName(value.value as string);
            return `${escapeCSharpName(typeName)}.${enumValueName}`;
          }
        }
        return `"${value.value}"`;
      case "number":
        return String(value.value);
      case "boolean":
        return value.value ? "true" : "false";
      case "null":
        return "null";
      case "Infinity":
        return value.negative
          ? "double.NegativeInfinity"
          : "double.PositiveInfinity";
      case "NaN":
        return "double.NaN";
      case "sequence":
        return "default";
      case "dictionary":
        return "default";
      default:
        return "default";
    }
  }

  private needsNewObjectDefaultAttribute(value: webidl.ValueDescription): boolean {
    return value.type === "dictionary";
  }

  private formatConstantValue(value: webidl.ValueDescription): string {
    return this.formatDefaultValue(value);
  }
}
