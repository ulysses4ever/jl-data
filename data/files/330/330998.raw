module RandomBandedMatrices
    using Base,RandomMatrices


export bandchi,bandGOE


bandchi(σ,v::Vector)=SymTridiagonal(σ*randn(length(v)+1),[RandomMatrices.chi(vk) for vk in v])
bandchi(v::Vector)=bandchi(1,v)
bandchi(n::Integer)=bandchi(ones(n))

function bandGOE(n,m)
    A=zeros(n,n)
    for k=1:n
        A[k,k]=2randn()
    end
    for k=2:m,j=1:n-k+1
        r=randn()
        A[j,j+k-1]=r
        A[j+k-1,j]=r
    end
    A
end


end #module
