module RandomBandedMatrices
    using Base,RandomMatrices


export bandchi


bandchi(σ,v::Vector)=SymTridiagonal(σ*randn(length(v)+1),[RandomMatrices.chi(vk) for vk in v])
bandchi(v::Vector)=bandchi(1,v)
bandchi(n::Integer)=bandchi(ones(n))

end #module
