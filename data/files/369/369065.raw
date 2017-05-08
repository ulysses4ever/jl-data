using MathToolkit
using Base.Test

@test recvec([1,2,3,4,5,6,7,8,9,10]) == [1,-2,1]
@test recvec([0,1,1,2,3,5,8,13], output=Float64) == [1.0,-1.0,-1.0]
@test recvec([2^k for k=0:7], compute=Int128) == [1,-2]
@test recvec([1//2^k for k=0:7], compute=Int128, output=Float64) == [2.0,-1.0]
@test recvec([1]) == []
@test recvec([1,2,3,4,5,6,7,8,9,10,42]) == []
