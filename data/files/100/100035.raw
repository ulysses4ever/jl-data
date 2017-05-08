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
#	IFFT::Array{BigInt, }
#	- FFT is the Fast Fourier Transform of HNF
function hn_ifft(N::UInt64, P::UInt64, M::BigInt, FFT::Array{BigInt, 1})
  IFFT = deepcopy(FFT)
  m1 = UInt64(1)
  for i = UInt64(1):N
    m2 = m1 << 1
    j = UInt64(0)
    for j = UInt(0):m2:P - 1
      for k = j:j + m1 - 1
        u = IFFT[k+1]
        v = IFFT[k + m1+1]
        IFFT[k+1] = ((u + v) * invmod(big(2), M)) % M
        IFFT[k + m1+1] = ((u - v) * invmod(big(2), M)) % M
      end
    end
    m1 <<= 1
  end
  return (IFFT + M) % M
end
