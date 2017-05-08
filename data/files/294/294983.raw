export mid_point

function mid_point (f,a,b,n)
h=(b-a)/n
sum=f(a+h/2)

for i=[1:n-1]
  sum+=f(a+h/2+i*h)
end

approx=h*sum
return approx
end
