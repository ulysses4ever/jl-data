# adds two numbers
sum(x,y) = x + y

# squares a number
function sqr(x)
  x ^ 2
end

# factorial
fac(n) = n > 0 ? n * fac(n - 1) : n == 0 ? 1 : error("n cannot be negative")

# factorial without recursion
function fac2(n)
  x = 1; 
  for i in 1:n
    x *= i; 
  end
  return x
end

f(x) = x^3 + 2x + 1

# calculate powers of ten
function powersOfTen(nbr)
  for n in 0:nbr
    println(10^n)
  end
end

# calculate powers of two
function powersOfTwo(nbr)
  for n in 0:nbr
    println(2^n)
  end
end

# Fibonacci numbers, x is how many numbers to generate and print
function fib(x)
  prev = 1;
  next = 1;
  println(prev)
  println(next)
  for n in 1:x-2
    tmp = next
    next = prev + next
    prev = tmp
    println(next)
  end
end

