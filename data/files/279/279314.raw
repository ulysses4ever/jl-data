type LSFit{T}
    coef::Vector{T}
    fittedfunc::Function
end

call(t::LSFit, x...) = t.fittedfunc(x...)

function _lsfit(flist::Array{Function}, A::Matrix, y::Vector)
    coef = pinv(A)*y
    # use a generated function to avoid the loop call each time you do a lookup
    @generated function fitter(x...)
        eq = :(($coef[1]*$flist[1](x...)))
        for i = 2:length(coef)
            eq = Expr(:call, :+, eq, :($coef[$i]*$flist[$i](x...)))
        end
        return eq
    end
    return LSFit(coef, fitter)
end

"""
    lsfit(flist, x, y)

"""
function lsfit(flist::Array{Function}, x::AbstractVector, y::AbstractVector)
    @assert size(x, 1) == size(y, 1)
    # TODO: figure out a fast and generic way of doing this
    A = eltype(y)[f(xi) for xi in x, f in flist]
    _lsfit(flist, A, y)
end

function lsfit(flist::Array{Function}, x::AbstractMatrix, y::AbstractVector)
    @assert size(x, 1) == size(y, 1)
    A = eltype(y)[f(x[i, :]...) for i in 1:size(x, 1), f in flist]
    _lsfit(flist, A, y)
end

"""
    @afuns(var, flist)

Generates an array of anonymous functions that take `var` as arguments.

# Examples
```jl
@afuns(x, [1, x, x^2])
```
returns
```jl
[x->1, x->x, x->x^2]
```
"""
macro afuns(var, list)
    if  typeof(list) != Expr || list.head != :vect
        throw(ArgumentError("Only simple arrays are supported"))
    end
    flist = []
    for fi in list.args
        push!(flist, Expr(:->, var, Expr(:block, fi)))
    end
    return Expr(:vect, flist...)
end
