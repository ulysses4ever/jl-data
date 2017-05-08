require("random_forest.jl")

using DataFrames
using L1RandomForest
using L1DecisionTree

df = readtable("../data/train_imputed.csv",
			   header=true, nrows=10000 )
X = df[1:5000, 1:end-1]
y = Float64[x for x in df[1:5000, size(df, 2)]]

println("Tree Feat Subset")
@time build_tree(X, y, 5, 50, ifloor(size(X, 2) / 3))

println("Tree All Feats")
@time build_tree(X, y, 5, 50)

println("Boostrapped Tree Feat Subset")
@time L1RandomForest.build_bootstrap_tree(X, y, 5, 50, ifloor(size(X, 2) / 3))

println("Boostrapped Tree All Feats")
@time L1RandomForest.build_bootstrap_tree(X, y, 5, 50)

