module SimPEG

# using BigLib: thing1, thing2

import Mesh
importall Utils
importall LinearOperators
importall MeshGrid

export Mesh


hx = ones(100)
hy = ones(100)
hz = ones(3)*2

M = Mesh.TensorMesh(hx, hy)
println(M.cnt.vnEx)

D = faceDiv(M)
C = edgeCurl(M)
G = nodalGrad(M)
# D*C*G

Av = aveCC2F(M)
sigma = ones(M.cnt.nC)
Msig = getFaceInnerProduct(M, sigma)

A = -D*Msig*D'
A[end,end] /= 1./M.vol[end]

q = zeros(M.cnt.vnC...)
q[50,25] = -1.0
q[50,75] = +1.0
q = q[:]

@time phi = A\q

end
