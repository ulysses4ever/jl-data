2^2
2^3
2^4
2^5
2^6
2^7
2^8
2^9
2^10
2^11
2^12
2^13
2^14
2^15
2^16
BigInt(2)^1000


# https://projecteuler.net/problem=15
#doesn't work yet...

print("Problem 15: ")

function problem15()
  n = BigInt(2)^1000
  sum = 0
  while n > 0
    sum += getIthDigit(n, 1)
    n = floor(n/10)
    println(n)
  end
  return sum
end

println(problem15())


function getIthDigit(n,i)
  return floor((n / (10^(i-1))) % 10)
end