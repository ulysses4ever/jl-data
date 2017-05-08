### SnpData - SNP allele data, [ind x snp] array

typealias SnpData Matrix{Int8}


### SnpInfo - SNP information

type SnpInfo{
        S<:Union{AbstractString, Integer}, 
        C<:Union{AbstractString, Integer}, 
        T<:Integer,
        A<:Union{AbstractString, Integer} 
    }
    
    snpid::Vector{S}
    chrom::Vector{C}
    pos::Vector{T}
    allele0::Vector{A}
    allele1::Vector{A}

end


### SnpMatrix - SNP data and information

type SnpMatrix
    
    data::SnpData
    info::SnpInfo
    # is the data phased or not (=unphased)
    phased::Bool
    
end