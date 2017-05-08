using TallSkinnyQR
using Base.Test

# write your own tests here
include("test_helpers.jl")

# Check if TSQR is working ok
A = gencond(1e8,1000,20)
A2 = convert(SharedArray,A)
Q,R = tsqr!(A2)
Q = constructQ!(Q)

@test norm(Q'*Q-eye(20,20)) < 1e-12
@test norm(A-Q*R)/norm(A) < 1e-12

# Check if B-orthogonal routines are working ok
A,C,M = make_acm(1000,20)
B = spgenband(1000,3)
res,orth = get_orthres(A,B,C,M,4,false)

@test all(res.<1e-12)
@test all(orth.<1e-12)

