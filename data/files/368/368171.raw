using Base.Test
using BlackScholes

tol = 1.0e-6
@test_approx_eq_eps(BSCall(10.0,10.0,0.15,0.0323,7.0,0.02),1.699938,tol)
@test_approx_eq_eps(BSPut(10.0,10.0,0.15,0.0323,7.0,0.02),0.982739,tol)

@test BSImpliedVol(10.0,10.0,0.0323,7.0,0.02,BSCall(10.0,10.0,0.55,0.0323,7.0,0.02),true) == 0.55
@test BSImpliedVol(10.0,10.0,0.0323,7.0,0.02,BSPut(10.0,10.0,0.55,0.0323,7.0,0.02),false) == 0.55

@test BSImpliedVol(10.0,10.0,0.0323,7.0,0.02,BSCall(10.0,10.0,0.55,0.0323,7.0,0.02),true) == 0.55
