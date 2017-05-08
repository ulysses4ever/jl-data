# Pre-image for Gaussian kernel
# From Kwok and Tsang, "The Pre-Image problem in kernel methods", ICML 2003
# (based on matlab code provided by authors)
# Also:
# Mika, et al. "Kernel PCA and Denoising in Feature Spaces", NIPS 1998
# and
# Teixeira et al. "KPCA Denoising and the pre-image problem revisited", DSP 2008
#
# Danny Perry (dperry@cs.utah.edu)
# May 2015

using Debug

include("Kernels.jl")

# Fixed point method to preimage
# y - projected data (trying to recover into input space)
# U - eigenvectors of K
# X - training data
# z_init - initial guess at z
# sigma - Gaussian kernel parameter
# tolerance - convergence criteria
# maxiters - max number of iters
function GaussianKernelPreImage(y,U, X, z_init, sigma, tolerance, maxiters)

	gamma = U * y # results in n x 1 vector

	z = copy(z_init)
	last_z = copy(z)
	iter = 0
	for iter=1:maxiters
		last_z = copy(z)
		diff = X - ones(size(X,1),1)*z
		diff .^= 2
		kz = gamma .* exp( -sum(diff,2) ./ sigma^2)
		if sum(kz) == 0
			println("Preimage fixed point iteration failed: initial guess too far away - reverting to initial guess.")
			return z_init # can't get any closer, returning initial guess.
		end
		z = sum(X .* (kz*ones(1,size(X,2))),1)/sum(kz)
		if norm(last_z-z)/sqrt(norm(z)*norm(last_z)) < tolerance
			break
		end
	end

	if false
		println("iters: ", iter)
		println("err: ", norm(last_z-z)/sqrt(norm(z)*norm(last_z)) , " < ", tolerance)
	end

	if iter == maxiters
		println("warning, did not converge.")
	end

	return z, iter
end

# Linear algebra approach to preimage
function GaussianKernelPreImage(distsq, X, neibsize)
	sidx = sortperm(distsq)
	sdistsq = distsq[sidx]
	XH = X[sidx[1:neibsize],:]
	Xmean = mean(XH,1)
	XH = XH - ones(neibsize,1) * Xmean # centered around neighborhood mean

	UM,SM,VM = svd(XH')
	rankM = rank(diagm(SM),1e-5)
	UM = UM[:,1:rankM]
	SM = SM[1:rankM]
	VM = VM[:,1:rankM]
	transf = UM*diagm(1./SM)*(VM'./2)

	sd0 = zeros(neibsize,1)
	ZM = diagm(SM)*VM'
	for i=1:neibsize
		sd0[i] = (ZM[:,i]'*ZM[:,i])[1]
	end
	result = transf * (vec(sd0) - vec(sdistsq[1:neibsize])) + vec(Xmean)
end

# X - training data (n x d)
# K - uncentered training data Gram (n x n)
# Ktest - uncentered test data Gram with training (n x nt)
function GaussianKernelPreImage(X,K,Ktest, neibsize, sigma)

	n  = size(K,1)
	nt = size(Ktest,2)
	d = size(X,2)
	
	spectrum_pct = 0
	target_dim = n
	centering = "additive"
	Kc,P,V,S,Y = KernelPCA(K, spectrum_pct, target_dim, centering)

	H = eye(n)-ones(n,n)/n # centering matrix
	HMH = H*P*P'*H
	cK = mean(K,2)
	meanK = mean(cK)

	result = zeros(nt,d)
	neibs = zeros(Int64, nt, neibsize)
	for j=1:nt
		# calculate the distance between the testing point and training points
		k_x = Ktest[:,j]
		gammaC = HMH*(k_x-cK);
		PphiNormC = ((k_x+cK)'*gammaC + meanK)[1]
		d2 = zeros(n);
		for i = 1:n
			PphiProjC = (K[i,:]*gammaC)[1]+cK[i]
			d2[i]  = -log(abs((1-PphiNormC+2*PphiProjC)/2))*(sigma*2)
		end           
		result[j,:] = GaussianKernelPreImage(d2,X,neibsize);

		closestind = sortperm(d2)
		neibs[j,:] = closestind[1:neibsize]
	end
 
	return result,neibs
end


function GaussianKernelDenoise(X,Xtest, iters, neibsize, sigma)

	n  = size(X,1)
	nt = size(Xtest,1)
	d = size(X,2)

	K = GaussianKernel(X,X,sigma)

	spectrum_pct = 0
	target_dim = n
	centering = "additive"
	Kc,P,V,S,Y = KernelPCA(K, spectrum_pct, target_dim, centering)

	H = eye(n)-ones(n,n)/n # centering matrix
	HMH = H*P*P'*H
	cK = mean(K,2)
	meanK = mean(cK)

	result = copy(Xtest)
	neibs = zeros(Int64, nt, neibsize)
	for iter=1:iters
		for j=1:nt
			# calculate the distance between the testing point and training points
			k_x = GaussianKernel(X,Xtest[j,:],sigma)
			gammaC = HMH*(k_x-cK);
			PphiNormC = ((k_x+cK)'*gammaC + meanK)[1]
			d2 = zeros(n);
			for i = 1:n
				PphiProjC = (vec(K[i,:])'*vec(gammaC)+cK[i])[1]
				d2[i]  = -log((1-PphiNormC+2*PphiProjC)/2)*sigma
			end           
			result[j,:] = GaussianKernelPreImage(d2,X,neibsize);

			closestind = sortperm(d2)
			neibs[j,:] = closestind[1:neibsize]
		end
	end
 
	return result,neibs
end

