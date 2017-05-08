# Gaussian Process Regression in Julia

include("GP/GP.jl")

# Add Gadfly plotting package in case it's not installed
Pkg.add("Gadfly")

# import GP and Gadfly
using GP
using Gadfly

# The function that we need to predict
function f(x)
	return x .* sin(x)
end

###
# Noise-free Data
##

X = [1., 3., 5., 6., 7., 8.]

# Observations
y = f(X)

x = linspace(0, 10, 1000)

# Create the Gaussian Process Model and Predict the values using the model
se = SquaredExponential(.75)
gp = GaussianProcess(0., se)
gpp = gppredict(gp, X, y, x)

# Predicted Values
y_pred = gpp.mean


# Generate the figures
draw(SVG("./noiseless-output.svg", 6inch, 6inch),
	plot(
		layer(y=y, x=X, Geom.point, Theme(default_color=color("purple"))),
		layer(y=f(x), x=x, Geom.line, Theme(default_color=color("purple"))),
		layer(y=y_pred, x=x, ymax=y_pred + (1.96*gpp.sd), ymin=y_pred - (1.96*gpp.sd), Geom.line, Geom.ribbon),
		layer(y=y_pred, x=x, Geom.line),
	)
)

###
# Noisy Data
###
X2 = linspace(0.1, 9.9, 20)

# Observations and noise
y2 = f(X2)

# using Mersenne Twister Random Number Generator
rng = MersenneTwister(-54321)
dy = 0.5 + 1.0 * rand(rng, size(y2))
y2 += dy

x2 = linspace(0, 10, 1000)

# Create the Gaussian Process Model and Predict the values using the model
se2 = SquaredExponential(0.9)
gp2 = GaussianProcess(.75, se2)
gpp2 = gppredict(gp2, X2, y2, x2)

# Predicted Values
y_pred2 = gpp2.mean

draw(SVG("./noisy-output.svg", 6inch, 6inch),
	plot(
		layer(y=y2, x=X2, Geom.point, Theme(default_color=color("purple"))),
		layer(y=y2, x=X2, ymax=y2+dy, ymin=y2-dy, Geom.errorbar, Theme(default_color=color("purple"))),
		layer(y=f(x2), x=x2, Geom.line, Theme(default_color=color("purple"))),
		layer(y=y_pred2, x=x2, ymax=y_pred2 + (1.96*gpp2.sd), ymin=y_pred2 - (1.96*gpp2.sd), Geom.line, Geom.ribbon),
		layer(y=y_pred2, x=x2, Geom.line)
	)
)


