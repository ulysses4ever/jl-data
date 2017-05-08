function diff_1(f,x,h)
n=size(x,1);
m=size(f(x),1);
J=Array(Float64,m,n);
e=eye(n);
for j=1:1:n
J[:,j]=(f(x+h*e[:,j])-f(x))/h;
end
return J;
end
