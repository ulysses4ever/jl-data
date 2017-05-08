
users = ["David" =>
           ["Imagine Dragons" => 3,
            "Daft Punk" => 5,
            "Lorde" => 4,
            "Fall Out Boy" => 1],
         "Matt" =>
           ["Imagine Dragons" => 3,
            "Daft Punk" => 4,
            "Lorde" => 4,
            "Fall Out Boy" => 1],
         "Ben" =>
           ["Kacey Musgraves" => 4,
            "Imagine Dragons" => 3,
            "Lorde" => 3,
            "Fall Out Boy" => 1],
         "Chris" =>
           ["Kacey Musgraves" => 4,
            "Imagine Dragons" => 4,
            "Daft Punk" => 4,
            "Lorde" => 3,
            "Fall Out Boy" => 1],
         "Tori" =>
           ["Kacey Musgraves" => 5,
            "Imagine Dragons" => 4,
            "Daft Punk" => 5,
            "Fall Out Boy" => 3]]

function normalizeRating(rating_value, min, max)
  numerator = 2*(rating_value - min) - (max - min)
  denominator = (max - min)
  return numerator / denominator
end

function denormalizeRating(rating_value, min, max)
  return 0.5*((rating_value + 1)*(max - min)) + min
end

function computeSimilarity(band1, band2, userRatings)
  averages = Dict()
  for key in userRatings
    averages[key[1]] = mean(values(userRatings[key[1]]))
  end

  numerator = 0
  denominator1 = 0
  denominator2 = 0

  for key in userRatings
    if haskey(key[2], band1) && haskey(key[2], band2)
      average = averages[key[1]]
      numerator += (key[2][band1] - average) * (key[2][band2] - average)
      denominator1 += (key[2][band1] - average)^2
      denominator2 += (key[2][band2] - average)^2
    end
  end

  return numerator / (sqrt(denominator1) * sqrt(denominator2))
end

function predict_user_rating(user, band, userRatings)
  normalizeFn = rating -> normalizeRating(rating, 1, 5)
  numerator = 0
  denominator = 0
  for rating in userRatings[user]
    similarity = computeSimilarity(band, rating[1], userRatings)
    numerator += similarity*normalizeFn(float(rating[2]))
    denominator += abs(similarity)
  end
  return numerator / denominator
end
