module GeneralizedMaps
using Docile


type Dart{T, S}
    index::T
    # involutions or references to other darts in the GeneralizedMap
    alpha::Vector{Dart{T,S}}
    # data associated with a global set of darts (an orbit or k-cell)
    globalembed::Vector{Nullable{S}}
    # references to the dart where the data is stored for each dim
    embedloc::Vector{Nullable{Dart{T,S}}}
    # marker for traversal algorithms
    ismarked::Bool
end

function Base.print{T, S}(d::Dart{T,S})
    println("Dart:")
    println("Index: ", d.index)
    print("alphas: ")
    for a in d.alpha
        print(a.index, " ")
    end
    println()
end

function Dart(dim, T, S)
    d = Dart{T, S}(zero(T), Dart{T,S}[], Nullable{S}[], Nullable{Dart{T,S}}[], false)
    d.alpha = fill(d, dim + 1)
    d.globalembed = fill(Nullable{S}(), dim + 1)
    d.embedloc = fill(Nullable{Dart{T,S}}(), dim + 1)
    return d
end

function dim{T, S}(d::Dart{T, S})
    return length(d.alpha) - 1
end

Docile.@doc """
Initialize an empty dart
""" ->
Dart(T, S) = Dart(0, T, S)

Docile.@doc """
A collection of connected darts.
""" ->
type GeneralizedMap{I,T,S}
    darts::Dict{I, Dart{T,S}}
end

Docile.@doc """
Initialize an empty GeneralizedMap with dart dimension of type T and storage type S.  The indices of the GeneralizedMap are set as Int64.
""" ->
GeneralizedMap(T::Type, S::Type) = GeneralizedMap(Dict{Int64, Dart{T, S}}())

Docile.@doc """
Push dart onto the GeneralizedMap gmap.  The index is updated and the result is stored.
""" ->
function Base.push!{I, T, S}(gmap::GeneralizedMap{I,T,S}, dart::Dart{T,S})
    dart.index = convert(I, length(gmap.darts) + 1)
    gmap.darts[dart.index] = dart
end


Docile.@doc """
Get the alpha reference for the dart d at dimension i
""" ->
function alpha{T,S}(d::Dart{T, S}, i::T)
    return d.alpha[i+1]
end

Docile.@doc """
Set the alpha reference for the dart d at dimension i to the dart other
""" ->
function setalpha!{T,S}(d::Dart{T, S}, i, other::Dart{T,S})
    d.alpha[i+1] = other
end

Docile.@doc """
Get the embedded data for dimension i of this dart.
""" ->
function data{T, S}(d::Dart{T, S}, i)
    return get(d.globalembed[i+1])
end

Docile.@doc """
Set the reference at which the data for dimension i of this dart is stored.
""" ->
function setdataloc!{T, S}(d::Dart{T, S}, i, loc::Dart{T,S})
    d.embedloc[i+1] = Nullable(loc)
end

Docile.@doc """
set the embedded data for dimension i in the dart d to data.
""" ->
function setdata!{T, S}(d::Dart{T, S}, i, data::Nullable{S})
    d.globalembed[i+1] = data
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
            next = alpha(d, j)
            if !next.ismarked
                mark!(next)
                push!(stack, next)
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
    return start.embedloc[dim+1]
end

function dispatchembedding{T,S}(start::Dart{T,S}, dim, loc::Dart{T,S})
    for d in collectcelldarts(start, dim)
        setdataloc!(d, dim, start)
    end
end
    
function sharecopyembedding{T,S}(d1::Dart{T,S}, d2::Dart{T,S}, dim)
    k1 = findcellkey(d1, dim)
    k2 = findcellkey(d2, dim)
    if !isequal(k1, k2)
        if isnull(k1)
            new_em = d2.globalembed[dim+1]
            setdata!(d1, dim, new_em)
            dispatchembedding(d1, dim, d1)
        else
            dispatchembedding(d1, dim, d1)
        end
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
                k2.embedloc[i+1] = k1
                dispatchembedding(k2, i, k1.globalembed[i+1])
            end
        end
        setalpha!(dp1, dim, dp2)
        setalpha!(dp2, dim, dp1)
    end
end

function polygon!(g, dim, n)
    for i in range(1, 2 * n)
        T = typeof(g)
        push!(g, Dart(dim, T.parameters[2], T.parameters[3]))
    end
    # first sew pairs of darts to each other to form vertices
    for i in range(1, 2, div(length(g.darts), 2))
        sew!(g.darts[i], g.darts[i+1], 0)
    end
    # now create edges
    for i in range(2, 2, div(length(g.darts), 2))
        sew!(g.darts[i], g.darts[(i+1)%(2*n)], 1)
    end
end

function collectkcells(g::GeneralizedMap, k)
    cells = Set{Set{eltype(g.darts)[2]}}()
    for (i, d) in g.darts
        push!(cells, collectcelldarts(d, k))
    end
    return cells
end

function countkcells(g::GeneralizedMap, k)
    cells = collectkcells(g, k)
    return length(cells)
end
end # module
