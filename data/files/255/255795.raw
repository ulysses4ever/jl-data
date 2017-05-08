function fibonacci(argu)
startlist = argu
lth = length(startlist)
new = startlist[lth-1] + startlist[lth]
while new <= 4000000
    push!(startlist,new)
    lth = length(startlist)
    new = startlist[lth-1] + startlist[lth]
end
return startlist
end

starting = [1,2]
fibon = fibonacci(starting)

function addevens(argu)
total = 0
for i = 1:length(argu)
    if argu[i] % 2 == 0
        total += argu[i]
    end
end
return total
end

println(addevens(fibon))