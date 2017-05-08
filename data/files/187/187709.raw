module series

function geometric (r)
  n = 0
  sum = 0
  while true
    val = (r)^n
    sum += val
    n += 1
    if val < 0.000000000000000001 break end
  end
  return sum, (1-r)^-1
end

function other (r)
  n = 1
  sum = 0
  while true
    val = n*r^(n-1)
    sum += val
    n += 1
    if val < 0.000000000000000001 break end
  end
  return sum, (1-r)^-2
end

end

using series: geometric, other

println(geometric(1/3))
println(geometric(1/4))
println(geometric(1/5))
println("---")
println(other(1/3))
println(other(1/4))
println(other(1/5))