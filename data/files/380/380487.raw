using DataStructures: Queue, enqueue!, dequeue!

# Reference
# Algorithms Design. Tardos and Kleinberg
# 7.1 The Maximum-Flow Problem and the Ford-Fulkerson Algorithm, pp. 338-346
function maxflow!(g::Graph)
    s, t = st(g)
    while true
        path = residualpath(g, s, t)
        if path == nothing
            break
        end
        delta = residualflow(path)
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

# Reference
# Network Flows. Ahuja, Magnanti and Orlin
# 9.6 Cycle-Canceling algorithm and the integrality property, pp. 317-320
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

function residualflow(p::Array{PathNode,1})
    v = tail(p[1])
    min(flow(v), availableflow(p))
end

function availableflow(p::Array{PathNode,1})
    minimum([free(i) for i in p])
end

function updateflow!(path::Array{PathNode,1}, delta::Int)
    for p in path
        p.edge.flow += p.reverse ? -delta : delta
    end
    nothing
end
