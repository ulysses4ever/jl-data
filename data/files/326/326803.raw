using MyNumerical
using PyPlot

function _dxdt(t, x, q, g, omD)
    th, om = x # theta, omega
    dth = om
    dom = -1.0/q * om - sin(th) +  g * cos(omD * t)
    return [dth, dom]
end


range_pi(x) = (x % 2pi)

global t0 = 0.0
global x0 = [0.1, 1.0]
global max_t = 120.0
global dt = 0.001

dxdt(q, g, omD) = (t,x) -> _dxdt(t, x, q, g, omD)

pygui(true)
res = tx_list(make_result(max_t, dt, t0, x0, dxdt(1./10, 1.0, 2./3.), rk), 3)

myplot(res[1, 1:end], res[2, 1:end])
myplot(res[1, 1:end], res[3, 1:end])

title("q=1.0/10, g=0.5, \$\\omega_D\$=2.0/3.0", fontname="Inconsolata")
xlabel("\$\\theta\$")
ylabel("\$\\omega\$")
myplot(res[2, 1:end], res[3, 1:end])

# Energy
Ex(x, p) = (x.^2 ) ./ 2
Ep(x, p) = (p.^2 ) ./ 2
Energy_x = Ex(res[2, 1:end], res[3, 1:end])
Energy_p = Ep(res[2, 1:end], res[3, 1:end])
Energy = (Energy_x + Energy_p) / 2.0
yscale("log")
myplot(res[1, 1:end], Energy_x)
myplot(res[1, 1:end], Energy_p)
myplot(res[1, 1:end], Energy)


# phase space
n = max_t / dt
start = n * 9. / 10.
myplot(res[2, 1:end-1], res[3, 1:end-1])

xlim(-pi, pi); myplot(range_pi(res[2, start:end-1]), res[3, start:end-1])

