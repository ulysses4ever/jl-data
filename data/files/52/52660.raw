using WeightedStats
using Base.Test

function approx_eq(a, b, tol)
    abs(a - b) < tol
end

tol = 1e-6

data = (
    [7, 1, 2, 4, 10],
    [7, 1, 2, 4, 10],
    [7, 1, 2, 4, 10, 15],
    [1, 2, 4, 7, 10, 15],
    [0, 10, 20, 30],
    [1, 2, 3, 4, 5],
    [1, 2, 3, 4, 5],
    [30, 40, 50, 60, 35],
    [2, 0.6, 1.3, 0.3, 0.3, 1.7, 0.7, 1.7, 0.4],
    [3.7, 3.3, 3.5, 2.8],
    [100, 125, 123, 60, 45, 56, 66],
)
weights = (
    [1, 1/3, 1/3, 1/3, 1],
    [1, 1, 1, 1, 1],
    [1, 1/3, 1/3, 1/3, 1, 1],
    [1/3, 1/3, 1/3, 1, 1, 1],
    [30, 191, 9, 0],
    [10, 1, 1, 1, 9],
    [10, 1, 1, 1, 900],
    [1, 3, 5, 4, 2],
    [2, 2, 0, 1, 2, 2, 1, 6, 0],
    [5, 5, 4, 1],
    [30, 56, 144, 24, 55, 43, 67],
)
median_answers = (7, 4, 8.5, 8.5, 10, 2.5, 5, 50, 1.7, 3.5, 100)
mean_answers = (6.444444, 4.800000, 8.583333,
                8.583333, 9.086956, 2.909091,
                4.949617, 47.333333, 1.275,
                3.453333, 91.782816)

num_tests = length(data)

@test_throws MethodError weighted_median(data[1])
@test_throws MethodError weighted_median("string", "input")
@test_throws MethodError weighted_mean(data[1])
@test_throws MethodError weighted_mean("string", "input")

for i = 1:num_tests
    @test approx_eq(weighted_median(data[i], weights[i]), median_answers[i], tol)
    @test approx_eq(weighted_mean(data[i], weights[i]), mean_answers[i], tol)
end
