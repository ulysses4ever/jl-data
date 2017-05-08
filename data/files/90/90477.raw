# first create the individual plot containers
p1=FramedPlot("xlabel","time","ylabel","R")
p2=FramedPlot("xlabel","time","ylabel","L")
p3=FramedPlot("xlabel","time","ylabel","RL")

# add the different plot types to the containers
# first points
add(p1,Points(time,R,"type","diamond", "color","blue"))
add(p2,Points(time,L,"type","circle", "color","blue"))
add(p3,Points(time,RL,"type","cross", "color","blue"))

# then line plots
add(p1,Curve(time,R, "color","blue"))
add(p2,Curve(time,L, "color","blue"))
add(p3,Curve(time,RL, "color","blue"))

# finally, create a Table with 1 row and 3 columns
t = Table(1,3)
# and add the different FramedPlot 
# containers to the Table elements
# (which is somewhat similar in style to MATLAB subplots)
t[1,1] = p1
t[1,2] = p2
t[1,3] = p3

# The figure width and height can be
# changed when creating the graphics file
file(t,"julia_rlbinding_subplot.png","width",800,"height",400)
