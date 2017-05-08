# Sample program to read data from a csv
data = readcsv("sample-data/gasoline.csv")

# Get the columns that correspond with our X values
# and create a new matrix to hold them
# syntax: data[row, column]
# to get a whole row do data[row, :]
# to get a whole column do data[:, column]
# to get a range of columns do data[:, column_a:column_b]

x = data[:, 2:4]
y = data[:, 6]

# Perform Linear Regression on the data and get the resulting coefficients
# Essentially, we are trying to solve for the "B" coefficients in the set of
# equations: y = (B_1 * x_1) + (B_2 * x_2) + ... + (B_i * x_i) + e
# given a known set of y and x_1..i
coefs = linreg(x, y)

