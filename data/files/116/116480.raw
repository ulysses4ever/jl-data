include("/Users/feifeihuang/lab3/lab3_3d.jl");
using Base.Test

srand(42);
N = 10000;
true_mean = 10000.;
y = true_mean+randn(N);

@test isa(y,Array);
@test isa(variance(y),Float64);
