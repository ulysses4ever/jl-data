highest = 0
for i = 1:9
val = i*(9^5)
if length(string(val)) >= i
highest = val
end
end
println(highest)

# highest is 354294

powsums = Int64[]
for i = 10:354294
    sumit = 0
    for j = 1:length(string(i))
        num = (string(i))[j]
        sumit += parseint(num)^5
        end
    if sumit == i
        push!(powsums,i)
        end
    end

finaltot = 0
for i = 1:length(powsums)
    finaltot += powsums[i]
    end

println(finaltot)