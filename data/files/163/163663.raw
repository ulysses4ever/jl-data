function WriteFluxes(i)
# Read number of timepoints
num_tp = convert(Int64,readdlm("./Ensemble18000/$i/Flux/num_tp")[1])
# Read first flux
rate_vector = readdlm("./Ensemble18000/$i/Flux/1")
# Read all other fluxes; append to first flux
j_range = 2:num_tp
for j in j_range
    r = readdlm("./Ensemble18000/$i/Flux/$j")
    rate_vector = [rate_vector r]
end
# Save flux at t = 0
tp = rate_vector[1,:]
index = find(tp.==minimum(tp))[1]
writedlm("./Ensemble18000/$i/flux_0",rate_vector[2:end,index])
# Save flux at t = 1.5
tp_1_5 = abs(tp-1.5)
index = find(tp_1_5.==minimum(tp_1_5))[1]
writedlm("./Ensemble18000/$i/flux_1_5",rate_vector[2:end,index])
# Save flux at t = 3
tp_3 = abs(tp-3.0)
index = find(tp_3.==minimum(tp_3))[1]
writedlm("./Ensemble18000/$i/flux_3",rate_vector[2:end,index])
end
