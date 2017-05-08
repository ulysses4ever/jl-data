# Problem 9
#
# A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
#
#   a^2 + b^2 = c^2
#
# For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
#
# There exists exactly one Pythagorean triplet for which a + b + c = 1000.
# Find the product abc.

istriplet(a, b, c) = a * a + b * b == c * c

product = (function()
  for a = 1:333, b = a:499
    c = 1000 - a - b
    if istriplet(a, b, c)
      return a * b * c
    end
  end
end)()

println(product)
# 31875000
