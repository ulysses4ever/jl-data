include("../logistic-map.jl")

colors = map(RGB24, [0xa50026, 0xd73027, 0xf46d43, 0xfdae61, 0xfee090, 0xe0f3f8, 0xabd9e9, 0x74add1, 0x4575b4, 0x313695])
i=1

layers = [layer(
        y=p[2],
        x=[1:k],
        Geom.point,
        Geom.line,
        Theme(default_color=colors[p[1]])
    ) for p in enumerate(xs)]

gp = plot(layers...,
  Guide.Title("Logistic maps with varying R=[0.1, 4.0]"),
  Guide.YLabel("f(x)"),
  Guide.XLabel("Iteration"))

fpp = plot(x=Rs, y=fps,
  color=[1:length(Rs)],
  Scale.color_discrete_manual(colors...),
  Guide.Title("Reaced fixed point in n'th iteration"),
  Guide.YLabel("Iteration"),
  Guide.XLabel("R"))

draw(PNG("logistic-map-contour.png", 600px, 600px / golden), gp)
draw(PNG("logistic-map-fixedpoints.png", 600px, 600px / golden), fpp)
