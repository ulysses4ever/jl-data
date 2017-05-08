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
