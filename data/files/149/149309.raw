# Project Euler Problem 4
# 4-11-14, Ben Southgate

# Question:
# Find the largest palindrome made from the product of two 3-digit numbers.

function palindrome()
  largest::Int64 = 0
  for i=999:-1:100
    for j=999:-1:100
      n::Int64 = i*j
      s = "$(n)"
      if s == reverse(s)
        largest = largest < n ? n : largest
      end
    end
  end
  return largest
end

print(palindrome())

