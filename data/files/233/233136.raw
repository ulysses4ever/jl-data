using Base.Test
using CSHEP2D

# generate dummy data
srand(1)
N = 2000
x = rand(N)
y = rand(N)

# simple function with known gradient
z = x.^2 + 2*y.^2

# interpolator
a = CubicShepard2DInterpolator(x, y, z)

# simple tests
c, cx, cy = valgrad(a, [0.5], [0.5])
@test abs(c[1] - 0.75) < 1e-6
@test abs(cx[1] - 1.00) < 1e-6
@test abs(cy[1] - 2.00) < 1e-6

c, cx, cy, cxx, cxy, cyy = valgradhes(a, [0.5], [0.5])
@test abs(c[1] - 0.75) < 1e-6
@test abs(cx[1] - 1.00) < 1e-6
@test abs(cy[1] - 2.00) < 1e-6
@test abs(cxx[1] - 2.00) < 1e-6
@test abs(cyy[1] - 4.00) < 1e-6
@test abs(cxy[1] - 0.0) < 1e-6


