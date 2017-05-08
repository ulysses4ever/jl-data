using Gadfly
export line_plot, scatter_plot
export new_figure, show_figure, save_figure
export set_xlabel, set_ylabel, set_title

type Figure
  layers::Array{Gadfly.Layer, 1}
  title::String
  xlabel::String
  ylabel::String

  function Figure(title::String, xlabel::String, ylabel::String)
    return new(Gadfly.Layer[], title, xlabel, ylabel)
  end
end

function build_plot(figure::Figure)
  if length(figure.layers) == 0
    error("No plots have been defined for current figure")
  end
  p = Gadfly.plot(
    figure.layers,
    Guide.title(figure.title),
    Guide.xlabel(figure.xlabel),
    Guide.ylabel(figure.ylabel)
  )
end

function get_figure(figure)
  if figure == nothing
    if cur_figure != nothing
      figure = cur_figure
    else
      figure = new_figure()
    end
  end
  return figure
end

function new_figure(; title="", xlabel="x", ylabel="y")
  figure = Figure(title, xlabel, ylabel)
  global cur_figure = figure
  return figure
end

function show_figure(; figure=nothing)
  figure = get_figure(figure)
  p = build_plot(figure)
  display(p)
  return figure
end
show_figure(figure) = show_figure(figure=figure)

function save_figure(name, width, height; figure=nothing)
  figure = get_figure(figure)
  p = build_plot(figure)
  draw(SVG(string(name, ".svg"), width, height), p)
  return figure
end

function generic_plot(x, y, geom, color_string, figure)
  figure = get_figure(figure)
  new_layer = nothing
  if color == nothing
    new_layer = Gadfly.layer(x=x, y=y, geom)
  else
    theme = Theme(default_color = color(color_string))
    new_layer = Gadfly.layer(x=x, y=y, geom, theme)
  end
  append!(figure.layers, new_layer)
end

function line_plot(x, y; color=nothing, figure=nothing)
  generic_plot(x, y, Geom.path, color, figure)
end

function scatter_plot(x, y; color=nothing, figure=nothing)
  generic_plot(x, y, Geom.point, color, figure)
end

function set_title(title::String; figure=nothing)
  figure = get_figure(figure)
  figure.title = title
end

function set_xlabel(xlabel::String; figure=nothing)
  figure = get_figure(figure)
  figure.xlabel = xlabel
end

function set_ylabel(ylabel::String; figure=nothing)
  figure = get_figure(figure)
  figure.ylabel = ylabel
end
