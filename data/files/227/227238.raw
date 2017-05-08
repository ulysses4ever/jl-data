# LU decomposition without pivoting

n=6
M = rand(n,n)
L = zeros(n,n)
U = zeros(n,n)

A = M
for j in 1:(n-1)
  L [j,j] = 1
  L [(j+1):n,j] = A [(j+1):n,j] / A [j,j]
  L [j,(j+1):n] = 0
  U [j,j] = A[j,j]
  U [(j+1):n,j] = 0
  U [j,(j+1):n] = A [j,(j+1):n]
  A [(j+1):n,(j+1):n] = A [(j+1):n,(j+1):n] - A [(j+1):n,j] * A [j,(j+1):n] / A [j,j]
  end

L [n,n] = 1
U [n,n] = A [n,n]


# Cholesky decomposition

n=6
M = rand(n,n)
M = M + M'			# applies only to a symmetric real matrix !! with positive leading minors

C = zeros(n,n)
for i in 1:n
  s = 0
  for j in 1:(i-1)	s = s + C[i,j] ^ 2	end
  C [i,i] = sqrt (M [i,i] - s)
  for k in (i+1):n
    s = 0
    for j in 1:(i-1)	s = s + C [i,j] * C [k,j]	end
    C [k,i] = (M [k,i] - s) / C [i,i]
    end
  end
C


