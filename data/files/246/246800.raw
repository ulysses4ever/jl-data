using Convex
using ECOS
using PyPlot

PyPlot.pygui(true)

m=100; n=30;
A=10*randn(m,n)
b=2*randn(m,1)

x1 = Variable(n)
x2 = Variable(n)
xDead = Variable(n)
xLog = Variable(n)
λ=.5

# Minimizing Least Squares with various penalties
prob1 = minimize(sum_squares(A*x1-b)+λ*norm(x1,1))
prob2 = minimize(sum_squares(A*x2-b)+λ*norm(x2,2))
probDead = minimize(sum_squares(A*xDead-b)+λ*sum(max(abs(xDead)-1,0)))
probLog = minimize(sum_squares(A*xLog-b)-λ*(sum(log(xLog+1)+log(1-xLog))))

solve!(prob1)
solve!(prob2)
solve!(probDead)
solve!(probLog)
prob1.status
prob2.status
probDead.status
probLog.status

# Plot the One norm solution
r= -.25:.1/50:.25;
plt[:hist](x1.value, 20, facecolor="w"); plot(r,  10*λ*abs(r), "k");
axis([-.25,.25,0,5]);
title(L"$\min\Vert Ax-b\Vert_2+\lambda\Vert x\Vert_1$ with $\lambda=.5$");
ylabel(L"10\lambda",fontsize=14)
xlabel(L"x", fontsize=14)
PyPlot.show()

# Plot the Two norm Solution
r= -.25:.1/50:.25;
plt[:hist](x2.value, 20, facecolor="w");
plot(r,  100*λ*r.^2, "k");
axis([-.25,.25,0,5]);
title(L"$\min\Vert Ax-b\Vert_2+\lambda\Vert x\Vert_2$ with $\lambda=.5$");
ylabel(L"100\lambda",fontsize=14)
xlabel(L"x", fontsize=14)
PyPlot.show()

# Plot the Dead Zone Solution
r= -5:.1/50:5;
plt[:hist](xDead.value, 213, facecolor="w");
plot(r,  λ*max(abs(r).-1,0), "k");
axis([-2,2,0,5]);
title(L"$\min\Vert Ax-b\Vert_2+\lambda\max\{\Vert x\Vert_1-1, 0\}$ with $\lambda=.5$");
ylabel(L"100\lambda",fontsize=14)
xlabel(L"x", fontsize=14)
PyPlot.show()

# I'm somewhat confused why this solution is so similar to zero

# Plot the Log Barrier Solution
r= -5:.1/50:5;
plt[:hist](xDead.value, 125, facecolor="w");
plot(r,  λ*max(abs(r).-1,0), "k");
axis([-2,2,0,5]);
title(L"$\min\Vert Ax-b\Vert_2+\lambda\big(\log(x$ with $\lambda=.5$");
ylabel(L"100\lambda",fontsize=14)
xlabel(L"x", fontsize=14)
PyPlot.show()
