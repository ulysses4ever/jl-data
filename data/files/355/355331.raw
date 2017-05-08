function plot_table2(table)
  (m,n) = size(table)
  x = Int[int(x) for x in table[2:end,1]]

  colors = ["red", "blue", "black", "green", "magenta"]

  legs = []
  plt = FramedPlot()

  for i = 1:5
    y = Float64[float64(x) for x in table[2:end,i+1]]
    c = Curve(x, y, "color", colors[i])
    setattr(c, "label", table[1,i+1])
    add(plt, c)
    p = Points(x, y, "color", colors[i], "symbolkind", "circle")
    add(plt, p)
    push!(legs, c)
  end

  setattr(plt, "xlog", true)
  setattr(plt, "ylog", true)
  add(plt, Legend(0.6, 0.95, legs))

  savefig(plt, "teste_plot.png", "width", 600, "height", 800)
end