require("random_forest.jl")

using DataFrames
using L1RandomForest
using L1DecisionTree
using Resampling

function get_mae(model, X, y)
	y_pred = predict(model, X)
	mean(abs(y_pred - y))
end

df = readtable("../data/train_imputed.csv",
			   header=true )

function train(df)
	X = df[:, 1:end-1]
	y = Float64[x for x in df[:, size(df, 2)]]
	build_forest(X, y, 1000, 3, 50)
end

function test(df, m)
	X = df[:, 1:end-1]
	y = Float64[x for x in df[:, size(df, 2)]]
	get_mae(m, X, y)
end

train_results, test_results = kfold_crossvalidate(df, train, test, 5)

println(test_results)

