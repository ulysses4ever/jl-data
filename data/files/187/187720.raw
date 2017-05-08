#
#
function gcd (a, b)
  (a, b) = a > b ? (a, b) : (b, a)
  while b != 0
    a, b = b, mod(a, b)
  end
  return a
end

#
#
function totient (n)
  count = 0
  for k = 1:n
    if gcd(n, k) == 1
      count += 1
    end
  end
  return count
end

# println(gcd(312, 471))

println(totient(3))
println(totient(11))