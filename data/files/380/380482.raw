function isbalanced(g::Graph)
    sum([v.flow for v in g.vertices]) == 0
end

function hasconservation(g::Graph)
    for v in g.vertices
        flow(v) == 0 || return false
    end
    true
end

function isfeasibleflow(g::Graph)
    hasconservation(g) || return false
    for e in g.edges
        e.flow >= e.low && e.flow <= e.cap || return false
    end
    true
end

function hasnonnegativecapacity(g::Graph)
    for e in g.edges
        e.cap >= 0 || return false
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
