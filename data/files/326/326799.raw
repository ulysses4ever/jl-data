using MyNumerical
using PyPlot

dxdt4(t, x) = [x[2], -sin(x[1])]

global t0 = 0.0
global x0 = [pi/2 + pi/3, 0.0]
global max_t = 100.0
global dt = 0.01

pygui(true)
# harmonic oscillator
# (1) (i) エネルギー保存
res = tx_list(make_result(max_t, dt, t0, x0, dxdt4, rk), 3)
Ep(res) = (res[3, 1:end].^2 ) / 2.
Ex(res) = -cos(res[2, 1:end])
Energy_x = Ex(res)
Energy_p = Ep(res)
Energy = (Energy_x + Energy_p)
myplot(res[1, 1:end], Energy) # 保存されている

# (ii)
x0 = [pi/200, 0.0] # 微小振動
r = 100 * 0.1 .^ [4:-1:1] # dt list
ress = [make_result(max_t, idt, t0, x0, dxdt4, rk) for idt in r]

# 微小振動での解 θ0 * cos(t) との誤差
errors = [abs(x0[1]*cos(tx[end][1]) - tx[end][2]) for tx in ress]
# RKで誤差がO(h^4)となっていることが確認できた
xscale("log"); yscale("log"); scatter([r],  errors, s=10)


# (2)
ω0 = [0.1, 0.5, 1.0, 1.9, 2.0, 2.1]
x0_list = [[0., om] for om = ω0]
ress = [tx_list(make_result(max_t, dt, t0, ix0, dxdt4, rk), 3) for ix0 in x0_list]

# τ-θ
for i in 1:length(ω0)
    myplot(ress[i][1, 1:end], ress[i][2, 1:end])
end
# phase space
for i in 1:length(ω0)
    xlim(-pi, pi); myplot(ress[i][2, 1:end], ress[i][3, 1:end])
end



res = tx_list(make_result(max_t, dt, t0, x0, dxdt4, rk), 3)
myplot(res[1, 1:end], res[2, 1:end])
myplot(res[1, 1:end], res[3, 1:end])
xlim(-pi, pi); myplot(res[2, 1:end], res[3, 1:end])




println()
for i in errors
    println(i)
end




Energy_x
Energy_p
