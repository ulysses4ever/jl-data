
function set_default(dictionary, key, default)
  dict = dictionary
  if !haskey(dict, key)
    dict[key] = default
  end
  return dict
end

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

function load_training_set(path, comment_field, class_field, data_fields, delimiter, strip_chars=[], header=false)
  training_vector = (ASCIIString, Array, ASCIIString)[]
  training_file = open(path)

  try
    i = 0
    for line in eachline(training_file)
      if !header || i > 0 
        fields = split(line, delimiter)
        comment = strip(strip(fields[comment_field]), strip_chars)
        class = strip(strip(fields[class_field]), strip_chars)
        data = ASCIIString[]
        for data_field in data_fields
          push!(data, strip(strip(fields[data_field]), strip_chars))
        end
        push!(training_vector, (class, data, comment))
      end
      i += 1
    end
  finally
    close(training_file)
  end

  return training_vector
end
