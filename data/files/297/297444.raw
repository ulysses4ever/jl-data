function isPrime(n)
  for i = 2:int(sqrt(n))
    n%i == 0 && return false
  end
  return true
end

function nextPrime()
  currentPrime = 1
  helper = function ()
    while true
      currentPrime += 1
      isPrime(currentPrime) && return currentPrime
    end
  end
end
