# Problem data.
n = 3
m = 2
T = 10
A = [1.003 0 -0.008;
     0.005 .997 0;
     0 0.005 1.002]
B = [1 0;
     4 5;
     6 2]

# Construct controllability matrix.
C = zeros(n, (T-1)*m)
for t=1:T-1
    C[1:end,(t-1)*m+1:t*m] = A^(t-1)*B
end

K_1 = # Your code here.

# Simulate the system.
T = 100
x1 = # Your code here.
x = zeros(n, T)
x[:,1] = x1
x_reg = copy(x)
for t=1:T-1
    x[:,t+1] = A*x[:,t]
    x_reg[:,t+1] = A*x_reg[:,t] + B*K_1*x_reg[:,t]
end

# Plot the result without regulation.
using Gadfly
set_default_plot_size(15cm, 6cm)
p1 = Gadfly.plot([layer(y=x[i,:]', x=[1:T], Geom.line,
                     Theme(default_color=color(["red" "blue" "green"][i%3+1]))) for i in 1:n]...,
                     Guide.XLabel("t"),
                     Guide.YLabel("xi"),
                     Guide.title("xi versus t without regulation"))

# Plot the result with regulation.
p2 = Gadfly.plot([layer(y=x_reg[i,:]', x=[1:T], Geom.line,
                     Theme(default_color=color(["red" "blue" "green"][i%3+1]))) for i in 1:n]...,
                     Guide.XLabel("t"),
                     Guide.YLabel("xi"),
                     Guide.title("xi versus t with regulation"))
display(p1)
display(p2)
