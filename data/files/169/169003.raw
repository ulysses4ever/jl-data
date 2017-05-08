#To install DataFrames.jl, use the following:
#Pkg.add("DataFrames")
# to run from console:  julia>include("dataframe_test.jl")

using DataFrames

println("DataArray is analogous to pandas Series")
da=DataArray([5:8])  #build from Array
length(da)
sum(da)
mean(da)
std(da)
da .> 7  #array of Bools  true/false
da[da.>7] #filter on condition

#see https://github.com/HarlanH/DataFrames.jl/blob/master/demo/demo3.jl
# Load a CSV file into a DataFrame.
df = read_table("toy_example.csv")

println("\nBasic ways to look at a DataFrame")
print(df)
head(df,3)
tail(df)

nrow(df)
ncol(df)

# columns
colnames(df)  # Array of colnames
describe(df)  # Print out a summary of each column.

df[:A]    # refer to col as Symbol
df["A"]   # refer to col as String
df[1]     # refer to col by index number
df[1:3]   # range of cols
df[["A","B"]]  # list of cols

println("\nLook at the data structure.")
dump(df)  # dump() is like R's str().
#idump(df)  # Look at the internal data structure.

# Basic referencing and slicing
# singleton references return a basic element; slices are DataFrames
df[1, :]
df["A"]
df[1, "A"]
df[1:2, "A"]
df[1:2, ["A", "B"]]

# return Array of Bool
with( df, :( A .> 4.0 ))
df["A"] .> 4.0

# new col
df["D"]= 2*df["A"]
df["E"]= 42
df["E"]= NA
write_table("toy2.csv", df)

# Select all rows where column A is greater than 4.0
# Element-wise operators in Julia usually have a leading "."
df[:( A .> 4.0 ), :]

# Make a new column using within
df2 = within(df, :( D = A + C ))

# This is similar, but now changes apply directly to df
within!(df, quote
    D = A + C
    E = A + sum(C)
end)


# add rows/cols
# hcat, vcat, hbind, cbind()

println("\nGrouping and aggregation")
grpB = groupby(df,"B")

# from https://github.com/HarlanH/DataFrames.jl/blob/master/demo/examples.jl
using RDatasets
iris = RDatasets.data("datasets", "iris")

unique(iris["Species"])
stack(iris, ["Petal.Length", "Petal.Width"])

for df in groupby(iris, "Species")
    println("A DataFrame with $(nrow(df)) rows")
    #print(head(df,2))
end

#
# The | (pipe) operator for GroupedDataFrame's allows you to run
# simple functions on the columns of the induced DataFrame's.
#
# You pass a simple function by producing a symbol with its name.
#

print(groupby(iris, "Species") | :mean)

#https://github.com/HarlanH/DataFrames.jl/blob/master/demo/demo4.jl
# Group by a and b:
by(df, ["a", "b"], :( x_sum = sum(x); x_len = length(x) ))


print("\nMerge and Join")
flowers = DataFrame()
flowers["Species"] = ["virginica", "versicolor", "setosa", "daisy"]
flowers["PrimaryColor"] = ["purplish", "purple", "purple", "yellow"]

merge(iris, flowers, "Species", "inner")
merge(iris, flowers, "Species", "left")
merge(iris, flowers, "Species", "right")
merge(iris, flowers, "Species", "outer")

print("Done")
