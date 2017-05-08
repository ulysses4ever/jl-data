using Graphs


# creates a graph from a filtered set of edges from the matrix P
function filtergraph(metadata, P, attrName, filterFunction)
    g = edgelist(ExVertex[], ExEdge{ExVertex}[], is_directed=false)
    
    # build the nodes
    nodes = Dict()
    for i in 1:length(metadata)
        nodes[i] = add_vertex!(g, metadata[i]["label"])
        for k in keys(metadata[i])
            nodes[i].attributes[k] = metadata[i][k]
        end
    end
    
    # build the edges
    for i in 1:size(P)[1]
        for j in i:size(P)[2]
            if i != j && filterFunction(P[i,j])
                e = add_edge!(g, nodes[i], nodes[j])
                e.attributes[attrName] = P[i,j]
            end
        end
    end
    g
end


# checks how many edges match between two graphs, where matching is
# based on the given attribute
function matchededges(g1, g2, matchAttr)
    
    # Build a hash to test membership in g1
    edgeHash = Dict()
    for e in edges(g1)
        sa = source(e).attributes
        ta = target(e).attributes
        if haskey(sa, matchAttr) && haskey(ta, matchAttr)
        	edgeMark = [false]
        	edgeHash[(sa[matchAttr], ta[matchAttr])] = edgeMark
            edgeHash[(ta[matchAttr], sa[matchAttr])] = edgeMark
        end
    end
    
    # Now count how many matched pairs of edges we can make
    matches = 0
    for e in edges(g2)
        sa = source(e).attributes
        ta = target(e).attributes
        if haskey(sa, matchAttr) && haskey(ta, matchAttr)
            k = (sa[matchAttr], ta[matchAttr])
            if haskey(edgeHash, k) && !edgeHash[k][1]
                edgeHash[k][1] = true
                matches += 1
            end
        end
    end
    
    matches
end


# permute the labels and attributes of the given vertices
function permutevertices!(verts)
    v = deepcopy(verts)
    permute!(v, randperm(length(v)))
    for i in 1:length(v)
        verts[i].label = v[i].label
        verts[i].attributes = v[i].attributes
    end
end


function permutationtest(valueFunc, g, numTrials=1000)
	value = valueFunc(g)

	newVals = zeros(numTrials)
	numAbove = 0
	numBelow = 0
	permg = deepcopy(g)
	#vs = filter(x->haskey(x.attributes, matchAttr), vertices(permg))
	for i in 1:numTrials
		permutevertices!(vertices(permg))
		newVals[i] = valueFunc(permg)
		if newVals[i] > value
			numAbove += 1
		elseif newVals[i] < value
			numBelow += 1
		end
	end

	return (value/mean(newVals), min(numTrials-numAbove+1, numTrials-numBelow+1)/(numTrials+1))
end


# loads a graph from lines of label,label pairs representing each edge
function loadedgelist(fileName, attr)
    g = edgelist(ExVertex[], ExEdge{ExVertex}[], is_directed=false)
    nodes = Dict()
    edgeHash = Dict()
    for line in eachline(open(fileName))
        parts = map(strip, split(line, ','))
        if !haskey(nodes, parts[1])
            nodes[parts[1]] = add_vertex!(g, parts[1])
            nodes[parts[1]].attributes[attr] = parts[1]
        end
        if !haskey(nodes, parts[2])
            nodes[parts[2]] = add_vertex!(g, parts[2])
            nodes[parts[2]].attributes[attr] = parts[2]
        end
        
        if !haskey(edgeHash, (parts[1], parts[2])) && !haskey(edgeHash, (parts[1], parts[2])) && parts[1] != parts[2]
            edgeHash[(parts[1], parts[2])] = true
            add_edge!(g, nodes[parts[1]], nodes[parts[2]])
        end
    end
    g
end


# restrict the given graph to the given vertices (which should be a subset of those in the graph)
function vertexinduce(verts, g)
    newG = edgelist(ExVertex[], ExEdge{ExVertex}[], is_directed=false)
    
    nodes = Dict()
    for v in verts
        nodes[v.label] = add_vertex!(newG, v.label)
        nodes[v.label].attributes = deepcopy(v.attributes)
    end

    edgeHash = Dict()
    for e in edges(g)
        sl = source(e).label
        tl = target(e).label
        if sl != tl && haskey(nodes, sl) && haskey(nodes, tl) && !haskey(edgeHash, (sl, tl)) && !haskey(edgeHash, (tl, sl))
            edgeHash[(sl, tl)] = true
            e2 = add_edge!(newG, nodes[sl], nodes[tl])
            for k in keys(e.attributes)
                e2.attributes[k] = e.attributes[k]
            end
        end
    end
    
    newG
end