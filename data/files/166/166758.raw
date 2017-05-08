tic()
println("Prepping...")

require("GjT_002_properties.jl")
require("GjT_002_proc.jl")

data_f = open(data_file)
data_arr = readlines(data_f)

ver_s = length(data_arr)
hor_s = length(split(data_arr[1], ','))
data = Array(Any, ver_s, hor_s)
for i in 1:ver_s
	tmp_row = split(data_arr[i], ',')
	for j in 1:hor_s
		data[i,j] = tmp_row[j]
	end
end

#data = readcsv(data_file, String)
data_dims = size(data)

data_attr_count = data_dims[2] - 1
data_entr_count = data_dims[1] - 1

data_attrs = Array(Float64, data_entr_count, data_attr_count)
data_class = Array(String, data_entr_count)

for i in 1:data_entr_count
	data_class[i] = chomp(data[i + 1, data_attr_count + 1])
end

for i in 1:data_entr_count, j in 1:data_attr_count
	data_attrs[i, j] = float64(data[i + 1, j])
end

data_class_map = unique(data_class)

guaranteed_entrs = div(data_entr_count, cross_folds)
extra_entrs = mod(data_entr_count, cross_folds)

data_fold_attrs = Array(Any, cross_folds)
data_fold_class = Array(Any, cross_folds)
for i in 1:cross_folds
	if extra_entrs > 0
		extra_entrs -= 1
		data_fold_attrs[i] = Array(Float64, guaranteed_entrs + 1, data_attr_count)
		data_fold_class[i] = Array(String, guaranteed_entrs + 1)
	else
		data_fold_attrs[i] = Array(Float64, guaranteed_entrs, data_attr_count)
		data_fold_class[i] = Array(String, guaranteed_entrs)
	end
	for j in 1:length(data_fold_class[i])
		roll = mod(rand(Int), size(data_attrs)[1]) + 1
		for k in 1:data_attr_count
			data_fold_attrs[i][j, k] = data_attrs[roll, k]
		end
		data_fold_class[i][j] = data_class[roll]
		tmp_attrs = data_attrs
		tmp_class = data_class
		data_attrs = Array(Float64, size(data_attrs)[1] - 1, size(data_attrs)[2])
		data_class = Array(String, length(data_class) - 1)
		counter = 1
		for k in 1:length(tmp_class)
			if roll != k
				for l in 1:data_attr_count
					data_attrs[counter, l] = tmp_attrs[k, l]
				end
				data_class[counter] = tmp_class[k]
				counter += 1
			end
		end
	end
end

threads = Array(Any,cross_folds)

println("Prepped")
println("Spawning...")
for i in 1:cross_folds
	test_data_attrs = data_fold_attrs[i]
	test_data_class = data_fold_class[i]
	training_data_attrs = Array(Float64, 0, data_attr_count)
	training_data_class = Array(String, 0)
	for j in 1:cross_folds
		if j != i
			training_data_attrs = vcat(training_data_attrs, data_fold_attrs[j])
			training_data_class = vcat(training_data_class, data_fold_class[j])
		end
	end
	threads[i] = @spawn run(data_class_map, training_data_attrs, training_data_class, test_data_attrs, test_data_class, mut_odds, ensemble_size, population_size, tree_depth, min_growth, min_growth_iters, size_of_elite)
end

println("Spawned")
println("Fetching...")

results = Array(Any,cross_folds)

for i in 1:cross_folds
	results[i] = fetch(threads[i])
end

println("Fetched")
println("Storing")

output_string = string("File name: ", data_file, "\n\nMutation odds: ", mut_odds, "\nEnsemble size: ", ensemble_size, "\nPopulation size: ", population_size, "\nTree depth: ", tree_depth, "\nMinimal growth: ", min_growth, "\nMinimal growth iterations: ", min_growth_iters, "\nNumber of folds: ", cross_folds, "\nSize of elite: ", size_of_elite, "\n\n")
sum = 0
for i in 1:cross_folds
	for j in 1:ensemble_size
		output_string = string(output_string, "#", j, ":\n", pretty_print_chromosome(results[i]["ensemble"][j], tree_depth, data_class_map), "\n")
	end
	output_string = string(output_string, "\n")
	for j in 1:length(data_class_map)
		output_string = string(output_string, data_class_map[j], "\t")
	end
	output_string = string(output_string, "<- classified as\n")
	for j in 1:length(data_class_map)
		for k in 1:length(data_class_map)
			output_string = string(output_string, results[i]["classified_as"][k, j], "\t")
		end
		output_string = string(output_string, data_class_map[j], "\n")
	end
	output_string = string(output_string, "precision: ", results[i]["percentage"], "\ngenerations: ", results[i]["iters"], "\n\n")
	sum += results[i]["percentage"]
end
output_string = string(output_string, "average: ", (sum / cross_folds))

println("Stored")
println("Done")
toc()

tmp_name = "tmp_file"
tmp_file = open(tmp_name, "w")
log_name = string("tmp\\", integer(time()))
log_file = open(log_name, "w")

print(tmp_file, output_string)
print(log_file, output_string)
close(tmp_file)
close(log_file)