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

# Test that the shuffled input is different than the output
@test Split.seeded_shuffle(indices_da, seed) != indices_da

# Test that the shuffled input is equal to itself when the seed is the same
@test Split.seeded_shuffle(indices_da, seed) == Split.seeded_shuffle(indices_da, seed)

# Test that the fractional split is correct
(a, b) = Split.sample_indices(size_da, fraction, seed)
@test size(a) == (2,) && size(b) == (3,)

# Test that the type for array is correct
@test typeof(Split.sample(a, fraction, seed)) <: Tuple{Array, Array}

# Test that the type for array is correct
@test typeof(Split.sample(da, fraction, seed)) <: Tuple{DataArray, DataArray}

# Test that the type for array is correct
@test typeof(Split.sample(df, fraction, seed)) <: Tuple{DataFrame, DataFrame}
