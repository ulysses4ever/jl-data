module ParticleFilters

using Distributions

import PyPlot.plot
using PyPlot

export ParticleFilterEstimator, update

"""
X is an MxN array representing N particles, each with M state variables
"""
type ParticleFilterEstimator
    X::Array{Float64, 2}
end

function plot(pf::ParticleFilterEstimator)
    if size(pf.X, 1) == 2
        # assume the first 2 state variables are x, y
        scatter(pf.X[1, :], pf.X[2, :])
    elseif size(pf.X, 1) > 2
        # assume the first 3 state variables are x, y, z
        scatter3D(pf.X[1, :]', pf.X[2, :]', pf.X[3, :]')
    else
        println("Must have at least 2 dimensions to plot")
    end
end


function update!(pf::ParticleFilterEstimator, u, z)
    X2 = predict(pf.X, u)
    w = weights(X2, z)
    pf.X = resample(X2, w)

    # currently just use the mean along each state variable
    mean(pf.X, 2)
end

"""
Given the previous state X and control input vector u, generate a prediction for
the current state X'
"""
function predict(X, u)
    # TODO: calculate the covariance matrix from experimental data
    d = MvNormal(zeros(size(X, 1)), ones(size(X, 1)) * 0.01)

    rand(d, size(X, 2)) + X
end

"""
Given the current state X and measurement vector z, generate a weight vector for
the state estimates
"""
function weights(X, z)

    # const anchors = [ -1.1082  2.0964  1.9340 -0.7987;
    #                    2.3606  2.3635  2.3635  2.3606;
    #                   4.0778  3.8079 -1.8402 -1.7995]
    const anchors = [ 0.0 0.0 1.0 1.0;
                      0.0 1.0 0.0 1.0]

    # TODO: calculate the variance from experimental data
    d = Normal(0.0, 0.1)

    w = ones(size(X, 2))

    for i in 1:length(z)
        # get the difference vector from each location to anchor i
        diff = X .- anchors[:, i]
        # take the norm of the difference vector (the distance to the anchor)
        dist = vec(mapslices(norm, diff, 1))
        # find the error (difference between the expected distance and measured)
        err = dist - z[i]
        # compute the product of the distance likelihoods from each anchor
        w = w .* pdf(d, err)
    end

    # now normalize the weights
    w / norm(w)
end

"""
Given the current state estimate X and weight vector w, resample a new set of
states. We use the low-variance resampling algorithm from Thrun, Burgard, and Fox's
"Probabilistic Robotics". By default it will keep the number of samples constant
"""
function resample(X, w, M=size(X, 2))
    X2 = similar(X, (size(X, 1), M))
    r = rand(Uniform(0, 1/M))
    c = w[1]
    i = 1

    for m in 1:M
        U = r + (m - 1) * (1/M)
        while c < U
            i += 1
            c = c + w[i]
        end
        X2[:, m] = X[i]
    end
    X2
end

end # module
