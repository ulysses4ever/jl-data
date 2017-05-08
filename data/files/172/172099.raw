
include("utility.jl")

function load_ratings(path, user_id_field, item_id_field, rating_field, delimiter, strip_chars=[])
  ratings_dict = Dict()
  ratings_file = open(path)

  try
    for line in eachline(ratings_file)
      fields = split(line, delimiter)
      user_id = strip(strip(fields[user_id_field]), strip_chars)
      item_id = strip(strip(fields[item_id_field]), strip_chars)
      rating = strip(strip(fields[rating_field]), strip_chars)

      set_default(ratings_dict, user_id, Dict())
      ratings_dict[user_id][item_id] = rating
    end
  finally
    close(ratings_file)
  end

  return ratings_dict
end

function load_users(path, user_id_field, user_name_field, delimiter, strip_chars=[])
  users_dict = Dict()
  users_file = open(path)

  try
    for line in eachline(users_file)
      fields = split(line, delimiter)
      user_id = strip(strip(fields[user_id_field]), strip_chars)
      user_name = strip(strip(fields[user_name_field]), strip_chars)

      set_default(users_dict, user_id, Dict())
      users_dict[user_id] = user_name
    end
  finally
    close(users_file)
  end

  return users_dict
end

function load_items(path, item_id_field, item_name_field, delimiter, strip_chars=[])
  items_dict = Dict()
  items_file = open(path)

  try
    for line in eachline(items_file)
      fields = split(line, delimiter)
      item_id = strip(strip(fields[item_id_field]), strip_chars)
      item_name = strip(strip(fields[item_name_field]), strip_chars)

      set_default(items_dict, item_id, Dict())
      items_dict[item_id] = item_name
    end
  finally
    close(items_file)
  end

  return items_dict
end

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

function normalize_vector(vector, training_set)
  normalized_vector = Float64[]
  for i in 1:length(vector)
    normalized_column, column_mean_std = normalize_column(i, training_set)
    push!(normalized_vector, (vector[i] - column_mean_std[1]) / column_mean_std[2])
  end
  return normalized_vector
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

