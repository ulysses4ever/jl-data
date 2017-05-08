module JFET

using FastGaussQuadrature
using MultiPoly

export ReferenceLine, ReferenceTriangle, ReferenceSquare,
       ReferenceTetrahedron, ReferenceCube, LagrangeFE

export dim, volume, make_quadrule, integrate, points,
        weights, vertices, edges, faces, facet, tabulate

#include("polybasis.jl")
include("refelements.jl")
include("finite_element.jl")
include("quadrature.jl")


end # module
