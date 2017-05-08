# Calculate a linear regression from the example dataset, "gasoline.csv"
# From https://forio.com/labs/julia-studio/tutorials/

data = readcsv("gasoline.csv")

# Julia is column-major and one-indexed. Get all rows from cols 2-4 and 6.
x = data[:, 2:4]
y = data[:, 6]

# Call linreg
coefs = linreg(x, y)

offset = coefs[1]
c1 = coefs[2]
c2 = coefs[3]
c3 = coefs[4]

println("Offset: ", offset)
println("C1: ", c1)
println("C2: ", c2)
println("C3: ", c3)
