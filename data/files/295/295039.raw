x = -4:0.1:4
i = 1

y1 = fill(0.0, size(x, 1))
y2 = fill(0.0, size(x, 1))

for s = -4:0.1:4

  y1[i] = tanh(sinh(s))

  y2[i] = sech(sinh(s))^2*cosh(s)

  i += 1

end

p = FramedPlot(
        title="",
        xlabel="t",
        ylabel="y")

add(p, Curve(x, y1))
add(p, Curve(x, y2, kind="dash"))