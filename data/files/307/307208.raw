# A collection of iterated maps

LogisticMap(r) = IteratedMap{:LogisticMap,1}(x->r*x*(1-x))

LogisticMap(r,x) = LogisticMap(r)(x)

HenonMap(p) = IteratedMap{:HenonMap,2}(x->[1-p[1]*x[1]^2+x[2],p[2]*x[1]])
HenonMap(p,x) = HenonMap(p)(x)

DuffingMap(p) = IteratedMap{:DuffingMap,2}(x->[x[2],-p[2]*x[1]+p[1]*x[2]-x[2]^3])
DuffingMap(p,x) = DuffingMap(p)(x)

TentMap(μ) = IteratedMap{:TentMap,1}(x->x<0.5?μ*x:μ*(1-x))
TentMap(μ,x) = TentMap(μ)(x)
