module TestCausalAlgorithms
using Base.Test
using Causality
using DataFrames
using Requests

sample_data = replace(replace(Requests.get("http://data.princeton.edu/wws509/datasets/smoking.dat").data, r" +", "\t"), r"\r", "")
io = IOBuffer(sample_data)
df = DataFrames.readtable(io, separator='\t', makefactors=true, header=true)
vars = names(df)




# each of these 
