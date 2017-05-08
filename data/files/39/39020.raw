
using DataStructures

include("container.jl")

import Base: start, done, next, isequal
export AbstractAdjacencyList
# Export the neighbor and vertex because the types are in 
# vertex_descriptor's type sometimes.
export AdjacencyList, AdjacencyListNeighbor, AdjacencyListVertex
export add_vertex!, add_edge!
export graph_property, vertex_property, edge_property
export num_vertices, vertices, num_edges, out_edges
export out_degree, out_neighbors, source, target
export start, done, next, isequal


abstract AbstractAdjacencyList{VP,EP,GP}

immutable type AdjacencyListNeighbor{ALV,EP}
    n::ALV
    edge_property::EP
end

# A Set container should contain one of each vertex, even if properties
# are specified differently.
function isequal(a::AdjacencyListNeighbor, b::AdjacencyListNeighbor)
    isequal(a.n, b.n)
end

immutable type AdjacencyListNeighborEmpty{ALV}
    n::ALV
end


# This fools the type system into creating v::Vector{Int} kinds
# of containers. It is dirty pool.
cconstruct(x::TypeVar, y...)=x
function cconstruct(VC::DataType, NC, VP, EP)
    VC{AdjacencyListVertex{VP,EP,VC,NC}}
end
function cconstruct(VC::DataType, NC, VP::(), EP)
    VC{AdjacencyListEmptyVertex{EP,VC,NC}}
end

store_construct(x::TypeVar, args...)=x
function store_construct(NC::DataType, VC, EP, self)
    alv=container_key(VC{self})
    NC{AdjacencyListNeighbor{alv,EP}}
end

function store_construct(NC::DataType, VC, EP::(), self)
    alv=container_key(VC{self})
    NC{AdjacencyListNeighborEmpty{alv}}
end


immutable type AdjacencyListVertex{VP,EP,VC,NC}
    v::store_construct(NC, VC, EP, AdjacencyListVertex{VP,EP,VC,NC})
    vertex_property::VP
    AdjacencyListVertex(vp::VP)=new(
        container_construct(store_construct(
            NC, VC, EP, AdjacencyListVertex{VP,EP,VC,NC})),
        vp)
end

function AdjacencyListVertex{VP}(VC, NC, EP, vp::VP)
    AdjacencyListVertex{VP,EP,VC,NC}(vp)
end

immutable type AdjacencyListEmptyVertex{EP,VC,NC}
    v::store_construct(NC, VC, EP, AdjacencyListEmptyVertex{EP,VC,NC})
    AdjacencyListEmptyVertex()=new(
        container_construct(store_construct(
            NC, VC, EP, AdjacencyListEmptyVertex{EP,VC,NC})))
end

function AdjacencyListEmptyVertex(VC, NC, EP)
    AdjacencyListEmptyVertex{EP,VC,NC}()
end

# Support bidirectionality through another Parametric type
# which is enum, effectively, using singleton types.
immutable type AdjacencyListBiVertex{VP,EP,VC,NC}
    v::store_construct(NC, VC, EP, AdjacencyListBiVertex{VP,EP,VC,NC})
    r::store_construct(NC, VC, EP, AdjacencyListBiVertex{VP,EP,VC,NC})
    vertex_property::VP
    AdjacencyListBiVertex(vp::VP)=new(
        container_construct(store_construct(
            NC, VC, EP, AdjacencyListBiVertex{VP,EP,VC,NC})),
        vp)
end

function AdjacencyListBiVertex{VP}(VC, NC, EP, vp::VP)
    AdjacencyListBiVertex{VP,EP,VC,NC}(vp)
end

immutable type AdjacencyListBiEmptyVertex{EP,VC,NC}
    v::store_construct(NC, VC, EP, AdjacencyListBiEmptyVertex{EP,VC,NC})
    r::store_construct(NC, VC, EP, AdjacencyListBiEmptyVertex{EP,VC,NC})
    AdjacencyListBiEmptyVertex()=new(
        container_construct(store_construct(
            NC, VC, EP, AdjacencyListBiEmptyVertex{EP,VC,NC})))
end

function AdjacencyListBiEmptyVertex(VC, NC, EP)
    AdjacencyListBiEmptyVertex{EP,VC,NC}()
end

type AdjacencyList{VP,EP,GP,VC,NC} <: AbstractAdjacencyList{VP,EP,GP}
    vertices::cconstruct(VC, NC, VP, EP)
    is_directed::Bool
    graph_property::GP
    AdjacencyList(directed::Bool, gp::GP)=new(
        container_construct(cconstruct(VC, NC, VP, EP)),
        directed,
        gp
        )
end


function AdjacencyList{GP}(VC::Union(DataType,TypeConstructor),  
        NC::Union(DataType,TypeConstructor), VP::Union(DataType,()),
        EP::Union(DataType,()), gp::GP; is_directed=true)
    AdjacencyList{VP,EP,GP,VC,NC}(is_directed, gp)
end


function AdjacencyList{GP}(VC::Union(DataType,TypeConstructor),  
        NC::Union(DataType,TypeConstructor), VP::DataType,
        EP::DataType, gp::GP, capacity::Int; is_directed=true)
    adj=AdjacencyList{VP,EP,GP,VC,NC}(is_directed, gp)
    for i in 1:capacity
        add_vertex!(adj)
    end
    adj
end


function add_vertex!{VP,EP,GP,VC,NC}(g::AdjacencyList{VP,EP,GP,VC,NC})
    container_add_key(g.vertices)
end

function add_vertex!{VP,EP,GP,VC,NC}(vp::VP, g::AdjacencyList{VP,EP,GP,VC,NC})
    container_add_key(g.vertices, vp)
end

# For when vertices are in a dict. k is the key.
function add_vertex!{VP,EP,GP,VC,NC}(k, vp::VP, g::AdjacencyList{VP,EP,GP,VC,NC})
    container_add_key(g.vertices, k, vp)
end


source(edge, g::AdjacencyList)=edge[1]
function target(edge, g::AdjacencyList)
    edge[2].n
end

# An edge is a tuple of the vertex_descriptor of the source
# and the vertex value of the target.
function edge(u, v, g::AdjacencyList)
    (u, container_get(container_get(g.vertices, u).v, v) )
end


function add_edge!{VP,EP,GP,VC,NC}(u, v, g::AdjacencyList{VP,EP,GP,VC,NC})
    uvertex=container_get(g.vertices, u)
    n=container_add(uvertex.v, v)
    if !g.is_directed
        vvertex=container_get(g.vertices, v)
        container_add(vvertex.v, u)
    end
    (u, n) # This is the edge descriptor.
end

function add_edge!{VP,EP,GP,VC,NC}(u, v, ep::EP, g::AdjacencyList{VP,EP,GP,VC,NC})
    uvertex=container_get(g.vertices, u)
    n=container_add(uvertex.v, v, ep)
    if !g.is_directed
        vvertex=container_get(g.vertices, v)
        container_add(vvertex.v, u, ep)
    end
    (u, n) # This is the edge descriptor.
end

# For when edges are in a dict. k is the key to the edge.
function add_edge!{VP,EP,GP,VC,NC}(u, v, k, ep::EP, g::AdjacencyList{VP,EP,GP,VC,NC})
    uvertex=container_get(g.vertices, u)
    n=container_add(uvertex.v, k, v, ep)
    if !g.is_directed
        vvertex=container_get(g.vertices, v)
        container_add(vvertex.v, k, u, ep)
    end
    (u, n) # This is the edge descriptor.
end


graph_property(g::AdjacencyList)=g.gp
vertex_property(vertex_descriptor, g::AdjacencyList)=g.vertices[vertex_descriptor].vertex_property
edge_property(edge_descriptor, g::AdjacencyList)=edge_descriptor[2].edge_property

num_vertices(g::AdjacencyList)=length(g.vertices)

vertices(g::AdjacencyList)=container_iter(g.vertices)

function num_edges{V,E}(g::AdjacencyList{V,E})
    sum([length(x.v) for v in g.vertices])
end

# Needs types
type OutEdgeNeighborIter{N,S}
    neighbor_iter::N
    source::S
end

start(iter::OutEdgeNeighborIter)=start(iter.neighbor_iter)
done(iter::OutEdgeNeighborIter, state)=done(iter.neighbor_iter, state)
function next(iter::OutEdgeNeighborIter, state)
    n, next_state=next(iter.neighbor_iter, state)
    ((iter.source, n), next_state)
end

function out_edges(vertex_descriptor, g::AdjacencyList)
    OutEdgeNeighborIter(container_value_iter(g.vertices[vertex_descriptor].v),
        vertex_descriptor)
end


out_degree(vertex_descriptor, g::AdjacencyList)=
        length(g.vertices[vertex_descriptor].v)


type AdjacencyListNeighborIter{I,V}
    inner::I
    v::V
    AdjacencyListNeighborIter(v)=new(container_iter(v), v)
end

start(iter::AdjacencyListNeighborIter)=start(iter.inner)
function next(iter::AdjacencyListNeighborIter, idx)
    container_get(v, next(iter.inner, idx)).n
end
done(iter::AdjacencyListNeighborIter, idx)=done(iter.inner, idx)

out_neighbors(vertex_descriptor, g::AdjacencyList)=
    AdjacencyListNeighborIter(g.vertices[vertex_descriptor].v)
