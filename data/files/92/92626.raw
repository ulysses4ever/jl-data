using RDatasets, DataFrames

anscombe = dataset("datasets","anscombe")

typeof(anscombe)

head(anscombe)
tail(anscombe)

size(anscombe) 
length(anscombe)

showcols(anscombe)



anscombe[anscombe[:Y1] .> 7.0, :]



mean(anscombe[:X2])
colwise(mean, anscombe)
