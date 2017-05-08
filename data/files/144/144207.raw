
##
# disc.jl
# Algemene functies voor de discretisatie
##

##
# De normale conventie in julia (en ook matlab overigens) is dat 0^0 = 1.
# Deze functie omzeilt deze conventie, en geeft 0^0 = 0.
# x		grondtal
# y		exponent
##
function pow0(x, y)
	if(x == 0 && y == 0)
		xy = 0;
	else
		xy = x^y;
	end
	xy
end

##
# Bereken ua = W*u
# W		Gereduceerde gewichtsmatrix
# u		Waarde van u(x)
# n		Nx, aantal ruimtestappen
# ua!	a-de afgeleide van u
##
function Dalpha!(W, u, n, ua, disc)
	for i = 1:n-1
		ua[i] = W[i, 1]*u[2];	# We don't include u[1] as that coefficient has already been incorporated in W[i, 1], assuming u[1]=u[2].
		
		#if i < n-1
		#	ua[i] += W[1, 2] * u[i+2];
		#else
		#	ua[i] += disc.s * W[1, 2] * u[i+1];
		#end
		
		for l=1:i
			ua[i] += W[l, 2] * u[i+3-l];
		end
	end
end

##
# Bereken de tridiagonale matrix voor impliciete berekeningen
##
function berekenWimpl(disc::DiscMethode, n, a, dx, dt, chi)
	lambda = dt*chi
	kappa = 1.0/(1-2^(-a))
	
	W1m = w(disc, 3, -1, a, dx)	#w_-1
	W0p = w(disc, 3, 0, a, dx)	#w_0
	W1p = w(disc, 3, 1, a, dx)	#w_1
	
	a = -lambda*W1p
	b = 1 - lambda*W0p
	c = -lambda*W1m
	
	A = a * ones(n-2);
	B = b * ones(n-1);
	C = c * ones(n-2);
	
	#B[1] = 0;
	#C[1] = 0;

	#A[1] = -lambda*w(disc, 1,1,a,dx)
	#B[2] = 1-lambda*w(disc, 1,0,a,dx)
	#C[2] = 1-lambda*w(disc, 1,-1,a,dx)

	#A[2] = -lambda*w(disc, 2,1,a,dx)
	
	A[1] =  -lambda*w(disc, 2,  1, a, dx);
	B[1] = 1-lambda*w(disc, 1,  0, a, dx) -        lambda*kappa*w(disc, 1, 1, a, dx);
	C[1] =  -lambda*w(disc, 1, -1, a, dx) + 2^(-a)*lambda*kappa*w(disc, 1, 1, a, dx);
	
	B[end] += c;
	

	Tridiagonal(A, B, C)
end


function berekenWimpl(disc::DiscMethode, Wred, n, dt, chi)
	lambda = dt*chi
	
	
	W1p = Wred[3, 2] #w_1
	W0p = Wred[2, 2] #w_0
	W1m = Wred[1, 2] #w_-1
	
	a = -lambda*W1p
	b = -lambda*W0p
	c = -lambda*W1m
	
	A = a * ones(n-2);
	B = b * ones(n-1);
	C = c * ones(n-2);
	
	
	A[1] = -lambda*Wred[2, 1];
	B[1] = -lambda*Wred[1, 1];
	
	#B[end] += disc.s * c;
	

	Tridiagonal(A, B, C)
end