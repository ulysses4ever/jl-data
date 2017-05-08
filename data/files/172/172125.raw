
function loadUserRatings(path="")
  file = open(string(path, "BX-Book-Ratings.csv"))
  try
    for line in eachline(file)
      fields = split(line, ';')
      user = strip(fields[1], '\"')
      book = strip(fields[2], '\"')
      rating = strip(rstrip(fields[3]), '\"')
      current_ratings = Dict()
      if haskey(user_ratings, user)
        current_ratings = user_ratings[user]
      end
      current_ratings[book] = rating
      user_ratings[user] = current_ratings
    end
  finally
    close(file)
  end
end

function loadBooks(path="")
  file = open(string(path, "BX-Books.csv"))
  try
    for line in eachline(file)
      fields = split(line, ';')
      isbn = strip(fields[1], '\"')
      title = strip(fields[2], '\"')
      author = strip(fields[3], '\"')
      title = string(title, " by ", author)
      isbn_book_map[isbn] = title
    end
  finally
    close(file)
  end
end

function loadUsers(path="")
  file = open(string(path, "BX-Users.csv"))
  try
    for line in eachline(file)
      fields = split(line, ';')
      user_id = strip(fields[1], '\"')
      location = strip(fields[2], '\"')
      age = strip(fields[3], '\"')
      location = string(location, " (age: ", age, ")")
      userid_location_map[user_id] = location
      location_userid_map[location] = user_id
    end
  finally
    close(file)
  end
end

function manhattan(rating1, rating2)
  distance = 0
  for key in rating1
    if haskey(rating2, key[1])
      distance += abs(rating1[key[1]] - rating2[key[1]])
    end
  end
  return distance
end

function minkowski(rating1, rating2, dim)
  distance = 0
  for key in rating1
    if haskey(rating2, key[1])
      distance += abs(rating1[key[1]] - rating2[key[1]])^dim
    end
  end
  return distance^(1/dim)
end

function pearson(rating1, rating2)
  sum_xy = 0
  sum_x = 0
  sum_y = 0
  sum_x2 = 0
  sum_y2 = 0
  n = 0
  for key in rating1
    if haskey(rating2, key[1])
      n += 1
      x = float(key[2])
      y = float(rating2[key[1]])
      sum_x += x
      sum_x2 += x^2
      sum_y += y
      sum_y2 += y^2
      sum_xy += x*y
    end
  end
  numerator = (sum_xy - ((sum_x*sum_y) / n))
  denominator = sqrt(sum_x2 - ((sum_x ^ 2) / n)) * sqrt(sum_y2 - ((sum_y ^ 2) / n))
  if denominator == 0 || isnan(denominator)
    return 0
  else
    return numerator / denominator
  end
end

user_ratings = Dict()
isbn_book_map = Dict()
userid_location_map = Dict()
location_userid_map = Dict()
fn = pearson
k = 3
n = 5

function lt(first_item, second_item)
  return first_item[2] < second_item[2]
end

function computeNearestNeighbour(user_id)
  distances = (ASCIIString, Float64)[]
  for user in user_ratings
    if user_id != user[1]
      distance = fn(user_ratings[user_id], user_ratings[user[1]])
      push!(distances, (user[1], distance))
    end
  end
  return sort(distances, lt=lt, rev=true)
end

function transformRecommendations(recommendations)
  list = (ASCIIString, Float64)[]
  for pair in recommendations
    push!(list, (isbn_book_map[pair[1]], pair[2]))
  end
  return list
end

function recommend(user_id)
  recommendations = Dict()
  println("Getting nearest neighbours")
  nearest = computeNearestNeighbour(user_id)
  ratings = user_ratings[user_id]
  total_distance = 0.0
  println("Calculating total distance")
  for i in 1:k
    total_distance += nearest[i][2]
  end

  println("Calculating recommendations with weights")
  for i in 1:k
    user = nearest[i][1]
    weight = nearest[i][2] / total_distance
    neighbour_ratings = user_ratings[user]

    @printf "User: %s\n" user

    for isbn_rating in neighbour_ratings
      if !haskey(ratings, isbn_rating[1])
        if !haskey(recommendations, isbn_rating[1])
          recommendations[isbn_rating[1]] = float(neighbour_ratings[isbn_rating[1]]) * weight
        else
          recommendations[isbn_rating[1]] = recommendations[isbn_rating[1]] + (float(neighbour_ratings[isbn_rating[1]]) * weight)
        end
      end
    end
  end

  recommendations = transformRecommendations(recommendations)
  recommendations = sort(recommendations, lt=lt, rev=true)

  return recommendations[1:n]
end

function loadDataset(path="Desktop/projects/Julia/BX-Dump/")
  println("Loading Ratings")
  tic()
  loadUserRatings(path)
  println("Loading Books")
  loadBooks(path)
  println("Loading Users")
  loadUsers(path)
  toc()
end

function exec()
  tic()
  recommendations = recommend("171118")
  toc()

  @printf "%s" recommendations
end
