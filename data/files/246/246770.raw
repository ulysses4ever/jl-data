using DataFrames, HDF5, JLD

include("EA.jl")
include("RobotGene.jl")
include("VarLengthIndividual.jl")
include("GAPopulation.jl")

df = DataFrame()

df[:α] = [100,1000,10000,100000,1000000]

df[symbol("β=100 : acc")] = [0,0,0,0,0]
df[symbol("β=100 : torque")] = [0,0,0,0,0]
df[symbol("β=100 : cost")] = [0,0,0,0,0]

df[symbol("β=10000 : acc")] = [0,0,0,0,0]
df[symbol("β=10000 : torque")] = [0,0,0,0,0]
df[symbol("β=10000 : cost")] = [0,0,0,0,0]

df[symbol("β=1000000 : acc")] = [0,0,0,0,0]
df[symbol("β=1000000 : torque")] = [0,0,0,0,0]
df[symbol("β=1000000 : cost")] = [0,0,0,0,0];

file = jldopen("allData.jld","r")
allData = Any[]
allData = read(file,"allData")
close(file);

torque_counts = zeros(Int,15,15)
acc_counts = zeros(Int,15,15)
costs = zeros(15,15);
