1 for resource like main objects like GPUAdapter, GPUBuffer etc, map them to interfaces, just like current existing IGPUAdapter (with except of GPU, which is entry point thus mapped to class)
2 For enum like data, use proper naming in CamelCases
3 For all webgpu webidl interfaces with destory method, map it to IClosable
4 make collection like type to IVector or IVectorView based on if it is mutable
5 map setlike type to IVectorView or IVector
6 map interface with only setlike/collectionlike directly to collections
7 map async properly to windows foundation's AsyncOption or similar types
8 for mixin, map them to interface inherients if properly
9 ensure result idl is WinRT idiomatic
