# it's like SciPy had a love child with R
y = vector(train_df["quality"])
X = matrix(train_df[[colnames(train_df) .!= "quality"]])

# Generate train/test split
n = length(y)
is_train = shuffle([1:n] .> floor(n * .25))

X_train,X_test = X[is_train,:],X[!is_train,:]
y_train,y_test = y[is_train],y[!is_train]

# print stuff to the user
println("Total number of observations: ",n)
println("Training set size: ", sum(is_train))
println("Test set size: ", sum(!is_train))
