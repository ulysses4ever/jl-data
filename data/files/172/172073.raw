
include("utility.jl")

function nearest_neighbour(data, training_set)
  nearest_neighbour_list = (Float64, (ASCIIString, Array{Float64}))[]
  for item in training_set
    push!(nearest_neighbour_list, (manhattan(data, item[2]), item)) 
  end
  return minimum_of_data(nearest_neighbour_list)
end

function test_dataset(training_set, test_set)
  results = (Float64, (ASCIIString, Array{Float64}))[]
  correct = 0
  total = length(test_set)
  for test in test_set
    push!(results, nearest_neighbour(test[2], training_set))
  end
  for (i, item) in enumerate(test_set)
    if results[i][2][1] == item[1]
      correct += 1
    end
  end
  return correct/total * 100
end

function test_fold(fold, split_data)
  results = Dict()
  training_folds = deepcopy(split_data)
  splice!(training_folds, fold)
  for data in split_data[fold]
    real_class = data[1]
    classified = nearest_neighbour(data[2], training_folds)
    classified_class = classified[2][1]
    set_default(results, real_class, Dict())
    set_default(results[real_class], classified_class, 0)
    results[real_class][classified_class] += 1
  end
  return results
end

function test_n_folds(number_of_folds, training_set)
  results = Dict()
  split_data = n_fold(number_of_folds, training_set)
  for i in 1:number_of_folds
    
  end
end
