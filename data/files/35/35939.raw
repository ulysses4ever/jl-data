__precompile__()

"""
    CompositeFunctions

Merge functions from different modules into a single function.
"""
module CompositeFunctions

using Base.Meta, Compat

export @merge, @kwmerge

"""
    @merge(func, modules...)

Merge functions from different modules.

**Examples**

```julia
module A

type T end

f(::T) = T

end

module B

type T end

f(::T) = T

end

@merge f A B

f(A.T()) == A.T
f(B.T()) == B.T
```

If several modules provide methods suitable for the specified arguments then the first
listed, in the above example it would be `A`, is selected.

**Generated Code**

`@merge` uses `@generated` to build specialised code for each tuple of arguments passed to
the merged function. The resulting code will typically have little to no overhead due to
inlining of the dispatch function.

```julia
module A

f(x::Int, y::Float64) = x + 2y

end

module B

f(x::Float64, y::Int) = x - 3y

end

@merge f A B

test(x, y) = f(x, y) + f(y, x)
@code_llvm test(1, 1.0)
```

```llvm
define double @julia_test_24571(i64, double) {
top:
  %2 = call double @"julia_*.1245"(i64 2, double %1)
  %3 = call double @"julia_+_24572"(i64 %0, double %2)
  %4 = mul i64 %0, 3
  %5 = call double @julia_-.1288(double %1, i64 %4)
  %6 = fadd double %3, %5
  ret double %6
}
```

*See also:* `@kwmerge`.
"""
macro merge(func, modules...) buildmerge(func, false, modules) end

"""
    @kwmerge(func, modules...)

Variant of `@merge` with support for passing keyword arguments.

**Examples**

```julia
@kwmerge f A B
f(1, a = 2, b =  3)
```

**Note:**

This macro should only be used when keywords are actually needed since the generated code
will probably not be as efficient as that of `@merge`.

*See also:* `@merge`.
"""
macro kwmerge(func, modules...) buildmerge(func, true, modules) end

function buildmerge(f, keywords, mods)
    mapping = [(m, getfield(m, f)) for m in [getfield(current_module(), m) for m in mods]]
    m = :(($pickmodule)($mapping, args))
    q = quot(f)
    expr = keywords ?
        :($(f)(args...; kwargs...) = :($($m).$($q)(args...; kwargs...))) :
        :($(f)(args...)            = :($($m).$($q)(args...)))
    esc(:(@generated $expr))
end

function pickmodule(choices, args)
    for (m, fn) in choices
        method_exists(fn, args) && return module_name(m)
    end
    error("No suitable method found with arguments '$args'.")
end

end # module
