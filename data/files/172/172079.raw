
include("utility.jl")

function knn(data, training_set, k=3)
  nearest_neighbour_list = (Float64, (ASCIIString, Array{Float64}))[]
  for item in training_set
    push!(nearest_neighbour_list, (manhattan(data, item[2]), item)) 
  end

  neighbour_count = Dict()
  neighbours = slice(sort(nearest_neighbour_list, lt=distance_lt), 1:k)
  for (distance, neighbour) in neighbours
    set_default(neighbour_count, neighbour[1], 0)
    neighbour_count[neighbour[1]] += 1
  end

  return maximum([(x[2], x[1]) for x in neighbour_count])[2]
end

function test_dataset(training_set, test_set)
  results = (Float64, (ASCIIString, Array{Float64}))[]
  correct = 0
  total = length(test_set)
  for test in test_set
    push!(results, knn(test[2], training_set))
  end
  for (i, item) in enumerate(test_set)
    if results[i][2][1] == item[1]
      correct += 1
    end
  end
  return correct/total * 100
end

function test_fold(fold, split_data, k=3)
  results = Dict()
  temp_folds = deepcopy(split_data)
  splice!(temp_folds, fold)
  training_folds = (ASCIIString, Array{Float64})[];

  for temp_fold in temp_folds
    for data in temp_fold
      push!(training_folds, data)
    end
  end

  for (real_class, data) in split_data[fold]
    classified_class = knn(data, training_folds, k)
    set_default(results, real_class, Dict())
    set_default(results[real_class], classified_class, 0)
    results[real_class][classified_class] += 1
  end

  return results
end

function test_n_folds(number_of_folds, training_set, k=3)
  results = Dict()
  split_data = n_fold(number_of_folds, training_set)
  for i in 1:number_of_folds
    test = test_fold(i, split_data, k)
    for (real_class, predictions) in test
      set_default(results, real_class, Dict())
      for (predicted_class, count) in predictions
        set_default(results[real_class], predicted_class, 0)
        results[real_class][predicted_class] += count
      end
    end
  end
  return results
end

function pretty_results(results)
  for (real_class, predictions) in results
    @printf "Prediction counts for %s:\n" real_class
    for (predicted_class, count) in predictions
      @printf "\t%s => %s\n" predicted_class count
    end
  end
end
