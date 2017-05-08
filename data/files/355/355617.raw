include ("getAprox.jl")
using PyPlot

function plotG (a, b, n, f)

  X=linspace(a,b,n); Y=[1.0:length(X)];

  for i=[1:length(X)]
    Y[i]=f(X[i])
  end
  
  C=difdiv(X,Y);
  x=linspace(a, b, 100); 
  y=[1.0:100]; z=[1.0:100];

  for i=[1:100]
    y[i]=f(x[i]); z[i]=getAprox(x[i], X, Y, C);
  end

  plt.plot(x, y, x, z, linestyle="--")
end