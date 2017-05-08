include("/home/jeb/Teaching/Research/Thermodynamics/eclipse-julia/HnFFTFp/src/FFT.jl")
include("/home/jeb/Teaching/Research/Thermodynamics/eclipse-julia/HnFFTFp/src/IFFT.jl")
include("/home/jeb/Teaching/Research/Thermodynamics/eclipse-julia/HnFFTFp/src/Convolution.jl")
include("/home/jeb/Teaching/Research/Thermodynamics/eclipse-julia/HnFFTFp/src/FastExp.jl")
# Demonstrates DH on Hn
# Parameters:
#	N::UInt64
#	- the dimension of Hn
# P:: UInt64
# - the size of Hn
#	M::BigInt
#	- the module
# Return
#	Nothing
function testDH(N::UInt64, P::UInt64, M::BigInt)
  println("> Diffie-Hellman test")
	alpha = zeros(BigInt, P)
	sum = 0
        for i = 2:P
          alpha[i] = big(rand(0:M-1))
          sum += alpha[i]
        end
        alpha[1] = -sum
        alpha = (alpha % M + M) % M
	s = big(13282872494219432555878943284284)
	t = big(19312894329423948992394329348438)
	t1 = time()
	publicAlice = fastExp(N, P, M, alpha, s)
	publicBob = fastExp(N, P, M, alpha, t)
  privateAlice = fastExp(N, P, M, publicBob, s)
	privateBob = fastExp(N, P, M, publicAlice, t)
  t2 = time()
	@assert maximum(abs(privateAlice -privateBob)) == 0
	println("> elapsed time: ", t2-t1, " s")
	println("> success")
end

testDH(UInt64(10), UInt64(1024), big(32416190071)) # 154.66 s
