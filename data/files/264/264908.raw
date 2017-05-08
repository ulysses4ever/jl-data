# What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
function evenDivTo20()

  x::Int64 = 0
  n::Int64 = 0
  p::Bool  = true

  while x <= 20
    x  = 2
    n += 1
    p  = true

    # While the number is divisble without remainder
    while p
      p = n % x == 0
      x += 1
    end
  end

  return n
end

ans = evenDivTo20()