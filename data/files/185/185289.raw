require("single_item_count.jl")
require("item_pair_count.jl")
result_file = "result.txt"
pairs_file = "pairs.txt"
data_files = "data/kosarak.dat"
threshold = 10000

@time item_count = single_item_count(result_file,data_files)

println("Before Filter")
println("number of items = ",length(values(item_count)))
println("max frequency = ",maximum(values(item_count)))
println("mean frequency = ",mean(values(item_count)))

for (item,count) in item_count
    if(count < threshold)
        delete!(item_count,item)
    end
end

fo=open(result_file,"w")
for (item,count) in item_count
	#println(item,"=",count)
	write(fo,"$(item)\t=\t$(count)\n")
end

println("After Filter: threshold > ", threshold)
println("number of items = ",length(values(item_count)))
println("max frequency = ",maximum(values(item_count)))
println("mean frequency = ",mean(values(item_count)))

@time pair_count = item_pair_count(item_count, data_files)
println("Before Filter")
println("number of pairs = ",length(values(pair_count)))
println("max pair frequency = ",maximum(values(pair_count)))
println("mean pair frequency = ",mean(values(pair_count)))

for (pair,count) in pair_count
    if(count < threshold)
        delete!(pair_count,pair)
    end
end

fo2=open(pairs_file,"w")
for (pair,count) in pair_count
	#println(item,"=",count)
	write(fo2,"$(pair[1])\t$(pair[2])\t=\t$(count)\n")
end

println("After Filter")
println("number of pairs = ",length(values(pair_count)))
println("max pair frequency = ",maximum(values(pair_count)))
println("mean pair frequency = ",mean(values(pair_count)))
