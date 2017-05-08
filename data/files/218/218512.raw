# gas_reg.jl

# Load CSV data
data = readcsv("data/gasoline.csv")

# Dissect data
x = data[:, 2:4]
y = data[:, 6]

# Call linreg
coefs = linreg(x, y)
println("Coeficients: ", coefs)
