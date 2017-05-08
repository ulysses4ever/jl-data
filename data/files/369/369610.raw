using Base.Test
using RandomFerns

features = reshape([0:0.01:10],1001,1);
labels = vec(sin(features) + (randn(size(features))/2));

println("\n ### k fold CV - Random Fern Regression ###")
r2 = kfoldCV_fern(labels, features, 10, 5)
@test mean(r2) > 0.3

println("\n ### k fold CV - Random Fern Ensemble Regression ###")
r2 = kfoldCV_fernEnsemble(labels, features, 10, 5, 100)
@test mean(r2) > 0.5
