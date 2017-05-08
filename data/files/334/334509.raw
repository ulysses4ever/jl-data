using Gadfly

function plot_orthogonal_transform(Q)
  triangle = [1 1 5 1; 1 4 1 1]
  transformed_triangle = Q*triangle
  set_default_plot_size(12cm, 12cm)
  plot(
    layer(
      x=triangle[1,:], y=triangle[2,:], Geom.path,
      yintercept=[0], Geom.hline,
      xintercept=[0], Geom.vline,
      Theme(default_color=color("black"))
    ),
    layer(
      x=transformed_triangle[1,:], y=transformed_triangle[2,:], Geom.path,
      Theme(default_color=color("red"))
    ),
    Guide.xticks(ticks=[-6:6]), Guide.yticks(ticks=[-6:6]),
    Guide.XLabel("x_1"), Guide.YLabel("x_2")
  )
end
