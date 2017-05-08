module SimPEG

# using BigLib: thing1, thing2

import Mesh
importall Utils
importall LinearOperators

export Mesh


hx = ones(3)
hy = ones(2)
hz = ones(3)*2

M = Mesh.TensorMesh(hx)
println(M.cnt.vnEx)

D = faceDiv(M)
C = edgeCurl(M)
G = nodalGrad(M)

Av = aveCC2F(M)

println(full(Av))

# D*C*G

end
