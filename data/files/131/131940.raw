export Basis1d, Element1d

type Basis1d
    Q::Int
    z::Array{Float64,1}
    w::Array{Float64,1}
    D::Array{Float64,2}
    
    function Basis1d(q::Int)
        Q = q
        z = zeros_glj(Q, T=Float64)
        w = weights_glj(z)
        D = diffmat_glj(z)
        new(Q, z, w, D)
    end
end

type Element1d

    basis::Basis1d
    Q::Int
    dx::Float64
    x::Array{Float64,1}
    dzdx::Float64
    jac::Float64
    mass::Array{Float64,1}

    function Element1d(b::Basis1d, xnodes::Array{Float64,1})
        basis = b
        Q = b.Q
        dx = xnodes[2] - xnodes[1]
        x = (1-b.z)/2 * xnodes[1] + (1+b.z)/2 * xnodes[2]
        dzdx = 2 / dx
        jac = dx / 2
        mass = jac * basis.w
        new(basis, Q, dx, x, dzdx, jac, mass)
    end
        
end

using Base.LinAlg.BLAS

function deriv_z(elem::Element1d, f::Array{Float64,1})
    elem.basis.D * f
end

function deriv_x(elem::Element1d, f::Array{Float64,1})
    elem.dzdx * deriv_z(elem, f)
end

function convective(elem::Element1d, f::Array{Float64,1}, u::Array{Float64,1})

    udf = deriv_x(elem, f)
    for i::Int = 1:elem.Q
        udf[i] *= u[i]
    end
    return udf
end

function integrate(elem::Element1d, f::Array{Float64,1})

    dot(elem.mass, f)
end

function laplace_matrix(elem::Element1d)

    local Q::Int = elem.Q, i::Int, j::Int

end
    