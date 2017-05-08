
module Diver
include("rubberband.jl")

export view, color_by

import Color, Cairo, Tk
import Base: convert, show
import Base.Graphics: width, height, BoundingBox, ymin, ymax, xmin, xmax


# 2D Domain type
type Domain{T <: Number}
  xmin::T
  ymin::T
  xmax::T
  ymax::T
end

xmin(dom::Domain) = dom.xmin
ymin(dom::Domain) = dom.ymin
xmax(dom::Domain) = dom.xmax
ymax(dom::Domain) = dom.ymax
width(dom::Domain) = dom.xmax - dom.xmin
height(dom::Domain) = dom.ymax - dom.ymin

function show(io::IO, d::Domain)
  print(io, "x: [$(d.xmin), $(d.xmax)] y: [$(d.ymin), $(d.ymax)]")
end

function eval!(func, color_map, domain, image::Array{Uint32, 2})
  dims = size(image)
  dx, dy = width(domain) / dims[1], height(domain) / dims[2]
  x, y = xmin(domain), ymin(domain)
  for i in 1:dims[2] 
    for j in 1:dims[1]
      image[j, i] = color_map(func(x, y))
      x += dx;
    end
    y += dy
    x = xmin(domain)
  end
end

function scaleDomain(d::Domain{Float64}, bb::BoundingBox)
  min = to_domain(d, xmin(bb), ymin(bb))
  max = to_domain(d, xmax(bb), ymax(bb))
  Domain{Float64}(min..., max...)
end

# scales x and y from (0, 1, 0, 1) to domain
to_domain(d::Domain, x, y) = xmin(d) + width(d) * x, ymin(d) + height(d) * y


# convert color table and scale factor to coloring function
convert(::Type{Uint32}, x::Color.RGB) = convert(Uint32, convert(Color.RGB24, x))
color_by(c, table) = (x) -> table[1 + ifloor(x * c) % length(table)]
const default_color = color_by(30, convert(Vector{Uint32}, Color.colormap("RdBu", 200)))


# Canvas for displaying a function
type FunctionCanvas
  func::Function
  zoom_stack::Vector{Domain}
  color_map::Function
  canvas::Tk.Canvas
  surface::Cairo.CairoSurface
  label
end

domain(fc::FunctionCanvas) = fc.zoom_stack[end]
surface(fc::FunctionCanvas) = fc.surface


function view(func::Function; domain=Domain{Float64}(-2.0,-1.0,1.0,1.0),
  w=800::Int, h=600::Int, color_map=default_color)

  if isa(color_map, Vector)
    color_map = color_by(30, convert(Vector{Uint32}, color_map))
  end

  canvas, surface, xy_label = make_window(w, h)
  fc = FunctionCanvas(func, Domain[domain], color_map, 
    canvas, surface, xy_label)

  set_callbacks!(fc)
  Tk.set_value(xy_label, string(domain))
  render!(fc)
  resize!(fc)
  Tk.configure(canvas)
end

function make_window(w, h)
  window = Tk.Toplevel("Function Diver", w, h, false)
  # scale this cell when the window resize!s
  Tk.grid_rowconfigure(window, 1, weight=1) 
  Tk.grid_columnconfigure(window, 1, weight=1)

  frame_canvas = Tk.Frame(window)
  Tk.grid(frame_canvas, 1, 1, sticky ="nsew")
  # Place the canvas and set its resize! properties
  canvas = Tk.Canvas(frame_canvas, w, h)
  # fill the edges of its cell on all 4 sides
  Tk.grid(canvas, 1, 1, sticky="nsew")  

  # Create the x, y positions reporter
  frame_coord = Tk.Frame(window)
  Tk.grid(frame_coord, 2, 1, sticky="ew")
  xy_pos = Tk.Label(frame_coord)
  Tk.grid(xy_pos, 1, 1, sticky="ne")

  surface = Cairo.CairoImageSurface(Array(Uint32, w, h), Cairo.FORMAT_RGB24, flipxy=false)
  Tk.set_visible(window, true)
  canvas, surface, xy_pos
end

function set_callbacks!(fc)
  c = fc.canvas
  c.draw = _ -> resize!(fc)
  c.mouse.button1press = (c, x, y) -> begin
    rubberband_start(c, x, y, (c, box) -> zoom_in!(fc, box))
  end
  c.mouse.button3press = (c, x, y) -> zoom_out!(fc)
end


# Functions to update canvas

render!(fc::FunctionCanvas) = eval!(fc.func, fc.color_map, domain(fc), surface(fc).data)

function redraw!(fc::FunctionCanvas)
  context = Cairo.getgc(fc.canvas)

  Cairo.save(context)
  Cairo.reset_transform(context)

  # define drawing region
  w, h = size(surface(fc).data)
  Cairo.rectangle(context, 0, 0, w, h)
  Cairo.set_source_surface(context, surface(fc), 0, 0)

  Cairo.pattern_set_filter(Cairo.get_source(context), Cairo.FILTER_GOOD)
  Cairo.fill(context)
  Cairo.restore(context)

  Tk.reveal(fc.canvas)
  Tk.update()
end

function resize!(fc::FunctionCanvas)
  context = Cairo.getgc(fc.canvas)
  redraw!(fc)
end

function zoom_out!(fc::FunctionCanvas)
  if length(fc.zoom_stack) > 1
    pop!(fc.zoom_stack)
    Tk.set_value(fc.label, repr(domain(fc)))
  end
  render!(fc)
  redraw!(fc)
end

function zoom_in!(fc::FunctionCanvas, box::BoundingBox)
  w, h = size(surface(fc).data)
  box = BoundingBox(xmin(box) / w, xmax(box) / w, ymin(box) / h, ymax(box) / h)
  push!(fc.zoom_stack, scaleDomain(domain(fc), box))
  Tk.set_value(fc.label, repr(domain(fc)))
  render!(fc)
  redraw!(fc)
end

end
