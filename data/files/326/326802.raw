using MyNumerical
using PyPlot

dxdt(t, x) = [x[2], -x[1]]
x_ex(t) = sin(t)

global t0 = 0.0
global x0 = [0.0, 1.0]
global max_t = 50.0

pygui(true)

res = tx_list(make_result(max_t, 0.1, t0, x0, dxdt, rk), 3)
myplot(res[1, 1:end], res[2, 1:end])
myplot(res[1, 1:end], res[3, 1:end])
#savefig("aaa.png")

# Phase Space
myplot(res[2, 1:end], res[3, 1:end])

# Energy
E(x, p) = (x.^2 + p.^2) ./ 2
Energy = abs(0.5 - E(res[2, 1:end], res[3, 1:end]))

xlabel("t")
ylabel("energy error")
yscale("log")
myplot(res[1,1:end], Energy)


# Comparison of errors
dts = 0.1 .^ [4:-1:1] # dt list
ress = [make_result(max_t, idt, t0, x0, dxdt, rk) for idt in dts]
errors = [abs(x_ex(txp[end][1]) - txp[end][2]) for txp in ress]
xscale("log"); yscale("log"); myplot([dts],  errors, ls=" ", marker="o", ms=5)
