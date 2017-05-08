using Distributions

module MixtureModels
    using NumericExtensions
    using Distributions
    export MixtureMultivariateNormals

    # K clusters in N-dimensional space
    # TODO: Fill out Distribution methods
    # TODO: Restore empty cluster pruning
    # TODO: Add method for getting point assignments (for all mixtures?)
    # TODO: Make custom cont. univ. mixture type?
    immutable MixtureMultivariateNormals <: Distributions.ContinuousMultivariateDistribution
    	mu::Matrix{Float64}
    	sigma::Array{Float64}
    	p::Vector{Float64}
        normals::Vector{MultivariateNormal}
        k::Int
        drawtable::Distributions.DiscreteDistributionTable
        function MixtureMultivariateNormals(mu::Matrix{Float64},
                                            sigma::Array{Float64},
                                            p::Vector{Float64})
            n, k = size(mu)
            if size(sigma) != (n, n, k)
                error("Covariance matrices do not match mean vectors")
            end
            if length(p) != k
                error("Probability vector must have length k")
            end
            normals = Array(MultivariateNormal, k)
            for cluster in 1:k
                normals[cluster] =
                  MultivariateNormal(mu[:, cluster],
                                     sigma[:, :, cluster])
            end
            new(mu, sigma, p, normals, k, Distributions.DiscreteDistributionTable(p))
        end
    end

    function Distributions.mean(d::MixtureMultivariateNormals)
        n, k = size(d.mu)
        mu = zeros(Float64, n)
        for i in 1:k
            for j in 1:n
                mu[j] += d.mu[j, i]
            end
        end
        for j in 1:n
            mu[j] /= k
        end
        return mu
    end

    function Distributions.pdf(d::MixtureMultivariateNormals, x::Vector)
        p = 0.0
        for cluster in 1:d.k
            p += d.p[cluster] * pdf(d.normals[cluster], x)
        end
        return p
    end

    function Distributions.logpdf(d::MixtureMultivariateNormals, x::Vector)
        p = 0.0
        for cluster in 1:d.k
            p += d.p[cluster] * pdf(d.normals[cluster], x)
        end
        return log(p)
    end

    Distributions.rand(d::MixtureMultivariateNormals) = rand(d.normals[rand(d.drawtable)])

    function Base.show(io::IO, d::MixtureMultivariateNormals)
        @printf io "Mixture of %d MultivariateNormal's\n" d.k
        for cluster in 1:(d.k - 1)
            @printf " * Component %d: %s\n" cluster d.mu[:, cluster]
        end
        @printf " * Component %d: %s" d.k d.mu[:, d.k]
    end

    # Utility functions needed for fitting Gaussian mixture model
    # using EM
    #
    #  X: n x o data matrix of o observations in R^n
    #  R: o x k matrix of responsibilities for k clusters
    #  k: Number of clusters

    function assign_labels!(X::Matrix{Float64},
                            mu::Matrix{Float64},
                            label::Vector{Int},
                            n::Integer,
                            o::Integer,
                            k::Integer)
        # Find closest cluster to each observation
        for i in 1:o
            mindist = Inf
            for cl in 1:k
                dist = 0.0
                for d in 1:n
                    dist += (X[d, i] - mu[d, cl])^2
                end
                if dist < mindist
                    mindist = dist
                    label[i] = cl
                end
            end
        end
        return
    end

    function initialize!(X::Matrix{Float64},
                         R::Matrix{Float64},
                         mu::Matrix{Float64},
                         n::Integer,
                         o::Integer,
                         k::Integer)
        # Randomly choose k points as cluster centers
        for cluster in 1:k
            exemplar = rand(1:o)
            for dim in 1:n
                mu[dim, cluster] = X[dim, exemplar]
            end
        end

        # Select initial assignments by finding closest cluster centers
        label = Array(Int, o)
        assign_labels!(X, mu, label, n, o, k)
        for i in 1:o
            R[i, label[i]] = 1.0
        end

        return
    end

    function mmn_Estep!(X::Matrix{Float64},
                        R::Matrix{Float64},
                        logRho::Matrix{Float64},
                        logR::Matrix{Float64},
                        mu::Matrix{Float64},
                        sigma::Array{Float64},
                        p::Vector{Float64},
                        T::Vector{Float64},
                        n::Integer,
                        o::Integer,
                        k::Integer)
        for cluster in 1:k
            d = MultivariateNormal(mu[:, cluster], sigma[:, :, cluster])
            for obs in 1:o
                logRho[cluster, obs] = logpdf(d, X[:, obs])
            end
        end

        for obs in 1:o
            for cluster in 1:k
                logRho[cluster, obs] += log(p[cluster])
            end
        end

        for obs in 1:o
            T[obs] = logsumexp(logRho[:, obs])
        end

        for obs in 1:o
            for cluster in 1:k
                logR[obs, cluster] = logRho[cluster, obs] - T[obs]
            end
        end

        for obs in 1:o
            for cluster in 1:k
                R[obs, cluster] = exp(logR[obs, cluster])
            end
        end

        # Return log likelihood
        return sum(T)
    end

    function mmn_Mstep!(X::Matrix{Float64},
                        Xo::Matrix{Float64},
                        R::Matrix{Float64},
                        mu::Matrix{Float64},
                        sigma::Array{Float64},
                        sigmatmp::Array{Float64},
                        p::Vector{Float64},
                        n::Integer,
                        o::Integer,
                        k::Integer,
                        nk::Vector{Float64},
                        sqrtR::Matrix{Float64})
        # Determine number of points in cluster
        fill!(nk, 0.0)
        for obs in 1:o
            for cluster in 1:k
                nk[cluster] += R[obs, cluster]
            end
        end

        # Take square roots for later matrix multiplication
        for obs in 1:o
            for cluster in 1:k
                sqrtR[obs, cluster] = sqrt(R[obs, cluster])
            end
        end

        # Update probabilities
        for cluster in 1:k
            p[cluster] = nk[cluster] / o
        end

        # Update means
        A_mul_B(mu, X, R)
        for cluster in 1:k
            for dim in 1:n
                mu[dim, cluster] /= nk[cluster]
            end
        end

        # Update covariances
        # Add a prior on covariances for numerical stability
        # TODO: Make a real prior (via convex combination) or
        #       relabel as stabilizer
        # TODO: Remove the temporaries used below
        for cluster = 1:k
            # Center values relative to mu
            # Xo = X .- mu[:, cluster]
            for obs in 1:o
                for dim in 1:n
                    Xo[dim, obs] = X[dim, obs] - mu[dim, cluster]
                end
            end
            # Xo = Xo .* sqrtR[obs, cluster]'
            # Downweight values based on R
            for obs in 1:o
                for dim in 1:n
                    Xo[dim, obs] *= sqrtR[obs, cluster]
                end
            end
            # Estimate scatter matrix
            # sigma[:, :, cluster] = Xo * Xo' / nk[cluster]
            A_mul_Bt(sigmatmp, Xo, Xo)
            for dim2 in 1:n
                for dim1 in 1:n
                    sigma[dim1, dim2, cluster] =
                      sigmatmp[dim1, dim2] / nk[cluster]
                end
            end
            for dim in 1:n
                sigma[dim, dim, cluster] += 1e-6
            end
        end

        return
    end

    function Distributions.fit(::Type{MixtureMultivariateNormals},
                 X::Matrix,
                 k::Integer = 2,
                 tol::Real = 1e-8,
                 maxiter::Integer = 500)
        # Cache dimensionality
        n, o = size(X)

        # Reuse storage
        mu = Array(Float64, n, k)
        sigma = Array(Float64, n, n, k)
        p = Array(Float64, k)

        # Initialize cluster assignments
        R = zeros(Float64, o, k)
        initialize!(X, R, mu, n, o, k)

        # Reuse temporaries
        logRho = Array(Float64, k, o)
        logR = Array(Float64, o, k)
        T = Array(Float64, o)
        nk = Array(Float64, k)
        sqrtR = Array(Float64, o, k)
        Xo = Array(Float64, n, o)
        sigmatmp = Array(Float64, n, n)

        # Store log likelihood history
        llh = Array(Float64, maxiter + 1)
        fill!(llh, -Inf)

        # Run EM until relative change in log likelihood goes below threshold
        converged, t = false, 1
        while !converged && t <= maxiter
            t += 1
            mmn_Mstep!(X, Xo, R, mu, sigma, sigmatmp, p, n, o, k, nk, sqrtR)
            llh[t] = mmn_Estep!(X, R, logRho, logR, mu, sigma, p, T, n, o, k)
            if llh[t] - llh[t - 1] < tol * abs(llh[t])
                converged = true
            end
        end

        # Return a full-fledged Distribution object
        return MixtureMultivariateNormals(mu, sigma, p)
    end
end
