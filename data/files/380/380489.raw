import Base.size

type Vertex
    id::Int
    edgesIn::Array
    edgesOut::Array
    flow::Int
end

degree(v::Vertex) = length(v.edgesIn) + length(v.edgesOut)
outdegree(v::Vertex) = length(v.edgesOut)
indegree(v::Vertex) = length(v.edgesIn)
flow(v::Vertex) = begin
    m = v.flow
    if !isempty(v.edgesIn)
        m += sum([e.flow for e in v.edgesIn])
    end
    if !isempty(v.edgesOut)
        m -= sum([e.flow for e in v.edgesOut])
    end
    m
end

Base.show(io::IO, v::Vertex) = print(io,"$(v.id)")

type Edge
    tail::Vertex
    head::Vertex
    cap::Int
    low::Int
    cost::Int
    flow::Int
end

Base.show(io::IO, e::Edge) = print(io,"($(e.tail))-[$(e.flow),$(e.cap),$(e.cost)]->($(e.head))")

type Graph
    vertices::Array{Vertex,1}
    edges::Array{Edge,1}
end

order(g::Graph) = length(g.vertices)
size(g::Graph) = length(g.edges)

Base.show(io::IO, g::Graph) = begin
    println(io, "G(V,E) = [$(order(g)),$(size(g))]")
    for i = 1:size(g)
        if size(g) <= 50 || i <= 10 || i > (size(g)-10)
            e = g.edges[i]
            println(io, "$i: $e")
        end
        if size(g) > 50 && i == 11
            println(io, "... $(size(g) - 20) ...")
        end
    end
end

Vertex(id::Int; flow=0) = Vertex(id, Edge[], Edge[], flow)
Edge(t::Vertex, h::Vertex; cap=0,low=0,cost=0,flow=0) = begin
    e = Edge(t,h,cap,low,cost,flow)
    push!(t.edgesOut, e)
    push!(h.edgesIn, e)
    e
end
