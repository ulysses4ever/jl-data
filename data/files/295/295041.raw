using Winston

x = -4:0.1:4
y1 = tanh(sinh(x))
y2 = sech(sinh(x)).^2.*cosh(x)

p = FramedPlot(
        title="Transformação senh-tgh",
        xlabel="t",
        ylabel="y")

add(p, Curve(x, y1))
add(p, Curve(x, y2, kind="dash"))

legend(p, ["tanh(sech(t))","sech^2(sinh(t))cosh(t)"], [0.55,0.15])
plot(p)
savefig("test.png")
