using Split, DataFrames
using Base.Test

# Array test
a = [1,2,3,4,5]

# DataArray test data
da = @data([1,2,3,4,5])
(size_da,) = size(da)
indices_da = [1:size_da;]

# DataFrames test data
df = DataFrame(A = 1:5, B = ["A", "B", "C", "D", "E"])

# Test data
fraction = 0.5
seed = 1234

@test Split.seeded_shuffle(indices_da, seed) == [1,3,2,5,4]

@test Split.sample_indices(size_da, fraction, seed) == ([1,3], [2,5,4])

@test Split.sample(a, fraction, seed) == ([1,3], [2,5,4])

@test Split.sample(da, fraction, seed) == ([1,3], [2,5,4])

@test Split.sample(df, fraction, seed) == (DataFrame(A = [1,3], B = ["A", "C"]), DataFrame(A = [2,5,4], B = ["B", "E", "D"]))
