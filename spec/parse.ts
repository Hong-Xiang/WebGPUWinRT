import { parse } from "webidl2";
import type * as webidl from 'webidl2';
import webgpuSpec from './webgpu.webidl' with { type: "text" };
import { visitRootType, BaseIDLVisitor, type IDLRootTypeVisitor } from './visitors';

const ast = parse(webgpuSpec);

// Example 1: Simple visitor that counts different node types
class NodeCounterVisitor extends BaseIDLVisitor<void> {
    counts = {
        interfaces: 0,
        dictionaries: 0,
        enums: 0,
        callbacks: 0,
        typedefs: 0,
    };

    protected defaultVisit(_node: any): void {
        // Do nothing by default
    }

    visitInterface(node: webidl.InterfaceType): void {
        this.counts.interfaces++;
        console.log(`Interface: ${node.name}`);
        return this.defaultVisit(node);
    }

    visitDictionary(node: webidl.DictionaryType): void {
        this.counts.dictionaries++;
        console.log(`Dictionary: ${node.name}`);
        return this.defaultVisit(node);
    }

    visitEnum(node: webidl.EnumType): void {
        this.counts.enums++;
        console.log(`Enum: ${node.name}`);
        return this.defaultVisit(node);
    }

    visitCallback(node: webidl.CallbackType): void {
        this.counts.callbacks++;
        console.log(`Callback: ${node.name}`);
        return this.defaultVisit(node);
    }

    visitTypedef(node: webidl.TypedefType): void {
        this.counts.typedefs++;
        console.log(`Typedef: ${node.name}`);
        return this.defaultVisit(node);
    }
}

// Example 2: Visitor that collects all interface names
class InterfaceNameCollector implements IDLRootTypeVisitor<string | null> {
    names: string[] = [];

    visitInterface(node: webidl.InterfaceType): string {
        this.names.push(node.name);
        return node.name;
    }

    visitCallback(_node: webidl.CallbackType): null { return null; }
    visitCallbackInterface(_node: webidl.CallbackInterfaceType): null { return null; }
    visitDictionary(_node: webidl.DictionaryType): null { return null; }
    visitEnum(_node: webidl.EnumType): null { return null; }
    visitIncludes(_node: webidl.IncludesType): null { return null; }
    visitInterfaceMixin(_node: webidl.InterfaceMixinType): null { return null; }
    visitNamespace(_node: webidl.NamespaceType): null { return null; }
    visitTypedef(_node: webidl.TypedefType): null { return null; }
}

// Use the visitors
console.log('=== Counting nodes ===');
const counter = new NodeCounterVisitor();
ast.forEach(node => visitRootType(node, counter));
console.log('\nCounts:', counter.counts);

console.log('\n=== Collecting interface names ===');
const collector = new InterfaceNameCollector();
ast.forEach(node => visitRootType(node, collector));
console.log('Interfaces:', collector.names);

// Output full AST as JSON (commented out to reduce noise)
// console.log(JSON.stringify(ast, null, 2));