require("random_forest.jl")

using DataFrames
using L1RandomForest
using L1DecisionTree

function get_mae(model, X, y)
	y_pred = predict(model, X)
	mean(abs(y_pred - y))
end

df = readtable("../data/train_imputed.csv",
			   header=true, nrows=10000 )
X = df[1:5000, 1:end-1]
y = Float64[x for x in df[1:5000, size(df, 2)]]
t1 = time()
rf = build_forest(X, y, 8, 3, 50)
t2 = time()
println("time to build forest: ", t2-t1)

tree = build_tree(X, y, 3, 50)

X_test = df[5001:10000, 1:end-1]
y_test = Float64[x for x in df[5001:10000, size(df, 2)]]


rf_train_mae = get_mae(rf, X, y)
rf_test_mae = get_mae(rf, X_test, y_test)

dt_train_mae = get_mae(tree, X, y)
dt_test_mae = get_mae(tree, X_test, y_test)

println("Random Forest:")
println("Train MAE: ", rf_train_mae)
println("Test MAE: ", rf_test_mae)

println("Decision Tree:")
println("Train MAE: ", dt_train_mae)
println("Test MAE: ", dt_test_mae)

