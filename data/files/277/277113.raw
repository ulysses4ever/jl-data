module GeneralizedMaps
using Compat
using Docile

export OrientedDart, Dart, id, ids, GeneralizedMap, sew, collectcelldarts, collectkcells, countkcells, Orbit, OrbitBut

type OrientedDart{T, S}
    index::T
    # involutions or references to other darts in the GeneralizedMap
    phi::Vector{Nullable{OrientedDart{T,S}}}
    # data associated with a global set of darts (an orbit or k-cell)
    globalembed::Vector{Nullable{S}}
    # references to the dart where the data is stored for each dim
    embedloc::Vector{Nullable{OrientedDart{T,S}}}
    isboundary::Bool
end


type Dart{T, S}
    index::T
    # involutions or references to other darts in the GeneralizedMap
    alpha::Vector{Nullable{Dart{T,S}}}
    # data associated with a global set of darts (an orbit or k-cell)
    globalembed::Vector{Nullable{S}}
    # references to the dart where the data is stored for each dim
    embedloc::Vector{Nullable{Dart{T,S}}}
    isboundary::Bool
end

typealias Dart2 Dart{ Uint, 3 }
typealias Dart3 Dart{ Uint, 4 }

Docile.@doc """ Returns new list with a zero before every entry """ ->
function intersperseLeadingZeros{T}(lst::Array{T})
    foldl( (a, x) -> begin
				  push!( a, 0 )
				  push!( a, x )
				  a
				  end, T[],  lst )
end

Docile.@doc """ Returns a list of dart ids """ ->
function ids( d )
    foldl( (a, x) -> push!( a, x.index ) , Set{Int}(),  d )
	#map( (x) -> x.index, d )
end

Docile.@doc """ Returns a dart's id """ ->
function id( d )
	d.index
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
    println()
end

function Base.print{T, S}(d::OrientedDart{T,S})
    println("Dart:")
    println("Index: ", d.index)
    print("phis: ")
    for phi in d.phi
        if !isnull(phi)
            print(get(phi).index, " ")
        end
    end
    println()
end

function Dart(dim, T, S)
    d = Dart{T, S}(zero(T), Dart{T,S}[], fill(Nullable{S}(), dim + 1), fill(Nullable{Dart{T,S}}(), dim + 1), false )
    d.alpha = fill(Nullable{Dart{T, S}}(), dim + 1)
    return d
end

function dim{T, S}(d::Dart{T, S})
    return length(d.alpha) - 1
end

function dim{T, S}(d::OrientedDart{T, S})
    return length(d.phi)
end

Docile.@doc """
A collection of connected darts.  Should consist of Darts /or/ OrientedDarts, not both.
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
Return true if this dart is part of the boundary
""" ->
function isboundary{T,S}(d::Union(Dart{T,S}, OrientedDart{T,S}))
    return d.isboundary
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
    d.alpha[i+1] = Nullable(other)
end

Docile.@doc """
Set the phi reference for the oriented dart d at dimension i to the dart other
""" ->
function setphi!{T,S}(d::OrientedDart{T, S}, i, other::OrientedDart{T,S})
    d.alpha[i+1] = Nullable(other)
end

Docile.@doc """
Get the embedded data for dimension i of this dart.
""" ->
function data{T, S}(d::Union(Dart{T, S}, OrientedDart{T,S}), i)
    return get(d.globalembed[i+1])
end

Docile.@doc """
Get the embedded data for i-cell containing this dart.
""" ->
function celldata{T, S}(d::Union(Dart{T, S}, OrientedDart{T,S}), i)
    key = get(d.embedloc[i+1])
    return(get(key.globalembed[i+1]))
end

Docile.@doc """
Set the reference at which the data for dimension i of this dart is stored.
""" ->
function setembedloc!{T, S}(d::Dart{T, S}, i, loc::Dart{T,S})
    d.embedloc[i+1] = Nullable(loc)
end

Docile.@doc """
Remove the reference at which the data for dimension i of this dart is stored.
""" ->
function delembedloc!{T, S}(d::Dart{T, S}, i)
    d.embedloc[i+1] = Nullable{Dart{T,S}}()
end

Docile.@doc """
set the embedded data for dimension i in the dart d to data.
""" ->
function setembed!{T, S}(d::Union(Dart{T, S}, OrientedDart{T,S}), i, data::Nullable{S})
    d.globalembed[i+1] = data
end

Docile.@doc """
An Orbit stores a function that produces pointer indices to define a path through the map.  This is used as input to the traverse functions.
""" ->
type Orbit
    index::Function
end

Docile.@doc """
Create an orbit of dimension dim that skips dimensions in exclude.
""" ->
function Orbit(dim; exclude=[])
    t = () ->
    for x in range(0, dim + 1)
        if !in(x, exclude)
            produce(x)
        end
    end
    return Orbit( t )
end

Docile.@doc """
Create an orbit of dimension dim that interposes pre and skips dimensions in exclude.
""" ->
function InterposeOrbit(dim; pre = 0, exclude=[])
    t = () ->
    for x in range(1, dim + 1)
        if !in(x, exclude)
            produce(pre)
            produce(x)
        end
    end
    return Orbit( t )
end

Docile.@doc """
Create an orbit of dimension dim that interposes post and skips dimensions in exclude.
""" ->
function InterposeOrbit(dim; post = 0, exclude=[])
    t = () ->
    for x in range(1, dim + 1)
        if !in(x, exclude)
            produce(x)
            produce(post)
        end
    end
    return Orbit( t )
end

Docile.@doc """
Create an orbit of dimension dim that interposes pre and skips dimensions in exclude.
""" ->
function InterposeOrbit(dim; pre = 0, post = 0, exclude=[])
    t = () ->
    for x in range(1, dim + 1)
        if !in(x, exclude)
            produce(pre)
            produce(x)
            produce(post)
        end
    end
    return Orbit( t )
end

function kcellorbit(d::Dart, k)
    return InterposeOrbit(dim(d); pre = 0, exclude = [k])
end

function kcellorbit(d::OrientedDart, k)
    return Orbit(dim(d), exclude = [0, k])
end

Docile.@doc """
Create an orbit of dimension dim that skips dimensions in exclude.
""" ->
function OrbitBut{T,S}( d::Dart{T,S}, k )
    return Orbit(dim(d), exclude=[ k ] )
end

Docile.@doc """
Create an orbit of dimension dim that skips dimensions k.
Returns all the unique darts seen during traversal
""" ->
function OrbitButForEach{T,S}( d::Dart{T,S}, k, f::Function )
    return traverse( OrbitBut( d, k ), d, f )
end

Docile.@doc """
Create an orbit of dimension dim that skips dimensions in exclude.
""" ->
function OrientedOrbitBut{T,S}( d::Dart{T,S}, k )
    return InterposeOrbit(dim(d); pre = 0, exclude = [k])
end

Docile.@doc """
Create an orbit of dimension dim that skips dimensions k.
Returns all the unique darts seen during traversal
""" ->
function OrientedOrbitButForEach{T,S}( d::Dart{T,S}, k, f::Function )
    return traverse( OrbitBut( d, k ), d, f )
end

Docile.@doc """
Traverse the input orbit starting at start and applying the function f.
Returns all the unique darts seen during traversal
""" ->
function traverse{T,S}(orbit::Orbit, start::Dart{T,S}, f::Function)
    seen = Dart{T, S}[]
    push!(seen, start)
    f(start)
    function traverseWorker( orbit::Orbit, start::Dart, func::Function )
        for j in Task(orbit.index)
	    next = start.alpha[j + 1]
            if isnull(next)
                next = Nullable(start)
		if ! in(get(next), seen)
		    func(get(next))
		    push!(seen, get(next))
                end
                continue
            else
		if ! in(get(next), seen)
		    func(get(next))
		    push!(seen, get(next))
		    traverseWorker(orbit, get(next), func)
		end
            end
        end
        return seen
    end
    return traverseWorker(orbit, start, f)
end

Docile.@doc """
Traverse the input orbit starting at the oriented dart start and applying the function f.
Returns all the unique darts seen during traversal
""" ->
function traverse{T,S}(orbit::Orbit, start::OrientedDart{T,S}, f::Function)
    seen = Dart{T, S}[]
    push!(seen, start)
    f(start)
    function traverseWorker( orbit::Orbit, start::OrientedDart, func::Function )
        for j in Task(orbit.index)
	    next = start.phi[j]
            if isnull(next)
                next = Nullable(start)
		if ! in(get(next), seen)
		    func(get(next))
		    push!(seen, get(next))
                end
                continue
            else
		if ! in(get(next), seen)
		    func(get(next))
		    push!(seen, get(next))
		    traverseWorker(orbit, get(next), func)
		end
            end
        end
	return seen
    end
    return traverseWorker(orbit, start, f)
end

Docile.@doc """
Collect the darts that define the k-cell that contains dart d.
""" ->
function collectcelldarts{T,S}(d::Dart{T,S}, k)
    return traverse( OrbitBut( d, k ), d, x -> x  )
end

function findcellkey{T,S}(start::Dart{T,S}, dim)
    return start.embedloc[dim+1]
end

function dispatchembedding{T,S}(start::Dart{T,S}, dim, loc::Dart{T,S})
    OrbitButForEach( start, dim, (d) -> setembedloc!(d, dim, loc) )
end

Docile.@doc """
Embeds data into specified key dart for the i-cell and sets the key dart as embedloc for itself and all other darts in the i-cell.
""" -> 
function setcellembed!{T,S}(keydart::Dart{T,S}, i, data)
    setembed!(keydart, i, Nullable{S}(data))
    dispatchembedding(keydart, i, keydart)
end
    
function sharecopyembedding{T,S}(d1::Dart{T,S}, d2::Dart{T,S}, dim)
    function copy_embed( ds, dd )
        setembed!(dd, dim, ds.globalembed[dim+1])
        dispatchembedding(dd, dim, dd)
    end
    k1 = findcellkey(d1, dim)
    k2 = findcellkey(d2, dim)
    if !isequal(k1, k2)
        if isnull(k1)
		    #FIXME is this a bug?
            new_em = d2.globalembed[dim+1]
            setembed!(d1, dim, new_em)
            dispatchembedding(d1, dim, d1)
        else
            new_em = d2.globalembed[dim+1]
            setembed!(d2, dim, new_em)
            dispatchembedding(d2, dim, d2)
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
                if !isnull(k1)
                    dispatchembedding(dp2, i, get(get(k1).embedloc[i+1]))
                else
                    if !isnull(k2)
                        dispatchembedding(dp1, i, get(get(k2).embedloc[i+1]))
                    end
                end
            end
        end
        setalpha!(dp1, dim, dp2)
        setalpha!(dp2, dim, dp1)
    end
end

Docile.@doc """
Connect or sew two cells of dimension dim  together.
""" ->
function orientedsew!{T, S}(d1::OrientedDart{T, S}, d2::OrientedDart{T, S}, dim)
    # TODO add check for validity of orientation involution
    for (dp1, dp2) in zip(collectcelldarts(d1, dim - 1), collectcelldarts(d2, dim - 1))
        for i in range(0, dim)
            k1 = findcellkey(dp1, i)
            k2 = findcellkey(dp2, i)
            if !isequal(k1, k2)
                if !isnull(k1)
                    dispatchembedding(dp2, i, get(get(k1).embedloc[i+1]))
                else
                    if !isnull(k2)
                        dispatchembedding(dp1, i, get(get(k2).embedloc[i+1]))
                    end
                end
            end
        end
        setphi!(dp1, dim, dp2)
    end
end

function polygon!{I, T, S}(g::GeneralizedMap{I, T, S}, dim, n)
    newdarts = Dart{T, S}[]
    for i in range(1, 2 * n)
        push!(newdarts, Dart(dim, T, S))
        push!(g, newdarts[end])
    end
    # first sew pairs of darts to each other to form vertices
    for i in range(1, 2, div(length(newdarts), 2))
        sew!(newdarts[i], newdarts[i+1], 0)
    end
    # now create edges
    for i in range(2, 2, div(length(newdarts), 2))
        sew!(newdarts[i], newdarts[(i+1) % (2*n)], 1)
    end
    return newdarts
end


function cube!{I, T, S}(g::GeneralizedMap{I, T, S}, dim)
    for i in 1:6                # Create 6 sqaures to be sewn together.
        polygon!(g, dim, 4)
    end
    for i in 0:3
        sew!(g.darts[2i+1], g.darts[8i+17], 2) # Sew "bottom" square to sides.
        sew!(g.darts[2i+9], g.darts[8i+22], 2) # Sew "top" square to sides.
        sew!(g.darts[8i+19], g.darts[mod1(8(i+2), 32)+16], 2) # Sew side edges together.
    end
end

function collectkcells(g::GeneralizedMap, k)
    cells = Set() #cells = Set{Set{eltype(g.darts)[2]}}()
    for (i, d) in g.darts
        darts = Set(collectcelldarts(d, k))
        if length(darts) > k
            push!(cells, darts)
        end
    end
    return cells
end

function countkcells(g::GeneralizedMap, k)
    return length ( collectkcells(g, k) )
end
end # module

# vim: set ts=4 sw=4:
