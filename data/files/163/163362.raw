Flux_early = vec(readdlm("Ensemble18000/1/flux_0"))
Flux_mid = vec(readdlm("Ensemble18000/1/flux_1_5"))
Flux_late = vec(readdlm("Ensemble18000/1/flux_3"))

for i = 2:18000
    println(i)
    flux_early = vec(readdlm("Ensemble18000/$i/flux_0"))
    flux_mid = vec(readdlm("Ensemble18000/$i/flux_1_5"))
    flux_late = vec(readdlm("Ensemble18000/$i/flux_3"))
    Flux_early = [Flux_early flux_early]
    Flux_mid = [Flux_mid flux_mid]
    Flux_late = [Flux_late flux_late]
end

writedlm("Flux_early",Flux_early)
writedlm("Flux_mid",Flux_mid)
writedlm("Flux_late",Flux_late)
