module SmileExtra

# TODO: incorporate Schmerling Learning

export adjacency_matrix

function adjacency_matrix(net::Network)
	# returns a BitMatrix in which index [parent,child] is true if parent->child is true

	allnodes = get_all_nodes(net)
	n = length(allnodes)
	adj = falses(n,n)
	for p in allnodes
		for c in get_children(net, p)
			adj[p+1,c+1] = true
		end
	end
	adj::BitMatrix
end

include("statistics.jl")


end # end module
