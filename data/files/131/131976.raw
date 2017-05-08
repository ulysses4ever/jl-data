
abstract LinearSolver


abstract StaticCondensation <: LinearSolver
abstract DirectStaticCondensation <: StaticCondensation


type CholeskySolver <: DirectStaticCondensation

    bmap::Array{Int,2}
    nel::Int
    nb::Int
    nbslv::Int
    
    nbe::Int
    nie::Int
    
    Abb::Array{Float64,2}
    Aii::Array{Float64,2}
end

function sym2pckd!(A, AP, uplo='L')
    n = size(A,1)
    np = div(n*(n+1),2)
        
    AP = zeros(eltype(A), np)

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



    
#function add_matrix(solver::CholeskySolver, Abb, Aib, Aii, is_dirichilet)

    
