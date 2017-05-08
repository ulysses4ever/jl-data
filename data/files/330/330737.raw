using PyPlot
using DataFrames


function main(file="")
  if isempty(file)
    ############################
    # Test Data
    ############################
    nx = 32
    ny = 16
    pos_x = linspace(0,100,nx)
    pos_y = linspace(0,50,ny)
    x = zeros(nx, ny)
    y = zeros(nx, ny)
    for r in 1:nx
      for c in 1:ny
        x[r,c] = pos_x[r];
        y[r,c] = pos_y[c];
      end
    end
    u = rand(nx, ny)
    v = rand(nx, ny) 
  else
    ############################
    # Real Data
    ############################
    csv_data_fluid2d = readtable(file, separator=',', header=true)
    #    use only 2D data
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
  end

  # plot grid
  figure()
  plot(reshape(x,nx*ny,1), reshape(y,nx*ny,1), marker="x", linestyle="none")

  figure()
  quiver(x,y,u,v)
  
  figure()
  plot_surface(x,y,u, rstride=2, cstride=2, cmap=ColorMap("hsv"), alpha=0.8, linewidth=0.25)
end