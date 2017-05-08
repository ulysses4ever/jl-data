using Gadfly

function plot_compartments(X)
  plot(
    layer(y=X[1,:], x=1:100, Geom.line, Theme(default_color=color("blue"))),
    layer(y=X[2,:], x=1:100, Geom.line, Theme(default_color=color("red"))),
    layer(y=X[3,:], x=1:100, Geom.line, Theme(default_color=color("green"))),
    Guide.XLabel("t"), Guide.YLabel("Amount"),
    Guide.xticks(ticks=[0:25:100]), Guide.yticks(ticks=[0:0.25:1.0])
  )
end

function plot_totals(totals)
  plot(y=totals,x=1:100,Geom.line, 
    Guide.XLabel("t"),Guide.YLabel("Total Amount"),
    Guide.xticks(ticks=[0:25:100]), Guide.yticks(ticks=[0:0.25:1.0])
  )
end
