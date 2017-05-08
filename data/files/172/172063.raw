
function set_default(dictionary, key, default)
  dict = dictionary
  if !haskey(dict, key)
    dict[key] = default
  end
  return dict
end

function absolute_standard_deviation(vector)
  sum = 0
  med = median(vector)
  for value in vector
    sum += abs(value - med)
  end
  return sum / length(vector)
end

function manhattan(vector1, vector2)
  return sum(abs(vector1 - vector2)) 
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

function distance_lt(data1, data2)
  return data1[1] < data2[1]
end

function minimum_of_data(data, k=1)
  sorted = sort(data)
  return slice(sorted, 1:k)
end
