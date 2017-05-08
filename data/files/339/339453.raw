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

# TODO: it would be cool to have a macro so that I could do
# @funclist :x [:1, :x, :x^2]
# and have it make the list of anon functions
# Expr(:->, :x, Expr(:block, Expr(:call, :*, 2, :x)))
# is the form of x -> 2*x
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
