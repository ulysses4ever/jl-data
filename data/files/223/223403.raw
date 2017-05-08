# View summary of data - note there are missing values in every column except 'good'
data

# Review the first 6 obs
head(data)

# Histogram of cancer deaths - doesn't work because of NAs
hist(data[ : , :dc])

# Create an index for non-missing dc
dc_nomiss = !isna(data[:, :dc])

# Histogram of cancer deaths, no NAs 
hist(data[ dc_nomiss, :dc])

# Are there really negative values for the death count?
minimum(data[ dc_nomiss, :dc])

maximum(data[ dc_nomiss, :dc])

quantile(data[ dc_nomiss, :dc])

# For what counties and states is dc missing?
data[ !dc_nomiss, "state"]

# See summary stats for all variables
describe(data)

# Let's plot some things
using Winston

hist_1 = FramedPlot(
	title = "Histogram of dc", 
	xlabel = "dc",
	ylabel = "Count")

add(hist_1, Histogram(data[ !dc_nomiss, :dc]))