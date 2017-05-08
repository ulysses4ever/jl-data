cost = zeros(18000,1)

i_range = 1:18000
for i in i_range
    if rem(i,1000) == 0
        println(i)
    end
    cost[i] = readdlm("Ensemble18000/$i/cost")[1]
end

cost_sorted = sort(vec(cost))
cutoff = cost_sorted[1]
top = find(cost.==cutoff)

cp("Ensemble18000/$top","EnsembleBest")

