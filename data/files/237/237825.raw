# Some kernels
# Daniel Perry (dperry@cs.utah.edu)
# June 2014

# compute k using a gaussian kernel
# @param X1 - data set
# @param X2 - data set
# @param sigma - sigma used in gaussian kernel
function GaussianKernel!{T}(K::Array{T,2},X1::Array{T,2},X2::Array{T,2}, sigma)
		if !isa(sigma,T)
			sigma = convert(T,sigma)
		end
    #for row = 1:size(X1,1)
		row = 1
		while row <= size(X1,1)
        #for col = 1:size(X2,1)
				col = 1
				while col <= size(X2,1)
            @inbounds tmp = sum((X1[row,:]-X2[col,:]).^2)
            @inbounds K[row,col] = exp(-tmp/(2*sigma^2))
						col += 1
        end
				row += 1
    end
end
function GaussianKernel{T}(X1::Array{T,2},X2::Array{T,2}, sigma)
		if !isa(sigma,T)
			sigma = convert(T,sigma)
		end
    K = zeros(T,size(X1,1),size(X2,1))
		GaussianKernel!(K,X1,X2,sigma)
    return K
end


# compute k using a gaussian kernel
# @param X - data set
# @param sigma - sigma used in gaussian kernel
function GaussianKernel!(K, X, sigma)
    #for row = 1:size(X,1)
		row = 1
		while row <= size(X,1)
        #for col = 1:row
				col = 1
				while col <= row
            tmp = sum((X[row,:]-X[col,:]).^2)
            K[row,col] = exp(-tmp/(2*sigma^2))
            K[col,row] = K[row,col]
						col += 1
        end
				row += 1
    end
end
function GaussianKernel{T}(X::Array{T,2}, sigma)
	if !isa(sigma,T)
		sigma = convert(T,sigma)
	end
  K = zeros(T,size(X,1),size(X,1))
	GaussianKernel!(K,X,sigma)
	return K
end

# compute distance in "input" space from distance in feature space between X_i, X_j
# @param feature dot project of X_i and X_i
# @param feature dot project of X_j and X_j
# @param feature distance between X_i and X_j
# @param sigma kernel parameter
#
# @return "input" distance
function GaussianKernelInverseDistance(Kii,Kjj,feature_distance_squared, sigma)
	-sigma^2 * log( .5 * (Kii + Kjj - feature_distance_squared) )
end

# compute k using an ANOVA kernel
# @param X1 - data set
# @param X2 - data set
# @param sigma,d  - kernel params
function ANOVAKernel(X1,X2, sigma, d)
    K = zeros(size(X1,1),size(X2,1))
    for row = 1:size(X1,1)
        for col = 1:size(X2,1)
            K[row,col] = sum( exp( - sigma .* (X1[row,:]-X2[col,:]).^2 ).^d )
        end
    end
    return K
end
# compute k using an ANOVA kernel
# @param X - data set
# @param sigma,d - kernel params
function ANOVAKernel(X, sigma, d)
    K = zeros(size(X,1),size(X,1))
    for row = 1:size(X,1)
        for col = 1:row
            K[row,col] = sum( exp( - sigma .* (X[row,:]-X[col,:]).^2 ).^d )
            K[col,row] = K[row,col]
        end
    end
    return K
end

# compute k using a linear kernel
# @param X1,X2 - data set
# @param scale,offset,power - polynomial parameters
function PolynomialKernel(X1,X2, scale,offset,power)
  K = (scale .* (X1*X2') .+ offset).^power
end
# compute k using a linear kernel
# @param X - data set
# @param scale,offset,power - polynomial parameters
function PolynomialKernel(X, scale,offset,power)
    K = (scale .* X*X' .+ offset).^power
end

# compute k using a linear kernel
# @param X1,X2 - data set
function LinearKernel(X1,X2)
  K = X1*X2'
end
# compute k using a linear kernel
# @param X - data set
function LinearKernel(X)
    K = X*X'
end


