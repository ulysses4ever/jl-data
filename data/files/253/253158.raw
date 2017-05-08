Pkg.add("Gadfly")
Pkg.add("Cairo")
using Gadfly
using Cairo

t = [1.1, 1.9, 3.3, 4.0]
x = [1, 2, 3, 4]

lambda = 0.01
#=
	model => y = w0 + w1x = w' x, where x0 = 1

	Cost function = Sum (t_n - y_n)^2 = (t_n - w0 - w1 x_n)^2

	Derivation of Cost function:

	d(Cost function) / d w0 = -2 (t - w0 - w1 x)
	d(Cost function) / d w1 = -2x (t - w0 - w1 x)

	We'll use gradient descent to learn the parameters:

	w0 = w0 - sum(lambda x d(Cost function) / d w0)
	w1 = w1 - sum(lambda x d(Cost function) / d w1)

	Here the sum is over all the data

	Repeat those iterations with respect to the input until w0 and w1 don't change anymore
=#

# initial values of the bias
# dimension is (2, )
w = [1.0, 1.0]

# transform x to add the bias point
# x_bias will become: [1.0  1
#					   1.0  2] etc
# dimension is (4, 2)
x_bias = [ones(length(x)) x]

for i = 1:10000
	y = x_bias * w
	w[1] = w[1] - lambda * sum( -2 * (t - y))
	w[2] = w[2] - lambda * sum( -2 * x' * (t - y))
end

println(w)
my_plot = plot(layer(x=x, y=t, Geom.point), layer(x=x, y=x_bias * w, Geom.line))
draw(PNG("myplot.png", 6inch, 3inch), my_plot)