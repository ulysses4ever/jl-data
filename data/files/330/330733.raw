using PyPlot
using DataFrames


function main(file)
  csv_data_fluid2d = readtable(file, separator=',', header=true)
  # use only 2D data
  csv_data_fluid2d = csv_data_fluid2d[csv_data_fluid2d[:Points_2] .== 0.5, :]
  pos_x = unique(csv_data_fluid2d[:Points_0])
  pos_y = unique(csv_data_fluid2d[:Points_1])
  nx = length(pos_x)
  ny = length(pos_y)
  x = reshape(repmat(pos_x, ny), nx, ny)
  y = reshape(repmat(pos_y, nx)', nx, ny)
  u = zeros(nx, ny)
  v = zeros(nx, ny)
  for i = 1: length(csv_data_fluid2d[:Points_0])
    idx_x = findfirst(pos_x, csv_data_fluid2d[i,:Points_0])
    idx_y = findfirst(pos_y, csv_data_fluid2d[i,:Points_1])
    u[idx_x, idx_y] = csv_data_fluid2d[i, :Velocity_0]
    v[idx_x, idx_y] = csv_data_fluid2d[i, :Velocity_1]
  end
  figure(1)
  quiver(x,y,u,v)
  
  figure(2)
  plot_surface(x,y,u, rstride=2, cstride=2, cmap=ColorMap("hsv"), alpha=0.8, linewidth=0.25)
end