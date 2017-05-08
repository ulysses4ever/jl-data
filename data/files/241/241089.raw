using MUMPSseq
using Base.Test

srand(1234321)
a = sprand(50,50,0.03)
ata = a'a + speye(50)
ff = DMumpssv(ata)  # create the factorization
rr = ones(50)
A_ldiv_B!(ff,rr)
@test_approx_eq ata*rr ones(50)


