#!/usr/bin/env julia
# or run inside julia 
#  include("plotpoints.jl")

using PyPlot, Distances
hold(false); # clear anything from before
ds=imread("dollySods.png");
# on cropped bottom left (0,0) is  41,20 to top,right is 46,26

ym, xm = size(ds);
xstep=46-41; ystep=26-20;
xs=xm/xstep; ys=ym/ystep;

# in km from UTM 17S 06 and 43 *10^5
ax=vec([45.8, 44.250, 43.395, 43.897, 44.210, 42.611]);
ay=vec([21.8, 20.736, 20.880, 22.962, 24.573, 25.015]);

# dist=euclidean(vec(ax),vec(ay))  # not right, 2 points in 6D
# dist=pairwise(Euclidean, vec(ax), vec(ay)) # bad syntax, see methods(pairwise)
dist=0
for i=1:5;
   dist+=((ax[i]-ax[i+1])^2 + (ay[i]-ay[i+1])^2)^(1/2);
end
println("as a crow: ", dist, "km")

x=(ax - 41)*xs; y=(ay - 20)*ys;

imshow(flipud(ds),origin="lower");
hold(true);
# show lines are mostly okay
axhline(y=4*ys) 
axvline(x=2*xs)
println("xscale vs yscale (should be 0, reflects skewedness) : ", abs(xs-ys))

plot(x,y, color="black")
scatter(x,y,color="blue")
ylim(0,ym)
xlim(0,xm)
axis("off")
savefig("withPoints.pdf")
