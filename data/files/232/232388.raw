##### 1.3.1

array1=(1,2,3,4,5)
array2=(1,2,3,4,5)
function inner_product(a,b)
  product=0;
  for (a1,a2) in zip(array1,array2)
    product=product+a1*a2;
  end
  return product;
end

inner_product(array1,array2)

num_eve=sum([(i+1)%2 for i in 0:99])

pairs=((2,5),(4,2),(9,8,),(12,10))
sum([(x%2==0)&&(y%2==0) for (x,y) in pairs])
sum([(x%2==0)&&(y%2==0) for (x,y) in pairs])


##### 1.3.2
function p(x,coeffs)
  sums=0;
  for (i, coeff) in enumerate(coeffs)
      sums = sums+coeff*x^(i-1)
  end
  return sums;
end
x=2
coeffs=(1,2,3)
p(x,coeffs)

##### 1.3.3
function f(string)
  count = 0
  for letter in string
    if (letter == uppercase(letter)) & isalpha(letter)
      count += 1
    end
  end
  return count
end

f("The Rain in Spain")


function linapprox(f, a, b, n, x)
    #=
    Evaluates the piecewise linear interpolant of f at x on the interval
    [a, b], with n evenly spaced grid points.

    =#
    length_of_interval = b - a
    num_subintervals = n - 1
    step = length_of_interval / num_subintervals

    # === find first grid point larger than x === #
    point = a
    while point <= x
        point += step
    end

    # === x must lie between the gridpoints (point - step) and point === #
    u, v = point - step, point

    return f(u) + (x - u) * (f(v) - f(u)) / (v - u)
end

f(x) = x^2
g(x) = linapprox(f, -1, 1, 3, x)