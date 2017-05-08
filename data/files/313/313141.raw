eigmaxreal(A::Matrix) = eigs(A,nev=1,which = :LR)[1][1]
eigminreal(A::Matrix) = eigs(A,nev=1,which = :SR)[1][1]
allpositive(x::Vector{Float64}) = all(x_i->x_i>0,x)
