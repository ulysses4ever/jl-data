abstract AbstractFiniteElement

abstract AbstractLagrangeFE

#type LagrangeFE{T <: AbstractReferenceElement}
#    ref_shape::T
#    basis::PolyBasis
#end

#get_coeff(LFE::LagrangeFE, i::Int) = LFE.basis[:, i]
#get_coeffs(LFE::LagrangeFE, i::Int) = LFE.basis[:, i]


function generate_basis_vectors(shape::AbstractReferenceElement_1D)
    collect(0:order)
end

function generate_basis_vectors(shape::AbstractReferenceElement_2D, order::Int)
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

    x = Array(Int, order^2)
    y = Array(Int, order^2)

    # Start exponent for x and y
    x_m = [0:order-1; (order-1) * ones(Int, order-1)]
    y_m = [zeros(Int, order-1); 0:order-1]

    # Length of row
    l = [1:order;order-1:-1:1]

    count = 1
    for i = 1:length(l)
        for j in 0:l[i]-1
            x[count] = x_m[i] - j
            y[count] = y_m[i] + j
            count += 1
        end
    end

    return (x, y)

end


function LagrangeFE(shape::AbstractReferenceElement, order::Int)
    points = make_lattice(shape)

    # Gets the coefficients for the standard monomial basis
    # for a given point x
    fedim = dim(shape)

    #P = PolyBasis{fedim}

    x, y = generate_basis_vectors(shape)
    P = PolyBasis2d(x, y)

    V= zeros()
    for (i, p) in enuermate(points)
        V(:, i) = evaluate(P(p))
    end




    # Lagrange coefficients for can be found by inverting
    # the Vandermonde matrix
    C = inv(V)



    # Find basis from dimension and order
end

abstract AbstractBasis{DIM}

type PolyBasis1d <: AbstractBasis{1}
    x_exponents::Vector{Int}
end

get_exponents(lgb::PolyBasis1d, i::Int) = lgb.x_exponents[i]

function evaluate(lgb::PolyBasis1d, x::Vector{Float64})
    assert(length(x) == 1)
    return [x[1]^q for q in 0:length(x_exponents)-1]
end


type PolyBasis2d <: AbstractBasis{2}
    x_exponents::Vector{Int}
    y_exponents::Vector{Int}
end

get_exponents(lgb::PolyBasis2d, i::Int) = (lgb.x_exponents[i], lgb.y_exponents[i])

function evaluate(lgb::PolyBasis2d, x::Vector{Float64})
    assert(length(x) == 2)
    v = zeros(length(lgb.x_exponents))
    for i in 1:length(lgb.x_exponents)
        p, q = get_exponents(lgb, i)
        v[i] = x[1]^p * x[2]^q
    end
    return v
end

type PolyBasis3d <: AbstractBasis{3}
    x_exponents::Vector{Int}
    y_exponents::Vector{Int}
    z_exponents::Vector{Int}
end
get_exponents(lgb::PolyBasis3d, i::Int) = (lgb.x_exponents[i], lgb.y_exponents[i], lgb.z_exponents[i])


function evaluate(lgb::PolyBasis3d, x::Vector{Float64})
    assert(length(x) == 3)
    for i in 1:length(lgb.e_exponents)
        p, q, r =  get_exponents(lgb , i)
        v[i] = x[1]^p * x[2]^q * x[3]^r
    end
    return v
end

