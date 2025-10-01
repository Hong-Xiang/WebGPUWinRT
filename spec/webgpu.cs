using WebIDL;
// Undefined

namespace WebGPU;

public interface GPUObjectBase
{
    USVString label { get; set; }
}


public class GPUObjectDescriptorBase
{
    USVString label;
}

public interface GPUSupportedLimits
{
    UInt64 maxTextureDimension1D { get; }
}

[WebIDLTypeDef(typeof(double), IsPrimitiveType = true)]
struct GPUPipelineConstantValue
{
}

namespace A
{
    const int E = 1;
}
