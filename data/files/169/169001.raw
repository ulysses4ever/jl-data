# exercise Winston for png and on-screen graphics
using Winston

# Example 1
x = [-pi:0.02:pi]
y = sin(x) + randn(length(x))/4.0
y2 = 0.4 + sin(x) + randn(length(x))/8.0
p = Winston.FramedPlot()
Winston.setattr(p, "width",1200)
Winston.setattr(p, "title", "Winston Test")
ts = Winston.getattr(p,"title_style")
ts["fontsize"]= 5.0

setattr(p, "xlabel", "Time")
setattr(p, "ylabel", "Value")
setattr( p.y1, "draw_grid", true )
setattr(p, "aspect_ratio", .6)
add(p, Curve(x, y, "color", "olive") )
add(p, Curve(x, y2, "color", "blue") )

file(p, "winston.png", "width",900, "height",700)

Winston.tk(p, "width",900, "height",700)  #on-screen display

z=4

function tkplot(x, y, title::String, xlabel::String, ylabel::String )
    p = Winston.FramedPlot()
    Winston.setattr(p, "width",1200)
    Winston.setattr(p, "title", title)
    ts = Winston.getattr(p,"title_style")
    ts["fontsize"]= 5.0

    setattr(p, "xlabel", xlabel)
    setattr(p, "ylabel", ylabel)
    setattr( p.y1, "draw_grid", true )
    setattr(p, "aspect_ratio", .6)
    add(p, Curve(x, y, "color", "olive") )
    Winston.tk(p, "width",900, "height",700)  #on-screen display
end

tkplot(x, y, "tkplot Test", "x time", "y val")

####################################################
# Example 2 xy plot
p = FramedPlot()

setattr(p, "xrange", (0,100))
setattr(p, "yrange", (0,100))
setattr(p, "aspect_ratio", 1)

n = 2100
x = linspace( 0, 100, n )
yA = 40 + 40randn(n)
yB = x + randn(n)

a = Points( x, yA, "type", "circle" )
setattr(a, "label", "a points")

b = Points( x, yB )
setattr(b, "label", "b points")
style(b, "type", "filled circle" )

s = Slope( 1, (0,0), "type", "dotted" )
setattr(s, "label", "slope")

l = Legend( .1, .9, {a,b,s} )

add( p, s, a, b, l )
file(p, "example2.png")
Winston.tk(p)

####################################################
# example 3: multiple plots
x = linspace( 0, 3pi, 30)
y = sin(x)

p = FramedPlot()
setattr(p, "title", "Title")
setattr(p, "xlabel", "X axis")
setattr(p, "ylabel", "Y axis")

add( p, Histogram(y, 1) )
add( p, PlotLabel(.5, .5, "Histogram", "color", 0xcc0000) )

t1 = Table( 1, 2 )
t1[1,1] = p
t1[1,2] = p

t2 = Table( 2, 1 )
t2[1,1] = t1
t2[2,1] = p

file(t2, "example3.png")


print("done")

