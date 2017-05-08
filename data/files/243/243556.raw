module SimPEG

include("Utils.jl")
include("Mesh.jl")
include("MeshGrid.jl")
include("LinearOperators.jl")

using PyCall

export plotImage
function plotImage(M::SimPEG.AbstractTensorMesh, vec)
    @pyimport SimPEG as pySimPEG
    Mesh = PyObject(pySimPEG.Mesh.o)
    h = M.cnt.dim == 3? (M.hx, M.hy, M.hz): M.cnt.dim == 2? (M.hx, M.hy) : (M.hx,)
    pyM = pycall(PyObject(Mesh["TensorMesh"]), PyObject, h)
    pycall(pyM["plotImage"], PyObject, vec)
end

end
