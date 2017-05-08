using Genetics
using Base.Test

si = LocusInfo(["1"; "2"], [1; 1], [Int8(1); Int32(2)], [1; 1], [2; 2])

@test typeof(si.locusid[1]) <: AbstractString
@test typeof(si.chrom[1]) <: Integer
@test typeof(si.pos[1]) <: Integer
@test typeof(si.allele1[1]) <: Integer
@test typeof(si.allele2[1]) <: Integer
