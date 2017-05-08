# Considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
function EvenFibToFourMillion()
  a::Int64 = 1 # N-1
  b::Int64 = 1 # N2
  t::Int64 = 0 # Total
  ans::Int64 = 0  # Sum of all even terms
  while a < 4000000 # Ensure the terms never exceed 4 Million
    a = t
    t = a + b
    b = a
    ans += a % 2 == 0 ? a : 0
  end
  return ans
end

println("The sum of all even terms is: $(EvenFibToFourMillion())")
