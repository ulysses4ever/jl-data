srand(0)

# Density in stars, density in smooth matter, external shear
rho_stars = 0.7

# Number of stars
N_stars = 100

# Radius of disc of stars
radius = 100.

# Pareto distribution parameters
min_mass = 1.
alpha = 2.

x_stars = zeros(Float64, N_stars)
y_stars = zeros(Float64, N_stars)
m_stars = zeros(Float64, N_stars)

# Generate star positions and masses
for i in 1:N_stars
  while true
    x_stars[i] = -radius + 2.*radius*rand()
    y_stars[i] = -radius + 2.*radius*rand()
    rsq = x_stars[i]^2 + y_stars[i]^2
    if rsq < radius^2
      break
    end
  end
  m_stars[i] = min_mass*(1. - rand())^(-1./alpha)
end

# Rescale masses to achieve target density
m_stars = m_stars*rho_stars/(sum(m_stars)/(pi*radius^2))

# Deflection angle function
function deflection_angles(x, y)
  ax = 0.
  ay = 0.
  for i in 1:N_stars
    rsq = (x - x_stars[i])^2 + (y - y_stars[i])^2
    ax += m_stars[i]*(x - x_stars[i])/(pi*rsq)
    ay += m_stars[i]*(y - y_stars[i])/(pi*rsq)
  end
  return [ax, ay]
end

# Magnification map
map = zeros(Int64, (100, 100))
xs_min = -10.
xs_max =  10.
ys_min = -10.
ys_max =  10.
dxs = (xs_max - xs_min)/(size(map)[2])
dys = (ys_max - ys_min)/(size(map)[1])

# Grid of rays to fire
x_min = xs_min/(1. - rho_stars)
x_max = xs_max/(1. - rho_stars)
y_min = ys_min/(1. - rho_stars)
y_max = ys_max/(1. - rho_stars)
Nx = 1000
Ny = 1000
dx = (x_max - x_min)/Nx
dy = (y_max - y_min)/Ny

for j in 1:Ny
  x = x_min + (j - 0.5)*dx
  for i in 1:Nx
    y = y_max - (i - 0.5)*dy

    # Shoot ray
    alpha = deflection_angles(x, y)
    xs = x - alpha[1]
    ys = y - alpha[2]

    # Find appropriate bin in source plane
    ii = convert(Int64, floor((ys_max - ys)/dys)) + 1
    jj = convert(Int64, floor((xs - xs_min)/dxs)) + 1
    if ii >= 1 && ii <= size(map)[1] && jj >= 1 && jj <= size(map)[2]
      map[ii, jj] += 1
    end
  end
  println(j, "/", Ny)
end

println(size(map))

import PyPlot
PyPlot.imshow(map, interpolation="nearest")
PyPlot.savefig("map.pdf", bbox_inches="tight")

