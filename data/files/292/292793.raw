require("random_forest.jl")

using Base.Test
using L1RandomForest
using L1DecisionTree
using DataFrames
import L1RandomForest: build_bootstrap_tree

function test_build_bootstrap()
	df = readtable("Boston.csv")
	X = df[:, 2:(size(df, 2)-1)]
	y = df[:, size(df, 2)].data
	tree = build_bootstrap_tree(X, y, 1)

	y_pred = predict(tree, X)

	@test mean(abs(y - y_pred)) < 2.
end

function test_build_rf()
	df = readtable("Boston.csv")
	X = df[:, 2:(size(df, 2)-1)]
	y = df[:, size(df, 2)].data
	rf = build_forest(X, y)

	y_pred = predict(rf, X)

	println(mean(abs(y - y_pred)))
	@test mean(abs(y - y_pred)) < 2.
end

# test_build_bootstrap()
test_build_rf()