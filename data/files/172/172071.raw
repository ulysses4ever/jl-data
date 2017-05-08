
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
