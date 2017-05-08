# Reference
# Algorithms Design. Tardos and Kleinberg
# 6.8 Shortest Paths in a Graph, pp. 290-297
# (Bellman-Ford algorithm)
function negativecycle(g::Graph)
    n = order(g)

    m = fill(Inf, n)
    p = Array(PathNode, n)
    for v in g.vertices
        v.flow < 0 || continue
        m[v.id] = 0.
        p[v.id] = PathNode(Edge(v,Vertex(0),0,0,0,0))
    end

    mark = Array(Bool,n)
    _findcycle(p::Array{PathNode,1}, i::Int) = findcycle(mark,p,i)

    for i=2:n
        for v in g.vertices
            mmin = m[v.id]
            k = nothing #Edge
            reverse = false
            for e in v.edgesOut
                e.flow < e.cap || continue
                mk = m[e.head.id] + e.cost
                if mk < mmin
                    mmin = mk
                    k = e
                end
            end
            for e in v.edgesIn
                e.flow > 0 || continue
                mk = m[e.tail.id] - e.cost
                if mk < mmin
                    mmin = mk
                    k = e
                    reverse = true
                end
            end
            if k != nothing
                p[v.id] = PathNode(k,reverse)
                m[v.id] = mmin
                
                i = _findcycle(p, v.id)
                i == 0 || return cycle(p, i)
            end
        end
    end
    nothing
end

function findcycle(mark::Array{Bool,1}, p::Array{PathNode,1}, i::Int)
    mark[:] = false
    j = i
    while j != 0 && !mark[j]
        mark[j] = true
        j = head(p[j]).id
    end
    j
end

function findcycle(p::Array{PathNode,1}, i::Int)
    mark = falses(length(p))
    findcycle(mark, p, i)
end

function cycle(p::Array{PathNode,1}, i::Int)
    r = Array(PathNode, length(p))
    n = 0
    j = i
    while n == 0 || i != j
        r[n += 1] = p[j]
        j = head(p[j]).id
    end
    resize!(r, n)
    r
end
