using Distributions

function betarnd(a,b,n,m)
	d = Beta(a,b)
	r = rand(d,int(n*m))
	reshape(r, n,m)
end

function randVonMisesFisher(m, n, kappa, mu = None)
	#% randVonMISESFISHERM Random number generation from von Mises Fisher
	#% distribution.
	#% X = randVonMisesFisherm(m, n, kappa) returns n samples of random unit 
	#% directions in m dimensional space, with concentration parameter kappa,
	#% and the direction parameter mu = e_m
	#% X = randVonMisesFisherm(m, n, kappa, mu) with direction parameter mu
	#% (m-dimensional column unit vector)
	#%
	#% Sungkyu Jung, Feb 3, 2010.
	#
	# converted into Julia, Daniel Perry, April 2015, 
	#
	# see http://www.stat.pitt.edu/sungkyu/MiscPage.html
	#     http://www.stat.pitt.edu/sungkyu/software/randVonMisesFisherm.zip
	#     http://www.stat.pitt.edu/sungkyu/software/randVonMisesFisher3.pdf


	if mu == None
		muflag = false;
	else 
		muflag = true;
	end

	if m < 2; 
			println("Message from randVonMisesFisherm.m: dimension m must be > 2")
			println("Message from randVonMisesFisherm.m: Set m to be 2")
			m = 2;
	end

	if kappa < 0; 
			println("Message from randVonMisesFisherm.m: kappa must be >= 0"); 
			println("Message from randVonMisesFisherm.m: Set kappa to be 0"); 
			kappa = 0;
	end

	#%
	#% the following algorithm is following the modified Ulrich's algorithm 
	#% discussed by Andrew T.A. Wood in "SIMULATION OF THE VON MISES FISHER 
	#% DISTRIBUTION", COMMUN. STATIST 23(1), 1994.

	#% step 0 : initialize
	b = (-2*kappa + sqrt(4*kappa^2 + (m-1)^2))/(m-1);
	x0 = (1-b)/(1+b);
	c = kappa*x0 + (m-1)*log(1-x0^2);

	#% step 1 & step 2
	nnow = n; 
	w = [];
	#%cnt = 0;
	while true
			ntrial = int(max(round(nnow*1.2),nnow+10))
			Z = betarnd((m-1)/2,(m-1)/2,ntrial,1);
			U = rand(ntrial,1);
			W = (1-(1+b)*Z)./(1-(1-b)*Z);
			
			indicator = (kappa*W + (m-1)*log(1-x0*W) - c) .>= log(U)
			if sum(indicator) >= nnow
					w1 = W[find(indicator)]
					w = [w ;w1[1:nnow]];
					break;
			else
					w = [w ; W[find(indicator)]];
					nnow = nnow-sum(indicator);
					#%cnt = cnt+1;disp(['retrial' num2str(cnt) '.' num2str(sum(indicator))]);
			end
	end

	#% step 3
	V = UNIFORMdirections(m-1,n);
	X = [repmat(sqrt(1-w'.^2),m-1,1).*V ;w'];

	if muflag
			mu = mu / norm(mu);
			X = rotMat(mu)'*X;
	end
	return X
end


function UNIFORMdirections(m,n)
	#% generate n uniformly distributed m dim'l random directions
	#% Using the logic: "directions of Normal distribution are uniform on sphere"

	V = zeros(m,n);
	nr = randn(m,n); #%Normal random 
	for i=1:n
			while true
					ni=(nr[:,i]'*nr[:,i])[1]; #% length of ith vector
					#% exclude too small values to avoid numerical discretization
					if ni < 1e-10 
							#% so repeat random generation
							nr[:,i]=randn(m,1);
					else
							 V[:,i]=nr[:,i]/sqrt(ni);
							break;
					end
			end
	end

	return V
end

function rotMat(b, a = None, alpha = None)
	#% ROTMAT returns a rotation matrix that rotates unit vector b to a
	#%
	#%   rot = rotMat(b) returns a d x d rotation matrix that rotate
	#%   unit vector b to the north pole (0,0,...,0,1)
	#%
	#%   rot = rotMat(b,a ) returns a d x d rotation matrix that rotate
	#%   unit vector b to a
	#%
	#%   rot = rotMat(b,a,alpha) returns a d x d rotation matrix that rotate
	#%   unit vector b towards a by alpha (in radian)
	#%
	#%    See also .
	#
	#% Last updated Nov 7, 2009
	#% Sungkyu Jung


	s1 = size(b,1)
	s2 = size(b,2)
	d = max(s1,s2);
	b= b/norm(b);

	if s1<=s2
		b = b'
	end

	if a == None 
			a = [zeros(d-1,1); 1];
	end
	if alpha == None
			alpha = acos((a'*b)[1]);
	end

	if abs((a'*b)[1] - 1) < 1e-15
		rot = eye(d)
		return rot
	end
	if abs((a'*b)[1] + 1) < 1e-15
		rot = -eye(d)
		return rot
	end

	c = b - a * (a'*b); c = c / norm(c);
	A = a*c' - c*a' ;

	rot = eye(d) + sin(alpha)*A + (cos(alpha) - 1)*(a*a' +c*c');
end

