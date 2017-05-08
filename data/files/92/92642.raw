using DataFrames
showln(x) = (show(x); println())
# TODO: needs more links to docs.

# A DataFrame is an in-memory database
df = DataFrame(A = [1, 2], B = [e, pi], C = ["xx", "xy"])
showln(df)
#> 2x3 DataFrame
#> |-------|---|---------|------|
#> | Row # | A | B       | C    |
#> | 1     | 1 | 2.71828 | "xx" |
#> | 2     | 2 | 3.14159 | "xy" |

# The columns of a DataFrame can be indexed using numbers or names
showln(df[1])
#> [1,2]
showln(df[:A])
#> [1,2]

showln(df[2])
#> [2.718281828459045,3.141592653589793]
showln(df[:B])
#> [2.718281828459045,3.141592653589793]

showln(df[3])
#> ASCIIString["xx","xy"]
showln(df[:C])
#> ASCIIString["xx","xy"]

# The rows of a DataFrame can be indexed only by using numbers
showln(df[1, :])
#> 1x3 DataFrame
#> |-------|---|---------|------|
#> | Row # | A | B       | C    |
#> | 1     | 1 | 2.71828 | "xx" |
showln(df[1:2, :])
#> 2x3 DataFrame
#> |-------|---|---------|------|
#> | Row # | A | B       | C    |
#> | 1     | 1 | 2.71828 | "xx" |
#> | 2     | 2 | 3.14159 | "xy" |

# importing data into DataFrames
# ------------------------------

# DataFrames can be loaded from CSV files using readtable()
iris = readtable("iris.csv")

# the iris dataset (and plenty of others) is also available from
using RDatasets
iris = dataset("datasets","iris")

# you can directly import your own R .rda dataframe with
# mydf = DataFrame(read_rda("path/to/your/df.rda")["name_of_df"]), e.g.
diamonds = DataFrame(read_rda(joinpath(Pkg.dir("RDatasets"),"data","ggplot2","diamonds.rda"))["diamonds"])

# showing DataFrames
# ------------------

# Check the names and element types of the columns of our new DataFrame
showln(names(iris))
#> [:SepalLength,:SepalWidth,:PetalLength,:PetalWidth,:Species]
showln(eltypes(iris))
#> Type[Float64,Float64,Float64,Float64,UTF8String]

# Subset the DataFrame to only include rows for one species
showln(iris[iris[:Species] .== "setosa", :])


# Count the number of rows for each species
showln(by(iris, :Species, df -> size(df, 1)))
#> 3x2 DataFrame
#> |-------|--------------|----|
#> | Row # | Species      | x1 |
#> | 1     | "setosa"     | 50 |
#> | 2     | "versicolor" | 50 |
#> | 3     | "virginica"  | 50 |

# Discretize entire columns at a time
iris[:SepalLength] = round(Integer, iris[:SepalLength])
iris[:SepalWidth] = round(Integer, iris[:SepalWidth])


# Tabulate data according to discretized columns to see "clusters"
tabulated = by(
    iris,
    [:Species, :SepalLength, :SepalWidth],
    df -> size(df, 1)
)
showln(tabulated)


# you can setup a grouped dataframe like this
gdf = groupby(iris,[:Species, :SepalLength, :SepalWidth])

# and then iterate over it
for idf in gdf
    println(size(idf,1))
end

# Adding/Removing columns
# -----------------------

# insert!(df::DataFrame,index::Int64,item::AbstractArray{T,1},name::Symbol)
# insert random numbers at col 5:
insert!(iris, 5, rand(nrow(iris)), :randCol)

# remove it
delete!(iris, :randCol)
