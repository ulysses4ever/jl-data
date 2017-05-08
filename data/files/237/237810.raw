# Kernel module
module Kernel

export KernelPCA, GaussianKernel!, GaussianKernel, GaussianKernelPreImage, GaussianKernelDenoise, LinearKernel, PolynomialKernel, ANOVAKernel, ProjectionError, IPKernel, InverseIPKernel, AEPFeature, AEPKernel, AEPCovariance, InverseAEPKernel, LinearMean, LogMap, ExpMap, FrechetMean, PGAFeature, PGAKernel, PGACovariance, InversePGAKernel, SphericalFeature, SphericalFeatureInverse, SphericalKernel, SphericalKernelLowMem, SphericalCosKernel, SphericalCovariance, SphericalCovarianceLowMem

# Kernel PCA
include("KPCA.jl")

# Kernel definitions
include("Kernels.jl")

# Kerne preimage definitions
include("PreImage.jl")

# Kernels specific to orientation data
include("KernelOrientation.jl")

# Computes projection error. Uses a TSVD approximation if necessary.
# @param Kxx - K(x,x) the feature space inner product of x with itself.
# @param Kx -  K(:,x) the feature space inner produce of x with all atoms of K.
# @param K - K(:,:) the kernel matrix / gram matrix in feature space of all atoms - this may be a rank-k approximation.
# @param S,U - Eigen decomposition of K - these may be rank-k approximations
# @param condK - condition number of K
# @param epsilon - the TSVD cut off.
function ProjectionError(Kxx, Kx, K, S, U, condK, epsilon)
	proj_err = 1e100
	if condK > 1e4 # remember that ||x-x'||/||x|| <= cond(A) * ||Ax'-b||/||b||, where x is the exact solution to Ax=b
		# attempt at computing this more carefully:
		Utkj = U' * Kx
		S[ find( S .< epsilon ) ] = 0
		S[ find( S .> epsilon ) ] = 1 ./ S[ find( S .> 1e-30 ) ]
		S = sqrt(S)
		Utkj = diagm(S) * Utkj
		proj_err = (Kxx - Utkj'*Utkj)[1,1]
	else
		proj_err = (Kxx - (Kx' * (K \ Kx)))[1,1]
	end

	proj_err = sqrt( 2 * abs(proj_err) )
	return proj_err
end

end # module
