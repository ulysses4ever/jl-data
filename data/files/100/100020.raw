# Parameters:
#	N::UInt64
#	- the dimension of Hn
# P:: UInt64
# - the size of Hn
#	M::Int
#	- the module
#	HNF::Array{BigInt, 1}
#	- HNF[i] is the value associated with the vertex i of Hn
# Return Value:
#	FFT::Array{BigInt, }
#	- FFT is the Fast Fourier Transform of HNF
function hn_fft(N::UInt64, P::UInt64, M::BigInt, HNF::Array{BigInt, 1})
  # FFT = SharedArray(BigInt,P)
  FFT = deepcopy(HNF)
  m1 = UInt64(1)
  for i = UInt64(1):N
    m2 = m1 << 1
    for j = UInt64(0):m2:P - 1
      for k = j:j + m1 -1
        u = FFT[k+1]
        v = FFT[k + m1+1]
        FFT[k+1] = (u + v) % M
        FFT[k + m1+1] = (u - v) % M
      end
    end
    m1 <<= 1
  end
  return (FFT + M) % M
end
