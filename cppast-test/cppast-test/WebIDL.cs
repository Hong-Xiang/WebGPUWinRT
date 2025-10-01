namespace WebIDL;

// WebIDL-related attributes
[AttributeUsage(AttributeTargets.All)]
public class WebIDLStringEnumAttribute : Attribute { }

[AttributeUsage(AttributeTargets.All)]
public class WebIDLNameAttribute : Attribute
{
    public string Name { get; }
    public WebIDLNameAttribute(string name) { Name = name; }
}

[AttributeUsage(AttributeTargets.All)]
public class WebIDLNullableAttribute : Attribute { }

[AttributeUsage(AttributeTargets.All)]
public class WebIDLOrUndefinedAttribute : Attribute { }

[AttributeUsage(AttributeTargets.All)]
public class WebIDLUnionAttribute : Attribute { }

[AttributeUsage(AttributeTargets.All)]
public class WebIDLCallbackInterfaceAttribute : Attribute { }

[AttributeUsage(AttributeTargets.All)]
public class WebIDLExposedAttribute : Attribute { }

[AttributeUsage(AttributeTargets.All)]
public class WebIDLSecureContextAttribute : Attribute { }

[AttributeUsage(AttributeTargets.All)]
public class WebIDLNewObjectDefaultValueAttribute : Attribute
{
}


// WebIDL generic type helpers
public class Sequence<T> : List<T> { }
public class FrozenArray<T> : IReadOnlyList<T> { public T this[int index] => throw new NotImplementedException(); public int Count => throw new NotImplementedException(); public IEnumerator<T> GetEnumerator() => throw new NotImplementedException(); System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator() => throw new NotImplementedException(); }
public class ObservableArray<T> : List<T> { }
public class Record<TKey, TValue> : Dictionary<TKey, TValue> { }
public class Promise<T> { }



// WebIDL special interface
public interface setlike<T>
{

}

public interface maplike<TKey, TValue>
{
}

// TypedArray and buffer types
public interface ArrayBuffer { }
public interface DataView { }
public interface Int8Array { }
public interface Int16Array { }
public interface Int32Array { }
public interface Uint8Array { }
public interface Uint16Array { }
public interface Uint32Array { }
public interface Uint8ClampedArray { }
public interface Float32Array { }
public interface Float64Array { }
public interface AllowSharedBufferSource { }
public interface EventTarget { }
public interface DOMException { }
public interface Event { }
public interface EventInit { }


public sealed class DOMString { };
public sealed class USVString { };
public struct Undefined { };

public enum PredefinedColorSpace
{
    srgb,
    [WebIDLName("display-p3")]
    display_p3,
}
