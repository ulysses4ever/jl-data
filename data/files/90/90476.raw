data = readdlm("RLBinding.csv",',') # julia uses "" to declare 
# strings, '' for characters and # for comments

# one of the improvements over matlab - the use of squared brackets [] to 
# index into arrays, to clearly distinguish it from function calls.
# Indices start at 1 in julia
t = data[:,1]; R = data[:,2]; L = data[:,3]; RL = data[:,4];

# similar to import in python - declare which package to use
using Winston # Winston is one of the three graphics packages available for julia at the moment

# FramedPlot can be used for plotting a single plot
p = FramedPlot("xlabel","time")
setattr(p,"ylabel","concentration") # attributes can be changed with setter functions 
# similar to MATLABs `set` and `get`

# building a plot using Winston is like composing a collage:
# build one element after the other
# then add it all to the canvas (the FramedPlot)
r = Points(time,R,"type","diamond", "color","blue")
l = Points(time,L,"type","circle", "color","blue")
rl = Points(time,RL,"type","cross", "color","blue")

cr = Curve(time,R, "color","blue")
cl = Curve(time,L, "color","blue")
crl = Curve(time,RL, "color","blue")

setattr(r,"label","R")
setattr(l,"label","L")
setattr(rl,"label","RL")
lgnd = Legend(.8,.9,{r,l,rl})

# adding does not! need to be done at the end
add(p,r,l,rl,cr,cl,crl,lgnd)
# Winston/ijulia do not yet support the display of the generated plots,
# but it is possible to save the plot to a file 
# eps, png and svg are supposed to be supported, but 
# svg did not work on my machine out of the box
file(p,"julia_rlbinding.png")
