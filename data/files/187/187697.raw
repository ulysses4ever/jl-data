function divides (divisor::Integer, val::Integer)
  return mod(val, divisor) == 0
end

function gcd (a, b)
  (a, b) = a > b ? (a, b) : (b, a)
  while b != 0
    a, b = b, mod(a, b)
  end
  return a
end

m, mcount = 71, 0
n, ncount = 62, 0

for k in 2:10000
  mcount += divides(m, k) ? 1 : 0
  ncount += divides(n, k) ? 1 : 0
end

d = gcd(mcount, ncount)

println(mcount/d, '/', ncount/d, '=', mcount/ncount)
println(n, '/', m, '=', n/m)