using Distributions

function computeCovariance()
    # provisoire
    M=randn(10,4)+100*ones(10,4)
    return M'*M
end


function dimensionReductionMatrix(C)
    maxLoss=0.1 # percentage of the sumsq
    d,R=eig(C)
    D=diagm(d)
    # C = R*D*R'
    cs=flipdim(cumsum(flipdim(d,1)),1)
    i=2
    while cs[i]>(1-maxLoss)*cs[1] && i<length(cs)# cs[1] = sum
        i+=1
    end
    i-=1

    T = (R')[i:end,:]
    return T
end


function testDimensionReduction()
C=computeCovariance()
T=dimensionReductionMatrix(C)
x=rand(MvNormal(zeros(4),C))
    hatX=T\(T*x) # reconstruction from projection
    println(x)
    println(hatX)
end


