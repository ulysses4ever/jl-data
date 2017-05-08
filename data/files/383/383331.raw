using ODE
using Winston
function f(t, y)
	mu = 2.5
	ydot = similar(y)
	ydot[1] = y[2]
	ydot[2] = mu*(1-y[1]^2)*y[2]-y[1]
	ydot
end
t = [0:.1:10.0;]
y0 = [1.0, 3.0]
t,y=ODE.ode23s(f, y0, t)
y1 = [ a[1] for a in y] # Rearranging the output,
y2 = [ a[2] for a in y] # more convenient
plot(float(y1),float(y2))
