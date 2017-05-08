using Gadfly

x = linspace(1,10,100)
y = linspace(1,30,200)
X = zeros(length(x)*length(y))
Y = zeros(length(x)*length(y))
Z = zeros(length(x)*length(y))

i =1
for xi in x
  for yi in y
    X[i] = xi
    Y[i] = yi
    Z[i] = xi*yi
    i+=1
  end
end
plot(x=X, y=Y, color=Z, Geom.rectbin)
