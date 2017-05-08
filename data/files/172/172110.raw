
ratings = ["Amy" =>
             ["Taylor Swift" => 4,
              "PSY" => 3,
              "Whitney Houston" => 4],
           "Ben" =>
             ["Taylor Swift" => 5,
              "PSY" => 2],
           "Clara" =>
             ["PSY" => 3.5,
              "Whitney Houston" => 4],
           "Daisy" =>
             ["Taylor Swift" => 5,
              "Whitney Houston" => 3]]

function set_default(dictionary, key, default)
  dict = dictionary
  if !haskey(dict, key)
    dict[key] = default
  end
  return dict
end

function lt(first_item, second_item)
  return first_item[2] < second_item[2]
end

function compute_deviations(rating_dict)
  deviations = Dict()
  frequencies = Dict()

  for (user, ratings) in rating_dict
    for (item, rating) in ratings
      frequencies = set_default(frequencies, item, Dict())
      deviations = set_default(deviations, item, Dict()) 
      for (item2, rating2) in ratings
        if item != item2
          frequencies[item] = set_default(frequencies[item], item2, 0)
          deviations[item] = set_default(deviations[item], item2, 0.0)
          frequencies[item][item2] += 1
          deviations[item][item2] += rating - rating2
        end
      end
    end
  end

  for (item, ratings) in deviations
    for (item2, rating) in ratings
      ratings[item2] /= frequencies[item][item2]
    end
  end

  return frequencies, deviations
end

function slope_one_recommend(user_ratings, frequencies, deviations)
  recommendations = Dict()
  recs = (ASCIIString, Float64)[]
  freqs = Dict()

  for (user_item, user_rating) in user_ratings
    for (other_item, other_ratings) in deviations
      if !haskey(user_ratings, other_item) && haskey(deviations[other_item], user_item)
        freq = frequencies[other_item][user_item]
        set_default(recommendations, other_item, 0.0)
        set_default(freqs, other_item, 0)
        recommendations[other_item] += (other_ratings[user_item] + user_rating) * freq
        freqs[other_item] += freq
      end
    end
  end

  for (key, value) in recommendations
    push!(recs, (key, value / freqs[key]))
  end

  sort(recs, lt=lt, rev=true)
  return recs
end

function exec(user)
  println("Computing deviations...")
  tic()
  frequencies, deviations = compute_deviations(ratings)
  toc()

  @printf "Gathering Slope One recommendations for %s...\n" user
  tic()
  recommendations = slope_one_recommend(ratings[user], frequencies, deviations)
  toc()

  @printf "\n Recommendation:\n %s\n" recommendations
end
