abstract AbstractFiniteElement

abstract AbstractLagrangeFE

#type LagrangeFE{T <: AbstractReferenceElement}
#    ref_shape::T
#    basis::PolyBasis
#end

#get_coeff(LFE::LagrangeFE, i::Int) = LFE.basis[:, i]
#get_coeffs(LFE::LagrangeFE, i::Int) = LFE.basis[:, i]


typealias NodePoly MPoly{Float64}

type LagrangeFE
    shape_functions::Vector{NodePoly}
    order::Int
    points::Vector{Vector{Float64}}
end


function LagrangeFE(shape::AbstractReferenceElement, order::Int)
    points = make_lattice(shape, LagrangeFE, order)


   db = generate_dual_basis(shape, LagrangeFE, order)

    V = zeros(length(points), length(points))
    for (i, p) in enumerate(points)
        V[:, i] = evaluate_basis(db, points[i]...)
    end

    C = inv(V)

    shape_functions = NodePoly[]
    for i in 1:size(C, 1)
        p1 = copy(db)
        coeffs = C[:, i]
        i = 1
        for (m, c) in db
            p1[m] = coeffs[i]
            i += 1
        end
        push!(shape_functions, p1)
    end

    LagrangeFE(shape_functions, order, points)

end

function tabulate(ele::LagrangeFE, pts::Vector{Vector{Float64}})
    Ns = Array(Vector{Float64}, 0)

    for point in pts
        N = tabulate(ele, point)
        push!(Ns, N)
    end
    return Ns
end
function tabulate(ele::LagrangeFE, point::Vector{Float64})
    N = Float64[]
    for sf in ele.shape_functions
        push!(N, evaluate(sf, point...))
    end
    return N
end

get_points_row(::Union(ReferenceTriangle, ReferenceTetrahedron), order::Int, col::Int) = order - col
get_points_row(::ReferenceSquare, order::Int, ::Int) = order


function generate_dual_basis(shape::AbstractLagrangeFE)
    collect(0:order)
end

function generate_dual_basis(shape::ReferenceSquare, ::Type{LagrangeFE}, order::Int)
    # Lagrange elements in 2D have this type from the Pascals triangle
    #=        1
            x   y
          .  .  .  .
     x^m .  .  .  . y^m
        x^m*y    y^m*x
           .     .
             (xy)^m
    =#

    # This is an unreadable mess but it basically
    # calculates the exponents for x and y row by row
    # left to right...

    x, y = generators(MPoly{Float64}, :x, :y)

    P = zero(x)

    # Start exponent for x and y
    x_m = [0:order-1; (order-1) * ones(Int, order-1)]
    y_m = [zeros(Int, order-1); 0:order-1]

    # Length of row
    l = [1:order;order-1:-1:1]

    for i = 1:length(l), j in 0:l[i]-1
            P += x^(x_m[i] - j) * y^(y_m[i] + j)
    end

    return P

end


# These could be made much nicer and more general:


make_lattice(::ReferenceLine, ::Type{LagrangeFE}, order::Int) = linspace(-1,1, order)

function make_lattice(refele::ReferenceTriangle, ::Type{LagrangeFE}, order::Int)
    vs = vertices(refele)
    intervals = [ (vs[i] - vs[1]) / order for i in 2:length(vs)]

    edges = edges(refele)
    for edge in edges
        push!(points, vs[edge])
    end

    points = Array(Vector{Float64},0)
    for i in 0:order, j in 0:get_points_row(refele, order, i)
            push!(points, intervals[:,1] * j + i * intervals[:,2])
    end
    return points
end



function make_lattice(refele::ReferenceSquare, ::Type{LagrangeFE}, order::Int)
    order -= 1
    vs = vertices(refele)
    intervals = [(vs[2] - vs[1])/order  (vs[4] - vs[1])/order]
    x0 = [vs[1][1], vs[1][2]]

    points = Array(Vector{Float64},0)
    for i in 0:order, j in 0:order
            push!(points, x0 + intervals[:,1] * j + i * intervals[:,2])
    end
    return points
end



function make_lattice(refele::ReferenceTetrahedron, ::Type{LagrangeFE}, order::Int)
    vs = vertices(refele)
    intervals = [ (vs[i] - vs[1]) / order for i in 2:length(vs)]
    points = Array(Vector{Float64},0)
    for m in 0:order
        for i in 0:get_points_row(refele, order, m)
            for j in 0:get_points_row(refele, get_points_row(refele, order, m), i)
                push!(points, intervals[1] * j + i * intervals[2] + m * intervals[3])
            end
        end
    end

    return points
end

function make_lattice(refele::ReferenceCube, ::Type{LagrangeFE}, order::Int)
    order -= 1
    vs = vertices(refele)
    intervals = [(vs[2] - vs[1])/order  (vs[4] - vs[1])/order (vs[5] - vs[1])/order]
    x0 = [vs[1][1], vs[1][2], vs[1][3]]
    points = Array(Vector{Float64},0)
    for m in 0:order, i = 0:order, j=0:order
        push!(points, x0 + intervals[1] * j + i * intervals[2] + m * intervals[3])
    end
    return points
end