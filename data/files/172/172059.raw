
include("utility.jl")

function naive_bayes_classify(features, bayes_prior, bayes_cond)
  class_probabilities = Dict()
  for (class, feature_dict) in bayes_cond
    cond_probability = bayes_prior[class]
    for (index, feature) in enumerate(features)
      cond_probability *= feature_dict[index][feature]
    end
    class_probabilities[class] = cond_probability
  end
  return reduce((x, y) -> x[2] > y[2] ? x : y, class_probabilities)
end

function naive_bayes_classify_gaussian(features, means, stds, bayes_prior)
  class_probabilities = Dict()
  for (class, feature_dict) in means
    probability = 1
    for (index, feature) in enumerate(features)
      probability *= gaussian_density(feature_dict[index], stds[class][index], feature)
    end
    class_probabilities[class] = probability
  end
  return reduce((x, y) -> x[2] > y[2] ? x : y, class_probabilities)
end

function gaussian_density(mean, sample_std_dev, x)
  denom = sqrt(2 * pi) * sample_std_dev
  enum = -1 * ((x - mean) ^ 2)
  edenom = 2 * (sample_std_dev ^ 2)
  return (1 / denom) * (e ^ (enum / edenom))
end
