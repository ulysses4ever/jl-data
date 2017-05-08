using MyNumerical
using PyPlot


# Plotting

dydx(t, x) = cos(t)

global x0 = 0.0
global y0 = 0.0
global max_x = 10.0

pygui(true)

# RK
r = 0.1 .^ [4:-1:0] # dt list
ress = [make_result(max_x, idx, x0, [y0], dydx, euler) for idx in r]
# calculate error at last x (max_x)
# sin is ecact solutoi of dydx (cos)
errors = [abs(sin(xy[end][1]) - xy[end][2]) for xy in ress]

xscale("log"); yscale("log"); scatter([r],  errors, s=10)

res = tx_list(make_result(max_x, 0.01, x0, [y0], dydx, euler), 2)
id=(1,2)
myplot(res[1, 1:end], res[2, 1:end])


# Runge Kutta
ress_rk = [make_result(max_x, idx, x0, [y0], dydx, rk) for idx in r]
errors_rk = [abs(sin(xy[end][1]) - xy[end][2]) for xy in ress_rk]
xscale("log"); yscale("log"); scatter([r],  errors_rk, s=10)

res_rk = tx_list(make_result(max_x, .001, x0, [y0], dydx, rk), 2)
plot_res(res[1, 1:end], res[2, 1:end]
