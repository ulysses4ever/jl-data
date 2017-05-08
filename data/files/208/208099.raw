Pkg.add("Gadfly")
using Gadfly

X = [[1 0.032],
     [1 0.034],
     [1 0.0214],
     [1 0.263],
     [1 0.275],
     [1 0.275],
     [1 0.45],
     [1 0.5],
     [1 0.5],
     [1 0.63],
     [1 0.8],
     [1 0.9],
     [1 0.9 ],
     [1 0.9 ],
     [1 0.9 ],
     [1 1.0 ],
     [1 1.1 ],
     [1 1.1 ],
     [1 1.4 ],
     [1 1.7 ],
     [1 2.0 ],
     [1 2.0 ],
     [1 2.0 ],
     [1 2.0 ]]

y = [170,
     290,
     -130,
     -70,
     -185,
     -220,
     200,
     290,
     270,
     200,
     300,
     30,
     650,
     150,
     500,
     920,
     450,
     500,
     500,
     960,
     500,
     850,
     800,
     1090]

X'
A = X'*X
b = X'*y

s = A\b
a = s[1]
b = s[2]


x = zeros(size(X)[1])
for i = 1:size(x)[1]
  x[i] = X[i,2]
end

# Plotando Pontos
plot(layer(x=x, y=y, Geom.point), layer(x=[0,2] ,y=[a, a + b*2], Geom.line),Guide.YLabel("Velocidade - KM/sec") ,Guide.XLabel("Distancia - 1x10⁶ parsec"))
