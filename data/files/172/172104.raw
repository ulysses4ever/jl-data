
include("utility.jl")

function load_training_set(path, class_field, data_fields, delimiter, header=false, format=(ASCIIString, Array{Float64}))
  training_vector = format[]
  training_file = open(path)

  try
    i = 0
    for line in eachline(training_file)
      if !header || i > 0 
        fields = split(line, delimiter)
        class = strip(fields[class_field])
        data = Float64[]
        for data_field in data_fields
          push!(data, float(strip(fields[data_field])))
        end
        push!(training_vector, (class, data))
      end
      i += 1
    end
  finally
    close(training_file)
  end

  return training_vector
end

function load_training_bayes(path, class_field, cat_data_fields, num_data_fields, delimiter, header=false)
  total = 0
  prior_dict = Dict()
  cond_dict = Dict()
  mean_dict = Dict()
  std_dict = Dict()
  count_dict = Dict()
  num_val_dict = Dict()
  training_file = open(path)

  try
    for line in eachline(training_file)
      if !header || i > 0
        fields = split(line, delimiter)
        class = strip(fields[class_field])
        set_default(prior_dict, class, 0)
        set_default(cond_dict, class, Dict());
        set_default(mean_dict, class, Dict());
        set_default(std_dict, class, Dict());
        set_default(count_dict, class, Dict());
        set_default(num_val_dict, class, Dict());
        for (index, data_field) in enumerate(cat_data_fields)
          cleaned_field = strip(fields[data_field])
          set_default(cond_dict[class], index, Dict())
          set_default(cond_dict[class][index], cleaned_field, 0)
          cond_dict[class][index][cleaned_field] += 1
        end
        for data_field in num_data_fields
          set_default(count_dict[class], data_field, 0);
          set_default(num_val_dict[class], data_field, Float64[]);
          count_dict[class][data_field] += 1
          push!(num_val_dict[class][data_field], float(fields[data_field]))
        end
        prior_dict[class] += 1
        total += 1
      end
    end
  finally
    close(training_file)
  end

  # Calculate conditional probabilities
  for (class, class_dict) in cond_dict
    for (feature, feature_dict) in class_dict
      for (feature_type, count) in feature_dict
        cond_dict[class][feature][feature_type] = count / prior_dict[class]
      end
    end
  end

  # Calculate prior for each class
  for (class, count) in prior_dict
    prior_dict[class] = count / total;
  end

  # Calculate means and stds for each class
  for (class, class_dict) in num_val_dict
    set_default(mean_dict, class, Dict())
    for (feature, feature_vec) in class_dict
      set_default(mean_dict[class], feature, mean(feature_vec))
      set_default(std_dict[class], feature, std(feature_vec))
    end
  end

  return (prior_dict, cond_dict, mean_dict, std_dict)
end

function load_corpus(path, stopwordlist)
  stop_words = Dict()
  vocab = Dict()
  prob = Dict()
  totals = Dict()
  
  # Load stop word list
  stop_word_file = open(stopwordlist)
  try
    for line in eachline(stopwordlist)
      stop_words[strip(line)] = 1
    end
  finally
    close(stop_word_file)
  end

  classes = filter(x -> isdir(string(path, x)), readdir(path))
  for class in classes
    (prob[class], totals[class]) = corpus_train(path, class)
  end
end

function corpus_train(path, class)
  
end

function split_data_by_class(training_set, format=(Array{Float64}))
  class_dict = Dict()
  for (class, data) in training_set
    set_default(class_dict, class, format[])
    push!(class_dict[class], data)
  end
  return class_dict
end

function normalize_column(column_number, training_set)
  column_vector = Float64[float(td[2][column_number]) for td in training_set]
  normalized_column = Float64[]
  column_median = median(column_vector)
  column_std = absolute_standard_deviation(column_vector)
  for value in column_vector
    push!(normalized_column, (value - column_median) / column_std) 
  end
  return normalized_column, (column_median, column_std)
end

function normalize_training_set(training_set)
  normalized_training_set = deepcopy(training_set)
  normalized_columns = Array{Float64}[]
  data_length = length(training_set[1][2])

  for i in 1:data_length
    normalized_column, column_mean_std = normalize_column(i, training_set)
    push!(normalized_columns, normalized_column)
  end

  for i in 1:length(normalized_training_set)
    for j in 1:length(normalized_training_set[i][2])
      normalized_training_set[i][2][j] = normalized_columns[j][i]
    end
  end

  return normalized_training_set
end

function n_fold(number_of_chunks, training_set, format=Array{(ASCIIString, Array{Float64})})
  split_data = format[]
  chunk_size = length(training_set) / number_of_chunks
  training_dict = split_data_by_class(training_set)
  classes = collect(keys(training_dict))

  i = 0
  j = 1
  push!(split_data, (ASCIIString, Array{Float64})[])
  while i != -1
    if length(filter(x -> !isempty(x), collect(values(training_dict)))) == 0
      i = -1
    else
      current_class  = classes[(i % length(classes)) + 1]
      if !isempty(training_dict[current_class])
        data = pop!(training_dict[current_class])
        if length(split_data[j]) >= chunk_size
          push!(split_data, (ASCIIString, Array{Float64})[])
          j += 1
        end
        push!(split_data[j], (current_class, data)) 
      end
      i += 1
    end
  end

  return split_data
end

