################################################################################
########## Plotting functions for Network using Gadfly                ##########
########## Maxime Legrand - Summer 2015                               ##########
################################################################################

# Pkg.add("Gadfly")
# using Gadfly
# include("../MCL_Julia/mcl.jl")

"Plots n vertices given through a n*2 array."
function plot_vertices(Coordinates)
  x_coor = Coordinates[:,1]
  y_coor = Coordinates[:,2]
  plot(x=x_coor, y=y_coor, Geom.point)
end

"""Plot a undirected n-network given :
 - a n*2 array of vertices coordinates
 - a n*n adjacency matrix (meant symetric : only inferior part is used)"""
function graphplot(A,C,test_mcl=false)
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
    push!(layers,
          layer(x = [xn1[i], xn2[i]], y = [yn1[i], yn2[i]], Geom.line)[1])
  end
  if test_mcl
    Am = mcl
    push!(layers, layer(x = C[:,1], y = C[:,2], Geom.point)[1]) # À CHANGER #
  else
    push!(layers, layer(x = C[:,1], y = C[:,2], Geom.point)[1])
  end
  plot(layers)
end

"Regular polygon positionning"
function rpolygon(n, center, radius)
  nodes = zeros(n,2)
  for i in 1:n
    nodes[i,1] = center[1] + radius * cos(2*i*pi/n)
    nodes[i,2] = center[2] + radius * sin(2*i*pi/n)
  end
  return nodes
end

"Superior part"
function spart(x::Float64)
  if x >= 0.
    return x
  else
    return 0.
  end
end

"""Force-directed layout
Inspired from physics, but not physically correct
Notations of "Simple Algorithms for Network Visualization" by M. J. McGuffin"""
function netplot(A, K, init="rand", test_mcl=false)
  n = size(A,1)
  R = 10
  L = 2*R/(n/2)
  Kr = 1
  Ks = 1
  delta = 2*R/K
  d2max = 2*R
  if init == "polygon"
    nodes = convert(Array{Float64,2}, rpolygon(n, [0 0], R))
  elseif init == "rand"
    nodes = -R + 2*R*rand(n,2)
  end
  for k in 1:K
    forces = zeros(n,2)
    for i1 in 1:(n-1)
      for i2 in (i1+1):n
        dx = nodes[i2,1] - nodes[i1,1]
        dy = nodes[i2,2] - nodes[i1,2]
        if (dx != 0) || (dy != 0)
          d2 = dx*dx + dy*dy
          d = sqrt(d2)
          # Repulsive force Fr = Kr/d^2
          Fr = Kr / ((L/10) + d2)
          fx = Fr * dx / d
          fy = Fr * dy / d
          forces[i1,1] = forces[i1,1] - fx
          forces[i1,2] = forces[i1,2] - fy
          forces[i2,1] = forces[i2,1] + fx
          forces[i2,2] = forces[i2,2] + fy
          # Spring force Fs = Ks(d-L)
          if A[i1,i2] != 0
            Fs = Ks * spart(d - L)
            fx = Fs * dx / d
            fy = Fs * dy / d
            forces[i1,1] = forces[i1,1] + fx
            forces[i1,2] = forces[i1,2] + fy
            forces[i2,1] = forces[i2,1] - fx
            forces[i2,2] = forces[i2,2] - fy
          end
        end
      end
    end
    # Updating positions
    for i in 1:n
      dx = delta * forces[i,1]
      dy = delta * forces[i,2]
#       d2 = dx*dx + dy*dy
#       if d2 > d2max
#         s = sqrt(d2max / d2)
#         dx = dx * s
#         dy = dy * s
#       end
      nodes[i,1] = nodes[i,1] + dx
      nodes[i,2] = nodes[i,2] + dy
    end
  end
  if test_mcl
    return graphplot(A,nodes) # À CHANGER #
  else
    return graphplot(A,nodes)
  end
end
