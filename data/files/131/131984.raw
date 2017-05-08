using Base.LinAlg.LAPACK.getrf!
using Base.LinAlg.LAPACK.getrs!
using Base.LinAlg.BLAS.gemm!
using Base.LinAlg.BLAS.gemv!
using ArrayViews

abstract LinearSolver


abstract StaticCondensation <: LinearSolver
abstract DirectStaticCondensation <: StaticCondensation


type CholeskySolver <: DirectStaticCondensation

    nel::Int
    nb::Int
    nbslv::Int
    bwd::Int
    
<<<<<<< HEAD
    nbe::Int
    nie::Int

    A2::Array{Float64, 2}
    X::Array{Float64,3}
    iAii::Array{Float64,2}

    function CholekySolver(bmap::Array{Int,2}, nb, nbslv, Q)
        nel = size(bmap,2)
        bwd = bandwidth(bmap, nbslv)

        nbe = 4 + 4*(Q-2)
        nie = Q*Q-nbe

        A2 = zeros(bwd+1, nbslv)
        X = zeros(nie, nbe, nel)
        iAii = zeros(div(nie*(nie+1),2), nel)
        new(bmap, nel, nb, nbslv, bwd, nbe, nie, A2, X, iAii)
    end
=======
    neb::Int
    nei::Int
    
    A::Array{Float64,2}
    Aii::Array{Float64,2}
    X::Array{Float64,3}
>>>>>>> ef030efb9656085dd4f7e05f695cbdb6bdca1eb0
end


         
function sym2pckd!(A, AP, uplo='L')
    n = size(A,1)
    np = div(n*(n+1),2)
        
    #AP = zeros(eltype(A), np)

    if uplo=='U' 
        count = 1
        for i = 1:n
            for j = 1:i
                AP[count] = A[j,i]
                count += 1
            end
        end
    else
        count = 1
        for i = 1:n
            for j = i:n
                AP[count] = A[i,j]
                count += 1
            end
        end
    end

    return AP
end



using ArrayViews
using XLAPACK
using Base.LinAlg.BLAS
function add_matrix(solver::CholeskySolver, bmap, e, Abb, Aib, Aii)


    Aiip = view(solver.Aii, :, e)
    sym2pckd!(Aii, Aiip, 'L')
    pptrf!('L', Aiip)
    X = view(solver.X, :, :, e)
    
    copy!(X, Aib)
    pptrs!('L', Aiip, X)

    gemm!('T', 'N', -1.0, Aib, X, 1.0, Abb)

    assemble(solver, Abb)
    
<<<<<<< HEAD
function add_matrix(solver::CholeskySolver, e, Abb, Aib, Aii)

    
    iAii = view(solver.iAii, :, e)
    X = view(solver.X, :, :, e)
    
    sym2pckd!(Aii, iAii, 'L')

    tmp,info = pptrf!('L', iAii)

    copy!(X, Aib)
    
    pptrs!('L', iAii, X)

    
    gemm!('T', 'N', -1.0, X, Aib, 1.0, Abb)
    
    assemble(solver, e, Abb)
end


function assemble(solver::ChokeskySolver, e, Ae)
=======
>>>>>>> ef030efb9656085dd4f7e05f695cbdb6bdca1eb0

end


function assemble(solver::ChokeskySolver, bmap, A)

    nei = solver.nei
    neb = solver.neb
    Ag = solver.A
    nbslv = solver.nbslv
    for i = 1:neb
        ig = bmap[i]
        if ig > nbslv
            continue
        end
        for k = 1:neb
            kg = bmap[k]
            if kg <= nbslv && kg >= ig
                if (kg >= ig)
                    Ag[kg-ig+1][ig] += A[k, i]
                end
            end
        end
    end

end
    
    bm = view(solver.bmap, :, 2)
    nbe = solver.nbe
    
    for i = 1:nbe
        ig = bm[i]
        if ig <= nblsv
            for j = 1:nbe
                jg = bm[j]
                if jg >= ig
                    solver.A2[ig, jg-ig+1] += A[j,i]
                end
            end
        end
    end

end

function trf(solver::CholeskySolver)

    pbtrf('L', solver.bwd, solver.A2)

end


function static_cond(solver::CholeskySolver, e, fbi)

    nbe = solver.nbe
    nbi = solver.nie
    
    fb = view(fbi, 1:nbe)
    fi = view(fbi, (nbe+1):(nbe+nie))

    gemv('T', -1.0, view(solver.X, :, :, e), fi, 1.0, fb)
    
end

function solve!(solver::Cholesky, xbi)

    bmap = solver.bmap
    nbslv = solver.nbslv
    bwd = solver.bwd
    
    xb = view(xbi, 1:nbslv)
    pbtrs!('L', solver.bwd, solver.A2, xb)

    #xbie = zeros(solver.nbe
