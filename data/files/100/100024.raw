# Parameters:
#	N::UInt64
#	- the dimension of Hn
#	P::UInt64
#	- the size of Hn
#	M::BigInt
#	- the module
#	SNF::Array{BigInt, 1}
#	- SNF[i] is the value associated with the vertex i of Hn
# E::Int
# - the exponent
# Return Values:
#	SNF1::Array{BigInt, 1}
#	- ISNF the convolution product SNF1 * SNF2
function fastExp(N::UInt64, P:: UInt64, M::BigInt, SNF::Array{BigInt, 1}, E::BigInt)
  FEXP = zeros(BigInt, P)
  t = zeros(BigInt, P)
  for i = 1:P
    t[i] = SNF[i]
  end
  Id = zeros(Int, N)
  for i = 1:N
    Id[i] = i
  end
  FEXP[1] = big(1)
  while  E > 0
    if E % 2 == 1
      u = hn_convolution(N, P, M, FEXP, t)
      E -= 1
      for i = 1:P
        FEXP[i] = u[i]
      end
    end
    u = hn_convolution(N, P, M, t, t)
    for i = 1:P
      t[i] = u[i]
    end
    E /= 2
  end
  return FEXP
end
