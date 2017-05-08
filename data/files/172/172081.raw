
include("load_dataset.jl")

function normalizeRating(rating_value, min, max)
  numerator = 2*(rating_value - min) - (max - min)
  denominator = (max - min)
  return numerator / denominator
end

function denormalizeRating(rating_value, min, max)
  return 0.5*((rating_value + 1)*(max - min)) + min
end

function computeSimilarity(item1, item2, rating_dict)
  averages = Dict()
  for (user, user_ratings) in rating_dict
    averages[user] = mean(map(x -> float(x), values(user_ratings)))
  end

  numerator = 0
  denominator1 = 0
  denominator2 = 0

  for (user, user_ratings) in rating_dict
    if haskey(user_ratings, item1) && haskey(user_ratings, item2)
      average = averages[user]
      numerator += (float(user_ratings[item1]) - average) * (float(user_ratings[item2]) - average)
      denominator1 += (float(user_ratings[item1]) - average)^2
      denominator2 += (float(user_ratings[item2]) - average)^2
    end
  end

  return numerator / (sqrt(denominator1) * sqrt(denominator2))
end

function adjusted_cosine_similarity(user, item, rating_dict)
  normalizeFn = rating -> normalizeRating(rating, 1, 5)
  denormalizeFn = rating -> denormalizeRating(rating, 1, 5)
  numerator = 0
  denominator = 0
  for (other_item, other_rating) in rating_dict[user]
    similarity = computeSimilarity(item, other_item, rating_dict)
    numerator += similarity*normalizeFn(float(other_rating))
    denominator += abs(similarity)
  end
  return denormalizeFn(numerator / denominator)
end
