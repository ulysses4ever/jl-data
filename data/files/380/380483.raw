using DataStructures

type PathNode
    parent::PathNode
    length::Int
    reverse::Bool
    edge::Edge
    
    PathNode(e::Edge) = (p = new(); (p.length, p.reverse, p.edge) = (0, false, e); p)
    PathNode(p::PathNode, r::Bool, e::Edge) = new(p, p.length + 1, r, e)
end

head(p::PathNode) = p.reverse ? p.edge.tail : p.edge.head
Base.start(p::PathNode) = p
Base.done(p::PathNode, i::PathNode) = !isdefined(i, :parent)
Base.next(p::PathNode, i::PathNode) = (i, i.parent)
path(p::PathNode) = begin
    result = Array(Edge, p.length)
    for i in p
        result[i.length] = i.edge
    end
    result
end
    
function residualpath(g::Graph, s::Vertex, t::Vertex)
    nodes = Queue(PathNode)
    mark = zeros(Bool,order(g))
    
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

function residualdelta(path::Array{Edge,1})
    delta = 0
    v = indegree(path[1].tail) == 0 ? path[1].tail : path[1].head
    for e in path
        m = 0
        if is(e.tail, v)
            m = e.cap - e.flow
            v = e.head
        elseif is(e.head, v)
            m = e.flow
            v = e.tail
        else
            error("Invalid path!")
        end
        if delta == 0 || delta > m
            delta = m
        end
    end
    delta
end

function updateflow!(path::Array{Edge,1}, delta::Int)
    v = indegree(path[1].tail) == 0 ? path[1].tail : path[1].head
    for e in path
        if is(e.tail, v)
            e.flow += delta
            v = e.head
        elseif is(e.head, v)
            e.flow -= delta
            v = e.tail
        else
            error("Invalid path!")
        end
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
