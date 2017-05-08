# kernel pca
# Daniel Perry (dperry@cs.utah.edu)
# June 2014

# kernel pca
# @param K - kernel matrix
# @param spectrum_percent - percent of eigen spctrum to keep
# @param target_dimension - optionally specify desired dimension
# @param centering - "none", "additive", "divisive"
function KernelPCA(K, spectrum_percent, target_dimension, centering)
    if (centering == "divisive")
      error("not yet implemented")
    end

    # center matrix:
    if(centering == "additive")
			#Kmean = mean(K,1)
			#n = size(K,1)
      #K = (K - ones(n,1)*Kmean - Kmean'*ones(1,n)) .+ mean(K[:])
      #K = K .- Kmean .- Kmean' .+ mean(K)
			oneM = ones(size(K)) * (1/size(K,1))
      K = K - oneM*K - K*oneM + oneM*K*oneM
    end
    
    # eigen decomposition
    U,S,tmp = svd(K)
    #S ./= N # N*S*K*U = K*U

		if abs(S[1]) < abs(S[end])
			# need to flip so largest is first
			S = S[reverse(1:end)]
			U = U[:, reverse(1:end)]
		end


    # determine target dimension:
    if target_dimension == 0
        tot = sum(abs(S))
        energy = 0
        for i=1:size(U,2)
            energy += abs(S[i])
            if energy / tot > spectrum_percent
                target_dimension = i
                break
            end
        end
    end
    if target_dimension == 0
      target_dimension = size(U,2)
    end
    #println("target dimension: ", target_dimension)
    
    # projection matrix:
    P = U[:,1:target_dimension] .* ( ones(size(U,1),)* (1./sqrt(abs(S[1:target_dimension]))') )
    
    Y = K*P
    
    # centered K, projection matrix, Eigenvectors, Eigenvalues, projected data
    return K,P,U,S,Y 
end
