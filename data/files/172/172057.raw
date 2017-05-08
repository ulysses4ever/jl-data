
include("utility.jl")

function naive_bayes_classify(features, bayes_prior, bayes_cond)
  class_probabilities = Dict()
  for (class, feature_dict) in bayes_cond
    cond_probability = 1
    for (index, feature) in enumerate(features)
      cond_probability *= feature_dict[index][feature]
    end
    class_probabilities[class] = cond_probability * bayes_prior[class]
  end
  return reduce((x, y) -> x[2] > y[2] ? x : y, class_probabilities)
end
