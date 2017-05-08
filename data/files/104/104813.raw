################################################################################
# Type Definitions
################################################################################

using FixedSizeArrays
import GeometryTypes: Point, Simplex, Face, Normal

"""
Connect describes the connection between points. The contents of Connect are
integers that index into a list of faces, i,e. Connect(1,3) corrsponds to face
1 and face 3. Connect types are usually contained in a connectivity array where
the Connect in position k contains indices corresponding to the faces attached
to point k.
"""
immutable Connect{N,T} <: FixedVector{N,T}
    _::NTuple{N,T}
end
# Required to allow Connect(s1, s2, ...)
function call{T<:Connect, F<:FixedVector}(::Type{T}, f::F...)
    Connect{length(f),F}(f)
end

# Boundary condition types
abstract BoundaryCondition
"""
A Dirichlet boundary condition is function defined on a boundary that prescribes
the value a field takes on the boundary. For example, it defines a fixed head
boundary in groundwater flow problems or a fixed temperature boundary in heat
flow problems.

The Dirichlet type contains a val field that is a function. The argument for the
function is a Point type. This way, the boundary condition can be spatially
variable. For example, if the Dirichlet boundary condition is f(x,y) = y, the
boundary condition would have the form

Dirichlet.val(Point(x,y)) = f(x,y) = y
"""
immutable Dirichlet{T<:Function} <: BoundaryCondition
val::T
end
"""
A Neumann boundary condition is function defined on a boundary that prescribes
the value a flux takes normal to the boundary. For example, it can be used to
prescribe the velocity component of groundwater normal to a boundary in
groundwater flow problems or a heat flux normal to a boundary in heat flow
problems.

The Neumann type contains a val field that is a function. The argument for the
is a Point type. This way, the boundary condition can be spatially variable.
For example, if the Neumann boundary condition is g(x,y) = y, the boundary
condition would have the form

Neumann.val(Point(x,y)) = g(x,y) = y
"""
immutable Neumann{T<:Function} <: BoundaryCondition
val::T
end

"""
Model contains all the spatial information of the problem before discretization.
For now, only one closed boundary is supported (so only one material type is
currently possible).

The vertices, faces, connectivity, normals and bcids fields
are arrays that describe the boundary of the model and should all be the same
length.

The bcs field is an array of the boundary conditions in the model. The
field_points field is an array of all the domain points where the field
potential is evaluated once the BEM solution is complete.

The element_order field specifies the polynomial order of the interpolating
shape functions used. element_order = 1 is for constant elements,
element_order = 2 is for linear elements, etc.
"""
immutable Model{VertT<:Point, FaceT<:Face, ConnectT<:Connect, NormT<:Normal,
                BcidT<:Int64, BcT<:BoundaryCondition}
    vertices      ::Vector{VertT}
    faces         ::Vector{FaceT}
    connectivity  ::Vector{ConnectT}
    normals       ::Vector{NormT}
    bcids         ::Vector{BcidT}
    bcs           ::Vector{BcT}
    field_points  ::Vector{VertT}
    element_order ::Int64
end

# Boundary element types
"""
A Node is a point inside a boundary element where the elment shape function is
interpolated.
"""
immutable Node{N, T} <: FixedVector{N, T}
    _::NTuple{N, T}
end
# Required to allow Node(p1, p2, ...)
function call{T<:Node, F<:FixedVector}(::Type{T}, f::F...)
    Node{length(f),F}(f)
end

# D is the ambient dimension of the problem (i.e. dimension of boundary surface
# = D - 1) and N is the order of the boundary element (1 = constant element,
# 2 = linear element, 3 = quadratic element, etc.)
"""
A BoundaryElement is the main structure where the computation for the BEM
happens. It consists of a simplex defining its geometry, nodes corresponding
to shape function interpolation points (and collocation points) and a unit
normal vector.
"""
immutable BoundaryElement{D, N, T}
    segment::Simplex{D, Point{D, T}}
    nodes::Node{N, Point{D, T}}
    normal::Normal{D, T}
end

"""
A DiscreteBoundary is a discretized version of a Model. It contains an array
of all the BoundaryElements, the connectivity structure of the elements and the
boundary conditions applicable to each element.
"""
type DiscreteBoundary{ElmT<:BoundaryElement, ConnectT<:Connect, BcidT<:Int64,
                      BcT<:BoundaryCondition}
    elements     ::Vector{ElmT}
    connectivity ::Vector{ConnectT}
    bcids        ::Vector{BcidT}
    bcs          ::Vector{BcT}
end

# Kernel types
abstract LaplaceKernel
immutable PotentialKernel <: LaplaceKernel end
immutable FluxKernel <: LaplaceKernel end
