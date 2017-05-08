################################################################################
# Type Definitions
################################################################################
# Geometry types
abstract segment
immutable Point{T<:Float64}
    x::T # x coordinate
    y::T # y coordinate
end
immutable BoundarySegment{T1<:Point, T2<:Array{Float64}}
    p1::T1 # Start point
    p2::T1 # End point
    n::T2  # Outward unit normal vector
end

# Boundary condition types
abstract BoundaryCondition
immutable Dirichlet <: BoundaryCondition
val::Float64
end
immutable Neumann <: BoundaryCondition
val::Float64
end

# Boundary element types
abstract BoundaryElement
immutable ConstantElement{T1<:Point,
                          T2<:Array{Float64},
                          T3<:BoundaryCondition} <: BoundaryElement
    p1::T1 # Segment start point
    p2::T1 # Segment end point
    node::T1 # Bubble node in the centre of the element
    n::T2 # Outward unit normal vector
    bc_node::T3 # Boundary condition at node
end
immutable LinearElement{T1<:Point,
                        T2<:Array{Float64},
                        T3<:BoundaryCondition} <: BoundaryElement
    p1::T1 # Segment start point
    p2::T1 # Segment end point
    # Shape function nodes coincide with p1 and p2
    n::T2 # Outward unit normal vector
    bc_1::T3 # Boundary Condition at p1
    bc_2::T3 # Boundary Condition at p2
end
immutable QuadraticElement{T1<:Point,
                           T2<:Array{Float64},
                           T3<:BoundaryCondition} <: BoundaryElement
    p1::T1 # Segment start point
    p2::T1 # Segment end point
    # First quadratic node coincides with p1
    node::T1 # Second quadratic node at the centre of the interval
    # Third quadratic node coincides with p2
    n::T2 # Outward unit normal vector
    bc_1::T3 # Boundary condition at p1
    bc_node::T3 # Boundary condition at node
    bc_2::T3 # Boundary condition at p2
end

# Kernel types
abstract LaplaceKernel
immutable PotentialKernel <: LaplaceKernel end
immutable FluxKernel <: LaplaceKernel end
