function online_mean (list)
  mu, count = 0, 0
  for n in list
    count += 1
    mu = mu + (n - mu)/count
  end
  return mu
end


vals = [ 1, 2, 3, 4, 5, 6, 10, 11, 23, 10, 40 ]

println(mean(vals))
println(online_mean(vals))