module GeneralizedMaps
using Docile
type Dart{T, S}
    index::T
    # involutions or pointers to other darts in the GeneralizedMap
    alpha::Vector{Nullable{Dart{T,S}}}
    # data associated with a global set of darts (an orbit or k-cell)
    globalembed::Vector{Nullable{S}}
    # boolean to indicate if this is the storage node for a global set of data (this may be unecessary)
    iskey::Vector{Bool}
    # marker for traversal algorithms
    ismarked::Bool
end

function Base.print{T, S}(d::Dart{T,S})
    println("Dart:")
    println("Index: ", d.index)
    print("alphas: ")
    for a in d.alpha
        if !isnull(a)
            print(get(a).index, " ")
        end
    end
end

function Dart(dim, T, S)
    alphas = fill(Nullable{Dart{T,S}}(), dim + 1)
    globalembed = fill(Nullable{S}(), dim + 1)
    iskey = [false for i in range(1, dim + 1)]
    return Dart{T, S}(0, alphas, globalembed, iskey, false)
end

Dart(T, S) = Dart(0, T, S)

function dim{T, S}(d::Dart{T, S})
    return length(d.alpha) - 1
end

Docile.@doc """
A collection of connected darts.
""" ->
type GeneralizedMap{T,S}
    darts::Vector{Dart{T,S}}
end

GeneralizedMap(T::Type, S::Type) = GeneralizedMap(Dart{T, S}[])

function Base.push!{T, S}(gmap::GeneralizedMap{T,S}, dart::Dart{T})
    dart.index = convert(T, length(gmap.darts) + 1)
    push!(gmap.darts, dart)
end


function alpha{T,S}(d::Dart{T, S}, i::T)
    return get(d.alpha[i+1])
end

function setalpha{T,S}(d::Dart{T, S}, i, alpha::Dart{T,S})
    d.alpha[i+1] = Nullable(alpha)
end

function data{T, S}(d::Dart{T, S}, i)
    return get(d.globalembed[i+1])
end

function setdata{T, S}(d::Dart{T, S}, i, data::S)
    d.globalembed[i+1] = Nullable(data)
end

function setdata{T, S}(d::Dart{T, S}, i, data::Nullable{S})
    d.globalembed[i+1] = data
end

function isnullalpha(d::Dart, i)
    return isnull(d.alpha[i+1])
end

Docile.@doc """
An Orbit stores a set of involution or pointer indices to define a path through the map
""" ->
type Orbit{T}
    index::Vector{T}
end

Orbit() = Orbit(Int32[])

Docile.@doc """
Create an orbit of dimension dim that skips dimensions in exclude.
""" ->
function Orbit(dim; exclude=[])
    orbit = Orbit{typeof(dim)}([])
    for j in range(0, dim+1)
        if length(findin(exclude, j)) == 0
            push!(orbit.index, j)
        end
    end
    return orbit
end

Docile.@doc """
Mark the Dart d as visited.
""" ->
function mark!(d::Dart)
    d.ismarked = true
end

Docile.@doc """
Remove the mark from this dart
""" ->
function unmark!(d::Dart)
    d.ismarked = false
end

Docile.@doc """
Traverse the input orbit starting at start and applying the function f.
""" ->
function traverse{T,S}(orbit::Orbit{T}, start::Dart{T,S}, f::Function)
    stack=typeof(start)[]
    mark!(start)
    push!(stack, start)
    while !isempty(stack)
        d = pop!(stack)
        f(d)
        for j in orbit.index
            if !isnullalpha(d, j)
                next = alpha(d, j)
                if !next.ismarked
                    mark!(next)
                    push!(stack, next)
                end
            end
        end
    end
end

Docile.@doc """
Collect the darts that define the k-cell that contains dart d.
""" ->
function collectcelldarts{T,S}(d::Dart{T,S}, k )
    darts = Set{Dart{T,S}}()
    orbit = Orbit(convert(T, dim(d)), exclude=[k])
    traverse(orbit, d, x->push!(darts, x))
    for dp in darts
        unmark!(dp)
    end
    return darts
end

function findcellkey{T,S}(start::Dart{T,S}, dim)
    for d in collectcelldarts(start, dim)
        if d.iskey[dim+1]
            return d
        end
    end
    return Dart(T, S)
end

function dispatchembedding{T,S}(start::Dart{T,S}, dim, data)
    for d in collectcelldarts(start, dim)
        setdata(d, dim, data)
    end
end
    
function sharecopyembedding{T,S}(d1::Dart{T,S}, d2::Dart{T,S}, dim)
    k1 = findcellkey(d1, dim)
    k2 = findcellkey(d2, dim)
    if !isequal(k1, Dart{T,S}())
        new_em = d2.globalembed[dim+1]
        d1.iskey[dim+1] = true
        dispatchembedding(d1, dim, new_em)
    else
        new_em = d1.globalembed[dim+1]
        d2.iskey[dim+1] = true
        dispatchembedding(d2, dim, new_em)
    end
end

Docile.@doc """
Connect or sew two cells of dimension dim  together.
""" ->
function sew!{T, S}(d1::Dart{T, S}, d2::Dart{T, S}, dim)
    for (dp1, dp2) in zip(collectcelldarts(d1, dim - 1), collectcelldarts(d2, dim - 1))
        for i in range(0, dim)
            k1 = findcellkey(dp1, i)
            k2 = findcellkey(dp2, i)
            if !isequal(k1, k2)
                k2.iskey[i+1] = false
                dispatchembedding(k2, i, k1.globalembed[i+1])
            end
        end
        dp1.alpha[dim+1] = dp2
        dp2.alpha[dim+1] = dp1
    end
end

end # module
