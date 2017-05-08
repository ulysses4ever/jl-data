# LU decomposition (without pivoting)

n = 6
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
# applies only to a symmetric real matrix with positive leading minors
# equiv: matrix of the form M M' where diag(M) > 0

n = 6
M = rand(n,n)
for i in 2:n	M[i-1,i:n] = 0	end
M = M * M'

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


# QR / Gram Schmidt

n = 8
r = 4
M = rand(n,r)
Q = zeros(n,r)
R = zeros(r,r)
for i in 1:r
  s = 0
  for j in 1:(i-1)
	R [j,i] = dot (Q [1:n,j], M [1:n,i])
    s = s + R [j,i] * Q [1:n,j]
    end
  R [i,i] = norm (M [1:n,i] - s)
  Q [1:n,i] = (M [1:n,i] - s) / R [i,i]
  end
