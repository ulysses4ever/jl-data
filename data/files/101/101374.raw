module covariance

export poisson_matrix, k_global_matrix, k_local_matrix
#Routines to efficiently create and modify covariance matrices for spectra.

const c = 2.99792458e5 #km/s; speed of light

#Create the Poisson matrix from a sigma array
function poisson_matrix(sigma::Vector{Float64})
    #Just variances along the diagonal
    return spdiagm(sigma.^2)
end

#Another option assuming all sigmas are the same
function poisson_matrix(wl::Vector{Float64}, sigma::Float64)
    N = length(wl)
    return poisson_matrix(sigma*2 .* ones(Float64, N))
end

#Create the "global" covariance matrix using a Matern nu=3/2 kernel
#a is units of flux, l is units of km/s
#internally, r and rs is also in units of km/s
function k_global_matrix(wl::Vector{Float64}, a::Float64, l::Float64)
    N = length(wl)
    r0 = 6. * l #What is the taper radius, set by the Hann window.
    offset = 0 #Tracking how many indexes from the diagonal until 0.
    diags = {}
    
    while offset < N
        #Pairwise calculate rs, the distances between individual wl points
        if offset == 0
            rs = zeros(Float64, N)
        else
            rs = abs(wl[offset + 1:end] - wl[1:end-offset]) ./wl[offset + 1:end] * c
        end
        if minimum(rs) >= r0
            #If even the smallest radius is larger than our truncation radius, 
            #we are done initializing the sparse array, exit
            break
        end
        k = similar(rs)
        #Hann window times Matern Kernel
        k = (0.5 + 0.5cos(pi .* rs/r0))  .* a .* (1 + sqrt(3) .* rs/l) .* exp(-sqrt(3) .* rs/l)
        k[rs .>= r0] = 0
        push!(diags, k)
        offset += 1
    end
        
    #Mirror the diagonals to the other side of the matrix
    front = diags[end:-1:2]
    diags = vcat(front, diags)
    offsets = [i for i=(-offset + 1):(offset-1)]
    return spdiagm(diags, offsets)
end

function k_local(w0::Float64, w1::Float64, a::Float64, mu::Float64, sigma::Float64)
    rw0 = abs(w0 - mu)
    rw1 = abs(w1 - mu)
    r_tap = rw0 > rw1 ? rw0 : rw1 #choose the greater distance
    
    r0 = 4.0 * sigma
    r_tap = c * r_tap/mu #convert to km/s
    taper = 0.5 + 0.5cos(pi * r_tap/r0)
    return taper * a^2 * exp(-((w0 - mu)^2 + (w1 - mu)^2)/(2 * sigma^2)) 
end

#This function is probably very fast but the look-up operation wl[i] could most likely be sped up
function k_local_matrix(wl::Vector{Float64}, a::Float64, mu::Float64, sigma::Float64)
    N = length(wl)
    #determine the wl indices that are within 4 sigma of mu
    r0 = 4.0 * sigma;
    
    #this loop should exit with first_ind being equal to the first row,col occurence of the region
    i = 1
    r = r0 + 1 #simply starts larger than r0
    first_ind = 1
    last_ind = N
    while (r > r0)
        r = c * abs(wl[i] - mu)/mu #how far away are we from mu?
        first_ind = i
        i += 1
    end
    
    #this loop should exit with last_ind being equal to the last row,col occurence (inclusive)    
    while (r < r0)
        last_ind = i 
        i += 1
        r = c * abs(wl[i] - mu)/mu
    end
    
    #println("Region stretches from indices $first_ind to $last_ind.")

    #how many non-zero elements?
    M = (last_ind - first_ind + 1)^2
    #println("There are $M non-zero elements.")

    if (M == 0)
        println("There are 0 non-zero elements. Returning null.")
        return 0;
    end
    
    II = Array(Int, M) 
    JJ = Array(Int, M) 
    SS = Array(Float64, M)
    k=1
    
    #we want a square and symmetric matrix
    #Only fill in the lower entries (and diagonal). 
    for i = first_ind:last_ind
        for j = first_ind:i
            #Initialize lower triangle
            II[k] = i
            JJ[k] = j
            SS[k] = k_local(wl[i], wl[j], a, mu, sigma)
            k += 1
            if i != j
                #Initialize upper triangle while skipping the diagonal the second time
                II[k] = j
                JJ[k] = i
                SS[k] = k_local(wl[j], wl[i], a, mu, sigma)
                k += 1
            end
        end
    end
    return sparse(II[1:k-1], JJ[1:k-1], SS[1:k-1], N, N)
end



#Compute the Chi^2 using Cholesky factorization
#function chi2(C)
#    cholobj = cholfact(S);
#    println(logdet(cholobj))
#    out = cholobj \ ys;
#    println(dot(ys, out[:,1]))
#end

end
