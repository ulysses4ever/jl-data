# exercise primitive forms, basic properties and combinations
# next:
#  1. display a labelled box with centered text
#     how to size text relative to canvas?
#
#  2. display mult labelled boxes with lines connecting them

using Compose

const phi = (1 + sqrt(5)) / 2

function sierpinski(n)
    if n == 0
        compose(canvas(), polygon((1,1), (0,1), (1/2, 0)))
    else
        t = sierpinski(n - 1)
        compose(canvas(),
                (canvas(1/4,   0, 1/2, 1/2), t),
                (canvas(  0, 1/2, 1/2, 1/2), t),
                (canvas(1/2, 1/2, 1/2, 1/2), t))
    end
end

img = SVG("sierpinski.svg", 4inch, 4(sqrt(3)/2)inch)
draw(img, compose( sierpinski(8), linewidth(0.1mm), fill(nothing) )   )
finish(img)


#function golden_rect(n::Int)
#    if n == 0; return empty_canvas; end
#    c = canvas() << (rectangle() << fill(LCHab(90, 80, 70 - 15n)))
#    #c | (canvas(0, -1/phi, 1h, 1/phi, Rotation(pi/2, 0, 1)) | golden_rect(n - 1))
#    c = compose(c,  golden_rect(n - 1)  )
#end

#img2 = SVG("GOLDEN.svg", 4inch, 4(sqrt(3)/2)inch)
#draw(img2, compose(golden_rect(5), linewidth(0.1mm), fill(nothing)))
#finish(img2)

# positions are relative time canvas size, between 0 and 1
x0 = 0.2
y0 = 0.1
h0  = 0.4
w0  = 0.6
multiprop = combine(fill("black"), opacity(0.5), stroke("gray") )  # combine properties to make a style

myrect = rectangle(x0, y0, w0, h0) << fill("blue") << linewidth(0.1mm)
mypoly = polygon( (0.1,0.1), (0.3,0.9), (0.7,0.1) ) << fill("gray") << opacity(0.3)
mycurve = curve( (0.1,0.1), (0.3,0.9), (0.7,0.1), (0.2,0.2) ) << fill(nothing) << stroke("green")
mycircle = circle(x0, y0, 0.2) << fill(nothing) << stroke("red")
mytext =  text(0.5, 0.5, "Hello", hcenter, vcenter) << multiprop << fontsize(18.0mm)
mylines = lines( (0.1,0.1), (0.3,0.8), (0.95,0.1), (0.95,0.3) ) << fill(nothing)

can = canvas() << myrect  # = compose( canvas(), myrect )
can.rot.theta = pi/4      # rotate canvas  ( have .rot.offset too)
print(can.box)  # see canvas.jl, cairo.jl
print(can.unit_box)

img2 = SVG("rect.svg", 4inch, 4inch)
draw(img2, can )
finish(img2)

function dform(myform, filename::String)
    img2 = SVG(filename, 6inch, 6inch)
    can = canvas() << myform  # = compose( canvas(), myrect )
    draw(img2, can )
    finish(img2)
end
dform( mypoly, "poly.svg" )
dform( mycurve, "curve.svg" )
dform( mycircle, "circle.svg" )
dform( mytext, "text.svg" )
dform( mylines, "lines.svg" )

multi = combine(mytext,mycurve,mylines,mypoly,myrect,mycircle)  #combine is for forms and properties. Leftmost is on top.
dform( multi, "multi.svg" )

# canvas in canvas
mycanvas = canvas(x0, y0, w0, h0) << linewidth(3.0mm)  << fill("gray") #children inherit properties unless over-ridden
print( mycanvas.box ) # bounding box size relative to parent
print( mycanvas.box.width )    #width with units
hv = mycanvas.box.height.value #height as Float64

dform( mycanvas << multi, "canvas.svg" )

# 3 x 3 grid of figures
mcan =  canvas() << multi
mrow = hstack( mcan, mcan, mcan )
mygrid = vstack( mrow, mrow, mrow )
dform( mygrid, "grid.svg" )

print("done")
