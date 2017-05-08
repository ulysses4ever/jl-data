################################################################################
########## Plotting functions for Network using Gadfly                ##########
########## Maxime Legrand - Berkeley 2015                             ##########
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

"""Graph Plot
Input : V, n*2 matrix of vextices coordinates
    A, n*n adjacency matrix
C, a vector of clusters to differentiate by vertices' color, Vector[] by default
Output : Corresponding undirected n-network plot"""
function graphplot(V, A; C=Vector[], title="")
  n = size(V,1)
  xn1 = Float64[]
  yn1 = Float64[]
  xn2 = Float64[]
  yn2 = Float64[]
  for i in 1:n
    for j in 1:i
      if A[i,j] != 0
        push!(xn1, V[i,1])
        push!(yn1, V[i,2])
        push!(xn2, V[j,1])
        push!(yn2, V[j,2])
      end
    end
  end
  layers = Layer[]
  for i=1:length(xn1)
    push!(layers,
          layer(x = [xn1[i], xn2[i]], y = [yn1[i], yn2[i]], Geom.line, Theme(default_color=color("lightgrey")))[1])
  end
    if length(C) == 0
    push!(layers, layer(x = V[:,1], y = V[:,2], Geom.point)[1])
  else
    part = map(k -> "$(vvfind(k,C))", 1:n)
    push!(layers, layer(x = V[:,1], y = V[:,2], color = part, Geom.point)[1])
  end
  return plot(layers, Guide.xlabel(""), Guide.ylabel(""), Guide.title(title))
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
Notations of "Simple Algorithms for Network Visualization" by M. J. McGuffin
Input : A, adjacency matrix of an undirected network
    K, number of steps taken by the algorithm
    C, clusters to color
    init, string setting the original position of the vertices
    nodes, if init is set to "custom", initial position of the nodes
Output : corresponding graph"""
function netplot(A; K=100, C=Vector[], init="rand", nodes=[], title="")
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
      nodes[i,1] = nodes[i,1] + dx
      nodes[i,2] = nodes[i,2] + dy
    end
  end
  return graphplot(nodes, A, C=C, title=title)
end
