
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

function naive_bayes_classify_document(document_path, classes, vocab, prob, totals)
  results = Dict()
  for class in classes
    results[class] = 0
  end

  file = open(document_path)
  for line in eachline(file)
    if is_valid_ascii(line)
      tokens = map(lowercase, map(token -> strip(token, ['\'', '"', '.', ',', '?', ':', '-']), split(line)))
      for token in tokens
        if token in keys(vocab)
          for class in classes
            results[class] += log(prob[class][token])
          end
        end
      end
    end
  end 

  return reduce((item1, item2) -> item1[2] > item2[2] ? item1 : item2, results)[1]
end

function classify_documents(test_dir, training_dir, stop_words_list)
  (classes, vocab, prob, totals) = load_corpus(training_dir, stop_words_list)

  correct = 0
  total = 0
  test_classes = filter(x -> isdir(string(test_dir, x)), readdir(test_dir))
  for class in test_classes
    class_path = string(test_dir, class, '/')
    class_documents = filter(file_name -> isfile(string(class_path, file_name)), readdir(class_path))
    for document in class_documents
      result = naive_bayes_classify_document(string(class_path, document), classes, vocab, prob, totals)
      if (result == class)
        correct += 1
      end
      total += 1
    end
  end
  return (correct / total) * 100
end

function gaussian_density(mean, sample_std_dev, x)
  denom = sqrt(2 * pi) * sample_std_dev
  enum = -1 * ((x - mean) ^ 2)
  edenom = 2 * (sample_std_dev ^ 2)
  return (1 / denom) * (e ^ (enum / edenom))
end
