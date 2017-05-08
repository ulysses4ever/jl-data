using WeightedStats
using Base.Test

data = (
    [7, 1, 2, 4, 10],
    [7, 1, 2, 4, 10],
    [7, 1, 2, 4, 10, 15],
    [1, 2, 4, 7, 10, 15],
    [0, 10, 20, 30],
    [1, 2, 3, 4, 5],
    [30, 40, 50, 60, 35],
    [2, 0.6, 1.3, 0.3, 0.3, 1.7, 0.7, 1.7, 0.4],
)
weights = (
    [1, 1/3, 1/3, 1/3, 1],
    [1, 1, 1, 1, 1],
    [1, 1/3, 1/3, 1/3, 1, 1],
    [1/3, 1/3, 1/3, 1, 1, 1],
    [30, 191, 9, 0],
    [10, 1, 1, 1, 9],
    [1, 3, 5, 4, 2],
    [2, 2, 0, 1, 2, 2, 1, 6, 0],
)
median_answers = (7, 4, 8.5, 8.5, 10, 2.5, 50, 1.7)
mean_answers = (6.444444444444444, 4.800000000000001, 8.583333333333334,
                8.583333333333332, 9.08695652173913, 2.909090909090909,
                47.33333333333333, 1.275)

num_tests = length(median_answers)

@test_throws MethodError weighted_median(data[1])
# @test_throws MethodError weighted_mean(data[1])
@test_throws MethodError weighted_median("string", "input")
# @test_throws MethodError weighted_mean("string", "input")

for i = 1:num_tests
    @test isa(data[i], NumericArray)
    @test isa(weights[i], NumericArray)
    @test typeof(median_answers[i]) <: Real
    @test weighted_median(data[i], weights[i]) == median_answers[i]
    @test weighted_mean(data[i], weights[i]) == mean_answers[i]
end
