#################################################
#  This module is to get the full Jacobian
#  by forward diff method
#  Author: wangjiechao
#  Main Fuction : getJacobian
#  Input :f::Function
#         x point
#         h step size
#  Output:Jacobian matrix
#  Date: 2016.1.13
#  Version: 1.0
#################################################
function getJacoMat(f,x,h)
n=size(x,1);
m=size(f(x),1);
J=Array(Float64,m,n);
e=eye(n);
for j=1:1:n
J[:,j]=(f(x+h*e[:,j])-f(x))/h;
end
return J;
end
