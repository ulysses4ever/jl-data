module Test

using Balance, DataFrames, DataArrays, RDatasets

l = 200
n = 4*l

# Get and clean test data

movies = dataset("ggplot2", "movies")

df = movies[movies[:MPAA] .!= "", [:Year, :Length, :Budget, :Rating, :Votes, :MPAA, :Action]]
df = df[df[:MPAA] .!= "NC-17", :][1:n, :]
df[:Action] = bool(df[:Action])
df[rand(1:n, fld(n, 10)), :Length] = NA

# Prep

a = [1:n];
g = FixedGroups([:control, :test1, :test2], [2l, l, l])

scales = prepdata(df, g)
iterations = 1_000


# Balance a couple ways 

split1 = splitby(a, g)
log1 = @time balance!(split1, scales, iterations, metric1)
print(log1)

split2 = splitby(a, g, 10)
log2 = @time balance!(split2, scales, iterations, metric1)
print(log2)

split3 = splitby(a, g, 2)
log3 = @time balance!(split3, scales, iterations, metric1)
print(log3)


end # module Test
