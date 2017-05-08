export statistics, log_bayes_score_component, log_bayes_score_component_BDeu, net_score, net_score_BDeu

function statistics(
    targetind::Int,
    parents::AbstractVector{Int},
    bincounts::AbstractVector{Int},
    discrete_data::AbstractMatrix{Int}
    )

    q = 1
    if !isempty(parents)
        Np = length(parents)
        q  = prod(bincounts[parents])
        stridevec = fill(1, Np)
        for k = 2:Np
            stridevec[k] = stridevec[k-1] * bincounts[parents[k-1]]
        end
        js = (discrete_data[parents,:] - 1)' * stridevec + 1
    else
        js = fill(1, size(discrete_data,2))
    end
    full(sparse(vec(discrete_data[targetind,:]), vec(js), 1, bincounts[targetind], q))
end
function statistics(
    parents :: Vector{Vector{Int}},
    bincounts :: AbstractVector{Int},
    discrete_data :: AbstractMatrix{Int},
    )

    #=
    Computes sufficient statistics from a discrete dataset
    for a Bayesian Net structure

    INPUT:
        parents:
            list of lists of parent indices
            A variable with index i has bincounts[i]
            and row in discrete_data[i,:]
            No acyclicity checking is done
        bincounts:
            list of variable bin counts, or number of
            discrete values the variable can take on, v ∈ {1 : bincounts[i]}
        discrete_data:
            table of discrete values [n×m]
            where n is the number of nodes
            and m is the number of samples

    OUTPUT:
        N :: Vector{Matrix{Int}}
            a sufficient statistics table for each variable
            Variable with index i has statistics table N[i],
            which is r × q where
            r = bincounts[i] is the number of variable instantiations and
            q is the number of parental instantiations of variable i

            The r-values are ordered from 1 → bincounts[i]
            The q-values are ordered in the same ordering as ind2sub() in Julia Base
                Thus the instantiation of the first parent (by order given in parents[i])
                is varied the fastest.

            ex:
                Variable 1 has parents 2 and 3, with r₁ = 2, r₂ = 2, r₃ = 3
                q for variable 1 is q = r₂×r₃ = 6
                N[1] will be a 6×2 matrix where:
                    N[1][1,1] is the number of time v₁ = 1, v₂ = 1, v₃ = 1
                    N[1][2,1] is the number of time v₁ = 1, v₂ = 2, v₃ = 1
                    N[1][3,1] is the number of time v₁ = 1, v₂ = 1, v₃ = 2
                    N[1][4,1] is the number of time v₁ = 1, v₂ = 2, v₃ = 2
                    N[1][5,1] is the number of time v₁ = 1, v₂ = 1, v₃ = 3
                    N[1][6,1] is the number of time v₁ = 1, v₂ = 2, v₃ = 3
                    N[1][6,2] is the number of time v₁ = 2, v₂ = 1, v₃ = 1
                    ...

    This function uses sparse matrix black magic and was
    mercilessly stolen from Ed Schmerling.
    =#

    n, m = size(discrete_data)
    N = Array(Matrix{Int}, n)
    for i = 1 : n
        # p = parents[i]
        # q = 1
        # if !isempty(p)
        #     Np = length(p)
        #     q  = prod(bincounts[parents[i]])
        #     stridevec = fill(1, Np)
        #     for k = 2:Np
        #         stridevec[k] = stridevec[k-1] * bincounts[p[k-1]]
        #     end
        #     js = (discrete_data[p,:] - 1)' * stridevec + 1
        # else
        #     js = fill(1, m)
        # end
        # N[i] = full(sparse(vec(discrete_data[i,:]), vec(js), 1, bincounts[i], q))
        N[i] = statistics(i, parents[i], bincounts, discrete_data)
    end
    N
end
function statistics(net::Network, bincounts::AbstractVector{Int}, discrete_data::AbstractMatrix{Int})

    n = length(bincounts)
	parentList = [int(collect(get_parents(net, i-1)+1)) for i in 1:n]
	statistics(parentList, bincounts, discrete_data)
end
function statistics(adj::BitMatrix, bincounts::AbstractVector{Int}, discrete_data::AbstractMatrix{Int})

    n = length(bincounts)
    @assert(size(adj,1) == size(adj,2) == n)
    parentList = [find(adj[:,i]) for i in 1:n]
    statistics(parentList, bincounts, discrete_data)
end

function log_bayes_score_component{I<:Integer}(i::Int, parents::AbstractVector{I}, r::AbstractVector{Int}, d::AbstractMatrix{Int})

    #=
    Computes the bayesian score component for the given target variable index
        This assumes a unit dirichlet prior (alpha)

    INPUT:
        i       - index of the target variable
        parents - list of indeces of parent variables (should not contain self)
        r       - list of instantiation counts accessed by variable index
                  r[1] gives number of discrete states variable 1 can take on
        d       - matrix of sufficient statistics / counts
                  d[j,k] gives the number of times the target variable took on its kth instantiation
                  given the jth parental instantiation

    OUTPUT:
        the log bayesian score, Float64
    =#

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
    return sum(lgamma(alpha + N)) - sum(lgamma(alpha)) + sum(lgamma(sum(alpha,1))) - sum(lgamma(sum(alpha,1) + sum(N,1)))::Float64
end
function log_bayes_score_component_BDeu{I<:Integer}(i::Int, parents::AbstractVector{I}, r::AbstractVector{Int}, d::AbstractMatrix{Int})

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
function log_bayes_score_component{I<:Integer}(
    i       :: Int,
    parents :: AbstractVector{I},
    r       :: AbstractVector{Int},
    d       :: AbstractMatrix{Int},
    alpha   :: AbstractMatrix{Float64}, # r[i]×prod(r[parents])
    )

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
function log_bayes_score_component{I<:Integer}(i::Int, parents::AbstractVector{I}, r::SharedArray{Int, 1}, d::SharedArray{Int, 2}, cache::Dict{Vector{Int}, Float64})
	if haskey(cache, parents)
        return cache[parents]
    end
    return (cache[parents] = log_bayes_score_component(i, parents, r, d))
end
function log_bayes_score_component{I<:Integer}(i::Int, parents::AbstractVector{I}, r::AbstractVector{Int}, d::Matrix{Int}, cache::Dict{Vector{Int}, Float64})
	if haskey(cache, parents)
        return cache[parents]
    end
    return (cache[parents] = log_bayes_score_component(i, parents, r, d))
end
function log_bayes_score_component{I<:Integer}(
    i       :: Int,
    parents :: AbstractVector{I},
    r       :: AbstractVector{Int},
    d       :: AbstractMatrix{Int},
    alpha   :: AbstractMatrix{Float64}, # r[i]×prod(r[parents])
    cache   :: Dict{Vector{Int}, Float64}
    )

    if haskey(cache, parents)
        return cache[parents]
    end
    return (cache[parents] = log_bayes_score_component(i, parents, r, d, alpha))
end

function net_score( net::Network, r::SharedArray{Int, 1}, d::SharedArray{Int, 2} )
	# compute the log bayes score for the given network on the dataset
	s = @parallel (+) for n in get_all_nodes(net)
		log_bayes_score_component(n + 1, get_parents(net, n)+1, r, d)
	end
	s
end
function net_score( net::Network, r::AbstractVector{Int}, d::Matrix{Int} )
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
function net_score_BDeu( net::Network, r::AbstractVector{Int}, d::Matrix{Int} )
	# compute the log bayes score for the given network on the dataset using the BDeu prior
	s = @parallel (+) for n in get_all_nodes(net)
		log_bayes_score_component_BDeu(n + 1, get_parents(net, n)+1, r, d)
	end
	s
end