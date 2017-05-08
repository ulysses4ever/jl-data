##  PROBLEM THREE -- BACK SUBSTITUTION

n=40					# parameter

A=zeros(n,n)			# define matrix A
for i in 1:(n-1)
	A[i,i]=1
	A[i,i+1]=2
	end
A[n,n]=1
A

b=ones(n)					# define rhs b
b[n]=1//3
b

x = Array (Float64, n)			# general purpose backsolver
x [n] = b [n] / A [n, n]
for i in linspace (n-1, 1, n-1)
	x[i] = (b [i] - dot (reshape (A [i, (i+1):n], n-i), x [(i+1):n])) / A[i,i]
	end

A*x - b								# ways to estimate size of error -- this is zero!
A[1,:] * x ; x[1] + 2 * x[2]			# both 1.0
x - 1//3 ; x - 1.0/3.0					# these two give same result


