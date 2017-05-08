
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

function prob_density_function(mean, sample_std_dev, x)
  denom = sqrt(2 * pi) * sample_std_dev
  enum = -1 * ((x - mean) ^ 2)
  edenom = 2 * (sample_std_dev ^ 2)
  return (1 / denom) * (e ^ (enum / edenom))
end
