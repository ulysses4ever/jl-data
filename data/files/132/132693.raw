#!/usr/bin/env julia

type Genotype
    a::Char
    b::Char
    freq::Int

    Genotype(gt::String,freq) = length(gt)==2 ? Genotype(gt[1],gt[2],freq) : nothing
    Genotype(a,b,freq) = new(a,b,freq)
end

function getFreqs(gts::Array{Genotype})
    alleleSums = Dict{Char,Int}()
    
    total = 0
    for gt in gts
        for allele in [gt.a, gt.b]
            total += gt.freq
            if has(alleleSums, allele)
                alleleSums[allele] += gt.freq
            else
                alleleSums[allele] = gt.freq
            end
        end
    end
    
    alleleFreqs = Dict{Char,Float64}()
    
    for allele in keys(alleleSums)
        alleleFreqs[allele] = alleleSums[allele] / total
    end
    
    alleleFreqs
end

sif = [Genotype("SS",12), Genotype("II",21), Genotype("FF",60), Genotype("SI",34), Genotype("SF",46), Genotype("IF",77)]

println(getFreqs(sif))