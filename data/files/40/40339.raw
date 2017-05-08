using Distributions
#normally we get brownian motion by integration of white noise
#we are starting with normal bm instead of fbm, with rmd

function midpoint_bm(maxlevel, sigma=1)
  gauss = Gaussian()
  X = [0 for i in 1:2049]
  st_devs = [sigma * power(0.5, (i+1)/2) for i in 1:maxlevel]
  N = power(2, maxlevel) + 1
  X[1] = 0
  X[N] = sigma * rand(gauss)
  midpoint_helper(X, 1, N, 1, maxlevel)
  #there should actually be an analytic expression for the stack depth
  #in which case we can dispense with the helper
end

function midpoint_helper(x, idx0, idx2, level, maxlevel, st_devs)
  gauss = Gaussian()
  idx1 = ((idx0 + idx2) / 2)::Int
  X[index1] = 0.5 * (X[idx0] + X[idx2]) + st_devs[level] * rand(gauss)
  if level < maxlevel
    midpoint_helper(X, idx0, idx1, level+1, maxlevel, st_devs)
    midpoint_helper(X, idx1, idx2, level+1, maxlevel, st_devs)
  end
end
