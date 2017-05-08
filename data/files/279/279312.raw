type LSFit{T}
    coef::Vector{T}
    fit::Function
end

call(t::LSFit, x) = t.fit(x)

"""
    lsfit(flist, x, y)

"""
function lsfit(flist::Array{Function}, x::AbstractVector, y::AbstractVector)
    # TODO: figure out a fast and generic way of doing this
    A = eltype(x)[f(xi) for xi in x, f in flist]
    coef = pinv(A)*y
    # use a generated function to avoid the loop call each time you do a lookup
    fit = @generated function fitted(x)
        eq = :(($coef[1]*$flist[1](x)))
        for i = 2:length(coef)
            eq = Expr(:call, :+, eq, :($coef[$i]*$flist[$i](x)))
        end
        return eq
    end
    return LSFit(coef, fit)
end

"""
    @funclist(var, flist)

Generates a vector of anonymous functions that take `var` as an argument.

# Examples
```jl
@funclist(x, [1, x, x^2])
```
returns
```jl
[x->1, x->x, x->x^2]
```
"""
macro funclist(var, list)
    if  typeof(list) != Expr || list.head != :vect
        throw(ArgumentError("Only simple arrays are supported"))
    end
    flist = []
    for fi in list.args
        push!(flist, Expr(:->, var, Expr(:block, fi)))
    end
    return Expr(:vect, flist...)
end
