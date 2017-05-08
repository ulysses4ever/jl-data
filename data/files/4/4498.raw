### StringOrInteger - Abstract type union

typealias StringOrInteger Union{AbstractString, Integer}


### SnpData - SNP allele data, [ind x snp] array

typealias SnpData Matrix{Int8}
# code unphased, biallelic
#   0 = NA
#   1 = AA
#   2 = AB | BA
#   3 = BB


### LocusInfo - Locus attributes

type LocusInfo{
        S<:StringOrInteger,
        C<:StringOrInteger,
        T<:Integer,
        A<:StringOrInteger
    }
    
    locusid::Vector{S}
    chrom::Vector{C}
    pos::Vector{T}
    allele1::Vector{A}
    allele2::Vector{A}

end


### SnpMatrix - SNP data and information

type SnpMatrix{
        I<:StringOrInteger
    }
    
    data::SnpData
    locus::LocusInfo
    individual::Vector{I}
    
end