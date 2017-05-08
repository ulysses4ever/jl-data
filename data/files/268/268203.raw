module RandomBandedMatrices
    using Base,RandomMatrices


export bandchi,bandGOE


bandchi(σ,v::Vector)=SymTridiagonal(σ*randn(length(v)+1),[RandomMatrices.chi(vk) for vk in v])
bandchi(v::Vector)=bandchi(1,v)
bandchi(n::Integer)=bandchi(ones(n))

function bandGOE(σ,n,m)
    i=[1:n;]
    j=[1:n;]
    r=σ*randn(n)
    for k=2:m+1
        i=[i;1:n-k+1;k:n]
        j=[j;k:n;1:n-k+1]
        rs=randn(n-k+1)
        r=[r;rs;rs]
    end
    sparse(i,j,r)
end


end #module
