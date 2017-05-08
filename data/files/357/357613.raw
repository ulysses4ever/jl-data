# https://projecteuler.net/problem=4

print("Problem 4: ")

function problem4()
  max = 999
  min = 100
  result = []
  for i = min:max
    for j = i:max
      currentResult = i*j
      isPalindrome(currentResult) || continue

      length(result) == 0 && (result = [i, j, i*j])

      if currentResult > result[3]
        result = [i, j, i*j]
      end
    end
  end
  return result[3]
end

function isPalindrome(n)
  numDigits = 0
  while true
    n-(10^numDigits)-1 <= 0 && break
    numDigits+=1
  end

  for i = 1:(numDigits / 2)
    getIthDigit(n, i) == getIthDigit(n, numDigits - (i-1)) || return false
  end
  return true
end

function getIthDigit(n,i)
  return floor((n / (10^(i-1))) % 10)
end

println(problem4())