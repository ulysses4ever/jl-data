function SR_bad (f,a,b,n)

h=(b-a)/n

sum=27*f(a+h)*f(b-h)/12+13*f(a+3h)*f(b-3h)/12

for i=[4:2:n-4]

  sum+=4*f(a+i*h)/3
end

for i=[5:2:n-5]

  sum+=2*f(a+i*h)/3
end

approx=h*sum
return approx
end