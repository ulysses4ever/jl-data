# Gadfly graphing library
# http://dcjones.github.io/Gadfly.jl/

using Gadfly

# If no plot elements are defined, point geometry is added by default.
# The point geometry takes as input the x and y aesthetics. So all thats
# needed to draw a scatterplot is to bind x and y.
scatter_plot = plot(x=rand(10), y=rand(10))

# Multiple elements can use the same aesthetics to produce different output.
# Here the point and line geometries act on the same data and their results are layered.
line_plot = plot(x=rand(10), y=rand(10), Geom.point, Geom.line)

# Example of a more complex plot created by combining elements
complex_plot = plot(x=1:10, y=2.^rand(10),
    Scale.y_sqrt, Geom.point, Geom.smooth,
    Guide.xlabel("Stimulus"), Guide.ylabel("Response"))


# To generate an image file from a plot, use the draw function.
# Gadfly supports a number of drawing backends. Each is used similarly.
# If used from IJulia, the output of plot will be shown automatically.
draw(PNG("sample-scatterplot.png", 4inch, 3inch), scatter_plot)
draw(PDF("sample-lineplot.pdf", 4inch, 3inch), line_plot)
draw(D3("sample-complexplot.js", 4inch, 3inch), complex_plot)


# Plots can also be made using DataFrames.
# In this case, the signature for the plot applied to a data frame is:
# => plot(data::AbstractDataFrame, elements::Element...; mapping...)
#
# In the subsequent example we will use the RDatasets package of example
# data sets from R packages
using RDatasets

# Example real-data plots
iris_plot = plot(data("datasets", "iris"), x="Sepal.Length", y="Sepal.Width", color="Species", Geom.point)
slid_plot = plot(data("car", "SLID"), x="wages", color="language", Geom.histogram)

# Draw the real-data plots
# Set the size using the golden ratio!
draw(PNG("iris-scatterplot.png", 9inch, (9inch / golden)), iris_plot)
draw(PDF("slid-histogram.pdf", 9inch, (9inch / golden)), slid_plot)


# Along with the standard plot function, Gadfly has some special forms 
# to make plotting functions and expressions more convenient:
#
# plot(f::Function, a, b, elements::Element...)
# plot(fs::Array, a, b, elements::Element...)
# @plot(expr, a, b)

sin_cos_plot = plot([sin, cos], 0, 25)
cos_plot = @plot(cos(x)/x, 5, 25)

draw(PNG("sin-cos-plot.png", 4inch, 3inch), sin_cos_plot)
draw(PNG("cos-plot.png", 4inch, 3inch), cos_plot)


# Gadfly can draw multiple layers to the same plot
layered_plot = plot(layer(x=rand(10), y=rand(10), Geom.point),
                    layer(x=rand(10), y=rand(10), Geom.line))
draw(PNG("layered-plot.png", 4inch, 3inch), layered_plot)

# Gadfly can also plot to a D3 backend, which produces javascript output
# This will show up in iJulia, or can be included in an html document
