# https://projecteuler.net/problem=9

print("Problem 9: ")

function problem9()
  for a = 1:998
    for b = (a+1):999
      for c = (b+1):1000
        a + b + c == 1000 && isPythagoreanTriplet(a,b,c) && return a*b*c
      end
    end
  end
end

function isPythagoreanTriplet(a,b,c)
  a < b && b < c && a^2 + b^2 == c^2 && return true
  return false
end


println(problem9())