MyNumerical
using PyPlot

function dxdt7(t, x, q, g, Ω)
    θ , ω = x
    θ_dot = ω
    ω_dot = (- 1./q * ω ) - sin( θ ) + (g * cos(Ω * t))
    [θ_dot, ω_dot]
end

function dxdt(q, g, Ω)
    return (t, x) -> dxdt7(t, x, q, g, Ω)
end


global t0 = 0.0
global x0 = [0.0, 0.0]
global max_t = 300.0
global dt = 0.01

# (1) パラメタ q=2, Ω = 2/3
# (a) g = 0.9
# (b) g = 1.07
# (c) g = 1.15
# (d) g = 1.35
# (e) g = 1.45
# (f) g = 1.47
# (g) g = 1.50

pygui(true)
q = 2
Ω = 2./3.
g_list = [0.9, 1.07, 1.15, 1.35, 1.45, 1.47, 1.50]
ress = [tx_list(make_result(max_t, dt, t0, x0, dxdt(q, g, Ω), rk), 3) for g in g_list]

x0_list = [(0.0, 0.0), (pi/4, 0.0), (pi/2, 0.0)]
ress_attractor = [[tx_list(make_result(max_t, dt, t0, x0, dxdt(q, g, Ω), rk), 3) for x0 in x0_list] for g in g_list]


xlim(-pi, pi); ylim(-5, 5)
for i in 1:length(g_list)
    myplot(ress[i][2, 1:end], ress[i][3, 1:end]) 
end


function plot_phase(i, ress)
    xlim(-pi, pi)
    zlim(0, max_t)
    zlabel("t")
    ylabel("\$\\theta\$")
    myplot3D(ress[i][2, :], ress[i][3, :], ress[i][1, :])
end

### Create Figures

ind_g = 3
for i in 1:length(x0_list)
    plot_phase(i, ress_attractor[ind_g])
end


ind_g = 4
for i in 1:length(x0_list)
    subplot(310 + i)
    myplot(ress_attractor[ind_g][i][2, 1:end], ress_attractor[ind_g][i][3, 1:end])
end
