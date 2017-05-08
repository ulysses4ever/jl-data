using Jacobi


type Basis2d
    Q::Int
    N::Int
    NB::Int
    NI::Int
    eindx::Array{Int,2}
    vindx::Array{Int,1}
    z::Array{Float64,1}
    w::Array{Float64,1}
    D::Array{Float64,2}
    t2bi_map::Array{Int,1}
    bi2t_map::Array{Int,1}

    function Basis2d(q::Int)
        n = q*q
        nb = 4*(q-1)
        ni = n - nb
        idx = reshape(1:n, q, q)
        eindx = zeros(Int, q, 4)
        eindx[:,1] = idx[:,1]
        eindx[:,2] = idx[q,:]
        eindx[:,3] = idx[:,q]
        eindx[:,4] = idx[1,:]
        vindx = [idx[1,1], idx[q,1], idx[q,q], idx[1,q]]
        
        z = Jacobi.zglj(q)
        w = Jacobi.wglj(z)
        D = Jacobi.dglj(z)
        m = zeros(Int, q*q)
        x = reshape(1:n,q,q)
        m[1] = x[1,1]
        m[2] = x[q,1]
        m[3] = x[q,q]
        m[4] = x[1,q]
        p = q-1
        if (q > 2)
            r = [1:(q-2)]
            nr = length(r)
            m[4+r] = x[2:p,1]
            m[4+nr+r] = x[q,2:p]
            m[4+2nr+r] = x[p:-1:2,q]
            m[4+3nr+r] = x[1,p:-1:2]
            m[(4+4nr+1):end] = reshape(x[2:p,2:p], (q-2)*(q-2))
        end
        m2 = zeros(Int,q*q)
        m2[m[1:n]] = [1:n]

        new(q, n, nb, ni, eindx, vindx, z, w, D, m, m2)
    end
end

nquad(b::Basis2d) = b.Q
nnodes(b::Basis2d) = b.z
weights(b::Basis2d) = b.w
diffmat(b::Basis2d) = b.D



mapt2bi(b::Basis2d, x) = x[b.t2bi_map]
mapt2b(b::Basis2d, x) = x[b.t2bi_map[1:b.NB]]
mapt2i(b::Basis2d, x) = x[b.t2bi_map[(b.NB+1):end]]
mapbi2t(b::Basis2d, xbi) = xbi[b.bi2t_map]

function mapt2bi!(b::Basis2d, x, xbi)
    m = b.t2bi_map
    for i = 1:b.N
        xbi[i] = x[m[i]]
    end
end

function mapt2b!(b::Basis2d, x, xbi)
    m = b.t2bi_map
    for i = 1:b.NB
        xbi[i] = x[m[i]]
    end
end

function mapt2i!(b::Basis2d, x, xi)
    m = b.t2bi_map
    for i = 1:b.NI
        xi[i] = x[m[i+b.NB]]
    end
end

function mapbi2t!(b::Basis2d, xbi, x)
    m = b.bi2t_map
    for i = 1:b.N
        x[i] = xbi[m[i]]
    end
end
    
using Mesh2d
import Base.LinAlg.BLAS
using Base.LinAlg.BLAS
using Devectorize
import Mesh2d
using Mesh2d

function deriv_a!(basis::Basis2d, r1, f, r2, da)
    gemm!('N', 'N', r1, basis.D, f, r2, da)
end

function deriv_a(basis::Basis2d, r1, f)
    da = Array(Float64,basis.Q, basis.Q)
    deriv_a!(basis, r1, f, 0.0, da)
    return da
end


function deriv_b!(basis::Basis2d, r1, f, r2, db)
    gemm!('N', 'T', r1, f, basis.D, r2, db)
end

function deriv_b(basis::Basis2d, r1, f)
    db = Array(Float64,basis.Q, basis.Q)
    deriv_b!(basis, r1, f, 0.0, db)
end



type Element2d

    Q::Int
    N::Int
    basis::Basis2d
    w::Array{Float64,1}
    z::Array{Float64,1}
    D::Array{Float64,2}
    x::Array{Float64,2}
    y::Array{Float64,2}
    dadx::Array{Float64,2}
    dady::Array{Float64,2}
    dbdx::Array{Float64,2}
    dbdy::Array{Float64,2}
    jac::Array{Float64,2}
    mass::Array{Float64,2}
    sjac::Array{Float64,2}
    smass::Array{Float64,2}
    nx::Array{Float64,2}
    ny::Array{Float64,2}
    curved::Bool

    function Element2d(basis::Basis2d)

        Q = basis.Q
        N = Q*Q
        w = basis.w
        z = basis.z
        D = basis.D
        x = zeros(Float64,Q,Q)
        y = zeros(Float64,Q,Q)
        dadx = zeros(Float64,Q,Q)
        dady = zeros(Float64,Q,Q)
        dbdx = zeros(Float64,Q,Q)
        dbdy = zeros(Float64,Q,Q)
        jac = zeros(Float64,Q,Q)
        mass = zeros(Float64,Q,Q)
        sjac = zeros(Float64,Q,4)
        smass = zeros(Float64,Q,4)
        nx = zeros(Float64,Q,4)
        ny = zeros(Float64,Q,4)
        curved = false
        
        new(Q, N, basis, w, z, D, x, y, dadx, dady, dbdx, dbdy,
            jac, mass, sjac, smass, nx, ny, curved)
    end
end

function Element2d(basis::Basis2d, quad::Mesh2d.Quad, crvs=[])

    el = Element2d(basis)
    element_setup(el, quad, crvs)
    return el
end

function standard_element(basis::Basis2d)

    el = Element2d(basis)
    Q = el.Q
    N = el.N

    el.jac[:] = 1.0
    el.dadx[:] = 1.0
    el.dady[:] = 0.0
    el.dbdx[:] = 0.0
    el.dbdy[:] = 1.0
    for i=1:Q, j=1:Q
        el.mass[j,i] = el.w[i]*el.w[j]
    end
    el.sjac[:] = 1.0

    for edge = 1:4, i=1:Q
        el.smass[i,edge] = el.w[i]
    end

    el.nx[:,1] = 0.0
    el.nx[:,2] = 1.0
    el.nx[:,3] = 0.0
    el.nx[:,4] = -1.0
    el.ny[:,1] = -1.0
    el.ny[:,2] = 0.0
    el.ny[:,3] = 1.0
    el.ny[:,4] = 0.0

    return el
end

function element_setup(el::Element2d, quad, crvs=[])
    # Calculate node coords:
    basis = el.basis
    node_coords(el.basis, quad, el.x, el.y, crvs)
    Q = el.Q
    x = el.x
    y = el.y
    el.curved = quad.curved

    dxda = Array(Float64, Q, Q)
    dyda = Array(Float64, Q, Q)
    dxdb = Array(Float64, Q, Q)
    dydb = Array(Float64, Q, Q)
        
    deriv_a!(basis, 1.0, x, 0.0, dxda)
    deriv_b!(basis, 1.0, x, 0.0, dxdb)
    deriv_a!(basis, 1.0, y, 0.0, dyda)
    deriv_b!(basis, 1.0, y, 0.0, dydb)
    
    @devec el.jac = dxda .* dydb .- dxdb .* dyda
    @devec el.dadx =  dydb ./ el.jac
    @devec el.dady = -dxdb ./ el.jac
    @devec el.dbdx = -dyda ./ el.jac
    @devec el.dbdy =  dxda ./ el.jac

    for i=1:Q, j=1:Q
        el.mass[j,i] = el.w[i]*el.w[j]*el.jac[j,i]
    end

    # Calculate surface parameters
    sjac = el.sjac
    # Surface Jacobian
    @devec el.sjac[:,1] = dxda[:,1] .* dxda[:,1] .+ dyda[:,1] .* dyda[:,1]
    @devec el.sjac[:,2] = dxdb[Q,:] .* dxdb[Q,:] .+ dydb[Q,:] .* dydb[Q,:]
    @devec el.sjac[:,3] = dxda[:,Q] .* dxda[:,Q] .+ dyda[:,Q] .* dyda[:,Q]
    @devec el.sjac[:,4] = dxdb[1,:] .* dxdb[1,:] .+ dydb[1,:] .* dydb[1,:]
    
    @devec el.sjac = sqrt(el.sjac)

    for edge = 1:4, i=1:Q
        el.smass[i,edge] = el.w[i]*el.sjac[i,edge]
    end

    # Compute normals:
    xv = quad.verts[:,1]
    yv = quad.verts[:,2] 
    icrv = quad.curve
    vine = [1 2 3 4; 2 3 4 1]
    for edge = 1:4
        ei = sub(basis.eindx, :, edge)
        v1 = vine[1,edge]
        v2 = vine[2,edge]
        icrv = quad.curve[edge]
        if icrv == 0
            nxy = Mesh2d.normal(xv[v1], yv[v1], xv[v2], yv[v2])
            for i = 1:Q
                el.nx[i,edge] = nxy[1]
                el.ny[i,edge] = nxy[2]
            end
        else
            for i = 1:Q
                el.nx[i,edge], el.ny[i, edge] = Mesh2d.normal(crvs[icrv], x[ei[i]], y[ei[i]])
            end
        end
    end
end


function node_coords(b::Basis2d, mshel, x, y, crvs)
    Q = b.Q
    N = b.N
    z = b.z
    xv = mshel.verts[:,1]
    yv = mshel.verts[:,2] 
    icrv = mshel.curve
    vine = [1 2 4 1; 2 3 3 4]
    for edge = 1:4
        ei = sub(b.eindx, :, edge)
        v = vine[:,edge]
        if icrv[edge] == 0
            x[ei], y[ei] = Mesh2d.coords(z, xv[v[1]], yv[v[1]], xv[v[2]], yv[v[2]], true)
        else
            x[ei], y[ei] = Mesh2d.coords(crvs[icrv[edge]], z, xv[v[1]], yv[v[1]],
                          xv[v[2]], yv[v[2]],  true)
        end
    end
    
    Mesh2d.gordon_hall(x, y, z)
end

function deriv_x!(el::Element2d, f, dx, ws)
    b = el.basis
    deriv_a!(b, 1.0, f, 0.0, dx)
    deriv_b!(b, 1.0, f, 0.0, ws)
    for i = 1:length(f)
        dx[i] = dx[i] * el.dadx[i] + ws[i] * el.dbdx[i]
    end
end

function deriv_x(el::Element2d, f)
    
    local ws = similar(f)
    dx = similar(f)
    println(dx)
    deriv_x!(el, f, dx, ws)
    return dx
end



function deriv_y!(el::Element2d, f, dy, ws)
    b = el.basis
    deriv_a!(b, 1.0, f, 0.0, dy)
    deriv_b!(b, 1.0, f, 0.0, ws)
    for i = 1:length(f)
        dy[i] = dy[i] * el.dady[i] + ws[i] * el.dbdy[i]
    end
end

function deriv_y(el::Element2d, f)
    
    ws = similar(f)
    dy = similar(f)
    deriv_y!(el, f, dy, ws)
    return dy
end

function deriv_y(el::Element2d, f)
    
    b = el.basis
    Q = el.Q
    dy = deriv_a(b, 1.0, f)
    @devec dy = dy .* el.dady
    
    ws = deriv_b(b, 1.0, f)
    @devec dy = ws .* el.dbdy .+ dy

    return dy
end

function gradient!(el::Element2d, f, dx, dy)
    Q = el.Q
    da = zeros(Q,Q)
    db = zeros(Q,Q)

    deriv_a!(el.basis, 1.0, f, 0.0, da)
    deriv_b!(el.basis, 1.0, f, 0.0, db)

    for i = 1:el.N
        dx[i] = da[i] * el.dadx[i] + db[i] * el.dbdx[i]
        dy[i] = da[i] * el.dady[i] + db[i] * el.dbdy[i]
    end
end

function gradient(el::Element2d, f)
    Q = el.Q
    dx = zeros(Q,Q)
    dy = zeros(Q,Q)

    gradient!(el, f, dx, dy)

    return dx, dy
end


    


function laplace_matrix(elem::Element2d)
    Q = elem.Q
    N = elem.N
    L = zeros(Q,Q,Q,Q)
    A = zeros(Q,Q)

    D = elem.D
    m = elem.mass
    
    for i = 1:N
        A[i] = m[i] * (elem.dadx[i]*elem.dadx[i] + elem.dady[i]*elem.dady[i])
    end
    B = zeros(Q,Q)
    for i = 1:N
        B[i] = m[i] * (elem.dbdx[i]*elem.dbdx[i] + elem.dbdy[i]*elem.dbdy[i])
    end
    C = zeros(Q,Q)
    for i = 1:N
        C[i] = m[i] * (elem.dadx[i]*elem.dbdx[i] + elem.dady[i]*elem.dbdy[i])
    end
    for k = 1:Q
        for l = 1:Q
            for p = 1:Q
                for r = 1:Q
                    L[p,k,r,k] += A[l,k] * D[l,p] * D[l,r]
                    L[l,p,l,r] += B[l,k] * D[k,p] * D[k,r]
                    L[l,p,r,k] += C[l,k] * D[k,p] * D[l,r]
                    L[p,k,l,r] += C[l,k] * D[l,p] * D[k,r]
                end
            end
        end
    end
    return reshape(L,N,N)

end



    
    