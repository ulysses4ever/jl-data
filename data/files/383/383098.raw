using Distributions

function dimensionReductionMatrix(C,maxLoss=0.01)
     # maxLoss=0.01 # percentage of the average sumsq
    d,R=eig(C)
    D=diagm(d)
    # C = R*D*R'
    cs=flipdim(cumsum(flipdim(d,1)),1)
    i=length(cs)
    while cs[i]<(1-maxLoss)*cs[1] && i>1 # cs[1] = sum
        i-=1
    end
    T = (R')[i:end,:]
    return T
end


function testDimensionReduction()

    M=randn(10,4)+5*ones(10,4)
    C=M'*M
    T=dimensionReductionMatrix(C)
    x=rand(MvNormal(zeros(4),C))
    hatX=T\(T*x) # reconstruction from projection
    println(x)
    println(hatX)
end

