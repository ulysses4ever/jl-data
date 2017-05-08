type OCCAVector{T<:Number}
    dev::OCCA.Device;
    devmem::OCCA.Memory;
    hostmem::Vector{T};
    devflag::OCCADevFlag;
end

function OCCAVector{T}(dev::OCCA.Device,v::Array{T})    
    hostmem=copy(v);
    devmem =OCCA.malloc(dev,hostmem);
    flag   =OCCADevFlag(onhost);
    return OCCAVector(dev,devmem,hostmem,flag);
end
