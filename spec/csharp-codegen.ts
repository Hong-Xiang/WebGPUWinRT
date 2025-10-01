/**
 * Utilities for generating C# code with proper formatting
 */

export class CSharpCodeBuilder {
  private lines: string[] = [];
  private usings: Set<string> = new Set();
  private indentLevel: number = 0;
  private readonly indentString: string = "    "; // 4 spaces

  /**
   * Adds a using directive (collected and emitted at the top)
   */
  addUsing(usingLine: string): this {
    this.usings.add(usingLine);
    return this;
  }

  /**
   * Adds a line of code with current indentation
   */
  addLine(line: string = ""): this {
    if (line === "") {
      this.lines.push("");
    } else {
      this.lines.push(this.indentString.repeat(this.indentLevel) + line);
    }
    return this;
  }

  /**
   * Adds multiple lines of code
   */
  addLines(lines: string[]): this {
    lines.forEach((line) => this.addLine(line));
    return this;
  }

  /**
   * Adds raw text without indentation
   */
  addRaw(text: string): this {
    this.lines.push(text);
    return this;
  }

  /**
   * Increases indentation level
   */
  indent(): this {
    this.indentLevel++;
    return this;
  }

  /**
   * Decreases indentation level
   */
  unindent(): this {
    if (this.indentLevel > 0) {
      this.indentLevel--;
    }
    return this;
  }

  /**
   * Adds an opening brace and increases indentation
   */
  openBrace(): this {
    return this.addLine("{").indent();
  }

  /**
   * Decreases indentation and adds a closing brace
   */
  closeBrace(semicolon: boolean = false): this {
    return this.unindent().addLine(semicolon ? "};" : "}");
  }

  /**
   * Adds a C# attribute
   */
  addAttribute(name: string, args?: string[]): this {
    if (args && args.length > 0) {
      return this.addLine(`[${name}(${args.join(", ")})]`);
    } else {
      return this.addLine(`[${name}]`);
    }
    return this;
  }

  /**
   * Adds multiple C# attributes
   */
  addAttributes(attributes: Array<{ name: string; args?: string[] }>): this {
    attributes.forEach((attr) => this.addAttribute(attr.name, attr.args));
    return this;
  }

  /**
   * Adds a C# comment
   */
  addComment(comment: string): this {
    return this.addLine(`// ${comment}`);
  }

  /**
   * Adds a multi-line C# comment
   */
  addBlockComment(lines: string[]): this {
    this.addLine("/*");
    lines.forEach((line) => this.addLine(` * ${line}`));
    this.addLine(" */");
    return this;
  }

  /**
   * Adds an XML documentation comment
   */
  addXmlDoc(summary: string, remarks?: string[]): this {
    this.addLine("/// <summary>");
    summary.split("\n").forEach((line) => this.addLine(`/// ${line}`));
    this.addLine("/// </summary>");

    if (remarks && remarks.length > 0) {
      this.addLine("/// <remarks>");
      remarks.forEach((remark) => this.addLine(`/// ${remark}`));
      this.addLine("/// </remarks>");
    }

    return this;
  }

  /**
   * Returns the generated code as a string, with usings at the top
   */
  toString(): string {
    const usings = Array.from(this.usings).sort().join("\n");
    return (usings ? usings + "\n" : "") + this.lines.join("\n");
  }

  /**
   * Clears all generated code
   */
  clear(): this {
    this.lines = [];
    this.indentLevel = 0;
    return this;
  }

  /**
   * Gets the current indentation level
   */
  getIndentLevel(): number {
    return this.indentLevel;
  }
}

/**
 * Helper to build C# method signatures
 */
export interface CSharpMethodSignature {
  modifiers?: string[];
  returnType: string;
  name: string;
  parameters: Array<{ type: string; name: string; defaultValue?: string }>;
  isAsync?: boolean;
}

export function buildMethodSignature(sig: CSharpMethodSignature): string {
  const parts: string[] = [];

  if (sig.modifiers && sig.modifiers.length > 0) {
    parts.push(sig.modifiers.join(" "));
  }

  if (sig.isAsync) {
    parts.push("async");
  }

  parts.push(sig.returnType);
  parts.push(sig.name);

  const params = sig.parameters.map((p) => {
    let param = `${p.type} ${p.name}`;
    if (p.defaultValue !== undefined) {
      param += ` = ${p.defaultValue}`;
    }
    return param;
  });

  parts.push(`(${params.join(", ")})`);

  return parts.join(" ");
}

/**
 * Helper to build C# property signatures
 */

export interface CSharpPropertySignature {
  modifiers?: string[];
  type: string;
  name: string;
  getter?: "get" | "get;" | string;
  setter?: "set" | "set;" | string;
  defaultValue?: string;
  required?: boolean;
  isInterface?: boolean;
}

export function buildPropertySignature(sig: CSharpPropertySignature): string {
  const parts: string[] = [];
  if (sig.modifiers && sig.modifiers.length > 0) {
    parts.push(sig.modifiers.join(" "));
  }
  if (sig.required) {
    parts.push("required");
  }
  parts.push(sig.type);
  parts.push(sig.name);
  if (sig.getter || sig.setter) {
    const accessors: string[] = [];
    if (sig.getter) {
      accessors.push(sig.getter);
    }
    if (sig.setter) {
      accessors.push(sig.setter);
    }
    parts.push(`{ ${accessors.join(" ")} }`);
  }
  if (sig.defaultValue !== undefined) {
    parts.push(`= ${sig.defaultValue}`);
  }
  
  // Only add semicolon if it's not an interface property
  if (sig.isInterface) {
    return parts.join(" ");
  }
  
  // For class properties: only add semicolon if there's a default value
  if (sig.defaultValue !== undefined) {
    return parts.join(" ") + ";";
  }
  
  // Properties with only { get; set; } don't need semicolon
  return parts.join(" ");
}
