module SimPEG

# using BigLib: thing1, thing2

import Mesh
importall Utils
import LinearOperators: faceDiv



export Mesh


hx = ones(1)
hy = ones(2)
hz = ones(3)*2

M = Mesh.TensorMesh(hx, hy, hz)
println(M)
println(M.cnt.nF)

@time println(full(faceDiv(M)))
@time println(full(faceDiv(M)))

end
