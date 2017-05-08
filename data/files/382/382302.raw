using MyNumerical
using PyPlot

dxdt3(t, x) = [x[2], -x[1]]

global t0 = 0.0
global x0 = [0.0, 1.0]
global max_t = 120.0
global dt = 0.001

# harmonic oscillator

res = tx_list(make_result(max_t, dt, t0, x0, dxdt3, rk), 3)
myplot(res[1, 1:end], res[2, 1:end])
myplot(res[1, 1:end], res[3, 1:end])

Ex(res) = (res[2, 1:end].^2 )
Ep(res) = (res[3, 1:end].^2 )
Energy_x = Ex(res)
Energy_p = Ep(res)
Energy = (Energy_x + Energy_p) ./ 2.0
myplot(res[1, 1:end], Energy[1, 1:end])
