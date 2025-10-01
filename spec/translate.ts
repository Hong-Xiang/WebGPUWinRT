import { parse } from "webidl2";
import type * as webidl from 'webidl2';
import webgpuSpec from './webgpu.webidl' with { type: "text" };
import { visitRootType } from './visitors';
import { WebIDLToCSharpVisitor, TranslationContext } from './webidl-to-csharp';
import { CSharpCodeBuilder } from './csharp-codegen';

/**
 * Main translator that converts WebIDL to C# code
 */
function translateWebIDLToCSharp(ast: webidl.IDLRootType[]): string {
    const context = new TranslationContext();
    const builder = new CSharpCodeBuilder();
    
    // First pass: Build context (collect mixins and includes)
    console.log('=== Building translation context ===');
    ast.forEach(node => {
        context.addRootType(node);
        
        if (node.type === 'interface mixin') {
            context.addMixin(node.name, node);
            console.log(`  Registered mixin: ${node.name}`);
        } else if (node.type === 'includes') {
            context.addInclude(node.target, node.includes);
            console.log(`  Registered include: ${node.target} includes ${node.includes}`);
        }
    });
    
    // Add using directives first
    builder.addUsing('using System;');
    builder.addUsing('using System.Collections.Generic;');
    builder.addUsing('using WebIDL;');
    builder.addUsing('using System.Diagnostics.CodeAnalysis;');
    
    // Add file header
    builder.addBlockComment([
        'Auto-generated from WebIDL specification',
        'Do not modify this file manually',
        `Generated: ${new Date().toISOString()}`,
    ]);
    builder.addLine();
    
    // Add file-scoped namespace
    builder.addLine('namespace WebGPU;');
    builder.addLine();
    
    // Second pass: Generate C# code for each root type
    console.log('\n=== Generating C# code ===');
    const visitor = new WebIDLToCSharpVisitor(context, builder);

    ast.forEach(node => {
        // Skip includes as they're already processed
        if (node.type === 'includes') {
            return;
        }

        // Determine the type name for deduplication
        let typeName: string | undefined = undefined;
        if ('name' in node && node.name) {
            typeName = node.name;
        }

        const nodeName = typeName || (node as any).type;
        console.log(`  Processing: ${nodeName} (${(node as any).type})`);

        // Visit the node (code is emitted as side effect to builder)
        visitRootType(node, visitor);
    });
    
    return builder.toString();
}

// Main execution
console.log('=== WebIDL to C# Translator ===\n');

const ast = parse(webgpuSpec);
console.log(`Parsed ${ast.length} root types from WebIDL specification\n`);

const csharpCode = translateWebIDLToCSharp(ast);

console.log('\n=== Translation Complete ===');
console.log(`Generated ${csharpCode.split('\n').length} lines of C# code\n`);

// Output the generated code
console.log('=== Generated C# Code ===\n');
console.log(csharpCode);

// Also write to file using Bun's API
const outputPath = './webgpu-generated.cs';
await Bun.write(outputPath, csharpCode);
console.log(`\n=== Code written to ${outputPath} ===`);
