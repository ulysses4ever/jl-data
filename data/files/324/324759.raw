function st(g::Graph)
    s = nothing
    t = nothing
    n = 0
    for v in g.vertices
        if v.flow > 0
            s = v
            n += 1
        elseif v.flow < 0
            t = v
            n += 1
        end
    end
    isa(s, Vertex) || error("Source not found")
    isa(t, Vertex) || error("Target not found")
    n == 2 || error("Not ST")
    indegree(s) == 0 || error("Souce invalid")
    outdegree(t) == 0 || error("Target invalid")
    s, t
end

function makest!(g::Graph)
    sf, tf = 0, 0
    for v in g.vertices
        if v.flow > 0
            sf += v.flow
        elseif v.flow < 0
            tf += v.flow
        end
    end
    sf != 0 || error("Missing Sources")
    tf != 0 || error("Missing Targets")
    n = order(g)
    s = Vertex(n + 1, flow=sf)
    t = Vertex(n + 2, flow=tf)
    for v in g.vertices
        if v.flow > 0
            e = Edge(s, v, cap=v.flow)
            push!(g.edges, e)
        elseif v.flow < 0
            e = Edge(v, t, cap=-v.flow)
            push!(g.edges, e)
        end
        v.flow = 0
    end
    push!(g.vertices, s, t)
    g
end

function resetst!(g::Graph)
    n = order(g) - 2
    s = g.vertices[n + 1]
    t = g.vertices[n + 2]
    m = size(g) - outdegree(s) - indegree(t)
    
    for e in s.edgesOut
        v = e.head
        pop!(v.edgesIn)
        v.flow = e.cap
    end
    for e in t.edgesIn
        v = e.tail
        pop!(v.edgesOut)
        v.flow = -e.cap
    end
    
    resize!(g.vertices, n)
    resize!(g.edges, m)
    g
end
