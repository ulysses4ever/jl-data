require("decision_tree.jl")

module L1RandomForest

using L1DecisionTree
using DataFrames
using Stats

import L1DecisionTree.predict

export RandomForest, build_forest, predict

type RandomForest{T}
	trees::Vector{DecisionTree{T}}
end

function build_forest(X::DataFrame, Y::Vector, n_trees::Int=50, min_leaf_samples::Int=5, max_depth::Int=50)
	feats_per_split = ifloor(size(X, 2) / 3)

	trees = @parallel (vcat) for i in 1:n_trees
		build_bootstrap_tree(X, Y, min_leaf_samples, max_depth, feats_per_split)
	end

	RandomForest(trees)
end

function predict(rf::RandomForest, X::DataFrame)

	results = @parallel (hcat) for t in rf.trees
		predict(t, X)
	end
	mapslices(median, results, 2)
end

function build_bootstrap_tree(X::DataFrame, Y::Vector, min_leaf_samples::Int=5, max_depth::Int=50, feats_per_split::Int=0)
	indices = Stats.sample(1:size(X,1), size(X,1), replace=true, ordered=true)
	L1DecisionTree.build_tree(X[indices, :], Y[indices], min_leaf_samples, max_depth, feats_per_split)
end

end