function sinh_tanh2(f,a,b,N)

q(t)=e^(-2sinh(t))
omg(t)=(b-a)*q(t)/(1+q(t))

h=log(2*pi*N*pi/2)/N

x(t)=(b+a+t(b-a)*tanh(sinh(t)))/2

w(t)=2*(b-a)*q(t)*cosh(t)/(1+q(t))^2

approx=f((a+b)/2)*w(0)

for j=[1:N]

  approx+=(f(a+omg(j))+f(b-omg(j)))*omg(j)
end
return h*approx
end

  