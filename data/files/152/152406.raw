module ParticleFilters

using Distributions
using StatsBase

# import PyPlot.plot
# using PyPlot

export ParticleFilterEstimator, update!

"""
X is an MxN array representing N particles, each with M state variables
"""
type ParticleFilterEstimator
    X::Array{Float64, 2}
    ranges::Array{Float64, 2}
    anchors::Array{Float64, 2}

    function ParticleFilterEstimator(n::Integer, xrange, yrange, zrange, anchors)
        xdiff = maximum(xrange) - minimum(xrange)
        ydiff = maximum(yrange) - minimum(yrange)
        zdiff = maximum(zrange) - minimum(zrange)

        xoff = minimum(xrange)
        yoff = minimum(yrange)
        zoff = minimum(zrange)
        particlesInit = rand(3, n) .* [xdiff, ydiff, zdiff] .- [xoff, yoff, zoff]
        ranges = [xrange[1] yrange[1] zrange[1];
                  xrange[2] yrange[2] zrange[2]]
        new(particlesInit, ranges, anchors)
    end

    function ParticleFilterEstimator(n::Integer=1000)
        # anchor locations for Fluid optitrack test
        anchors = [ -1.1082  2.0964  1.9340 -0.7987;
                  2.3606  2.3635  2.3635  2.3606;
                  4.0778  3.8079 -1.8402 -1.7995]

        ParticleFilterEstimator(n, (-3, 3), (0, 3), (-3, 3), anchors)
    end
end

# function plot(pf::ParticleFilterEstimator, z=nothing)
#     if z == nothing
#         c = nothing
#     else
#         l(x) = likelihood(x, z)
#         c = vec(mapslices(l, pf.X, 1))
#     end
#
#     if size(pf.X, 1) == 2
#         # assume the first 2 state variables are x, y
#         if c != nothing
#             scatter(pf.X[1, :], pf.X[2, :], c=c, s=5)
#             colorbar()
#         else
#             scatter(pf.X[1, :], pf.X[2, :], s=5)
#         end
#     elseif size(pf.X, 1) > 2
#         # assume the first 3 state variables are x, y, z
#         if c != nothing
#             scatter3D(pf.X[1, :]', pf.X[2, :]', pf.X[3, :]', c=c, s=5)
#         else
#             scatter3D(pf.X[1, :]', pf.X[2, :]', pf.X[3, :]', s=5)
#         end
#     else
#         println("Must have at least 2 dimensions to plot")
#     end
# end
#
# """
# Plots the likelihood with the given observation
# """
# function plotlikelihood(pf::ParticleFilterEstimator, z::Vector)
#     v = linspace(0, 1, 100)
#     l = Array(Float64, 100, 100)
#     for (i, x) in enumerate(v)
#         for (j, y) in enumerate(v)
#             l[i, j] = likelihood([x, y], z)
#         end
#     end
#
#     imshow(l; origin="lower")
#     colorbar()
# end

function update!(pf::ParticleFilterEstimator, u, z, maxiters=20, thresh=[0.01, 0.02, 0.01])
    errbias = [0.1153, 0.0571, 0.0237, 0.0538]

    # copy so we don't mess it up when we subtract off the error bias
    z = copy(z)

    for i in 1:length(z)
        if z[i] != -1.0
            # correct for the bias that we measured per-anchor
            z[i] = z[i] - errbias[i]
        end
    end

    fitnorm = fit(DiagNormal, pf.X)
    iters = 0
    while iters < maxiters
        X2 = predict(pf.X, u)
        w = weights(X2, z, pf)
        pf.X, _ = resample(X2, w)
        fitnorm = fit(DiagNormal, pf.X)
        iters += 1
        # check at the end so we make sure we go at least one time through even
        # if the system started out with small covariance
        if all(diag(cov(fitnorm)) .< thresh)
            break
        end
    end

    fitnorm, iters
end

"""
Given the previous state X and control input vector u, generate a prediction for
the current state X'
"""
function predict(X, u)
    # TODO: calculate the covariance matrix from experimental data
    d = MvNormal(zeros(size(X, 1)), ones(size(X, 1)) * 0.1)

    rand(d, size(X, 2)) + X
end

"""
Computes the likelihood of the obvservation z given the state x
"""
function likelihood(x::Vector{Float64}, z::Vector{Float64}, pf::ParticleFilterEstimator)
    # approximate std dev (rounded up a bit) from measured data
    d = Normal(0.0, 0.035)

    l = 1.0
    for i in 1:length(z)
        if z[i] != -1.0
            l *= (0.2 + 0.8 * pdf(d, norm(x - pf.anchors[:, i]) - z[i]))
        else
            l *= 0.2
        end
    end

    for i in 1:3
        if !(pf.ranges[1, i] < x[i] < pf.ranges[2, i])
            # keep our solutions inside the box. This is particularly an issue
            # for reflections across the plane of the sensors, but is also to keep
            # the particle population from drifting out too much if there's no data
            l = 0.0
        end
    end

    l
end

"""
Given the current state X and measurement vector z, generate a weight vector for
the state estimates
"""
function weights(X::Array{Float64, 2}, z::Vector{Float64}, pf::ParticleFilterEstimator)
    # for i in 1:length(z)
    #     # get the difference vector from each location to anchor i
    #     diff = X .- anchors[:, i]
    #     # take the norm of the difference vector (the distance to the anchor)
    #     dist = vec(mapslices(norm, diff, 1))
    #     # find the error (difference between the expected distance and measured)
    #     err = dist - z[i]
    #     # compute the product of the distance likelihoods from each anchor
    #     w = w .* pdf(d, err)
    # end

    # create a temporary function to compute the likelihood with the given z
    l(x::Vector{Float64}) = likelihood(x, z, pf)

    w = vec(mapslices(l, X, 1))
    # now normalize the weights
    w / sum(w)
end

"""
Given the current state estimate X and weight vector w, resample a new set of
states. We use the low-variance resampling algorithm from Thrun, Burgard, and Fox's
"Probabilistic Robotics". By default it will keep the number of samples constant
"""
function resample(X, w, M=size(X, 2))
    X2 = similar(X, (size(X, 1), M))
    w2 = zeros(M)
    r = rand(Uniform(0, 1/M))
    c = w[1]
    i = 1
    for m in 1:M
        # calculate the next sample point
        U = r + (m - 1) * (1/M)
        while c < U
        # find the first weight that puts us past the sample point
            i += 1
            c = c + w[i]
        end
        X2[:, m] = X[:, i]
        w2[m] = w[i]
    end
    X2, w2
end

"""
Resample using the sample function from StatsBase
"""
function resample2(X, w, M=size(X, 2))
    X2 = similar(X, (size(X, 1), M))
    w2 = zeros(M)
    wv = WeightVec(w)

    for m in 1:M
        i = sample(wv)
        X2[:, m] = X[:, i]
        w2[m] = w[i]
    end
    X2, w2
end

end # module
