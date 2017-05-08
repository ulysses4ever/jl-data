include("decision_tree.jl")

using Base.Test
using L1DecisionTree
import L1DecisionTree: FastMAEAccumulator, get_split, get_best_gain, build_stump
using DataFrames

function test_FastMAEAccumulator_insert_many!()
	x = rand(100)
	acc = FastMAEAccumulator()
	insert!(acc, x)
	@test median(acc.data) == median(x)
	@test acc.mae == sum(abs(x - median(x)))
end

function test_FastMAEAccumulator_insert!()
	# start with even number of elements, insert number > median
	x = linspace(0, 5, 6)
	acc = FastMAEAccumulator()
	insert!(acc, x)
	insert!(acc, 3.5)
	@test_approx_eq acc.mae sum(abs([x, 3.5] - 3))

	# start with even number of elements, insert number < median
	x = linspace(0, 5, 6)
	acc = FastMAEAccumulator()
	insert!(acc, x)
	insert!(acc, 0.5)
	@test_approx_eq acc.mae sum(abs([x, 0.5] - 2))

	# start with odd number of elements, insert number > median
	x = linspace(0, 4, 5)
	acc = FastMAEAccumulator()
	insert!(acc, x)
	insert!(acc, 3.5)
	@test_approx_eq acc.mae sum(abs([x, 3.5] - 2.5))

	# start with odd number of elements, insert number < median
	x = linspace(0, 4, 5)
	acc = FastMAEAccumulator()
	insert!(acc, x)
	insert!(acc, 0.5)
	@test_approx_eq acc.mae sum(abs([x, 0.5] - 1.5))

	n::Int64 = 100
	x = rand(n)
	acc = FastMAEAccumulator()
	split::Int64 = floor(n/2)
	insert!(acc, x[1:split])
	for i in (split+1):n
		insert!(acc, x[i])
		@test size(acc.data) == size(x[1:i], 1)
		@test_approx_eq acc.mae sum(abs(x[1:i] - median(x[1:i]))) 
	end
end

function test_FastMAEAccumulator_delete!()
	n::Int64 = 100
	x = rand(n)
	acc = FastMAEAccumulator()
	split::Int64 = floor(n/2)
	insert!(acc, x)
	for i in reverse([(split):n])
		delete!(acc, x[i])
		@test size(acc.data) == size(x[1:i-1], 1)
		@test_approx_eq acc.mae sum(abs(x[1:i-1] - median(x[1:i-1]))) 
	end
end

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
	feat, split = get_split(X, y, 3)
	@test feat == 2
	@test split == 50
end

function test_build_stump()
	X = DataFrame()
	X[1] = rand(100)
	X[2] = [1:100]
	X[3] = rand(100)
	y = [ones(50), 2 * ones(50)]
	stump = build_stump(X, y, 10, 1, 3)
end


function test_decision_tree()
	df = readtable("Boston.csv")
	X = df[:, 2:(size(df, 2)-1)]
	y = df[:, size(df, 2)].data
	tree = build_tree(X, y, 1)

	y_pred = predict(tree, X)

	@test mean(abs(y - y_pred)) < 1.
end

function time_decision_tree()
	df = readtable("../../Kaggle/LoanDefault/data/train_imputed.csv",
				   header=true, nrows=5000 )

	# run once to get everything jit-ed
	X = df[1:100, 1:20]
	y = Float64[x for x in df[1:100, size(df, 2)]]
	build_tree(X, y, 1, 10)

	function time_tree(n::Integer, m::Integer)
		if m > size(df, 2)-1
			error("m must be less than number of features in dataset")
		end
		X = df[1:n, 1:(1+m)]
		y = Float64[x for x in df[1:n, size(df, 2)]]
		t1 = time()
		build_tree(X, y, 1, 5, ifloor(size(X, 2) / 2))
		t2 = time()
		println(n, ",", m, ",", t2-t1)
	end

	for n in 50:50:2000
		time_tree(n, 30)
	end
end


# test_FastMAEAccumulator_insert_many!()
# test_FastMAEAccumulator_insert!()
# test_FastMAEAccumulator_delete!()
test_get_best_gain()
test_get_split()
test_build_stump()
test_decision_tree()
test_decision_tree()
time_decision_tree()