using DataFrames
include("bst.jl")
using BinarySearchTree
import Base: insert!, delete!, median

abstract DTAbstractNode{T<:Real}

type DTNode{T<:Real} <: DTAbstractNode{T}
	split_feat::Uint
	split_val::Real
	left_child::DTAbstractNode{T}
	right_child::DTAbstractNode{T}
end

type DTLeaf{T<:Real} <: DTAbstractNode{T}
	value::T
end

type DecisionTree{T<:Real}
	head::DTNode{T}
end

function build_tree{T}(X::DataFrame, Y::Vector{T}, min_leaf_samples::Int=5)
	return DecisionTree(build_stump(X, Y, min_leaf_samples))
end

function predict{T}(tree::DecisionTree{T}, X::DataFrame)
	return predict(tree.head, X)
end

function predict{T}(node::DTNode{T}, X::DataFrame)
	return [predict(node, DataArray(x)) for x in EachRow(X)]::Array{T, 1}
end

function predict{T}(node::DTNode{T}, x::DataArray)
	if x[node.split_feat][1] <= node.split_val
		return predict(node.left_child, x)
	else
		return predict(node.right_child, x)
	end
end

function predict{T}(leaf::DTLeaf{T}, x)
	return leaf.value::T
end

function build_stump{T}(X::DataFrame, Y::Vector{T}, min_leaf_samples::Int)
	if length(Y) <= min_leaf_samples
		return DTLeaf(median(Y))
	else
		split_feat, split_val = get_split(X::DataFrame, Y::Vector)
		if split_feat == 0
			return DTLeaf(median(Y))
		end
		left_mask = X[:, split_feat] .<= split_val
		right_mask = X[:, split_feat] .> split_val
		if all(left_mask) || all(right_mask)
			error(split_feat, " ", split_val, " ", X)
		end
		return DTNode(split_feat, split_val,
					  build_stump(X[left_mask, :], Y[left_mask], min_leaf_samples),
					  build_stump(X[right_mask, :], Y[right_mask], min_leaf_samples)
					 )
	end
end

function get_split(X::DataFrame, Y::Vector)
	best_gain = 0.0
	n_feats = size(X, 2)
	best_feat::Uint = 0
	best_split = 0.0

	for feat in 1:n_feats
		split, gain = get_best_gain(X[:, feat], Y)
		if gain > best_gain
			best_gain = gain
			best_feat = feat
			best_split = split
		end
	end

	return best_feat, best_split
end

function get_best_gain(x::DataArray, y::Vector)
	sorted_indices = sortperm(x)
	ys = y[sorted_indices]
	xs = x[sorted_indices]

	best_split_pos::Int = 1
	best_gain::Float64 = 0.

	left = FastMAEAccumulator()
	right = FastMAEAccumulator()
	insert!(right, ys)

	total_mae::Float64 = right.mae

	for split_pos in 1:length(ys)
		insert!(left, ys[split_pos])
		delete!(right, ys[split_pos])
		if (split_pos < length(ys)) && (xs[split_pos + 1] == xs[split_pos])
			continue
		end
		gain = total_mae - left.mae - right.mae

		if gain > best_gain
			best_gain = gain
			best_split_pos = split_pos
		end
	end

	return xs[best_split_pos], best_gain
end


abstract MAEAccumulator

type OrderStatisticsTree
end

type FastMAEAccumulator{T} <: MAEAccumulator
	data::BST
	median::T
	mae::Float64
end

type VectorMAEAccumulator <: MAEAccumulator
	data::Vector
	median
	mae::Float64
end

FastMAEAccumulator() = FastMAEAccumulator{Float64}(BST(), 0.0, 0.0)
VectorMAEAccumulator() = VectorMAEAccumulator([], 0.0, 0.0)


function insert_many!(acc::VectorMAEAccumulator, y::Vector)
	acc.data = [acc.data, y]
	acc.median = median(y)
	acc.mae = sum(abs(y - acc.median))
	return acc
end

function insert!(acc::FastMAEAccumulator, y::Vector)
	insert!(acc.data, y)
	acc.median = median(acc.data)
	acc.mae = sum(abs(y - acc.median))
	return acc
end


function insert!(acc::VectorMAEAccumulator, yi::Real)
	n_by_2_before = floor(size(acc.data, 1) / 2)
	old_median = acc.median
	acc.data = [acc.data, yi]
	n_by_2_after = floor(size(acc.data, 1) / 2)
	new_median = median(acc.data)
	acc.mae += abs(yi - new_median)
	acc.mae += abs(old_median - new_median) * (n_by_2_after - n_by_2_before)
	acc.median = new_median
end

function insert!(acc::FastMAEAccumulator, yi::Real)
	n_by_2_before = ifloor(size(acc.data) / 2)
	old_median = acc.median
	insert!(acc.data, yi)
	n_by_2_after = ifloor(size(acc.data) / 2)
	new_median = median(acc.data)
	acc.mae += abs(yi - new_median)
	acc.mae += abs(old_median - new_median) * (n_by_2_after - n_by_2_before)
	acc.median = new_median
end

	
function delete!(acc::MAEAccumulator, yi::Real)
	n_by_2_before = ifloor(size(acc.data) / 2)
	old_median = acc.median
	delete!(acc.data, yi)
	n_by_2_after = ifloor(size(acc.data) / 2)
	new_median = size(acc.data) > 0 ? median(acc.data) : 0.0
	acc.mae -= abs(yi - old_median)
	acc.mae += abs(old_median - new_median) * (n_by_2_after - n_by_2_before)
	acc.median = new_median
end

function delete{T}(v::Vector{T}, y::T)
	o = Array(T, length(v)-1)
	found = false
	j::Uint = 1
	for i in 1:length(v)
		if v[i] != y || found
			o[j] = v[i]
			j += 1
		else
			found = true
		end
	end
	return o
end


using Base.Test

# function test_VectorMAEAccumulator_insert_many!()
# 	x = rand(100)
# 	acc = VectorMAEAccumulator()
# 	insert_many!(acc, x)
# 	@test median(acc.data) == median(x)
# 	@test acc.mae == sum(abs(x - median(x)))
# end

# function test_VectorMAEAccumulator_insert!()
# 	# start with even number of elements, insert number > median
# 	x = linspace(0, 5, 6)
# 	acc = VectorMAEAccumulator()
# 	insert_many!(acc, x)
# 	insert!(acc, 3.5)
# 	@test_approx_eq acc.mae sum(abs([x, 3.5] - 3))

# 	# start with even number of elements, insert number < median
# 	x = linspace(0, 5, 6)
# 	acc = VectorMAEAccumulator()
# 	insert_many!(acc, x)
# 	insert!(acc, 0.5)
# 	@test_approx_eq acc.mae sum(abs([x, 0.5] - 2))

# 	# start with odd number of elements, insert number > median
# 	x = linspace(0, 4, 5)
# 	acc = VectorMAEAccumulator()
# 	insert_many!(acc, x)
# 	insert!(acc, 3.5)
# 	@test_approx_eq acc.mae sum(abs([x, 3.5] - 2.5))

# 	# start with odd number of elements, insert number < median
# 	x = linspace(0, 4, 5)
# 	acc = VectorMAEAccumulator()
# 	insert_many!(acc, x)
# 	insert!(acc, 0.5)
# 	@test_approx_eq acc.mae sum(abs([x, 0.5] - 1.5))

# 	n::Int64 = 100
# 	x = rand(n)
# 	acc = VectorMAEAccumulator()
# 	split::Int64 = floor(n/2)
# 	insert_many!(acc, x[1:split])
# 	for i in (split+1):n
# 		insert!(acc, x[i])
# 		@test size(acc.data, 1) == size(x[1:i], 1)
# 		@test_approx_eq acc.mae sum(abs(x[1:i] - median(x[1:i]))) 
# 	end
# end

# function test_VectorMAEAccumulator_delete!()
# 	n::Int64 = 100
# 	x = rand(n)
# 	acc = VectorMAEAccumulator()
# 	split::Int64 = floor(n/2)
# 	insert_many!(acc, x)
# 	for i in reverse([(split):n])
# 		delete!(acc, x[i])
# 		@test size(acc.data, 1) == size(x[1:i-1], 1)
# 		@test_approx_eq acc.mae sum(abs(x[1:i-1] - median(x[1:i-1]))) 
# 	end
# end

function test_get_best_gain()
	x = DataArray([1:10])
	y = [ones(5), 2 * ones(5)]
	split, gain = get_best_gain(x, y)
	@test split == 5
	@test gain == sum(abs(y - 1.5))
end

function test_get_split()
	X = DataFrame()
	X[1] = rand(100)
	X[2] = [1:100]
	X[3] = rand(100)
	y = [ones(50), 2 * ones(50)]
	feat, split = get_split(X, y)
	@test feat == 2
	@test split == 50
end

function test_build_stump()
	X = DataFrame()
	X[1] = rand(100)
	X[2] = [1:100]
	X[3] = rand(100)
	y = [ones(50), 2 * ones(50)]
	stump = build_stump(X, y, 10)
	println(stump)
end


function test_decision_tree()
	df = readtable("Boston.csv")
	X = df[:, 2:(size(df, 2)-1)]
	y = df[:, size(df, 2)].data
	tree = build_tree(X, y, 1)

	y_pred = predict(tree, X)

	println(mean(abs(y - y_pred)))
end


# test_VectorMAEAccumulator_insert_many!()
# test_VectorMAEAccumulator_insert!()
# test_VectorMAEAccumulator_delete!()
test_get_best_gain()
test_get_split()
test_build_stump()
test_decision_tree()
@time test_decision_tree()
