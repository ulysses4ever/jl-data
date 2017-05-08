"""
    lsfit(flist, x, y)

"""
function lsfit(flist::Array{Function}, x::AbstractVector, y::AbstractVector)
    # TODO: figure out a fast and generic way of doing this
    A = eltype(x)[f(xi) for xi in x, f in flist]
    pinv(A)*y
end
