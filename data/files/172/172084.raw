
function set_default(dictionary, key, default)
  dict = dictionary
  if !haskey(dict, key)
    dict[key] = default
  end
  return dict
end

function load_ratings(path, user_id_field, item_id_field, rating_field, delimiter)
  ratings_dict = Dict()
  ratings_file = open(path)

  try
    for line in eachline(ratings_file)
      fields = split(line, delimiter)
      user_id = strip(fields[user_id_field])
      item_id = strip(fields[item_id_field])
      rating = strip(fields[rating_field])

      set_default(ratings_dict, user_id, Dict())
      ratings_dict[user_id][item_id] = rating
    end
  finally
    close(ratings_file)
  end

  return ratings_dict
end

function load_users(path, user_id_field, user_name_field, delimiter)
  users_dict = Dict()
  users_file = open(path)

  try
    for line in eachline(users_file)
      fields = split(line, delimiter)
      user_id = strip(fields[user_id_field])
      user_name = strip(fields[user_name_field])

      set_default(users_dict, user_id, Dict())
      users_dict[user_id] = user_name
    end
  finally
    close(users_file)
  end

  return users_dict
end

function load_items(path, item_id_field, item_name_field, delimiter)
  items_dict = Dict()
  items_file = open(path)

  try
    for line in eachline(items_file)
      fields = split(line, delimiter)
      item_id = strip(fields[item_id_field])
      item_name = strip(fields[item_name_field])

      set_default(items_dict, item_id, Dict())
      items_dict[item_id] = item_name
    end
  finally
    close(items_file)
  end

  return items_dict
end
