include("../cosine-map.jl")

using Gadfly
using Compose

p = plot(x=[1:k], y=x,
    Geom.point,
    Geom.line,

    Guide.Title("Cosine Map"),
    Guide.YLabel("f(x)"),
    Guide.XLabel("Iteration"),
    Guide.XTicks(ticks=[1:2:k]),
    Guide.Annotation(
      compose(context(),
        compose(context(), text(fp, x[fp] + 0.04, "Fixed Point", hleft, vcenter)),
        compose(context(), circle(fp, x[fp], 2.5mm), fill(nothing), stroke("orange"))
      )
    ),
    Guide.Annotation(
      compose(context(),
        compose(context(),
          line([(1.4, x[fp] + 0.02), (fp - 0.4, x[fp] + 0.02)]),
          fill(nothing),
          stroke("steelblue"),
          strokedash([2mm, 1mm])
        ),
        compose(context(), text(fp / 2, x[fp] + 0.05, "Transient", hcenter, vcenter))
      )
    ))

draw(PNG("cosine-map.png", 600px, 600px / golden), p)
