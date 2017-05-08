# belief for heuristics
type RevealedGraph <: Belief
    revealed_edges::Set{Edge}
    revealed_adj::Vector{Vector{Int}}
    revealed_nodes::Set{Int}
    known_labels::Dict{Int,Int} # constant
    probed::Set{Int}
    # highest_degree_not_probed::Int # -1 if unknown
    budget::Int
    p_intra::Float64
    p_inter::Float64
    n_comms::Int
    RevealedGraph() = new()
end
n_nodes(r::RevealedGraph) = length(r.revealed_adj)

create_belief(p::CommunityAffiliationPOMDP) = RevealedGraph()

function initial_belief(p::CommunityAffiliationPOMDP, r::RevealedGraph=RevealedGraph())
    r.revealed_edges = copy(p.known_edges)
    r.revealed_nodes = copy(p.known_nodes)
    r.known_labels = copy(p.known_labels)
    r.probed = Set{Int}()
    r.budget = p.budget
    r.p_intra = p.p_intra
    r.p_inter = p.p_inter
    r.n_comms = p.true_network.n_comms
    r.revealed_adj = [Array(Int,0) for i in 1:length(p)]
    for ed in r.revealed_edges
        push!(r.revealed_adj[ed.first], ed.second)
        push!(r.revealed_adj[ed.second], ed.first)
    end
    node_vector = collect(r.revealed_nodes)
    # r.highest_degree_not_probed = node_vector[indmax([degree(r,n) for n in node_vector])]
    return r
end

function clone!(new::RevealedGraph, b::RevealedGraph)
    new.revealed_edges = copy(b.revealed_edges)
    new.revealed_adj = copy(b.revealed_adj)
    new.revealed_nodes = copy(b.revealed_nodes)
    new.known_labels = b.known_labels
    new.probed = copy(b.probed)
    # new.highest_degree_not_probed = b.highest_degree_not_probed
    new.budget = b.budget
    new.p_intra = b.p_intra
    new.p_inter = b.p_inter
    new.n_comms = b.n_comms
end

function add_edge!(g::RevealedGraph, i::Int, j::Int)
    ed = Edge(i,j)
    if !(ed in g.revealed_edges || reverse(ed) in g.revealed_edges)
        push!(g.revealed_edges, ed)
        push!(g.revealed_adj[ed.first], ed.second)
        push!(g.revealed_adj[ed.second], ed.first)
    end
end

function degree(g::RevealedGraph, i::Int)
    return length(g.revealed_adj[i])
end

function neighbors(g::RevealedGraph, i::Int)
    return g.revealed_adj[i]
end

# right now this generates a whole graph. should it generate something partial?
function Base.rand!(rng::AbstractRNG, s::CommunityNetwork, d::RevealedGraph)
    # fill in edges for probed nodes
    s.graph = Graph(n_nodes(d))
    s.labels = Array(Int, n_nodes(d))
    s.n_comms = d.n_comms
    s.budget = d.budget
   
    # assign node affiliation
    for n in 1:n_nodes(d)
        if length(d.revealed_adj[n]) > 0
            adj_labeled = filter(x->haskey(d.known_labels,x), d.revealed_adj[n])
            n_labeled = length(adj_labeled)
            if n_labeled > 0
                adj_labels = [d.known_labels[n] for n in adj_labeled]
                # use heuristic bayes rule approximation to guess label
                rel_p = Array(Float64, d.n_comms)
                for c in 1:d.n_comms
                    n_intra = sum(adj_labels.==c)
                    rel_p[c] = d.p_inter^n_intra*d.p_inter^(n_labeled-n_intra)
                end
                # select from the probability vector
                x = rand(rng)*sum(rel_p); i = 1; p_sum = rel_p[1];
                while p_sum < x
                    i += 1; p_sum += rel_p[i];
                end
                s.labels[n] = i
                continue
            end
        end
        # if we have not continued by now, assign randomly
        s.labels[n] = ceil(rand(rng)*d.n_comms)
    end

    # connect based on probabilities
    # XXX speed up by moving if statements outside?
    for i in 1:n_nodes(d)
        if !(i in d.probed)
            for j in i+1:n_nodes(d)
                if !(j in d.probed)
                    if s.labels[i] == s.labels[j]
                        if rand(rng) < d.p_intra
                            add_edge!(s.graph, i, j)
                        end
                    else
                        if rand(rng) < d.p_inter
                            add_edge!(s.graph, i, j)
                        end
                    end
                end
            end
        end
    end

    # make sure to add edges we know about
    for ed in d.revealed_edges
        if !has_edge(s.graph, ed)
            add_edge!(s.graph, ed)
        end
    end

    return s 
end

function belief(p::CommunityAffiliationPOMDP, b::RevealedGraph, a::ProbeNode, o::Neighborhood, d=RevealedGraph())

    clone!(d, b)
    push!(d.probed, a.node)
    d.budget = d.budget-1
    for n in o.neighbors
        add_edge!(d, a.node, n)
        push!(d.revealed_nodes, n)
    end

    return d
end

function belief(p::CommunityAffiliationPOMDP, b::RevealedGraph, a::GuessAffiliation, o::Neighborhood, d=RevealedGraph())
    clone!(d,b)
    d.budget -= 1
    return d
end


