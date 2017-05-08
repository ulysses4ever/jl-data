module RandomTestMatrices

export randsym, randantisym, randposdef, randstable, randnormal, randorth, randunitary

#=

Random test matrices. These are for testing and debugging purposes, for random matrix ensembles with known limiting distributions, see the package RandomMatrices.jl . 

=#


"""
randsym(d)
             
	Gaussian random symmetric matrix of dimension ``d``.
"""	
function randsym(d)
    y = randn(d, d) 
	triu(y) + triu(y,1)' 
end


"""
randantisym(d)

    Anti symmetric matrix
"""
function randantisym(d)
	y = randn(d, d) 
	triu(y,1) - triu(y,1)' 
end


"""
randposdef(d, n = d)
             
	Random positive definite matrix of dimension ``d`` from the Laguerre ensemble ``n``. 
"""
function randposdef(d,n = d)
	x = randn(d, n) 
	x'* x/n
end

"""
randstable(d)
             
	Random stable matrix (matrix with eigenvalues with negative real part) with dimension ``d``.
"""
function randstable(d)
	# positive definite matrix
	x = randn(d, d) 
	a = x'*x/d 
	
	# antisymmetric matrix
	b = randantisym(d)
	
	# return stable matrix
	b - a
end

"""
randunitary(d)
             
	Random unitary matrix of dimension ``d``.
"""	
randunitary(d) = expm(im* randposdef(d))

"""
randorth(d)
             
	Orthogonal matrix drawn according to the Haar measure on the group of orthogonal matrices.
"""	
randorth(d) = qr(randn(d,d))[1]



function tridiag(di, u, l)
	assert(length(di) -1 == length(u) == length(l))
	M = diagm(di)
	for i in 1:length(u)
	  M[i,i+1] = l[i]
  	  M[i+1,i] = u[i]
	end
	M
	
end

"""
randnormal(d) 
             
	Random normal matrix of dimension ``d``.
"""	
function randnormal(d) 
	Q = randorth(d)
	B = schur(randn(d,d))[1] #same eigenvalues as a randn(d,d)
	m = d
	alpha = zeros(d)
	beta = zeros(d-1)
	while m > 1
	   s = abs(B[m-1,m-1]) + abs(B[m,m])
	   if s + abs(B[m,m-1]) > s # if significant offdiagonal value: evaluate submatrix m-1:m;
		spur = B[m,m] + B[m-1,m-1]
		dis2 = abs2(B[m,m]- B[m-1,m-1]) + 4.0*B[m,m-1]*B[m-1,m] # = spur^2 - 4det
		alpha[m] = alpha[m-1] = 0.5*spur
		
		beta[m-1] = 0.5*sqrt(-dis2)
		m -= 2       
	   else
	        alpha[m] = B[m,m]
	        beta[m-1] = 0
	        m -= 1        
	   end
	   
	end
	if (m == 1) 
		alpha[1] = B[1,1]
	end
	
	Q' * tridiag(alpha, beta, -beta) * Q
	
end

end # module
