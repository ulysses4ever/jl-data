export statistics, log_bayes_score_component, log_bayes_score_component_BDeu, net_score, net_score_BDeu

function statistics(net::Network, r::SharedArray{Int, 1}, d::SharedArray{Int, 2})
	n, m = size(d)
	N = Array(Matrix{Int}, n)
	parentList = [int(collect(get_parents(net, i+1)+1)) for i in 1:n]
	for i = 1 : n
		p = parentList[i]
		q = 1
		if !isempty(p)
			Np = length(p)
			q  = prod(r[parentList[i]])
            stridevec = fill(1, Np)
            for k = 2:Np
                stridevec[k] = stridevec[k-1] * r[p[k-1]]
            end
            js = (d[p,:] - 1)' * stridevec + 1
        else
            js = fill(1, m)
        end
        N[i] = full(sparse(vec(d[i,:]), vec(js), 1, r[i], q))
	end
	N
end
function statistics(net::Network, r::Vector{Int}, d::Matrix{Int})
	n, m = size(d)
	N = Array(Matrix{Int}, n)
	parentList = [int(collect(get_parents(net, i+1)+1)) for i in 1:n]
	for i = 1 : n
		p = parentList[i]
		q = 1
		if !isempty(p)
			Np = length(p)
			q  = prod(r[parentList[i]])
            stridevec = fill(1, Np)
            for k = 2:Np
                stridevec[k] = stridevec[k-1] * r[p[k-1]]
            end
            js = (d[p,:] - 1)' * stridevec + 1
        else
            js = fill(1, m)
        end
        N[i] = full(sparse(vec(d[i,:]), vec(js), 1, r[i], q))
	end
	N
end
function statistics(adj::BitMatrix, r::SharedArray{Int, 1}, d::SharedArray{Int, 2})
	n, m = size(d)
	N = Array(Matrix{Int}, n)
	parentList = [find(adj[:,i]) for i in 1:n]
	for i = 1 : n
		p = parentList[i]
		q = 1
		if !isempty(p)
			Np = length(p)
			q  = prod(r[parentList[i]])
            stridevec = fill(1, Np)
            for k = 2:Np
                stridevec[k] = stridevec[k-1] * r[p[k-1]]
            end
            js = (d[p,:] - 1)' * stridevec + 1
        else
            js = fill(1, m)
        end
        N[i] = full(sparse(vec(d[i,:]), vec(js), 1, r[i], q))
	end
	N
end
function statistics(adj::BitMatrix, r::Vector{Int}, d::Matrix{Int})
	n, m = size(d)
	N = Array(Matrix{Int}, n)
	parentList = [find(adj[:,i]) for i in 1:n]
	for i = 1 : n
		p = parentList[i]
		q = 1
		if !isempty(p)
			Np = length(p)
			q  = prod(r[parentList[i]])
            stridevec = fill(1, Np)
            for k = 2:Np
                stridevec[k] = stridevec[k-1] * r[p[k-1]]
            end
            js = (d[p,:] - 1)' * stridevec + 1
        else
            js = fill(1, m)
        end
        N[i] = full(sparse(vec(d[i,:]), vec(js), 1, r[i], q))
	end
	N
end

function log_bayes_score_component{I<:Integer}(i::Int, parents::Vector{I}, r::SharedArray{Int, 1}, d::SharedArray{Int, 2})
    alpha = fill(1, r[i], isempty(parents) ? 1 : prod(r[parents]))
    (n, m) = size(d)
    if !isempty(parents)
        Np = length(parents)
        stridevec = fill(1, Np)
        for k = 2:Np
            stridevec[k] = stridevec[k-1] * r[parents[k-1]]
        end
        js = (d[parents,:] - 1)' * stridevec + 1
    else
        js = fill(1, m)
    end
    N = sparse(vec(d[i,:]), vec(js), 1, size(alpha)...) # note: duplicates are added together
    return sum(lgamma(alpha + N)) - sum(lgamma(alpha)) + sum(lgamma(sum(alpha,1))) - sum(lgamma(sum(alpha,1) + sum(N,1)))
end
function log_bayes_score_component{I<:Integer}(i::Int, parents::Vector{I}, r::Vector{Int}, d::Matrix{Int})
    alpha = fill(1, r[i], isempty(parents) ? 1 : prod(r[parents]))
    (n, m) = size(d)
    if !isempty(parents)
        Np = length(parents)
        stridevec = fill(1, Np)
        for k = 2:Np
            stridevec[k] = stridevec[k-1] * r[parents[k-1]]
        end
        js = (d[parents,:] - 1)' * stridevec + 1
    else
        js = fill(1, m)
    end
    N = sparse(vec(d[i,:]), vec(js), 1, size(alpha)...) # note: duplicates are added together
    return sum(lgamma(alpha + N)) - sum(lgamma(alpha)) + sum(lgamma(sum(alpha,1))) - sum(lgamma(sum(alpha,1) + sum(N,1)))
end
function log_bayes_score_component_BDeu{I<:Integer}(i::Int, parents::Vector{I}, r::SharedArray{Int, 1}, d::SharedArray{Int, 2})
	
	# obtain BDeu alpha
	if isempty(parents)
		α = 1.0 / r[i]
	else
		α = 1.0 / (r[i] * prod(r[parents]))
	end

    alpha = fill(α, r[i], isempty(parents) ? 1 : prod(r[parents]))
    (n, m) = size(d)
    if !isempty(parents)
        Np = length(parents)
        stridevec = fill(1, Np)
        for k = 2:Np
            stridevec[k] = stridevec[k-1] * r[parents[k-1]]
        end
        js = (d[parents,:] - 1)' * stridevec + 1
    else
        js = fill(1, m)
    end
    N = sparse(vec(d[i,:]), vec(js), 1, size(alpha)...) # note: duplicates are added together
    return sum(lgamma(alpha + N)) - sum(lgamma(alpha)) + sum(lgamma(sum(alpha,1))) - sum(lgamma(sum(alpha,1) + sum(N,1)))
end
function log_bayes_score_component_BDeu{I<:Integer}(i::Int, parents::Vector{I}, r::Vector{Int}, d::Matrix{Int})
	
	# obtain BDeu alpha
	if isempty(parents)
		α = 1.0 / r[i]
	else
		α = 1.0 / (r[i] * prod(r[parents]))
	end

    alpha = fill(α, r[i], isempty(parents) ? 1 : prod(r[parents]))
    (n, m) = size(d)
    if !isempty(parents)
        Np = length(parents)
        stridevec = fill(1, Np)
        for k = 2:Np
            stridevec[k] = stridevec[k-1] * r[parents[k-1]]
        end
        js = (d[parents,:] - 1)' * stridevec + 1
    else
        js = fill(1, m)
    end
    N = sparse(vec(d[i,:]), vec(js), 1, size(alpha)...) # note: duplicates are added together
    return sum(lgamma(alpha + N)) - sum(lgamma(alpha)) + sum(lgamma(sum(alpha,1))) - sum(lgamma(sum(alpha,1) + sum(N,1)))
end
function log_bayes_score_component{I<:Integer}(i::Int, parents::Vector{I}, r::SharedArray{Int, 1}, d::SharedArray{Int, 2}, cache::Dict{Vector{Int}, Float64})
	if haskey(cache, parents)
        return cache[parents]
    end
    return (cache[parents] = log_bayes_score_component(i, parents, r, d))
end
function log_bayes_score_component{I<:Integer}(i::Int, parents::Vector{I}, r::Vector{Int}, d::Matrix{Int}, cache::Dict{Vector{Int}, Float64})
	if haskey(cache, parents)
        return cache[parents]
    end
    return (cache[parents] = log_bayes_score_component(i, parents, r, d))
end

function net_score( net::Network, r::SharedArray{Int, 1}, d::SharedArray{Int, 2} )
	# compute the log bayes score for the given network on the dataset
	s = @parallel (+) for n in get_all_nodes(net)
		log_bayes_score_component(n + 1, get_parents(net, n)+1, r, d)
	end
	s
end
function net_score( net::Network, r::Vector{Int}, d::Matrix{Int} )
	# compute the log bayes score for the given network on the dataset
	s = @parallel (+) for n in get_all_nodes(net)
		log_bayes_score_component(n + 1, get_parents(net, n)+1, r, d)
	end
	s
end
function net_score_BDeu( net::Network, r::SharedArray{Int, 1}, d::SharedArray{Int, 2} )
	# compute the log bayes score for the given network on the dataset using the BDeu prior
	s = @parallel (+) for n in get_all_nodes(net)
		log_bayes_score_component_BDeu(n + 1, get_parents(net, n)+1, r, d)
	end
	s
end
function net_score_BDeu( net::Network, r::Vector{Int}, d::Matrix{Int} )
	# compute the log bayes score for the given network on the dataset using the BDeu prior
	s = @parallel (+) for n in get_all_nodes(net)
		log_bayes_score_component_BDeu(n + 1, get_parents(net, n)+1, r, d)
	end
	s
end