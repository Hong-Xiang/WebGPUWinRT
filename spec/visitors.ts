import type * as webidl from 'webidl2';

/**
 * Visitor interface for traversing IDL root-level declarations.
 * Generic parameter T represents the return type of visitor methods.
 */
export interface IDLRootTypeVisitor<T> {
    visitCallback(node: webidl.CallbackType): T;
    visitCallbackInterface(node: webidl.CallbackInterfaceType): T;
    visitDictionary(node: webidl.DictionaryType): T;
    visitEnum(node: webidl.EnumType): T;
    visitIncludes(node: webidl.IncludesType): T;
    visitInterfaceMixin(node: webidl.InterfaceMixinType): T;
    visitInterface(node: webidl.InterfaceType): T;
    visitNamespace(node: webidl.NamespaceType): T;
    visitTypedef(node: webidl.TypedefType): T;
}

/**
 * Visitor interface for traversing interface/mixin/namespace members.
 */
export interface IDLMemberVisitor<T> {
    visitAttribute(node: webidl.AttributeMemberType): T;
    visitConstant(node: webidl.ConstantMemberType): T;
    visitConstructor(node: webidl.ConstructorMemberType): T;
    visitOperation(node: webidl.OperationMemberType): T;
    visitIterable(node: webidl.IterableDeclarationMemberType): T;
    visitMaplike(node: webidl.MaplikeDeclarationMemberType): T;
    visitSetlike(node: webidl.SetlikeDeclarationMemberType): T;
    visitField(node: webidl.FieldType): T;
}

/**
 * Visitor interface for traversing IDL type descriptions.
 */
export interface IDLTypeVisitor<T> {
    visitSingleType(node: webidl.SingleTypeDescription): T;
    visitUnionType(node: webidl.UnionTypeDescription): T;
    visitPromiseType(node: webidl.PromiseTypeDescription): T;
    visitSequenceType(node: webidl.SequenceTypeDescription): T;
    visitFrozenArrayType(node: webidl.FrozenArrayTypeDescription): T;
    visitObservableArrayType(node: webidl.ObservableArrayTypeDescription): T;
    visitRecordType(node: webidl.RecordTypeDescription): T;
}

/**
 * Visitor interface for traversing value descriptions (default values, constants).
 */
export interface IDLValueVisitor<T> {
    visitStringValue(node: webidl.ValueDescriptionString): T;
    visitNumberValue(node: webidl.ValueDescriptionNumber): T;
    visitBooleanValue(node: webidl.ValueDescriptionBoolean): T;
    visitNullValue(node: webidl.ValueDescriptionNull): T;
    visitInfinityValue(node: webidl.ValueDescriptionInfinity): T;
    visitNaNValue(node: webidl.ValueDescriptionNaN): T;
    visitSequenceValue(node: webidl.ValueDescriptionSequence): T;
    visitDictionaryValue(node: webidl.ValueDescriptionDictionary): T;
}

/**
 * Visitor interface for traversing extended attributes.
 */
export interface IDLExtendedAttributeVisitor<T> {
    visitExtendedAttribute(node: webidl.ExtendedAttribute): T;
}

/**
 * Visitor interface for traversing function/operation arguments.
 */
export interface IDLArgumentVisitor<T> {
    visitArgument(node: webidl.Argument): T;
}

/**
 * Combined visitor interface that includes all visitor methods.
 * Use this for full AST traversal capabilities.
 */
export interface IDLVisitor<T> extends 
    IDLRootTypeVisitor<T>,
    IDLMemberVisitor<T>,
    IDLTypeVisitor<T>,
    IDLValueVisitor<T>,
    IDLExtendedAttributeVisitor<T>,
    IDLArgumentVisitor<T> {}

/**
 * Helper function to visit an IDL root type node.
 */
export function visitRootType<T>(node: webidl.IDLRootType, visitor: IDLRootTypeVisitor<T>): T {
    switch (node.type) {
        case 'callback':
            return visitor.visitCallback(node);
        case 'callback interface':
            return visitor.visitCallbackInterface(node);
        case 'dictionary':
            return visitor.visitDictionary(node);
        case 'enum':
            return visitor.visitEnum(node);
        case 'includes':
            return visitor.visitIncludes(node);
        case 'interface mixin':
            return visitor.visitInterfaceMixin(node);
        case 'interface':
            return visitor.visitInterface(node);
        case 'namespace':
            return visitor.visitNamespace(node);
        case 'typedef':
            return visitor.visitTypedef(node);
        default:
            const _exhaustive: never = node;
            throw new Error(`Unknown root type: ${_exhaustive['type']}`);
    }
}

/**
 * Helper function to visit an IDL member node.
 */
export function visitMember<T>(node: webidl.IDLInterfaceMemberType | webidl.FieldType, visitor: IDLMemberVisitor<T>): T {
    switch (node.type) {
        case 'attribute':
            return visitor.visitAttribute(node);
        case 'const':
            return visitor.visitConstant(node);
        case 'constructor':
            return visitor.visitConstructor(node);
        case 'operation':
            return visitor.visitOperation(node);
        case 'iterable':
            return visitor.visitIterable(node);
        case 'maplike':
            return visitor.visitMaplike(node);
        case 'setlike':
            return visitor.visitSetlike(node);
        case 'field':
            return visitor.visitField(node);
        default:
            const _exhaustive: never = node;
            throw new Error(`Unknown member type: ${_exhaustive['type']}`);
    }
}

/**
 * Helper function to visit an IDL type description node.
 */
export function visitType<T>(node: webidl.IDLTypeDescription, visitor: IDLTypeVisitor<T>): T {
    if (node.union) {
        return visitor.visitUnionType(node);
    }
    
    switch (node.generic) {
        case '':
            return visitor.visitSingleType(node);
        case 'Promise':
            return visitor.visitPromiseType(node);
        case 'sequence':
            return visitor.visitSequenceType(node);
        case 'FrozenArray':
            return visitor.visitFrozenArrayType(node);
        case 'ObservableArray':
            return visitor.visitObservableArrayType(node);
        case 'record':
            return visitor.visitRecordType(node);
        default:
            throw new Error(`Unknown generic type: ${(node as any).generic}`);
    }
}

/**
 * Helper function to visit an IDL value description node.
 */
export function visitValue<T>(node: webidl.ValueDescription, visitor: IDLValueVisitor<T>): T {
    switch (node.type) {
        case 'string':
            return visitor.visitStringValue(node);
        case 'number':
            return visitor.visitNumberValue(node);
        case 'boolean':
            return visitor.visitBooleanValue(node);
        case 'null':
            return visitor.visitNullValue(node);
        case 'Infinity':
            return visitor.visitInfinityValue(node);
        case 'NaN':
            return visitor.visitNaNValue(node);
        case 'sequence':
            return visitor.visitSequenceValue(node);
        case 'dictionary':
            return visitor.visitDictionaryValue(node);
        default:
            const _exhaustive: never = node;
            throw new Error(`Unknown value type: ${_exhaustive['type']}`);
    }
}

/**
 * Abstract base class that provides default implementations for all visitor methods.
 * Extend this class and override only the methods you need.
 */
export abstract class BaseIDLVisitor<T> implements IDLVisitor<T> {
    // Root types
    visitCallback(node: webidl.CallbackType): T {
        return this.defaultVisit(node);
    }
    
    visitCallbackInterface(node: webidl.CallbackInterfaceType): T {
        return this.defaultVisit(node);
    }
    
    visitDictionary(node: webidl.DictionaryType): T {
        return this.defaultVisit(node);
    }
    
    visitEnum(node: webidl.EnumType): T {
        return this.defaultVisit(node);
    }
    
    visitIncludes(node: webidl.IncludesType): T {
        return this.defaultVisit(node);
    }
    
    visitInterfaceMixin(node: webidl.InterfaceMixinType): T {
        return this.defaultVisit(node);
    }
    
    visitInterface(node: webidl.InterfaceType): T {
        return this.defaultVisit(node);
    }
    
    visitNamespace(node: webidl.NamespaceType): T {
        return this.defaultVisit(node);
    }
    
    visitTypedef(node: webidl.TypedefType): T {
        return this.defaultVisit(node);
    }
    
    // Members
    visitAttribute(node: webidl.AttributeMemberType): T {
        return this.defaultVisit(node);
    }
    
    visitConstant(node: webidl.ConstantMemberType): T {
        return this.defaultVisit(node);
    }
    
    visitConstructor(node: webidl.ConstructorMemberType): T {
        return this.defaultVisit(node);
    }
    
    visitOperation(node: webidl.OperationMemberType): T {
        return this.defaultVisit(node);
    }
    
    visitIterable(node: webidl.IterableDeclarationMemberType): T {
        return this.defaultVisit(node);
    }
    
    visitMaplike(node: webidl.MaplikeDeclarationMemberType): T {
        return this.defaultVisit(node);
    }
    
    visitSetlike(node: webidl.SetlikeDeclarationMemberType): T {
        return this.defaultVisit(node);
    }
    
    visitField(node: webidl.FieldType): T {
        return this.defaultVisit(node);
    }
    
    // Types
    visitSingleType(node: webidl.SingleTypeDescription): T {
        return this.defaultVisit(node);
    }
    
    visitUnionType(node: webidl.UnionTypeDescription): T {
        return this.defaultVisit(node);
    }
    
    visitPromiseType(node: webidl.PromiseTypeDescription): T {
        return this.defaultVisit(node);
    }
    
    visitSequenceType(node: webidl.SequenceTypeDescription): T {
        return this.defaultVisit(node);
    }
    
    visitFrozenArrayType(node: webidl.FrozenArrayTypeDescription): T {
        return this.defaultVisit(node);
    }
    
    visitObservableArrayType(node: webidl.ObservableArrayTypeDescription): T {
        return this.defaultVisit(node);
    }
    
    visitRecordType(node: webidl.RecordTypeDescription): T {
        return this.defaultVisit(node);
    }
    
    // Values
    visitStringValue(node: webidl.ValueDescriptionString): T {
        return this.defaultVisit(node);
    }
    
    visitNumberValue(node: webidl.ValueDescriptionNumber): T {
        return this.defaultVisit(node);
    }
    
    visitBooleanValue(node: webidl.ValueDescriptionBoolean): T {
        return this.defaultVisit(node);
    }
    
    visitNullValue(node: webidl.ValueDescriptionNull): T {
        return this.defaultVisit(node);
    }
    
    visitInfinityValue(node: webidl.ValueDescriptionInfinity): T {
        return this.defaultVisit(node);
    }
    
    visitNaNValue(node: webidl.ValueDescriptionNaN): T {
        return this.defaultVisit(node);
    }
    
    visitSequenceValue(node: webidl.ValueDescriptionSequence): T {
        return this.defaultVisit(node);
    }
    
    visitDictionaryValue(node: webidl.ValueDescriptionDictionary): T {
        return this.defaultVisit(node);
    }
    
    // Extended attributes
    visitExtendedAttribute(node: webidl.ExtendedAttribute): T {
        return this.defaultVisit(node);
    }
    
    // Arguments
    visitArgument(node: webidl.Argument): T {
        return this.defaultVisit(node);
    }
    
    /**
     * Default visit method called by all specific visit methods.
     * Override this to provide a common behavior for all nodes.
     */
    protected abstract defaultVisit(node: any): T;
}
