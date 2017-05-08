module SmileExtra

using Smile

export adjacency_matrix, adjacency_matrix_to_net

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
function adjacency_matrix_to_net(adj::BitMatrix, dset::Dataset)

	n = size(adj,1)
	@assert(n == size(adj,2))
	@assert(n == get_number_of_variables(dset))

	pat = Pattern()
	set_size(pat, n)

	for p = 1 : n
		for c = 1 : n
			if adj[p,c]
				set_edge(pat, p, c, DSL_EDGETYPE_DIRECTED)
			end
		end
	end

	@assert(is_DAG(pat))

	net = Network()
	to_network(pat, dset, net)

	net
end

include("statistics.jl")
include("laplace_smoothing.jl")


end # end module
