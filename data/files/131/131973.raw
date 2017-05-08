
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

    A::Array{Float64,2}
end

