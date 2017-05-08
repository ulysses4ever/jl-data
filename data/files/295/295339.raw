include ("getAprox.jl")
include ("difdiv.jl")

function getDistance (a, b, n, f)

  X=linspace(a,b,n); Y=[1.0:length(X)];

  for i=[1:length(X)]
    Y[i]=f(X[i])
  end

  C=difdiv(X,Y);
  x=linspace(a, b, 100); distance = 0;
  y=[1.0:100]; z=[1.0:100];

  for i=[1:n]
    y[i]=f(x[i]); z[i]=getAprox(x[i], X, Y, C);
    
    if (abs(y[i]-z[i])>distance)
      distance = abs(y[i]-z[i])
    end
  end

  return distance
end