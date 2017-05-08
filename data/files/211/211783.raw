# test

using Gadfly
using DataFrames
# get the file names in the current folder
files = readdir()
# read the data into dataframe - named 
# function arguments, yeah!
data = readtable(files[2],separator=',',header=false)
# rename the column headers - ! at the 
# end of function names indicates that 
# the inputs will be modified by the function (though
# this is only based on mutual agreement, not an 
# in-built language feature) 
colnames!(data,["time","R","L","RL"])


