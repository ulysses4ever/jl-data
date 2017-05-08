#To install DataFrames.jl, use the following:
#Pkg.add("DataFrames")
# to run from console: 
# julia>include("dataframe_test.jl")

# Load DataFrames
#require("DataFrames")
using DataFrames


# DataArray is analogous to pandas Series
da=DataArray([5:8])  #build from Array
length(da)
sum(da)
mean(da)
std(da)
da .> 7  #array of Bools  true/false
da[da.>7] #filter on condition

# Load a CSV file into a DataFrame.
df = read_table("toy_example.csv")

# Basic ways to look at a DataFrame
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

# Look at the data structure.
dump(df)  # dump() is like R's str().
idump(df)  # Look at the internal data structure.

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

# add rows/cols
# hcat, vcat, hbind, cbind()

#aggregation
grpB = groupby(df,"B")
