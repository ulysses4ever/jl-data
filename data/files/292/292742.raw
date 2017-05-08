"""
Split.jl
"""
module Split

using DataFrames

# functions
export sample

"""
Sample splits a set into two sets by a specificed percentage
# Arguments
* `df`: Array, DataFrame or DataArray to be split
* `fraction::Real`: Fraction of the split
* `seed::Integer`: Seed to replicable split
# Returns
* '(training_set, test_set)': Split result
"""
function sample(df, fraction::Real, seed::Integer)
    # copy
    norm_df = deepcopy(df)

    # rows
    (rows,) = size(norm_df)

    # split
    train_index, test_index = sample_indices(rows, fraction, seed)

	return norm_df[train_index, :], norm_df[test_index, :]
end

# Returns the indicies for each set
function sample_indices(rows::Integer, fraction::Real, seed::Integer)
    # index all rows
	indices = [1:rows;]

    # shuffle indicies to a reproducable set based on seed
    indices = seeded_shuffle(indices, seed)

    # round to integer based on a % of rows
	index = round(Integer, rows * fraction)

	return indices[1:index], indices[(index + 1):rows]
end

# Shuffles an array in a repeatable manner, if the same seed is provided.
function seeded_shuffle(indices, seed::Integer)
    # Create a new randomizer
    mt = Base.Random.MersenneTwister(seed)

    # Seed for replicable random
    srand(seed)

    return shuffle(mt, indices)
end

end
