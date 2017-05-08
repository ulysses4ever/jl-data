using DataStructures

include("container.jl")

import Base: start, done, next, isequal
export CreateAdjacencyList
# Export the neighbor and vertex because the types are in 
# vertex_descriptor's type sometimes.
export AdjacencyList
export add_vertex!, add_edge!
export graph_property, vertex_property, edge_property
export num_vertices, vertices, num_edges, out_edges
export out_degree, out_neighbors, source, target
export in_edges
export start, done, next, isequal

include("container.jl")

immutable type ALNeighborProperty{ALV,EP}
    n::ALV
    edge_property::EP
end

# A Set container should contain one of each vertex, even if properties
# are specified differently.
function isequal(a::ALNeighborProperty, b::ALNeighborProperty)
    isequal(a.n, b.n)
end

immutable type ALNeighborEmpty{ALV}
    n::ALV
end

abstract ALVertex

abstract ALBiVertex <: ALVertex

abstract AdjacencyList

type ALBidirectional
end

type ALUnidirectional
end

function CreateVertex(container, vkey, ::Type{ALUnidirectional}, VP::Type, EP::Type)
    key_name=(vkey==:self) ? "" : string(vkey)
    vertex_type=symbol("ALVertex$(string(container))$(key_name)VE")
    curly_type=:(($vertex_type){VP,EP})
    println(names(BGraph))
    if isdefined(BGraph, vertex_type)
        return curly_type
    end
    local vtype
    if vkey==:self
        vtype=:(ALNeighborProperty{$vertex_type{VP,EP},EP})
    else
        vtype=:(ALNeighborProperty{($vkey),EP})
    end
    println("VertexVE ", vertex_type, " key ", vkey)
    eval(quote
        immutable type $vertex_type{VP,EP} <: ALVertex
            v::($container){($vtype)}
            vp::VP
            $(vertex_type)(p::VP)=new(
                container_construct(
                    $(container){($vtype)}),
                p)
        end
    end)
    curly_type
end


function CreateVertex(container, vkey, ::Type{ALBidirectional}, VP::Type, EP::Type)
    key_name=(vkey==:self) ? "" : string(vkey)
    vertex_type=symbol("ALVertexBi$(string(container))$(key_name)VE")
    curly_type=:(($vertex_type){VP,EP})
    if isdefined(vertex_type)
        return curly_type
    end
    local vtype
    if vkey==:self
        vtype=:(ALNeighborProperty{$vertex_type{VP,EP},EP})
    else
        vtype=:(ALNeighborProperty{($vkey),EP})
    end
    println(vertex_type)
    eval(quote
        immutable type $vertex_type{VP,EP} <: ALBiVertex
        v::($container){($vtype)}
        r::($container){($vtype)}
            vp::VP
            $(vertex_type)(p::VP)=new(
                container_construct(
                    $(container){($vtype)}),
                container_construct(
                    $(container){($vtype)}),
                p)
        end
    end)
    curly_type
end


function CreateVertex(container, vkey, ::Type{ALUnidirectional}, VP::Type, EP::Bool)
    key_name=(vkey==:self) ? "" : string(vkey)
    vertex_type=symbol("ALVertex$(string(container))$(key_name)V")
    curly_type=:(($vertex_type){VP})
    if isdefined(vertex_type)
        return curly_type
    end
    local vtype
    if vkey==:self
        vtype=:(ALNeighborEmpty{$vertex_type{VP}})
    else
        vtype=:(ALNeighborEmpty{$vkey})
    end
    println(vertex_type)
    eval(quote
        immutable type ($vertex_type){VP} <: ALVertex
            v::($container){($vtype)}
            vp::VP
            $(vertex_type)(p::VP)=new(
                container_construct(
                    $(container){($vtype)}),
                p)
        end
    end)
    curly_type
end


function CreateVertex(container, vkey, ::Type{ALBidirectional}, VP::Type, EP::Bool)
    key_name=(vkey==:self) ? "" : string(vkey)
    vertex_type=symbol("ALVertexBi$(string(container))$(key_name)V")
    curly_type=:(($vertex_type){VP})
    if isdefined(vertex_type)
        return curly_type
    end
    local vtype
    if vkey==:self
        vtype=:(ALNeighborEmpty{$vertex_type{VP}})
    else
        vtype=:(ALNeighborEmpty{$vkey})
    end
    println(vertex_type)
    eval(quote
        immutable type ($vertex_type){VP} <: ALBiVertex
        v::($container){($vtype)}
        r::($container){($vtype)}
            vp::VP
            $(vertex_type)(p::VP)=new(
                container_construct(
                    $(container){($vtype)}),
                container_construct(
                    $(container){($vtype)}),
                p)
        end
    end)
    curly_type
end





function CreateAdjList(vcontainer, ncontainer;
        bidirectional::Bool=false, VP=false, EP=false)
    adj_sym=symbol(join(ASCIIString[
        "Adjacency",
        string(vcontainer),
        string(ncontainer),
        bidirectional ? "Bi" : "",
        VP==false ? "" : "V",
        EP==false ? "" : "E"]))
    templates=[
        (true, true) => :(($adj_sym){VP,EP}),
        (true, false) => :(($adj_sym){VP}),
        (false, true) => :(($adj_sym){EP}),
        (false, false) => :(($adj_sym))
    ]
    adj_type=templates[(VP!=false, EP!=false)]
    if isdefined(adj_sym)
        return adj_type
    end
    println(adj_type)
    direct_type = bidirectional ? ALBidirectional : ALUnidirectional
    vertex_type=CreateVertex(ncontainer, container_key(eval(vcontainer)),
        direct_type, VP==false? false : Int, EP==false ? false : Int)
    eval(quote
        type ($adj_type) <: AdjacencyList
            vertices::($vcontainer){($vertex_type)}
            is_directed::Bool
        end
    end)

    ex2=quote
        function ($adj_sym)(; is_directed=false)
            ($adj_type)( container_construct(($vcontainer){($vertex_type)}),
                is_directed)
        end
    end
    # Adding types to the argument list of the function.
    if false!=VP
        push!(ex2.args[2].args[1].args, :VP)
    end
    if false!=EP
        push!(ex2.args[2].args[1].args, :EP)
    end
    eval(ex2)
    adj_type
end


function CreateAdjListG(vcontainer, ncontainer;
        bidirectional::Bool=false, VP=false, EP=false)
    adj_sym=symbol(join(ASCIIString[
        "Adjacency",
        string(vcontainer),
        string(ncontainer),
        bidirectional ? "Bi" : "",
        VP==false ? "" : "V",
        EP==false ? "" : "E",
        "G"]))
    templates=[
        (true, true) => :(($adj_sym){VP,EP,GP}),
        (true, false) => :(($adj_sym){VP,GP}),
        (false, true) => :(($adj_sym){EP,GP}),
        (false, false) => :(($adj_sym{GP}))
    ]
    adj_type=templates[(VP!=false, EP!=false)]
    if isdefined(adj_sym)
        return adj_type
    end
    println(adj_type)
    direct_type = bidirectional ? ALBidirectional : ALUnidirectional
    vertex_type=CreateVertex(ncontainer, container_key(eval(vcontainer)),
        direct_type, VP==false? false : Int, EP==false ? false : Int)
    println("CreateAdjGP vert ", vertex_type)
    ex1=quote
        type ($adj_type) <: AdjacencyList
            vertices::($vcontainer){($vertex_type)}
            is_directed::Bool
            graph_property::GP
        end
    end
    println("CreateAdjGP ", ex1)
    eval(ex1)

    ex2=quote
        function ($adj_sym){GP}(gp::GP; is_directed=false)
            ($adj_type)( container_construct(($vcontainer){($vertex_type)}),
                is_directed, gp)
        end
    end
    # Adding types to the argument list of the function.
    if false!=VP
        insert!(ex2.args[2].args[1].args, 3, :VP)
    end
    if false!=EP
        insert!(ex2.args[2].args[1].args, 4, :EP)
    end
    eval(ex2)
    adj_type
end

function CreateAdjacencyList(vcontainer, ncontainer;
        bidirectional::Bool=false, VP=false, EP=false, GP=false)
    if GP
        CreateAdjListG(vcontainer, ncontainer,
            bidirectional=bidirectional, VP=VP, EP=EP)
    else
        CreateAdjList(vcontainer, ncontainer,
            bidirectional=bidirectional, VP=VP, EP=EP)
    end
end

function add_vertex!(g::AdjacencyList)
    container_add_key(g.vertices)
end

function add_vertex!(vp, g::AdjacencyList)
    container_add_key(g.vertices, vp)
end

# For when vertices are in a dict. k is the key.
function add_vertex!(k, vp, g::AdjacencyList)
    container_add_key(g.vertices, k, vp)
end


source(edge, g::AdjacencyList)=edge[1]
function target(edge, g::AdjacencyList)
    edge[2].n
end


function add_edge!(u, v, g::AdjacencyList)
    uvertex=container_get(g.vertices, u)
    n=container_add(uvertex.v, v)
    if !g.is_directed
        vvertex=container_get(g.vertices, v)
        container_add(vvertex.v, u)
    end
    (u, n) # This is the edge descriptor.
end


function add_edge!(u, v, ep, g::AdjacencyList)
    uvertex=container_get(g.vertices, u)
    println("add_edge! type of edges ", typeof(uvertex.v))
    n=container_add(uvertex.v, v, ep)
    println("add_edge! added")
    if !g.is_directed
        vvertex=container_get(g.vertices, v)
        container_add(vvertex.v, u, ep)
    end
    (u, n) # This is the edge descriptor.
end


# For when edges are in a dict. k is the key to the edge.
function add_edge!(u, v, k, ep, g::AdjacencyList)
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

function num_edges(g::AdjacencyList)
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


function in_edges_vertex{T<:ALBiVertex}(vertex_descriptor, vertex::T,
        g::AdjacencyList)
    println("Bidirectional in edges")
end

function in_edges_vertex{T<:ALVertex}(vertex_descriptor, vertex::T,
        g::AdjacencyList)
    println("Unidirectional in edges")
    if g.is_directed
    else
    end
end

function in_edges(vertex_descriptor, g::AdjacencyList)
    in_edges_vertex(vertex_descriptor, g.vertices[vertex_descriptor], g)
end

