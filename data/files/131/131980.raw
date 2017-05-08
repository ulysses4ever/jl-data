
abstract LinearSolver


abstract StaticCondensation <: LinearSolver
abstract DirectStaticCondensation <: StaticCondensation


type CholeskySolver <: DirectStaticCondensation

    nel::Int
    nb::Int
    nbslv::Int
    
    neb::Int
    nei::Int
    
    A::Array{Float64,2}
    Aii::Array{Float64,2}
    X::Array{Float64,3}
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
    
