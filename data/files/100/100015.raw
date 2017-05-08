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
#	- HNF the convolution product SNF1 * SNF2
function hn_convolution(N::UInt64, P::UInt64, M::BigInt, HNF1::Array{BigInt, 1}, HNF2::Array{BigInt, 1})
  FFT1 = hn_fft(N, P, M, HNF1)
  FFT2 = hn_fft(N, P, M, HNF2)
  @assert length(FFT1) == length(FFT2)
  L = length(FFT1)
  product = Array(BigInt, L)
  while L != 0
    product[L] = (FFT1[L] * FFT2[L]) % M
    L -= 1
  end
  CONV = hn_ifft(N, P, M, product)
  return CONV
end
