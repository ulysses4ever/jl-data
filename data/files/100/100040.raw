include("/home/jeb/Teaching/Research/Thermodynamics/eclipse-julia/HnFFTFp/src/FFT.jl")
include("/home/jeb/Teaching/Research/Thermodynamics/eclipse-julia/HnFFTFp/src/IFFT.jl")
include("/home/jeb/Teaching/Research/Thermodynamics/eclipse-julia/HnFFTFp/src/Convolution.jl")

# Parameters:
#	N::UInt64
#	- the dimension of Hn
# P:: UInt64
# - the size of Hn
#	M::Int64
#	- the module
#	HNF1::Array{BigInt, 1}
#	- HNF1[i] is the value associated with the vertex i of Hn
#	HNF2::Array{BigInt, 1}
#	- HNF2[i] is the value associated with the vertex i of Hn
# Return Values:
#	HNF::Array{Int, 1}
#	- HNF the standard convolution product SNF1 * SNF2 on Hn

function st_convolution(N::UInt64, P::UInt64, M::BigInt,  HNF1::Array{BigInt, 1}, HNF2::Array{BigInt, 1})
  CONV = zeros(BigInt, P)
    for i = UInt64(0):P-1
      for j = UInt64(0):P-1
        CONV[i+1] = (CONV[i+1] + (HNF1[(i $ j) + 1] * HNF2[j+1])) % M
      end
    end
    return (CONV + M) % M
  end

# Demonstrates fast convolution and standard convolution deliver the same result
# Parameters:
#	N::UInt64
#	- the dimension of Hn
#	P::UInt64
#	- the size of Hn
#	M::Int
#	- the module
# Return
#	Nothing
function testConvolution(N::UInt64, P::UInt64, M::BigInt)
  println("> convolution test")
	alpha = zeros(BigInt, P)
	beta = zeros(BigInt, P)
	c2 = zeros(Int, P)
        for i = 1:P
          alpha[i] = (big(rand(Int)) % M + M) % M
          beta[i] = (big(rand(Int)) % M + M) % M
        end
	c1 = hn_convolution(N, P, M, alpha, beta)
	# standard slow convolution
  c2 = st_convolution(N, P, M, alpha, beta)
	@assert maximum(abs(c1-c2)) == 0
  println("> sucess")
end

testConvolution(UInt(4), UInt(16), big(997))
