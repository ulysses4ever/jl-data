using LinearLeastSquares
# Problem data.
m = 5;
T = 200;
h = 0.1;
eta = 0.05;
A = [1 0 h 0;
     0 1 0 h;
     0 0 1-((eta*h)/m) 0;
     0 0 0 1-((eta*h)/m)];
B = [0 0;
     0 0;
     h/m 0;
     0 h];
C = [1 0 0 0;
     0 1 0 0]

# Starting conditions.
x_start = [0, 0, -5, 0]
z_start = [10, 10, 0, -5]

x = Variable(4, T)
u = Variable(2, T-1)
z = Variable(4, T)
v = Variable(2, T-1)
lambda_vals = [0.1 1 10]
using Gadfly
set_default_plot_size(15cm, 10cm)
plot_list = {}
for idx=1:length(lambda_vals)
    lambda = lambda_vals[idx]
    # Your code here.


    # Plot the vehicle trajectories.
    x_layer = layer(x=evaluate(C*x)[1,:]', y=evaluate(C*x)[2,:]', Geom.point,
                    Theme(default_color=color("red")))
    z_layer = layer(x=evaluate(C*z)[1,:]', y=evaluate(C*z)[2,:]', Geom.line,
                    Theme(default_color=color("blue")))
    p = Gadfly.plot(x_layer, z_layer,
                     Guide.XLabel("p1"),
                     Guide.YLabel("p2"),
                     Guide.title("Vehicle trajectories for lamdba=$lambda"))
    display(p)
end
