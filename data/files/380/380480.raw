function isbalanced(g::Graph)
    sum = 0
    for v in g.vertices
        sum += v.flow
    end
    sum == 0
end

function hasconservation(g::Graph)
    for v in g.vertices
        sum = v.flow
        for e in v.edgesIn
            sum += e.flow
        end
        for e in v.edgesOut
            sum -= e.flow
        end
        if sum != 0
            return false
        end
    end
    true
end

function hasnonnegativecapacity(g::Graph)
    for e in g.edges
        if e.cap < 0
            return false
        end
    end
    true
end

function issingleedge(g::Graph)
    for v in g.vertices
        for e1 in v.edgesOut
            for e2 in v.edgesOut
                if !is(e1, e2) && is(e1.head, e2.head)
                    return false
                end
            end
        end
    end
    true
end
