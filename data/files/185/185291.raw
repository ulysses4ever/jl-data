require("single_item_count.jl")
result_file = "result.txt"
data_files = "data/kosarak.dat"
threshold = 1000

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
