using DataStructures

type PathNode
    parent::PathNode
    length::Int
    reverse::Bool
    edge::Edge
    
    PathNode(e::Edge,r=false) = (p = new(); (p.length, p.reverse, p.edge) = (0, r, e); p)
    PathNode(p::PathNode, r::Bool, e::Edge) = new(p, p.length + 1, r, e)
end

head(p::PathNode) = p.reverse ? p.edge.tail : p.edge.head
tail(p::PathNode) = p.reverse ? p.edge.head : p.edge.tail
flow(p::PathNode) = p.reverse ? (p.edge.cap - p.edge.flow) : p.edge.flow
free(p::PathNode) = p.reverse ? p.edge.flow : (p.edge.cap - p.edge.flow)
cap(p::PathNode) = p.edge.cap
cost(p::PathNode) = p.reverse ? -p.edge.cost : p.edge.cost

Base.show(io::IO, p::PathNode) = print(io,"($(tail(p)))-[$(flow(p)),$(cap(p)),$(cost(p))]->($(head(p))), reverse=$(p.reverse)")

path(leaf::PathNode) = begin
    p = Array(PathNode, leaf.length)
    i = leaf
    while isdefined(i, :parent)
        p[i.length] = PathNode(i.edge, i.reverse) # inverse root distance
        i = i.parent
    end
    p
end

function availableflow(p::Array{PathNode,1})
    minimum([free(i) for i in p])
end

function residualpath(g::Graph, s::Vertex, t::Vertex)
    flow(s) > 0 || return nothing
    nodes = Queue(PathNode)
    mark = falses(order(g))
    
    enqueue!(nodes, PathNode(Edge(Vertex(0),s,0,0,0,0)))
    mark[s.id] = true
    
    while length(nodes) > 0
        n = dequeue!(nodes)
        v = head(n)
        for e in v.edgesOut
            if e.flow == e.cap || mark[e.head.id]
                continue
            end
            next = PathNode(n,false,e)
            if is(e.head, t)
                return path(next)
            end
            enqueue!(nodes, next)
            mark[e.head.id] = true
        end
        for e in v.edgesIn
            if e.flow == 0 || mark[e.tail.id]
                continue
            end
            next = PathNode(n,true,e)
            if is(e.tail, t)
                return path(next)
            end
            enqueue!(nodes, next)
            mark[e.tail.id] = true
        end
    end
    nothing
end

function residualdelta(p::Array{PathNode,1})
    v = tail(p[1])
    min(flow(v), availableflow(p))
end

function updateflow!(path::Array{PathNode,1}, delta::Int)
    for p in path
        p.edge.flow += p.reverse ? -delta : delta
    end
    nothing
end

function maxflow!(g::Graph)
    s, t = st(g)
    while true
        path = residualpath(g, s, t)
        if path == nothing
            break
        end
        delta = residualdelta(path)
        updateflow!(path, delta)
    end
    g
end

function maxflow_castst!(g::Graph)
    makest!(g)
    maxflow!(g)
    resetst!(g)
    g
end

function mincost_cyclecanceling!(g::Graph)
    isfeasibleflow(g) || error("missing flow")
    while true
        cycle = negativecycle(g)
        if cycle == nothing
            break
        end
        delta = availableflow(cycle)
        updateflow!(cycle, delta)
    end
    g
end
