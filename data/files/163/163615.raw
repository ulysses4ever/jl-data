cost = zeros(180000,1)

i_range = 1:180000
for i in i_range
    if rem(i,1000) == 0
        println(i)
    end
    cost[i] = readdlm("Ensemble/$i/cost")[1]
end

cost_sorted = sort(vec(cost))
cutoff = cost_sorted[180]
top_percent = find(cost.<=cutoff)

i_range = 1:length(top_percent)
for i in i_range
    dir = top_percent[i]
    cp("Ensemble/$dir","Ensemble180/$i")
end

