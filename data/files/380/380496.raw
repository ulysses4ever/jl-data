# Reference
# http://elib.zib.de/pub/Packages/mp-testdata/mincost/netg/info
function netg(file::String)
    open(file) do f
        vertices = nothing
        edges = nothing
        k = 0
        
        xint(n::Int, line::String, k::String, v::String) = try
            parse(Int, v)
        catch e
            error("$n, $line - $k: $(e.msg)")
        end
    
        for (n, line) in enumerate(eachline(f))
            xint(k::String, v::String) = xint(n, line, k, v)
            xerror(m::String) = error("$n, $line - $m")
            
            if startswith(line, 'c')
                continue
            elseif startswith(line, 'p')
                m = split(line, ' ')
                length(m) == 4 || xerror("Problem line (4): $(length(m))") 
                order = xint("Number of vertices", m[3])
                size = xint("Number of edges", m[4])
                
                vertices = Array(Vertex, order)
                for i = 1:order
                    vertices[i] = Vertex(i)
                end
                edges = Array(Edge, size)
            elseif startswith(line, 'n')
                m = split(line, ' ')
                length(m) == 3 || xerror("Vertex line (3): $(length(m))")
                id = xint("Vertex id", m[2])
                flow = xint("Vertex flow", m[3])
                
                vertices[id].flow = flow
            elseif startswith(line, 'a')
                k < length(edges) || xerror("Edge extra: $(length(edges))")
                m = split(line, ' ')
                length(m) == 6 || xerror("Edge line (6): $(length(m))")
                tail_idx = xint("Edge tail", m[2])
                head_idx = xint("Edge head", m[3])
                low = xint("Edge lower bound", m[4])
                cap = xint("Edge capacity", m[5])
                cost = xint("Edge cost", m[6])
                
                tail = vertices[tail_idx]
                head = vertices[head_idx]
                edges[k += 1] = Edge(tail, head, cap=cap, low=low, cost=cost)
            else
                xerror("Unknown line")
            end
        end
        k == length(edges) || error("Missing edges: $k of $(length(edges)) ($(length(edges) - k))")
        
        Graph(vertices, edges)
    end
end
