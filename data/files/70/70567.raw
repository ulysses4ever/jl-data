using DataFrames
using Gadfly

# file to read (with headers)
fname = ""
out = ""

data = read_table(fname)

# Equivalent to sort(unique(data["ds"]))
distinct_dates = sort(unique(data[:,1]))

# Get the data for a specific date
data_11_10 = data[:(ds .== "2013-11-10"), :]

my_plot = plot(data, x="x_col", y="y_col", color="color_col", Geom.histogram)

draw(SVG(out, 9inch, 9inch / golden), my_plot)
