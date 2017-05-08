__precompile__()

"""
Provides the [`@suffix`](@ref) macro for generating shorthand numeric conversion suffixes.

**Examples**

```julia
x = 1i8        # Convert `1` to `Int8`.
y = 3u32       # Convert `3` to `UInt32`.
z = (x + y)r16 # Convert `4` to `Float16`.
```

**Default Suffixes**

$(length(suffixes)) suffixes are provided by default:

$(join(["- `$(rpad(k, 4)) --> $v`\n" for (k, v) in suffixes]))

Additional user defined suffixes can be made using the `@suffix` macro.
"""
module NumericSuffixes

using Base.Meta, Compat

export @suffix

abstract AbstractSuffix

gentype(n :: Symbol) = :(Base.@__doc__(immutable $n <: $AbstractSuffix end))
gentype(n)           = error("invalid `@suffix` usage. `name` must be a `Symbol`.")

function genfunc(n, ex :: Expr)
    isexpr(ex, :->, 2)      || error("expression must be an anonymous function.")
    isa(ex.args[1], Symbol) || error("anonymous function must have one argument.")
    :(@inline (*)($(ex.args[1]) :: Number, ::Type{$n}) = $(ex.args[2]))
end
genfunc(n, T :: Symbol) = genfunc(n, :(x -> $(T)(x)))
genfunc(n, other)       = error("invalid arguments for `@suffix` macro.")

"""
Generate a new numeric suffix named `n` which converts numbers to type `T`.

**Signature**

```julia
@suffix n T
```

**Examples**

```julia
@suffix i8 Int8

x = 1i8
typeof(x) == Int8
```

More complex conversions can be made using anonymous function syntax:

```julia
@suffix t16 x -> trunc(Int16, x)

x = 1.2t16
typeof(x) == Int16
```
"""
macro suffix(n, T)
    quote
        import Base.Operators: (*)
        $(gentype(n))
        $(genfunc(n, T))
        $n
    end |> esc
end

const suffixes = (
    # Signed integers.
    :i8   => :Int8,
    :i16  => :Int16,
    :i32  => :Int32,
    :i64  => :Int64,
    :i128 => :Int128,
    # Unsigned integers.
    :u8   => :UInt8,
    :u16  => :UInt16,
    :u32  => :UInt32,
    :u64  => :UInt64,
    :u128 => :UInt128,
    # Floating point.
    :r16  => :Float16,
    :r32  => :Float32,
    :r64  => :Float64,
    # Complex floating point.
    :c32  => :Complex32,
    :c64  => :Complex64,
    :c128 => :Complex128,
)

for (n, T) in suffixes
    @eval begin
        export $n
        @doc("Numeric suffix for `$($T)` values.", @suffix($n, $T))
    end
end

end # module
