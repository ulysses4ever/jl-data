################################################################################
########## Plotting functions for Network using Gadfly                ##########
########## Maxime Legrand - Summer 2015                               ##########
################################################################################

# Pkg.add("Gadfly")
using Gadfly

"Plots n vertices given through a n*2 array."
function plot_vertices(Coordinates)
  x_coor = Coordinates[:,1]
  y_coor = Coordinates[:,2]
  plot(x=x_coor, y=y_coor, Geom.point)
end

"Plot a symetrically-linked n-network given :
 - a n*2 array of vertices coordinates
 - a n*n adjacency matrix (meant symetric : only inferior part is considerated)"
function graphplot(A,C)
  n = size(C,1)
  xn1 = Float64[]
  yn1 = Float64[]
  xn2 = Float64[]
  yn2 = Float64[]
  for i in 1:n
    for j in 1:i
      if A[i,j] != 0
        push!(xn1, C[i,1])
        push!(yn1, C[i,2])
        push!(xn2, C[j,1])
        push!(yn2, C[j,2])
      end
    end
  end
  layers = Layer[]
  for i=1:length(xn1)
    push!(layers, layer(x = [xn1[i], xn2[i]], y = [yn1[i], yn2[i]], Geom.line)[1])
  end
  push!(layers, layer(x = C[:,1], y = C[:,2], Geom.point)[1])
  plot(layers)
end
