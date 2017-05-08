function addLargeNumbers(a,b)
  a = reverse(a)
  b = reverse(b)
  result = ""
  carry = 0
  i = 1
  while carry != 0 || i <= max(length(a), length(b))
    digit, carry = addDigit(a,b,i,carry)
    result = string(digit, result)
    i += 1
  end
  return result
end

function addDigit(a,b,i,carry)
  aInt = (length(a) >= i ? parseint(a[i]) : 0)
  bInt = (length(b) >= i ? parseint(b[i]) : 0)
  result = aInt + bInt + carry
  return string(int(result%10)), int(floor(result/10))
end