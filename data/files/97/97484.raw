using Base.Test
using MultiCriteriaSort
using MultiCriteriaSort.mc_lt
using Base.Forward

matrix = [1 3 2; 1 2 3; 1 1 1; 3 4 4; 3 4 1; 3 4 2]
result = [1 1 1; 1 2 3; 1 3 2; 3 4 1; 3 4 2; 3 4 4]
result_rev =  [3 4 4; 3 4 2; 3 4 1; 1 3 2; 1 2 3; 1 1 1]

# All columns
@test sort(matrix, [1:3]) == result
@test sort(matrix, [1:3]; rev = true) == result_rev
@test sortperm(matrix, [1:3]) == [3, 2, 1, 5, 6, 4]
@test sortperm(matrix, [1:3]; rev = true) == [4,6,5,1,2,3]


# Two columns
result = [1 1 1; 1 3 2; 1 2 3; 3 4 1; 3 4 2; 3 4 4]
result_rev =  [3 4 4; 3 4 2; 3 4 1; 1 2 3; 1 3 2; 1 1 1]

@test sort(matrix, [1,3]) == result
@test sort(matrix, [1,3]; rev = true) == result_rev
@test sortperm(matrix, [1,3]) == [3, 1, 2, 5, 6, 4]
@test sortperm(matrix, [1,3]; rev = true) == [4,6,5,2,1,3]

# One column
result = [1 1 1; 3 4 1; 1 3 2; 3 4 2; 1 2 3; 3 4 4]
result_rev =  [3 4 4; 1 2 3; 1 3 2; 3 4 2; 1 1 1;  3 4 1]

@test sort(matrix, [3]) == result
@test sort(matrix, [3]; rev = true) == result_rev
@test sortperm(matrix, [3]) == [3, 5, 1, 6, 2, 4]
@test sortperm(matrix, [3]; rev = true) == [4, 2, 1, 6, 3, 5]

# Errors
@test_throws sort!(matrix, [1:3]; dim = 3)
@test_throws sort!(matrix, [1:3]; dim = 0)

a = rand(1:3, 1000, 10)
for alg in [InsertionSort, QuickSort, MergeSort]
    b = sort(a, [1:10], alg = alg)
    @test !(all([mc_lt(Forward, b, i, i - 1, [1:10], 1) for i = 2:1000]))
    ix = sortperm(a, [1:10], alg = alg)
    b = a[ix, :]
    @test !(all([mc_lt(Forward, b, i, i - 1, [1:10], 1) for i = 2:1000]))
end
