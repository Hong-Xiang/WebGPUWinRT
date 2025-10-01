using GPUBufferDynamicOffset = uint;
using GPUBufferUsageFlags = uint;
using GPUColorWriteFlags = uint;
using GPUDepthBias = int;
using GPUFlagsConstant = uint;
using GPUIndex32 = uint;
using GPUIntegerCoordinate = uint;
using GPUIntegerCoordinateOut = uint;
using GPUMapModeFlags = uint;
using GPUPipelineConstantValue = double;
using GPUSampleMask = uint;
using GPUShaderStageFlags = uint;
using GPUSignedOffset32 = int;
using GPUSize32 = uint;
using GPUSize32Out = uint;
using GPUSize64 = ulong;
using GPUSize64Out = ulong;
using GPUStencilValue = uint;
using GPUTextureUsageFlags = uint;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System;
using WebIDL;
/*
 * Auto-generated from WebIDL specification
 * Do not modify this file manually
 * Generated: 2025-10-01T15:09:52.587Z
 */

namespace WebGPU;


/// <summary>
/// Interface Mixin: GPUObjectBase
/// </summary>
public interface GPUObjectBase
{
    string label { get; set; }
}

/// <summary>
/// Dictionary: GPUObjectDescriptorBase
/// </summary>
public class GPUObjectDescriptorBase
{
    public string label { get; set; } = "";
}

/// <summary>
/// Interface: GPUSupportedLimits
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
public interface GPUSupportedLimits
{
    uint maxTextureDimension1D { get; }
    uint maxTextureDimension2D { get; }
    uint maxTextureDimension3D { get; }
    uint maxTextureArrayLayers { get; }
    uint maxBindGroups { get; }
    uint maxBindGroupsPlusVertexBuffers { get; }
    uint maxBindingsPerBindGroup { get; }
    uint maxDynamicUniformBuffersPerPipelineLayout { get; }
    uint maxDynamicStorageBuffersPerPipelineLayout { get; }
    uint maxSampledTexturesPerShaderStage { get; }
    uint maxSamplersPerShaderStage { get; }
    uint maxStorageBuffersPerShaderStage { get; }
    uint maxStorageTexturesPerShaderStage { get; }
    uint maxUniformBuffersPerShaderStage { get; }
    ulong maxUniformBufferBindingSize { get; }
    ulong maxStorageBufferBindingSize { get; }
    uint minUniformBufferOffsetAlignment { get; }
    uint minStorageBufferOffsetAlignment { get; }
    uint maxVertexBuffers { get; }
    ulong maxBufferSize { get; }
    uint maxVertexAttributes { get; }
    uint maxVertexBufferArrayStride { get; }
    uint maxInterStageShaderVariables { get; }
    uint maxColorAttachments { get; }
    uint maxColorAttachmentBytesPerSample { get; }
    uint maxComputeWorkgroupStorageSize { get; }
    uint maxComputeInvocationsPerWorkgroup { get; }
    uint maxComputeWorkgroupSizeX { get; }
    uint maxComputeWorkgroupSizeY { get; }
    uint maxComputeWorkgroupSizeZ { get; }
    uint maxComputeWorkgroupsPerDimension { get; }
}

/// <summary>
/// Interface: GPUSupportedFeatures
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
[WebIDLReadonlySetlike]
// readonly setlike<string>
public interface GPUSupportedFeatures : setlike<string>
{
}

/// <summary>
/// Interface: WGSLLanguageFeatures
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
[WebIDLReadonlySetlike]
// readonly setlike<string>
public interface WGSLLanguageFeatures : setlike<string>
{
}

/// <summary>
/// Interface: GPUAdapterInfo
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
public interface GPUAdapterInfo
{
    string vendor { get; }
    string architecture { get; }
    string device { get; }
    string description { get; }
    uint subgroupMinSize { get; }
    uint subgroupMaxSize { get; }
    bool isFallbackAdapter { get; }
}

/// <summary>
/// Interface Mixin: NavigatorGPU
/// </summary>
public interface NavigatorGPU
{
    GPU gpu { get; }
}

/// <summary>
/// Interface: GPU
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
public interface GPU
{
    Promise<GPUAdapter?> requestAdapter (GPURequestAdapterOptions options = default);
    GPUTextureFormat getPreferredCanvasFormat ();
    WGSLLanguageFeatures wgslLanguageFeatures { get; }
}

/// <summary>
/// Dictionary: GPURequestAdapterOptions
/// </summary>
public class GPURequestAdapterOptions
{
    public string featureLevel { get; set; } = "core";
    public GPUPowerPreference powerPreference { get; set; }
    public bool forceFallbackAdapter { get; set; } = false;
    public bool xrCompatible { get; set; } = false;
}

/// <summary>
/// Enum: GPUPowerPreference
/// </summary>
[WebIDLStringEnum]
public enum GPUPowerPreference
{
    [WebIDLName("low-power")]
    low_power,
    [WebIDLName("high-performance")]
    high_performance
}

/// <summary>
/// Interface: GPUAdapter
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
public interface GPUAdapter
{
    GPUSupportedFeatures features { get; }
    GPUSupportedLimits limits { get; }
    GPUAdapterInfo info { get; }
    Promise<GPUDevice> requestDevice (GPUDeviceDescriptor descriptor = default);
}

/// <summary>
/// Dictionary: GPUDeviceDescriptor
/// </summary>
public class GPUDeviceDescriptor : GPUObjectDescriptorBase
{
    public Sequence<GPUFeatureName> requiredFeatures { get; set; } = default;
    [WebIDLNewObjectDefaultValue]
public Record<string, ulong?> requiredLimits { get; set; } = default;
    [WebIDLNewObjectDefaultValue]
public GPUQueueDescriptor defaultQueue { get; set; } = default;
}

/// <summary>
/// Enum: GPUFeatureName
/// </summary>
[WebIDLStringEnum]
public enum GPUFeatureName
{
    [WebIDLName("core-features-and-limits")]
    core_features_and_limits,
    [WebIDLName("depth-clip-control")]
    depth_clip_control,
    [WebIDLName("depth32float-stencil8")]
    depth32float_stencil8,
    [WebIDLName("texture-compression-bc")]
    texture_compression_bc,
    [WebIDLName("texture-compression-bc-sliced-3d")]
    texture_compression_bc_sliced_3d,
    [WebIDLName("texture-compression-etc2")]
    texture_compression_etc2,
    [WebIDLName("texture-compression-astc")]
    texture_compression_astc,
    [WebIDLName("texture-compression-astc-sliced-3d")]
    texture_compression_astc_sliced_3d,
    [WebIDLName("timestamp-query")]
    timestamp_query,
    [WebIDLName("indirect-first-instance")]
    indirect_first_instance,
    [WebIDLName("shader-f16")]
    shader_f16,
    [WebIDLName("rg11b10ufloat-renderable")]
    rg11b10ufloat_renderable,
    [WebIDLName("bgra8unorm-storage")]
    bgra8unorm_storage,
    [WebIDLName("float32-filterable")]
    float32_filterable,
    [WebIDLName("float32-blendable")]
    float32_blendable,
    [WebIDLName("clip-distances")]
    clip_distances,
    [WebIDLName("dual-source-blending")]
    dual_source_blending,
    subgroups,
    [WebIDLName("texture-formats-tier1")]
    texture_formats_tier1,
    [WebIDLName("texture-formats-tier2")]
    texture_formats_tier2
}

/// <summary>
/// Interface: GPUDevice
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPUDevice : EventTarget, GPUObjectBase
{
    GPUSupportedFeatures features { get; }
    GPUSupportedLimits limits { get; }
    GPUAdapterInfo adapterInfo { get; }
    GPUQueue queue { get; }
    void destroy ();
    GPUBuffer createBuffer (GPUBufferDescriptor descriptor);
    GPUTexture createTexture (GPUTextureDescriptor descriptor);
    GPUSampler createSampler (GPUSamplerDescriptor descriptor = default);
    GPUExternalTexture importExternalTexture (GPUExternalTextureDescriptor descriptor);
    GPUBindGroupLayout createBindGroupLayout (GPUBindGroupLayoutDescriptor descriptor);
    GPUPipelineLayout createPipelineLayout (GPUPipelineLayoutDescriptor descriptor);
    GPUBindGroup createBindGroup (GPUBindGroupDescriptor descriptor);
    GPUShaderModule createShaderModule (GPUShaderModuleDescriptor descriptor);
    GPUComputePipeline createComputePipeline (GPUComputePipelineDescriptor descriptor);
    GPURenderPipeline createRenderPipeline (GPURenderPipelineDescriptor descriptor);
    Promise<GPUComputePipeline> createComputePipelineAsync (GPUComputePipelineDescriptor descriptor);
    Promise<GPURenderPipeline> createRenderPipelineAsync (GPURenderPipelineDescriptor descriptor);
    GPUCommandEncoder createCommandEncoder (GPUCommandEncoderDescriptor descriptor = default);
    GPURenderBundleEncoder createRenderBundleEncoder (GPURenderBundleEncoderDescriptor descriptor);
    GPUQuerySet createQuerySet (GPUQuerySetDescriptor descriptor);
}

/// <summary>
/// Interface: GPUBuffer
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPUBuffer : GPUObjectBase
{
    GPUSize64Out size { get; }
    uint usage { get; }
    GPUBufferMapState mapState { get; }
    Promise<Undefined> mapAsync (uint mode, ulong offset = 0, ulong? size = default);
    ArrayBuffer getMappedRange (ulong offset = 0, ulong? size = default);
    void unmap ();
    void destroy ();
}

/// <summary>
/// Enum: GPUBufferMapState
/// </summary>
[WebIDLStringEnum]
public enum GPUBufferMapState
{
    unmapped,
    pending,
    mapped
}

/// <summary>
/// Dictionary: GPUBufferDescriptor
/// </summary>
public class GPUBufferDescriptor : GPUObjectDescriptorBase
{
    public required ulong size { get; set; }
    public required uint usage { get; set; }
    public bool mappedAtCreation { get; set; } = false;
}

/// <summary>
/// Namespace: GPUBufferUsage
/// </summary>
public static class GPUBufferUsage
{
    public const uint MAP_READ = 0x0001;
    public const uint MAP_WRITE = 0x0002;
    public const uint COPY_SRC = 0x0004;
    public const uint COPY_DST = 0x0008;
    public const uint INDEX = 0x0010;
    public const uint VERTEX = 0x0020;
    public const uint UNIFORM = 0x0040;
    public const uint STORAGE = 0x0080;
    public const uint INDIRECT = 0x0100;
    public const uint QUERY_RESOLVE = 0x0200;
}

/// <summary>
/// Namespace: GPUMapMode
/// </summary>
public static class GPUMapMode
{
    public const uint READ = 0x0001;
    public const uint WRITE = 0x0002;
}

/// <summary>
/// Interface: GPUTexture
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPUTexture : GPUObjectBase
{
    GPUTextureView createView (GPUTextureViewDescriptor descriptor = default);
    void destroy ();
    GPUIntegerCoordinateOut width { get; }
    GPUIntegerCoordinateOut height { get; }
    GPUIntegerCoordinateOut depthOrArrayLayers { get; }
    GPUIntegerCoordinateOut mipLevelCount { get; }
    GPUSize32Out sampleCount { get; }
    GPUTextureDimension dimension { get; }
    GPUTextureFormat format { get; }
    uint usage { get; }
}

/// <summary>
/// Dictionary: GPUTextureDescriptor
/// </summary>
public class GPUTextureDescriptor : GPUObjectDescriptorBase
{
    public required GPUExtent3D size { get; set; }
    public uint mipLevelCount { get; set; } = 1;
    public uint sampleCount { get; set; } = 1;
    public GPUTextureDimension dimension { get; set; } = GPUTextureDimension._2d;
    public required GPUTextureFormat format { get; set; }
    public required uint usage { get; set; }
    public Sequence<GPUTextureFormat> viewFormats { get; set; } = default;
}

/// <summary>
/// Enum: GPUTextureDimension
/// </summary>
[WebIDLStringEnum]
public enum GPUTextureDimension
{
    [WebIDLName("1d")]
    _1d,
    [WebIDLName("2d")]
    _2d,
    [WebIDLName("3d")]
    _3d
}

/// <summary>
/// Namespace: GPUTextureUsage
/// </summary>
public static class GPUTextureUsage
{
    public const uint COPY_SRC = 0x01;
    public const uint COPY_DST = 0x02;
    public const uint TEXTURE_BINDING = 0x04;
    public const uint STORAGE_BINDING = 0x08;
    public const uint RENDER_ATTACHMENT = 0x10;
}

/// <summary>
/// Interface: GPUTextureView
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPUTextureView : GPUObjectBase
{
}

/// <summary>
/// Dictionary: GPUTextureViewDescriptor
/// </summary>
public class GPUTextureViewDescriptor : GPUObjectDescriptorBase
{
    public GPUTextureFormat format { get; set; }
    public GPUTextureViewDimension dimension { get; set; }
    public uint usage { get; set; } = 0;
    public GPUTextureAspect aspect { get; set; } = GPUTextureAspect.all;
    public uint baseMipLevel { get; set; } = 0;
    public uint mipLevelCount { get; set; }
    public uint baseArrayLayer { get; set; } = 0;
    public uint arrayLayerCount { get; set; }
}

/// <summary>
/// Enum: GPUTextureViewDimension
/// </summary>
[WebIDLStringEnum]
public enum GPUTextureViewDimension
{
    [WebIDLName("1d")]
    _1d,
    [WebIDLName("2d")]
    _2d,
    [WebIDLName("2d-array")]
    _2d_array,
    cube,
    [WebIDLName("cube-array")]
    cube_array,
    [WebIDLName("3d")]
    _3d
}

/// <summary>
/// Enum: GPUTextureAspect
/// </summary>
[WebIDLStringEnum]
public enum GPUTextureAspect
{
    all,
    [WebIDLName("stencil-only")]
    stencil_only,
    [WebIDLName("depth-only")]
    depth_only
}

/// <summary>
/// Enum: GPUTextureFormat
/// </summary>
[WebIDLStringEnum]
public enum GPUTextureFormat
{
    r8unorm,
    r8snorm,
    r8uint,
    r8sint,
    r16unorm,
    r16snorm,
    r16uint,
    r16sint,
    r16float,
    rg8unorm,
    rg8snorm,
    rg8uint,
    rg8sint,
    r32uint,
    r32sint,
    r32float,
    rg16unorm,
    rg16snorm,
    rg16uint,
    rg16sint,
    rg16float,
    rgba8unorm,
    [WebIDLName("rgba8unorm-srgb")]
    rgba8unorm_srgb,
    rgba8snorm,
    rgba8uint,
    rgba8sint,
    bgra8unorm,
    [WebIDLName("bgra8unorm-srgb")]
    bgra8unorm_srgb,
    rgb9e5ufloat,
    rgb10a2uint,
    rgb10a2unorm,
    rg11b10ufloat,
    rg32uint,
    rg32sint,
    rg32float,
    rgba16unorm,
    rgba16snorm,
    rgba16uint,
    rgba16sint,
    rgba16float,
    rgba32uint,
    rgba32sint,
    rgba32float,
    stencil8,
    depth16unorm,
    depth24plus,
    [WebIDLName("depth24plus-stencil8")]
    depth24plus_stencil8,
    depth32float,
    [WebIDLName("depth32float-stencil8")]
    depth32float_stencil8,
    [WebIDLName("bc1-rgba-unorm")]
    bc1_rgba_unorm,
    [WebIDLName("bc1-rgba-unorm-srgb")]
    bc1_rgba_unorm_srgb,
    [WebIDLName("bc2-rgba-unorm")]
    bc2_rgba_unorm,
    [WebIDLName("bc2-rgba-unorm-srgb")]
    bc2_rgba_unorm_srgb,
    [WebIDLName("bc3-rgba-unorm")]
    bc3_rgba_unorm,
    [WebIDLName("bc3-rgba-unorm-srgb")]
    bc3_rgba_unorm_srgb,
    [WebIDLName("bc4-r-unorm")]
    bc4_r_unorm,
    [WebIDLName("bc4-r-snorm")]
    bc4_r_snorm,
    [WebIDLName("bc5-rg-unorm")]
    bc5_rg_unorm,
    [WebIDLName("bc5-rg-snorm")]
    bc5_rg_snorm,
    [WebIDLName("bc6h-rgb-ufloat")]
    bc6h_rgb_ufloat,
    [WebIDLName("bc6h-rgb-float")]
    bc6h_rgb_float,
    [WebIDLName("bc7-rgba-unorm")]
    bc7_rgba_unorm,
    [WebIDLName("bc7-rgba-unorm-srgb")]
    bc7_rgba_unorm_srgb,
    [WebIDLName("etc2-rgb8unorm")]
    etc2_rgb8unorm,
    [WebIDLName("etc2-rgb8unorm-srgb")]
    etc2_rgb8unorm_srgb,
    [WebIDLName("etc2-rgb8a1unorm")]
    etc2_rgb8a1unorm,
    [WebIDLName("etc2-rgb8a1unorm-srgb")]
    etc2_rgb8a1unorm_srgb,
    [WebIDLName("etc2-rgba8unorm")]
    etc2_rgba8unorm,
    [WebIDLName("etc2-rgba8unorm-srgb")]
    etc2_rgba8unorm_srgb,
    [WebIDLName("eac-r11unorm")]
    eac_r11unorm,
    [WebIDLName("eac-r11snorm")]
    eac_r11snorm,
    [WebIDLName("eac-rg11unorm")]
    eac_rg11unorm,
    [WebIDLName("eac-rg11snorm")]
    eac_rg11snorm,
    [WebIDLName("astc-4x4-unorm")]
    astc_4x4_unorm,
    [WebIDLName("astc-4x4-unorm-srgb")]
    astc_4x4_unorm_srgb,
    [WebIDLName("astc-5x4-unorm")]
    astc_5x4_unorm,
    [WebIDLName("astc-5x4-unorm-srgb")]
    astc_5x4_unorm_srgb,
    [WebIDLName("astc-5x5-unorm")]
    astc_5x5_unorm,
    [WebIDLName("astc-5x5-unorm-srgb")]
    astc_5x5_unorm_srgb,
    [WebIDLName("astc-6x5-unorm")]
    astc_6x5_unorm,
    [WebIDLName("astc-6x5-unorm-srgb")]
    astc_6x5_unorm_srgb,
    [WebIDLName("astc-6x6-unorm")]
    astc_6x6_unorm,
    [WebIDLName("astc-6x6-unorm-srgb")]
    astc_6x6_unorm_srgb,
    [WebIDLName("astc-8x5-unorm")]
    astc_8x5_unorm,
    [WebIDLName("astc-8x5-unorm-srgb")]
    astc_8x5_unorm_srgb,
    [WebIDLName("astc-8x6-unorm")]
    astc_8x6_unorm,
    [WebIDLName("astc-8x6-unorm-srgb")]
    astc_8x6_unorm_srgb,
    [WebIDLName("astc-8x8-unorm")]
    astc_8x8_unorm,
    [WebIDLName("astc-8x8-unorm-srgb")]
    astc_8x8_unorm_srgb,
    [WebIDLName("astc-10x5-unorm")]
    astc_10x5_unorm,
    [WebIDLName("astc-10x5-unorm-srgb")]
    astc_10x5_unorm_srgb,
    [WebIDLName("astc-10x6-unorm")]
    astc_10x6_unorm,
    [WebIDLName("astc-10x6-unorm-srgb")]
    astc_10x6_unorm_srgb,
    [WebIDLName("astc-10x8-unorm")]
    astc_10x8_unorm,
    [WebIDLName("astc-10x8-unorm-srgb")]
    astc_10x8_unorm_srgb,
    [WebIDLName("astc-10x10-unorm")]
    astc_10x10_unorm,
    [WebIDLName("astc-10x10-unorm-srgb")]
    astc_10x10_unorm_srgb,
    [WebIDLName("astc-12x10-unorm")]
    astc_12x10_unorm,
    [WebIDLName("astc-12x10-unorm-srgb")]
    astc_12x10_unorm_srgb,
    [WebIDLName("astc-12x12-unorm")]
    astc_12x12_unorm,
    [WebIDLName("astc-12x12-unorm-srgb")]
    astc_12x12_unorm_srgb
}

/// <summary>
/// Interface: GPUExternalTexture
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPUExternalTexture : GPUObjectBase
{
}

/// <summary>
/// Dictionary: GPUExternalTextureDescriptor
/// </summary>
public class GPUExternalTextureDescriptor : GPUObjectDescriptorBase
{
    public required object /* Union: HTMLVideoElement | VideoFrame */ source { get; set; }
    public PredefinedColorSpace colorSpace { get; set; } = PredefinedColorSpace.srgb;
}

/// <summary>
/// Interface: GPUSampler
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPUSampler : GPUObjectBase
{
}

/// <summary>
/// Dictionary: GPUSamplerDescriptor
/// </summary>
public class GPUSamplerDescriptor : GPUObjectDescriptorBase
{
    public GPUAddressMode addressModeU { get; set; } = GPUAddressMode.clamp_to_edge;
    public GPUAddressMode addressModeV { get; set; } = GPUAddressMode.clamp_to_edge;
    public GPUAddressMode addressModeW { get; set; } = GPUAddressMode.clamp_to_edge;
    public GPUFilterMode magFilter { get; set; } = GPUFilterMode.nearest;
    public GPUFilterMode minFilter { get; set; } = GPUFilterMode.nearest;
    public GPUMipmapFilterMode mipmapFilter { get; set; } = GPUMipmapFilterMode.nearest;
    public float lodMinClamp { get; set; } = 0;
    public float lodMaxClamp { get; set; } = 32;
    public GPUCompareFunction compare { get; set; }
    public ushort maxAnisotropy { get; set; } = 1;
}

/// <summary>
/// Enum: GPUAddressMode
/// </summary>
[WebIDLStringEnum]
public enum GPUAddressMode
{
    [WebIDLName("clamp-to-edge")]
    clamp_to_edge,
    repeat,
    [WebIDLName("mirror-repeat")]
    mirror_repeat
}

/// <summary>
/// Enum: GPUFilterMode
/// </summary>
[WebIDLStringEnum]
public enum GPUFilterMode
{
    nearest,
    linear
}

/// <summary>
/// Enum: GPUMipmapFilterMode
/// </summary>
[WebIDLStringEnum]
public enum GPUMipmapFilterMode
{
    nearest,
    linear
}

/// <summary>
/// Enum: GPUCompareFunction
/// </summary>
[WebIDLStringEnum]
public enum GPUCompareFunction
{
    never,
    less,
    equal,
    [WebIDLName("less-equal")]
    less_equal,
    greater,
    [WebIDLName("not-equal")]
    not_equal,
    [WebIDLName("greater-equal")]
    greater_equal,
    always
}

/// <summary>
/// Interface: GPUBindGroupLayout
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPUBindGroupLayout : GPUObjectBase
{
}

/// <summary>
/// Dictionary: GPUBindGroupLayoutDescriptor
/// </summary>
public class GPUBindGroupLayoutDescriptor : GPUObjectDescriptorBase
{
    public required Sequence<GPUBindGroupLayoutEntry> entries { get; set; }
}

/// <summary>
/// Dictionary: GPUBindGroupLayoutEntry
/// </summary>
public class GPUBindGroupLayoutEntry
{
    public required uint binding { get; set; }
    public required uint visibility { get; set; }
    public GPUBufferBindingLayout buffer { get; set; }
    public GPUSamplerBindingLayout sampler { get; set; }
    public GPUTextureBindingLayout texture { get; set; }
    public GPUStorageTextureBindingLayout storageTexture { get; set; }
    public GPUExternalTextureBindingLayout externalTexture { get; set; }
}

/// <summary>
/// Namespace: GPUShaderStage
/// </summary>
public static class GPUShaderStage
{
    public const uint VERTEX = 0x1;
    public const uint FRAGMENT = 0x2;
    public const uint COMPUTE = 0x4;
}

/// <summary>
/// Enum: GPUBufferBindingType
/// </summary>
[WebIDLStringEnum]
public enum GPUBufferBindingType
{
    uniform,
    storage,
    [WebIDLName("read-only-storage")]
    read_only_storage
}

/// <summary>
/// Dictionary: GPUBufferBindingLayout
/// </summary>
public class GPUBufferBindingLayout
{
    public GPUBufferBindingType type { get; set; } = GPUBufferBindingType.uniform;
    public bool hasDynamicOffset { get; set; } = false;
    public ulong minBindingSize { get; set; } = 0;
}

/// <summary>
/// Enum: GPUSamplerBindingType
/// </summary>
[WebIDLStringEnum]
public enum GPUSamplerBindingType
{
    filtering,
    [WebIDLName("non-filtering")]
    non_filtering,
    comparison
}

/// <summary>
/// Dictionary: GPUSamplerBindingLayout
/// </summary>
public class GPUSamplerBindingLayout
{
    public GPUSamplerBindingType type { get; set; } = GPUSamplerBindingType.filtering;
}

/// <summary>
/// Enum: GPUTextureSampleType
/// </summary>
[WebIDLStringEnum]
public enum GPUTextureSampleType
{
    [WebIDLName("float")]
    @float,
    [WebIDLName("unfilterable-float")]
    unfilterable_float,
    depth,
    sint,
    [WebIDLName("uint")]
    @uint
}

/// <summary>
/// Dictionary: GPUTextureBindingLayout
/// </summary>
public class GPUTextureBindingLayout
{
    public GPUTextureSampleType sampleType { get; set; } = GPUTextureSampleType.@float;
    public GPUTextureViewDimension viewDimension { get; set; } = GPUTextureViewDimension._2d;
    public bool multisampled { get; set; } = false;
}

/// <summary>
/// Enum: GPUStorageTextureAccess
/// </summary>
[WebIDLStringEnum]
public enum GPUStorageTextureAccess
{
    [WebIDLName("write-only")]
    write_only,
    [WebIDLName("read-only")]
    read_only,
    [WebIDLName("read-write")]
    read_write
}

/// <summary>
/// Dictionary: GPUStorageTextureBindingLayout
/// </summary>
public class GPUStorageTextureBindingLayout
{
    public GPUStorageTextureAccess access { get; set; } = GPUStorageTextureAccess.write_only;
    public required GPUTextureFormat format { get; set; }
    public GPUTextureViewDimension viewDimension { get; set; } = GPUTextureViewDimension._2d;
}

/// <summary>
/// Dictionary: GPUExternalTextureBindingLayout
/// </summary>
public class GPUExternalTextureBindingLayout
{
}

/// <summary>
/// Interface: GPUBindGroup
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPUBindGroup : GPUObjectBase
{
}

/// <summary>
/// Dictionary: GPUBindGroupDescriptor
/// </summary>
public class GPUBindGroupDescriptor : GPUObjectDescriptorBase
{
    public required GPUBindGroupLayout layout { get; set; }
    public required Sequence<GPUBindGroupEntry> entries { get; set; }
}

/// <summary>
/// Union typedef: GPUBindingResource
/// </summary>
[WebIDLUnion]
public abstract class GPUBindingResource
{
    // Union type members would be generated here
}

/// <summary>
/// Dictionary: GPUBindGroupEntry
/// </summary>
public class GPUBindGroupEntry
{
    public required uint binding { get; set; }
    public required GPUBindingResource resource { get; set; }
}

/// <summary>
/// Dictionary: GPUBufferBinding
/// </summary>
public class GPUBufferBinding
{
    public required GPUBuffer buffer { get; set; }
    public ulong offset { get; set; } = 0;
    public ulong size { get; set; }
}

/// <summary>
/// Interface: GPUPipelineLayout
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPUPipelineLayout : GPUObjectBase
{
}

/// <summary>
/// Dictionary: GPUPipelineLayoutDescriptor
/// </summary>
public class GPUPipelineLayoutDescriptor : GPUObjectDescriptorBase
{
    public required Sequence<GPUBindGroupLayout?> bindGroupLayouts { get; set; }
}

/// <summary>
/// Interface: GPUShaderModule
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPUShaderModule : GPUObjectBase
{
    Promise<GPUCompilationInfo> getCompilationInfo ();
}

/// <summary>
/// Dictionary: GPUShaderModuleDescriptor
/// </summary>
public class GPUShaderModuleDescriptor : GPUObjectDescriptorBase
{
    public required string code { get; set; }
    public Sequence<GPUShaderModuleCompilationHint> compilationHints { get; set; } = default;
}

/// <summary>
/// Dictionary: GPUShaderModuleCompilationHint
/// </summary>
public class GPUShaderModuleCompilationHint
{
    public required string entryPoint { get; set; }
    public object /* Union: GPUPipelineLayout | GPUAutoLayoutMode */ layout { get; set; }
}

/// <summary>
/// Enum: GPUCompilationMessageType
/// </summary>
[WebIDLStringEnum]
public enum GPUCompilationMessageType
{
    error,
    warning,
    info
}

/// <summary>
/// Interface: GPUCompilationMessage
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSerializable]
[WebIDLSecureContext]
public interface GPUCompilationMessage
{
    string message { get; }
    GPUCompilationMessageType type { get; }
    ulong lineNum { get; }
    ulong linePos { get; }
    ulong offset { get; }
    ulong length { get; }
}

/// <summary>
/// Interface: GPUCompilationInfo
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSerializable]
[WebIDLSecureContext]
public interface GPUCompilationInfo
{
    FrozenArray<GPUCompilationMessage> messages { get; }
}

/// <summary>
/// Interface: GPUPipelineError
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
[WebIDLSerializable]
public interface GPUPipelineError : DOMException
{
    // [Constructor] attribute
    GPUPipelineErrorReason reason { get; }
}

/// <summary>
/// Dictionary: GPUPipelineErrorInit
/// </summary>
public class GPUPipelineErrorInit
{
    public required GPUPipelineErrorReason reason { get; set; }
}

/// <summary>
/// Enum: GPUPipelineErrorReason
/// </summary>
[WebIDLStringEnum]
public enum GPUPipelineErrorReason
{
    validation,
    [WebIDLName("internal")]
    @internal
}

/// <summary>
/// Enum: GPUAutoLayoutMode
/// </summary>
[WebIDLStringEnum]
public enum GPUAutoLayoutMode
{
    auto
}

/// <summary>
/// Dictionary: GPUPipelineDescriptorBase
/// </summary>
public class GPUPipelineDescriptorBase : GPUObjectDescriptorBase
{
    public required object /* Union: GPUPipelineLayout | GPUAutoLayoutMode */ layout { get; set; }
}

/// <summary>
/// Interface Mixin: GPUPipelineBase
/// </summary>
public interface GPUPipelineBase
{
    GPUBindGroupLayout getBindGroupLayout (uint index);
}

/// <summary>
/// Dictionary: GPUProgrammableStage
/// </summary>
public class GPUProgrammableStage
{
    public required GPUShaderModule module { get; set; }
    public string entryPoint { get; set; }
    [WebIDLNewObjectDefaultValue]
public Record<string, double> constants { get; set; } = default;
}

/// <summary>
/// Interface: GPUComputePipeline
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
// Includes mixin: GPUPipelineBase
public interface GPUComputePipeline : GPUObjectBase, GPUPipelineBase
{
}

/// <summary>
/// Dictionary: GPUComputePipelineDescriptor
/// </summary>
public class GPUComputePipelineDescriptor : GPUPipelineDescriptorBase
{
    public required GPUProgrammableStage compute { get; set; }
}

/// <summary>
/// Interface: GPURenderPipeline
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
// Includes mixin: GPUPipelineBase
public interface GPURenderPipeline : GPUObjectBase, GPUPipelineBase
{
}

/// <summary>
/// Dictionary: GPURenderPipelineDescriptor
/// </summary>
public class GPURenderPipelineDescriptor : GPUPipelineDescriptorBase
{
    public required GPUVertexState vertex { get; set; }
    [WebIDLNewObjectDefaultValue]
public GPUPrimitiveState primitive { get; set; } = default;
    public GPUDepthStencilState depthStencil { get; set; }
    [WebIDLNewObjectDefaultValue]
public GPUMultisampleState multisample { get; set; } = default;
    public GPUFragmentState fragment { get; set; }
}

/// <summary>
/// Dictionary: GPUPrimitiveState
/// </summary>
public class GPUPrimitiveState
{
    public GPUPrimitiveTopology topology { get; set; } = GPUPrimitiveTopology.triangle_list;
    public GPUIndexFormat stripIndexFormat { get; set; }
    public GPUFrontFace frontFace { get; set; } = GPUFrontFace.ccw;
    public GPUCullMode cullMode { get; set; } = GPUCullMode.none;
    public bool unclippedDepth { get; set; } = false;
}

/// <summary>
/// Enum: GPUPrimitiveTopology
/// </summary>
[WebIDLStringEnum]
public enum GPUPrimitiveTopology
{
    [WebIDLName("point-list")]
    point_list,
    [WebIDLName("line-list")]
    line_list,
    [WebIDLName("line-strip")]
    line_strip,
    [WebIDLName("triangle-list")]
    triangle_list,
    [WebIDLName("triangle-strip")]
    triangle_strip
}

/// <summary>
/// Enum: GPUFrontFace
/// </summary>
[WebIDLStringEnum]
public enum GPUFrontFace
{
    ccw,
    cw
}

/// <summary>
/// Enum: GPUCullMode
/// </summary>
[WebIDLStringEnum]
public enum GPUCullMode
{
    none,
    front,
    back
}

/// <summary>
/// Dictionary: GPUMultisampleState
/// </summary>
public class GPUMultisampleState
{
    public uint count { get; set; } = 1;
    public GPUSampleMask mask { get; set; } = 0xFFFFFFFF;
    public bool alphaToCoverageEnabled { get; set; } = false;
}

/// <summary>
/// Dictionary: GPUFragmentState
/// </summary>
public class GPUFragmentState : GPUProgrammableStage
{
    public required Sequence<GPUColorTargetState?> targets { get; set; }
}

/// <summary>
/// Dictionary: GPUColorTargetState
/// </summary>
public class GPUColorTargetState
{
    public required GPUTextureFormat format { get; set; }
    public GPUBlendState blend { get; set; }
    public uint writeMask { get; set; } = 0xF;
}

/// <summary>
/// Dictionary: GPUBlendState
/// </summary>
public class GPUBlendState
{
    public required GPUBlendComponent color { get; set; }
    public required GPUBlendComponent alpha { get; set; }
}

/// <summary>
/// Namespace: GPUColorWrite
/// </summary>
public static class GPUColorWrite
{
    public const uint RED = 0x1;
    public const uint GREEN = 0x2;
    public const uint BLUE = 0x4;
    public const uint ALPHA = 0x8;
    public const uint ALL = 0xF;
}

/// <summary>
/// Dictionary: GPUBlendComponent
/// </summary>
public class GPUBlendComponent
{
    public GPUBlendOperation operation { get; set; } = GPUBlendOperation.add;
    public GPUBlendFactor srcFactor { get; set; } = GPUBlendFactor.one;
    public GPUBlendFactor dstFactor { get; set; } = GPUBlendFactor.zero;
}

/// <summary>
/// Enum: GPUBlendFactor
/// </summary>
[WebIDLStringEnum]
public enum GPUBlendFactor
{
    zero,
    one,
    src,
    [WebIDLName("one-minus-src")]
    one_minus_src,
    [WebIDLName("src-alpha")]
    src_alpha,
    [WebIDLName("one-minus-src-alpha")]
    one_minus_src_alpha,
    dst,
    [WebIDLName("one-minus-dst")]
    one_minus_dst,
    [WebIDLName("dst-alpha")]
    dst_alpha,
    [WebIDLName("one-minus-dst-alpha")]
    one_minus_dst_alpha,
    [WebIDLName("src-alpha-saturated")]
    src_alpha_saturated,
    constant,
    [WebIDLName("one-minus-constant")]
    one_minus_constant,
    src1,
    [WebIDLName("one-minus-src1")]
    one_minus_src1,
    [WebIDLName("src1-alpha")]
    src1_alpha,
    [WebIDLName("one-minus-src1-alpha")]
    one_minus_src1_alpha
}

/// <summary>
/// Enum: GPUBlendOperation
/// </summary>
[WebIDLStringEnum]
public enum GPUBlendOperation
{
    add,
    subtract,
    [WebIDLName("reverse-subtract")]
    reverse_subtract,
    min,
    max
}

/// <summary>
/// Dictionary: GPUDepthStencilState
/// </summary>
public class GPUDepthStencilState
{
    public required GPUTextureFormat format { get; set; }
    public bool depthWriteEnabled { get; set; }
    public GPUCompareFunction depthCompare { get; set; }
    [WebIDLNewObjectDefaultValue]
public GPUStencilFaceState stencilFront { get; set; } = default;
    [WebIDLNewObjectDefaultValue]
public GPUStencilFaceState stencilBack { get; set; } = default;
    public GPUStencilValue stencilReadMask { get; set; } = 0xFFFFFFFF;
    public GPUStencilValue stencilWriteMask { get; set; } = 0xFFFFFFFF;
    public GPUDepthBias depthBias { get; set; } = 0;
    public float depthBiasSlopeScale { get; set; } = 0;
    public float depthBiasClamp { get; set; } = 0;
}

/// <summary>
/// Dictionary: GPUStencilFaceState
/// </summary>
public class GPUStencilFaceState
{
    public GPUCompareFunction compare { get; set; } = GPUCompareFunction.always;
    public GPUStencilOperation failOp { get; set; } = GPUStencilOperation.keep;
    public GPUStencilOperation depthFailOp { get; set; } = GPUStencilOperation.keep;
    public GPUStencilOperation passOp { get; set; } = GPUStencilOperation.keep;
}

/// <summary>
/// Enum: GPUStencilOperation
/// </summary>
[WebIDLStringEnum]
public enum GPUStencilOperation
{
    keep,
    zero,
    replace,
    invert,
    [WebIDLName("increment-clamp")]
    increment_clamp,
    [WebIDLName("decrement-clamp")]
    decrement_clamp,
    [WebIDLName("increment-wrap")]
    increment_wrap,
    [WebIDLName("decrement-wrap")]
    decrement_wrap
}

/// <summary>
/// Enum: GPUIndexFormat
/// </summary>
[WebIDLStringEnum]
public enum GPUIndexFormat
{
    uint16,
    uint32
}

/// <summary>
/// Enum: GPUVertexFormat
/// </summary>
[WebIDLStringEnum]
public enum GPUVertexFormat
{
    uint8,
    uint8x2,
    uint8x4,
    sint8,
    sint8x2,
    sint8x4,
    unorm8,
    unorm8x2,
    unorm8x4,
    snorm8,
    snorm8x2,
    snorm8x4,
    uint16,
    uint16x2,
    uint16x4,
    sint16,
    sint16x2,
    sint16x4,
    unorm16,
    unorm16x2,
    unorm16x4,
    snorm16,
    snorm16x2,
    snorm16x4,
    float16,
    float16x2,
    float16x4,
    float32,
    float32x2,
    float32x3,
    float32x4,
    uint32,
    uint32x2,
    uint32x3,
    uint32x4,
    sint32,
    sint32x2,
    sint32x3,
    sint32x4,
    [WebIDLName("unorm10-10-10-2")]
    unorm10_10_10_2,
    [WebIDLName("unorm8x4-bgra")]
    unorm8x4_bgra
}

/// <summary>
/// Enum: GPUVertexStepMode
/// </summary>
[WebIDLStringEnum]
public enum GPUVertexStepMode
{
    vertex,
    instance
}

/// <summary>
/// Dictionary: GPUVertexState
/// </summary>
public class GPUVertexState : GPUProgrammableStage
{
    public Sequence<GPUVertexBufferLayout?> buffers { get; set; } = default;
}

/// <summary>
/// Dictionary: GPUVertexBufferLayout
/// </summary>
public class GPUVertexBufferLayout
{
    public required ulong arrayStride { get; set; }
    public GPUVertexStepMode stepMode { get; set; } = GPUVertexStepMode.vertex;
    public required Sequence<GPUVertexAttribute> attributes { get; set; }
}

/// <summary>
/// Dictionary: GPUVertexAttribute
/// </summary>
public class GPUVertexAttribute
{
    public required GPUVertexFormat format { get; set; }
    public required ulong offset { get; set; }
    public required uint shaderLocation { get; set; }
}

/// <summary>
/// Dictionary: GPUTexelCopyBufferLayout
/// </summary>
public class GPUTexelCopyBufferLayout
{
    public ulong offset { get; set; } = 0;
    public uint bytesPerRow { get; set; }
    public uint rowsPerImage { get; set; }
}

/// <summary>
/// Dictionary: GPUTexelCopyBufferInfo
/// </summary>
public class GPUTexelCopyBufferInfo : GPUTexelCopyBufferLayout
{
    public required GPUBuffer buffer { get; set; }
}

/// <summary>
/// Dictionary: GPUTexelCopyTextureInfo
/// </summary>
public class GPUTexelCopyTextureInfo
{
    public required GPUTexture texture { get; set; }
    public uint mipLevel { get; set; } = 0;
    [WebIDLNewObjectDefaultValue]
public GPUOrigin3D origin { get; set; } = default;
    public GPUTextureAspect aspect { get; set; } = GPUTextureAspect.all;
}

/// <summary>
/// Dictionary: GPUCopyExternalImageDestInfo
/// </summary>
public class GPUCopyExternalImageDestInfo : GPUTexelCopyTextureInfo
{
    public PredefinedColorSpace colorSpace { get; set; } = PredefinedColorSpace.srgb;
    public bool premultipliedAlpha { get; set; } = false;
}

/// <summary>
/// Union typedef: GPUCopyExternalImageSource
/// </summary>
[WebIDLUnion]
public abstract class GPUCopyExternalImageSource
{
    // Union type members would be generated here
}

/// <summary>
/// Dictionary: GPUCopyExternalImageSourceInfo
/// </summary>
public class GPUCopyExternalImageSourceInfo
{
    public required GPUCopyExternalImageSource source { get; set; }
    [WebIDLNewObjectDefaultValue]
public GPUOrigin2D origin { get; set; } = default;
    public bool flipY { get; set; } = false;
}

/// <summary>
/// Interface: GPUCommandBuffer
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPUCommandBuffer : GPUObjectBase
{
}

/// <summary>
/// Dictionary: GPUCommandBufferDescriptor
/// </summary>
public class GPUCommandBufferDescriptor : GPUObjectDescriptorBase
{
}

/// <summary>
/// Interface Mixin: GPUCommandsMixin
/// </summary>
public interface GPUCommandsMixin
{
}

/// <summary>
/// Interface: GPUCommandEncoder
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
// Includes mixin: GPUCommandsMixin
// Includes mixin: GPUDebugCommandsMixin
public interface GPUCommandEncoder : GPUObjectBase, GPUCommandsMixin, GPUDebugCommandsMixin
{
    GPURenderPassEncoder beginRenderPass (GPURenderPassDescriptor descriptor);
    GPUComputePassEncoder beginComputePass (GPUComputePassDescriptor descriptor = default);
    void copyBufferToBuffer (GPUBuffer source, GPUBuffer destination, ulong? size);
    void copyBufferToBuffer (GPUBuffer source, ulong sourceOffset, GPUBuffer destination, ulong destinationOffset, ulong? size);
    void copyBufferToTexture (GPUTexelCopyBufferInfo source, GPUTexelCopyTextureInfo destination, GPUExtent3D copySize);
    void copyTextureToBuffer (GPUTexelCopyTextureInfo source, GPUTexelCopyBufferInfo destination, GPUExtent3D copySize);
    void copyTextureToTexture (GPUTexelCopyTextureInfo source, GPUTexelCopyTextureInfo destination, GPUExtent3D copySize);
    void clearBuffer (GPUBuffer buffer, ulong offset = 0, ulong? size = default);
    void resolveQuerySet (GPUQuerySet querySet, uint firstQuery, uint queryCount, GPUBuffer destination, ulong destinationOffset);
    GPUCommandBuffer finish (GPUCommandBufferDescriptor descriptor = default);
}

/// <summary>
/// Dictionary: GPUCommandEncoderDescriptor
/// </summary>
public class GPUCommandEncoderDescriptor : GPUObjectDescriptorBase
{
}

/// <summary>
/// Interface Mixin: GPUBindingCommandsMixin
/// </summary>
public interface GPUBindingCommandsMixin
{
    void setBindGroup (uint index, GPUBindGroup? bindGroup, Sequence<GPUBufferDynamicOffset> dynamicOffsets = default);
    void setBindGroup (uint index, GPUBindGroup? bindGroup, Uint32Array dynamicOffsetsData, ulong dynamicOffsetsDataStart, uint dynamicOffsetsDataLength);
}

/// <summary>
/// Interface Mixin: GPUDebugCommandsMixin
/// </summary>
public interface GPUDebugCommandsMixin
{
    void pushDebugGroup (string groupLabel);
    void popDebugGroup ();
    void insertDebugMarker (string markerLabel);
}

/// <summary>
/// Interface: GPUComputePassEncoder
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
// Includes mixin: GPUCommandsMixin
// Includes mixin: GPUDebugCommandsMixin
// Includes mixin: GPUBindingCommandsMixin
public interface GPUComputePassEncoder : GPUObjectBase, GPUCommandsMixin, GPUDebugCommandsMixin, GPUBindingCommandsMixin
{
    void setPipeline (GPUComputePipeline pipeline);
    void dispatchWorkgroups (uint workgroupCountX, uint workgroupCountY = 1, uint workgroupCountZ = 1);
    void dispatchWorkgroupsIndirect (GPUBuffer indirectBuffer, ulong indirectOffset);
    void end ();
}

/// <summary>
/// Dictionary: GPUComputePassTimestampWrites
/// </summary>
public class GPUComputePassTimestampWrites
{
    public required GPUQuerySet querySet { get; set; }
    public uint beginningOfPassWriteIndex { get; set; }
    public uint endOfPassWriteIndex { get; set; }
}

/// <summary>
/// Dictionary: GPUComputePassDescriptor
/// </summary>
public class GPUComputePassDescriptor : GPUObjectDescriptorBase
{
    public GPUComputePassTimestampWrites timestampWrites { get; set; }
}

/// <summary>
/// Interface: GPURenderPassEncoder
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
// Includes mixin: GPUCommandsMixin
// Includes mixin: GPUDebugCommandsMixin
// Includes mixin: GPUBindingCommandsMixin
// Includes mixin: GPURenderCommandsMixin
public interface GPURenderPassEncoder : GPUObjectBase, GPUCommandsMixin, GPUDebugCommandsMixin, GPUBindingCommandsMixin, GPURenderCommandsMixin
{
    void setViewport (float x, float y, float width, float height, float minDepth, float maxDepth);
    void setScissorRect (uint x, uint y, uint width, uint height);
    void setBlendConstant (GPUColor color);
    void setStencilReference (GPUStencilValue reference);
    void beginOcclusionQuery (uint queryIndex);
    void endOcclusionQuery ();
    void executeBundles (Sequence<GPURenderBundle> bundles);
    void end ();
}

/// <summary>
/// Dictionary: GPURenderPassTimestampWrites
/// </summary>
public class GPURenderPassTimestampWrites
{
    public required GPUQuerySet querySet { get; set; }
    public uint beginningOfPassWriteIndex { get; set; }
    public uint endOfPassWriteIndex { get; set; }
}

/// <summary>
/// Dictionary: GPURenderPassDescriptor
/// </summary>
public class GPURenderPassDescriptor : GPUObjectDescriptorBase
{
    public required Sequence<GPURenderPassColorAttachment?> colorAttachments { get; set; }
    public GPURenderPassDepthStencilAttachment depthStencilAttachment { get; set; }
    public GPUQuerySet occlusionQuerySet { get; set; }
    public GPURenderPassTimestampWrites timestampWrites { get; set; }
    public ulong maxDrawCount { get; set; } = 50000000;
}

/// <summary>
/// Dictionary: GPURenderPassColorAttachment
/// </summary>
public class GPURenderPassColorAttachment
{
    public required object /* Union: GPUTexture | GPUTextureView */ view { get; set; }
    public uint depthSlice { get; set; }
    public object /* Union: GPUTexture | GPUTextureView */ resolveTarget { get; set; }
    public GPUColor clearValue { get; set; }
    public required GPULoadOp loadOp { get; set; }
    public required GPUStoreOp storeOp { get; set; }
}

/// <summary>
/// Dictionary: GPURenderPassDepthStencilAttachment
/// </summary>
public class GPURenderPassDepthStencilAttachment
{
    public required object /* Union: GPUTexture | GPUTextureView */ view { get; set; }
    public float depthClearValue { get; set; }
    public GPULoadOp depthLoadOp { get; set; }
    public GPUStoreOp depthStoreOp { get; set; }
    public bool depthReadOnly { get; set; } = false;
    public GPUStencilValue stencilClearValue { get; set; } = 0;
    public GPULoadOp stencilLoadOp { get; set; }
    public GPUStoreOp stencilStoreOp { get; set; }
    public bool stencilReadOnly { get; set; } = false;
}

/// <summary>
/// Enum: GPULoadOp
/// </summary>
[WebIDLStringEnum]
public enum GPULoadOp
{
    load,
    clear
}

/// <summary>
/// Enum: GPUStoreOp
/// </summary>
[WebIDLStringEnum]
public enum GPUStoreOp
{
    store,
    discard
}

/// <summary>
/// Dictionary: GPURenderPassLayout
/// </summary>
public class GPURenderPassLayout : GPUObjectDescriptorBase
{
    public required Sequence<GPUTextureFormat?> colorFormats { get; set; }
    public GPUTextureFormat depthStencilFormat { get; set; }
    public uint sampleCount { get; set; } = 1;
}

/// <summary>
/// Interface Mixin: GPURenderCommandsMixin
/// </summary>
public interface GPURenderCommandsMixin
{
    void setPipeline (GPURenderPipeline pipeline);
    void setIndexBuffer (GPUBuffer buffer, GPUIndexFormat indexFormat, ulong offset = 0, ulong? size = default);
    void setVertexBuffer (uint slot, GPUBuffer? buffer, ulong offset = 0, ulong? size = default);
    void draw (uint vertexCount, uint instanceCount = 1, uint firstVertex = 0, uint firstInstance = 0);
    void drawIndexed (uint indexCount, uint instanceCount = 1, uint firstIndex = 0, int baseVertex = 0, uint firstInstance = 0);
    void drawIndirect (GPUBuffer indirectBuffer, ulong indirectOffset);
    void drawIndexedIndirect (GPUBuffer indirectBuffer, ulong indirectOffset);
}

/// <summary>
/// Interface: GPURenderBundle
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPURenderBundle : GPUObjectBase
{
}

/// <summary>
/// Dictionary: GPURenderBundleDescriptor
/// </summary>
public class GPURenderBundleDescriptor : GPUObjectDescriptorBase
{
}

/// <summary>
/// Interface: GPURenderBundleEncoder
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
// Includes mixin: GPUCommandsMixin
// Includes mixin: GPUDebugCommandsMixin
// Includes mixin: GPUBindingCommandsMixin
// Includes mixin: GPURenderCommandsMixin
public interface GPURenderBundleEncoder : GPUObjectBase, GPUCommandsMixin, GPUDebugCommandsMixin, GPUBindingCommandsMixin, GPURenderCommandsMixin
{
    GPURenderBundle finish (GPURenderBundleDescriptor descriptor = default);
}

/// <summary>
/// Dictionary: GPURenderBundleEncoderDescriptor
/// </summary>
public class GPURenderBundleEncoderDescriptor : GPURenderPassLayout
{
    public bool depthReadOnly { get; set; } = false;
    public bool stencilReadOnly { get; set; } = false;
}

/// <summary>
/// Dictionary: GPUQueueDescriptor
/// </summary>
public class GPUQueueDescriptor : GPUObjectDescriptorBase
{
}

/// <summary>
/// Interface: GPUQueue
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPUQueue : GPUObjectBase
{
    void submit (Sequence<GPUCommandBuffer> commandBuffers);
    Promise<Undefined> onSubmittedWorkDone ();
    void writeBuffer (GPUBuffer buffer, ulong bufferOffset, AllowSharedBufferSource data, ulong dataOffset = 0, ulong? size = default);
    void writeTexture (GPUTexelCopyTextureInfo destination, AllowSharedBufferSource data, GPUTexelCopyBufferLayout dataLayout, GPUExtent3D size);
    void copyExternalImageToTexture (GPUCopyExternalImageSourceInfo source, GPUCopyExternalImageDestInfo destination, GPUExtent3D copySize);
}

/// <summary>
/// Interface: GPUQuerySet
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
// Includes mixin: GPUObjectBase
public interface GPUQuerySet : GPUObjectBase
{
    void destroy ();
    GPUQueryType type { get; }
    GPUSize32Out count { get; }
}

/// <summary>
/// Dictionary: GPUQuerySetDescriptor
/// </summary>
public class GPUQuerySetDescriptor : GPUObjectDescriptorBase
{
    public required GPUQueryType type { get; set; }
    public required uint count { get; set; }
}

/// <summary>
/// Enum: GPUQueryType
/// </summary>
[WebIDLStringEnum]
public enum GPUQueryType
{
    occlusion,
    timestamp
}

/// <summary>
/// Interface: GPUCanvasContext
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
public interface GPUCanvasContext
{
    object /* Union: HTMLCanvasElement | OffscreenCanvas */ canvas { get; }
    void configure (GPUCanvasConfiguration configuration);
    void unconfigure ();
    GPUCanvasConfiguration? getConfiguration ();
    GPUTexture getCurrentTexture ();
}

/// <summary>
/// Enum: GPUCanvasAlphaMode
/// </summary>
[WebIDLStringEnum]
public enum GPUCanvasAlphaMode
{
    opaque,
    premultiplied
}

/// <summary>
/// Enum: GPUCanvasToneMappingMode
/// </summary>
[WebIDLStringEnum]
public enum GPUCanvasToneMappingMode
{
    standard,
    extended
}

/// <summary>
/// Dictionary: GPUCanvasToneMapping
/// </summary>
public class GPUCanvasToneMapping
{
    public GPUCanvasToneMappingMode mode { get; set; } = GPUCanvasToneMappingMode.standard;
}

/// <summary>
/// Dictionary: GPUCanvasConfiguration
/// </summary>
public class GPUCanvasConfiguration
{
    public required GPUDevice device { get; set; }
    public required GPUTextureFormat format { get; set; }
    public uint usage { get; set; } = 0x10;
    public Sequence<GPUTextureFormat> viewFormats { get; set; } = default;
    public PredefinedColorSpace colorSpace { get; set; } = PredefinedColorSpace.srgb;
    [WebIDLNewObjectDefaultValue]
public GPUCanvasToneMapping toneMapping { get; set; } = default;
    public GPUCanvasAlphaMode alphaMode { get; set; } = GPUCanvasAlphaMode.opaque;
}

/// <summary>
/// Enum: GPUDeviceLostReason
/// </summary>
[WebIDLStringEnum]
public enum GPUDeviceLostReason
{
    unknown,
    destroyed
}

/// <summary>
/// Interface: GPUDeviceLostInfo
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
public interface GPUDeviceLostInfo
{
    GPUDeviceLostReason reason { get; }
    string message { get; }
}

/// <summary>
/// Interface: GPUError
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
public interface GPUError
{
    string message { get; }
}

/// <summary>
/// Interface: GPUValidationError
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
public interface GPUValidationError : GPUError
{
    // [Constructor] attribute
}

/// <summary>
/// Interface: GPUOutOfMemoryError
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
public interface GPUOutOfMemoryError : GPUError
{
    // [Constructor] attribute
}

/// <summary>
/// Interface: GPUInternalError
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
public interface GPUInternalError : GPUError
{
    // [Constructor] attribute
}

/// <summary>
/// Enum: GPUErrorFilter
/// </summary>
[WebIDLStringEnum]
public enum GPUErrorFilter
{
    validation,
    [WebIDLName("out-of-memory")]
    out_of_memory,
    [WebIDLName("internal")]
    @internal
}

/// <summary>
/// Interface: GPUUncapturedErrorEvent
/// </summary>
[WebIDLExposed("Window", "Worker")]
[WebIDLSecureContext]
public interface GPUUncapturedErrorEvent : Event
{
    // [Constructor] attribute
    GPUError error { get; }
}

/// <summary>
/// Dictionary: GPUUncapturedErrorEventInit
/// </summary>
public class GPUUncapturedErrorEventInit : EventInit
{
    public required GPUError error { get; set; }
}

/// <summary>
/// Dictionary: GPUColorDict
/// </summary>
public class GPUColorDict
{
    public required double r { get; set; }
    public required double g { get; set; }
    public required double b { get; set; }
    public required double a { get; set; }
}

/// <summary>
/// Union typedef: GPUColor
/// </summary>
[WebIDLUnion]
public abstract class GPUColor
{
    // Union type members would be generated here
}

/// <summary>
/// Dictionary: GPUOrigin2DDict
/// </summary>
public class GPUOrigin2DDict
{
    public uint x { get; set; } = 0;
    public uint y { get; set; } = 0;
}

/// <summary>
/// Union typedef: GPUOrigin2D
/// </summary>
[WebIDLUnion]
public abstract class GPUOrigin2D
{
    // Union type members would be generated here
}

/// <summary>
/// Dictionary: GPUOrigin3DDict
/// </summary>
public class GPUOrigin3DDict
{
    public uint x { get; set; } = 0;
    public uint y { get; set; } = 0;
    public uint z { get; set; } = 0;
}

/// <summary>
/// Union typedef: GPUOrigin3D
/// </summary>
[WebIDLUnion]
public abstract class GPUOrigin3D
{
    // Union type members would be generated here
}

/// <summary>
/// Dictionary: GPUExtent3DDict
/// </summary>
public class GPUExtent3DDict
{
    public required uint width { get; set; }
    public uint height { get; set; } = 1;
    public uint depthOrArrayLayers { get; set; } = 1;
}

/// <summary>
/// Union typedef: GPUExtent3D
/// </summary>
[WebIDLUnion]
public abstract class GPUExtent3D
{
    // Union type members would be generated here
}