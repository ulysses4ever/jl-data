# Find the largest palindrome made from the product of two 3-digit numbers.
function _isNumericPalindrome(n::Int64)

  s = string(n) # Convert the integer to a string
  l = length(s) # Length of the string

  # Middle of string, where both pointers should stop. If the length is not even then stop midway
  m::Int64 = l % 2 == 0 ? div(l,2) : div(l,2) + 1
  b::Int64 = 1 # Begining of string
  e::Int64 = l # End of string
  p::Bool = true # Palindrome

  while b <= m && e > m && p
    p = isequal(s[b],s[e])
    if (p) b += 1; e -= 1 end
  end
  return p
end

a = Int64[]

# 111 -> 999 O(n^2)
for x in [111:999]
  for y in [111:999]
    if _isNumericPalindrome(x*y)
      push!(a,x*y)
    end
  end
end

ans = maximum(a)
