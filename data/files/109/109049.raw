
# In main.jl
data = readcsv("C:\\Files\\Programs\\Wush\\Julia\\data\\gasoline.csv")

# Get the columns that correspond with our X values
# and create a new matrix to hold them
# syntax: data[row, column]
# to get a whole row do data[row, :]
# to get a whole column do data[:, column]
# to get a range of columns do data[:, column_a:column_b]

# Dissect data
x = data[:, 2:3]
y = data[:, 6]

# Call linreg
coefs = linreg(x, y)

println(coefs)

a1 = [1 2 3; 4 5 6]

a = [1, 2]
ar = repmat(a, 1, 3)
ar

broadcast(+, a, a1)

a + a1

dm = DataArray([1.0 0.0; 0.0 1.0])
dm[1, 1] = NA
dm * dm

df = DataFrame(A = 1:4, B = ["M", "F", "F", "M"])

nrows = size(df, 1)

df = readtable("C:\\Files\\Programs\\Wush\\Julia\\data\\gasoline.csv")

using DataFrames, RDatasets

iris = data("datasets", "iris")

by(iris, "Species", nrow)
by(iris, "Species", df -> mean(df["Petal.Length"]))
by(iris, "Species", :(N = size(_DF, 1)))

for subdf in groupby(iris, "Species")
	println(size(subdf, 1))
end

z = 0.0
for i = 1:100000000 
  z = sqrt(i + 1.0)
end
println(z)

@debug let  # line 1
   parts = {} # 2
   @bp        # 3
   for j=1:3  # 4
       for i=1:3  # 5
           push(parts,"($i,$j) ") # 6
       end        # 7
   end        # 8
   @bp        # 9
   println(parts...)
end

nr = 10
vec_ret = randn(nr)/100
dum_mat = rand(0:1, nr, 5)
