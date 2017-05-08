include ("getAprox.jl")
using PyPlot

function plotG (a, b, n, f, X, Y)

  x=linspace(a, b, n); 
  y=[1.0:n]; z=[1.0:n];

  for i=[1:n]
    y[i]=f(x[i]); z[i]=getAprox(x[i], X, Y);
  end

  plt.plot(x, y, x, z, linestyle="--")
end