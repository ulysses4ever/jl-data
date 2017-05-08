using Plots

u = [5.0, 15.0, 25.0, 35.0, 45.0, 50.0, 45.0, 35.0, 25.0, 15.0, 5.0]

i = length(u)

x = [0.0:1.0:i-1]/100

M = heat_exp(u, 0, 15, x[i], 1.54e-5, 5)

plot()

plot!(x, M[1:i,1])
plot!(x, M[1:i,2])
plot!(x, M[1:i,3])
plot!(x, M[1:i,4])
plot!(x, M[1:i,5])
plot!(x, M[1:i,6])

scatter!(x, M[1:i,1], marker=:pentagon, lab=:"t=0")
scatter!(x, M[1:i,2], marker=:star4, label=:"t=3")
scatter!(x, M[1:i,3], marker=:star5, label=:"t=6")
scatter!(x, M[1:i,4], marker=:star6, label=:"t=9")
scatter!(x, M[1:i,5], marker=:star7, label=:"t=12")
scatter!(x, M[1:i,6], marker=:star8, label=:"t=15")


yaxis!("Temperatura")
xaxis!("Posição")
