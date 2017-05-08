using Gadfly

function plot_rational_interp(x)
  t = -2:0.01:8
  f = (x[1] + x[2]*t + x[3]*t.^2) ./ (1 + x[4]*t + x[5]*t.^2)
  interp_t = [1, 2, 3, 4, 5]
  interp_f = [2, 5, 9, -1, -4]
  plot(
    layer(y=f, x=t, Geom.line),
    layer(y=interp_f, x = interp_t, Geom.point, Theme(default_color=color("red"))),
    Guide.XLabel("t"), Guide.YLabel("f(t)"),
    Guide.xticks(ticks=[-2:8]), Guide.yticks(ticks=[-5:10])
  )
end
