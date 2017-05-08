#=
  Soma os múltiplos de x ou y até z.
=#
function sumMultiplesOfXOrYBelowZ(x, y, z)
  sum = 0
  for i in [1:z]
    if (i % x == 0) || (i % y == 0)
      sum += i
    end
  end
  return sum
end

value = sumMultiplesOfXOrYBelowZ(3, 5, 1000)

println("$value")

