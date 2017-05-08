using Distances
type KMeans
    centers::Matrix{Float64}
    clusters::Vector{Int64}
end


function fit(::Type{KMeans}, X::Matrix{Float64}, k=5, n_iter=20)
    centers = X[:, randcycle(size(X)[2])[1:k]]
    closest = zeros(Int64, size(X)[2])
    dists = zeros(size(X)[2], k)

    for i=1:n_iter
        pairwise!(dists,SqEuclidean(), X, centers)
        closest .= vec(mapslices(indmin,dists,2))
        for j=1:k
            centers[:,j] = mean(X[:, closest .== j], 2)
        end
    end
    return(KMeans(centers, closest))
end
