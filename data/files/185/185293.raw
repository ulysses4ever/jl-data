require("single_item_count.jl")
require("candidate_pair.jl")
result_file = "result.txt"
data_files = "data/kosarak.dat"
candidate_file = "candidate.txt"
threshold = 2000
hash_type = "sum_keys"

@time item_count = single_item_count(result_file,data_files)

println("Before Filter")
println("number of single items = ",length(values(item_count)))
println("max single frequency = ",maximum(values(item_count)))
println("mean singel frequency = ",mean(values(item_count)))

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



@time candidate_count = candidate_pair(item_count, hash_type, data_files)
println("Before Filter")
println("number of canditates = ",length(values(candidate_count)))
println("max candidate frequency = ",maximum(values(candidate_count)))
println("mean candidate frequency = ",mean(values(candidate_count)))

for (hashKey,count) in candidate_count
    if(count < threshold)
        delete!(candidate_count,hashKey)
    end
end

fo2=open(candidate_file,"w")
for (hashKey,count) in candidate_count
        #println(item,"=",count)
        write(fo2,"$(hashKey)\t=\t$(count)\n")
end

println("After Filter")
println("number of canditates = ",length(values(candidate_count)))
println("max candidate frequency = ",maximum(values(candidate_count)))
println("mean candidate frequency = ",mean(values(candidate_count)))