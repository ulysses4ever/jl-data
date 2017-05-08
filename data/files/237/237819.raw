
# kernels for normal vectors from:
# Snape, Zafeiriou, "Kernel-PCA Analysis of Surface Normals for Shape-from-Shading", 2014


using Debug

# IPKernel = Inner Product kernel - this is linear kernel w/o centering
function IPKernel(X1,X2)
	K = X1*X2'
	#K = zeros(size(X1,1), size(X2,1))
	#d = size(X1,2)
	#for i=1:size(X1,1)
	#	for j=1:size(X2,1)
	#		# sum of inner products of the normals for each "pin list"
	#		for k=1:3:d
	#			K[i,j] += (X1[i,k:k+2]' * X2[j,k:k+2])[1]
	#		end
	#	end
	#end
	return K
end

# Given a list of points in feature space (projected onto PCA subspace and back)
# this function computes what the corresponding pre-image points would be
function InverseIPKernel(Y)
	n = size(Y,1)
	d = size(Y,2)
	Xp = zeros(size(Y))
	for i=1:n
		for j=1:3:d
			Xp[i,j:j+2] = Y[i,j:j+2] / norm(Y[i,j:j+2])
		end
	end
	return Xp
end

# Compute the Azimuthal Equidistant Projection (AEP) feature vectors
function AEPFeature(X,mus)
	feature = zeros(size(mus))
	d = length(X)
	muk = 1
	for k=1:3:d
		mphi = mus[muk]
		mtheta = mus[muk+1]

		x = X[k]
		y = X[k+1]
		z = X[k+2]
		phi = atan( y/x )
		theta = pi/2 - asin( z )
		cosc = sin(mtheta)*sin(theta) + cos(mtheta)*cos(theta)*cos(phi-mphi)
		c = acos(cosc)
		sinc = sin(c)
		k = c / sinc

		tx = k * cos(theta) * sin(phi - mphi)
		ty = k * (cos(mtheta) * sin(phi) - sin(mphi)*cos(theta)*cos(phi-mphi))
		feature[muk] = tx
		feature[muk+1] = ty

		muk += 2
	end
	feature
end
# interface that computes mu as needed.
function AEPFeature(X)
	mus = LinearMean(X)
	xaep1 = AEPFeature(X[1,:],mus)
	F = zeros(size(X,1), length(xaep1))
	for i=1:size(X,1)
		F[i,:] = AEPFeature(X[i,:],mus)
	end
	F
end


# Azimuthal Equidistant Projection (AEP) kernel
# X1,X2 - data sets
# mus - mean for each point as elevation and azimuthal angles
function AEPKernel(X1,X2,mus)
	K = zeros(size(X1,1), size(X2,1))
	d = size(X1,2)
	for i=1:size(X1,1)
		feature1 = AEPFeature(X1[i,:],mus)
		for j=1:size(X2,1)
			feature2 = AEPFeature(X2[i,:],mus)
			K[i,j] = (feature1 * feature2')[1]
		end
	end
	return K
end

# interface that computes mu as needed.
function AEPKernel(X1,X2)
	if X1 == X2
		mus = LinearMean(X1)
	else
		mus = LinearMean([X1; X2])
	end
	K = AEPKernel(X1,X2,mus)
	K,mus
end

# Azimuthal Equidistant Projection (AEP) covariance - perform computation direction in feature space
# NOTE: use this when dimension of feature < n
#       (for AEP dimension of feature <=> dimension of input)
# X1,X2 - data sets
# mus - mean for each point as elevation and azimuthal angles
function AEPCovariance(X,mus)
	ftmp = AEPFeature(X[1,:],mus)
	fl = length(ftmp)
	cmat = zeros(fl,fl) # it appears that this will be smaller thann
	d = size(X,2)
	n = size(X,1)
	for i=1:size(X1,1)
		feature = AEPFeature(X[i,:],mus)
		cmat += feature * feature' # outer product
	end
	cmat / n
end

# interface that computes mu as needed.
function AEPCovariance(X)
	mus = LinearMean(X)
	cmat = AEPCovariance(X1,X2,mus)
	cmat,mus
end


# Inverse Azimuthal Equidistant Projection (AEP) kernel
# Y - data in feature space 
# mus - mean for each point as elevation and azimuthal angles
function InverseAEPKernel(Y,mus)
	n = size(Y,1)
	d = size(Y,2)
	X = zeros(n,(d/2)*3)
	for i=1:n
		Xk = 1
		for k=1:2:d
			mphi = mus[k]
			mtheta = mus[k+1]

			tx = Y[i,k]
			ty = Y[i,k+1]

			c = sqrt( tx^2 + ty^2 )
			if abs(mtheta-pi/2) < eps(typeof(mtheta)) # mtheta == pi/2
				psi = -tx/ty
			elseif abs(mtheta+pi/2) < eps(typeof(mtheta)) #mtheta == -pi/2
				psi = tx/ty
			else
				psi = (tx * sin(c)) / (c * cos(mtheta) * cos(c) - ty * sin(mtheta) * sin(c))
			end

			theta = asin(cos(c) * sin(mtheta) - (1/c) * ty * sin(c) * cos(mtheta))
			phi = mphi + atan(psi)

			nz = sin(pi/2 - theta)
			# ny/nx = tan(phi)
			h = sqrt(1 - nz^2) # hypotenuse
			nx = h * cos(phi)
			ny = h * sin(phi)

			# make sure it's unit length:
			len = sqrt(nx^2 + ny^2 + nz^2)
			nx /= len
			ny /= len
			nz /= len

			X[i,Xk] = nx
			X[i,Xk+1] = ny
			X[i,Xk+2] = nz
			
			Xk += 3
		end
	end
	X
end


# compute the linear mean and then reproject onto the sphere
function LinearMean(X)
	mu = mean(X,1)
	d = size(X,2)
	for i=1:3:d
		mu[i:i+2] /= norm(mu[i:i+2])
	end
	mu
end

# project onto tangent plane of mus
# see Srivastava,Jermyn,Joshi, "Riemannian Analysis of Probability Density Functions with Applications in Vision", equation (9)
# X - matrix: (num_of_data, 3*num_of_positions) - so each row has a normal for each positions, and each column is the list of normals for that position
# mus - vector: (3*num_of_positions) - tangent point for each position
# undirected - true => ignore direction (sign of vector)
function LogMap(X,mus, undirected=false)
	dim = 3
	n = size(X,1)
	d = size(X,2)
	logmap = zeros(size(X))
	for position = 1:dim:d
		Xp = X[:,position:position+2]
		mu = reshape(mus[position:position+2],1,dim)
		if undirected
			# flip for consistent (undirected) orientation
			flip = find((Xp * mu) .< 0)
			Xp[flip,:] *= -1
		end
		inner = max( -1, min(1, Xp * mu ) )
		u = Xp - ((inner*ones(1,dim)) .* (ones(n,1)*mu))
		unorm = sqrt(sum(u.^2,2))
		coef = acos(inner) ./ max(eps(typeof(unorm[1])), unorm)
		logmap[:,position:position+2] = coef .* u
	end
	logmap
end

# project onto sphere from tangent plane of mus
# see Srivastava,Jermyn,Joshi, "Riemannian Analysis of Probability Density Functions with Applications in Vision", equation (8)
# X - matrix: (num_of_data, 3*num_of_positions) - so each row has a normal for each positions, and each column is the list of normals for that position
# mus - vector: (3*num_of_positions) - tangent point for each position
# undirected - true => ignore direction (sign of vector)
@debug function ExpMap(X,mus,undirected=false)
	dim = 3
	n = size(X,1)
	d = size(X,2)
	expmap = zeros(size(X))
	for position = 1:dim:d
		Xp = X[:,position:position+2]
		mu = reshape(mus[position:position+2],1,dim)

		dist = sqrt(sum( Xp.^2, 2))

		if undirected
			# flip to shortest orientation (for consistent undirected vectors)
			shorten = find(dist .> pi/2)
			Xp[shorten,:] ./= (dist[shorten]*ones(1,dim))
			dist[shorten] .-= pi/2
			Xp[shorten,:] = -Xp[shorten,:] .* (dist[shorten]*ones(1,dim))
		end
		
		@bp
		expmap[:,position:position+2] = (cos(dist)*mu) + (sin(dist) * (Xp ./ (max(eps(typeof(dist[1])), dist)*ones(1,dim))))
	end
	expmap
end

# Frechet Mean using gradient descent
# X - the data 
# mu0 - initial guess at mean
# stepsize - step size in gradient descent
# maxiters - maximum number of steps
# stopping - convergence of mu below this value
function FrechetMean(X, mu0, stepsize, maxiters, stopping)
	n = size(X,1)
	d = size(X,2)
	dim = 3
	mu = copy(mu0)

	for iter = 1:maxiters
		gradient = -mean(LogMap(X, mu),1)

		lastmu = copy(mu)
		mu = ExpMap(-stepsize * gradient, lastmu )

		if norm(mu-lastmu) < stopping
			break
		end
	end

	mu
end

# feature vector for PGA Kernel
function PGAFeature(X,mus)
	LogMap(X,mus)
end

# Kernel Based on PGA given the intrinsic means
function PGAKernel(X1,X2,mus)
	d = length(mus)
	K = zeros(size(X1,1),size(X2,1))
	for i=1:size(X1,1)
		feature1 = PGAFeature(X1[i,:],mus)
		for j=1:size(X2,1)
			feature2 = PGAFeature(X2[i,:],mus)
			K[i,j] = feature1' * feature2
		end
	end
	K
end

# Kernel Based on PGA - interface that computes mus as needed
function PGAKernel(X1,X2)

	stepsize = 1e-1
	maxiters = 1000
	stopping = 1e-7
	
	if X1 == X2
		mus = LinearMean(X1)
		mus = FrechetMean(X1,mus,stepsize,maxiters,stopping)
	else
		mus = LinearMean([X1;X2])
		mus = FrechetMean([X1;X2],mus,stepsize,maxiters,stopping)
	end

	K = PGAKernel(X1,X2,mus)
	K, mus
end

# Covariance Based on PGA given the intrinsic means - compute in feature space directly
# NOTE: use this when PGA feature dimension < size of data
#       for PGA feature dimension <=> input dimension
function PGACovariance(X,mus)
	d = length(mus)
	n = size(X,1)
	ftmp = PGAFeature(X[1,:],mus)
	fl = length(ftmp)
	cmat = zeros(fl,fl)
	for i=1:n
		feature = PGAFeature(X[i,:],mus)
		cmat += feature * feature'
	end
	cmat / n
end

# Covariance Based on PGA - interface that computes mus as needed
function PGACovariance(X)

	stepsize = 1e-1
	maxiters = 1000
	stopping = 1e-7
	
	if X1 == X2
		mus = LinearMean(X1)
		mus = FrechetMean(X1,mus,stepsize,maxiters,stopping)
	else
		mus = LinearMean([X1;X2])
		mus = FrechetMean([X1;X2],mus,stepsize,maxiters,stopping)
	end

	cmat = PGACovariance(X,mus)
	cmat, mus
end


# Inverse PGA kernel
function InversePGAKernel(Y,mus)
	X = ExpMap(Y,mus)
end

# Spherical Feature
function SphericalFeature(X)
	n = size(X,1)
	d = size(X,2)
	dim = 3
	feature = zeros(n,int(4*(d/dim)))
	for i=1:n
		fk = 1
		for k=1:dim:d
			nrm = norm(X[i,k:k+2])
			if nrm > 0
				feature[i,fk:fk+2] = X[i,k:k+2] / nrm 
				feature[i,fk+3] = sqrt( 1 - feature[i,fk+2]^2 )
			end
			fk += 4
		end
	end
	feature
end
function SphericalFeatureInverse(Phi)
	dim = 3
	X = zeros(size(Phi,1),int(dim*(size(Phi,2)/4)))
	n = size(X,1)
	d = size(X,2)
	for i=1:n
		fk = 1
		for k=1:dim:d
			gx = Phi[i,fk]
			gy = Phi[i,fk+1]
			gz = Phi[i,fk+2]
			sgz = Phi[i,fk+3]
			#rho = atan2( (gy/sqrt((gx^2)+(gy^2))) , (gx/sqrt((gx^2)+(gy^2))) )
			rho = atan2( gy , gx )
			#psi = atan2( (sgz/sqrt((gz^2)+(sgz^2))) , (gz/sqrt((gz^2)+(sgz^2))) )
			psi = atan2( sgz, gz ) 
			#v = [(cos(psi)*sin(rho)), (sin(psi)*sin(rho)), cos(psi)]
			#gzh = sqrt(gz^2 + sgz^2)
			#v = [(cos(psi)*sin(rho)), (sin(psi)*sin(rho)), cos(psi)*gzh]
			v = [gx,gy,gz]
			X[i,k:k+2] = v / norm(v)
			fk += 4
		end
	end
	X
end



# Spherical Kernel (aka Cosine kernel)
function SphericalKernel(X1,X2)
	Phi1 = SphericalFeature(X1)
	Phi2 = SphericalFeature(X2)
	K = Phi1 * Phi2'
end
function SphericalKernelLowMem(X1,X2)
	K = zeros(size(X1,1),size(X2,1))
	for i=1:size(X1,1)
		feature1 = SphericalFeature(X1[i,:])
		feature1[find(isnan(feature1))] = 0
		for j=1:size(X2,1)
			feature2 = SphericalFeature(X2[i,:])
			feature2[find(isnan(feature2))] = 0
			K[i,j] = (feature1 * feature2')[1]
		end
	end
	return K
end

# Equivalent to Spherical Kernel above, but uses cos,acos,atan instead of constructing feature vectors..
function SphericalCosKernel(X1,X2)
	error("does not match SphericalKernel() result")
	d = size(X1,2)
	dim = 3
	dpr = int(d / dim)
	K = zeros(size(X1,1),size(X2,1))
	for i=1:size(X1,1)
		phi1 = zeros(dpr)
		theta1 = zeros(dpr)
		dpri = 1
		for k = 1:dim:d
			v = X1[i,k:k+2] / norm(X1[i,k:k+2])
			phi1[dpri] = atan( v[2]/v[1] )
			theta1[dpri] = acos( v[3] )
			dpri += 1
		end
		for j=1:size(X2,1)
			phi2 = zeros(dpr)
			theta2 = zeros(dpr)
			dpri = 1
			for k = 1:dim:d
				v = X2[i,k:k+2] / norm(X2[i,k:k+2])
				phi2[dpri] = atan( v[2]/v[1] )
				theta2[dpri] = acos( v[3] )
				dpri += 1
			end
			K[i,j] = sum( cos(phi1-phi2) ) + sum( cos(theta1-theta2) )
		end
	end
	K
end
# Covariance Based on Spherical kernel
# NOTE: use this when [spherical feature dimension] < [size of data]
#       for [spherical feature dimension] <=> (4/3)*[input dimension]
function SphericalCovariance(X)
	n = size(X,1)
	Phi = SphericalFeature(X)
	cmat = (Phi'*Phi) / n
end
function SphericalCovarianceLowMem(X)
	d = size(X,2)
	n = size(X,1)
	ftmp = SphericalFeature(X[1,:])
	fl = length(ftmp[:])
	cmat = zeros(fl,fl)
	for i=1:n
		feature = SphericalFeature(X[i,:])
		cmat += feature * feature'
	end
	cmat / n
end


