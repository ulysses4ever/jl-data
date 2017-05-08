module HMM

using Distributions

import Distributions.rand
import Distributions.fit

immutable HiddenMarkovModel{TP, K}
    theta::Vector{TP}
    A::Matrix{Float64}
    pi::Vector{Float64}

    function HiddenMarkovModel(theta, A, pi)
        @assert length(theta) == K
        @assert size(A) == (K, K)
        @assert length(pi) == K

        tol = 1e-6

        #@assert sum(pi) - 1.0 < tol, sum(pi)

        for k=1:K
            #@assert(sum(A[k, :]) - 1.0 < tol, string(k, " ", sum(A[k, :])))
        end

        return new(theta, A, pi)
    end
end

function HiddenMarkovModel{TP}(::Type{TP}, K::Int64)
    pi = rand(K)
    pi /= sum(pi)

    theta = [TP() for k=1:K]

    A = rand(K, K)
    for k=1:K
        A[k, :] /= sum(A[k, :])
    end

    return HiddenMarkovModel{TP, K}(theta, A, pi)
end

function HiddenMarkovModel{TP}(theta::Vector{TP})
    K = length(theta)
    pi = rand(K)
    pi /= sum(pi)

    A = rand(K, K)
    for k=1:K
        A[k, :] /= sum(A[k, :])
    end

    return HiddenMarkovModel{TP, K}(theta, A, pi)
end

function rand{TP, K}(hmm::HiddenMarkovModel{TP, K}, len::Int64)
    z = zeros(Int, len)

    _pi = prior_distribution(hmm)
    z[1] = rand(_pi)
    _A = transition_distributions(hmm)
    for i=2:len
        z[i] = rand(_A[z[i-1]])
    end

    x = Array(typeof(rand(hmm.theta[1])), len)
    for i=1:len
        x[i] = rand(hmm.theta[z[i]])
    end

    return (x, z)
end

function transition_distributions{TP, K}(hmm::HiddenMarkovModel{TP, K})
    A = Array(Categorical, K)
    for k=1:K
        A[k, :] = Categorical(vec(hmm.A[k, :]))
    end

    return A
end

function viterbi{TP, K, TO}(hmm::HiddenMarkovModel{TP, K}, x::Array{TO})
    len = length(x)
    z = zeros(Int64, len)

    backptr = zeros(Int64, len-1, K)
    pr = zeros(K)

    for k=1:K
        pr[k] = logpdf(hmm.theta[k], x[1]) + log(hmm.pi[k])
    end

    for i=2:len
        next_pr = zeros(K)
        for k=1:K
            maxk, maxp = -1, -Inf
            for t=1:K
                prob = pr[t] + log(hmm.A[t, k]) + logpdf(hmm.theta[k], x[i])
                if prob > maxp
                    maxk, maxp = t, prob
                end
            end
            backptr[i-1, k] = maxk
            next_pr[k] = maxp
        end
        pr = next_pr
    end

    z[len] = indmax(pr)
    for i=len-1:-1:1
        z[i] = backptr[i, z[i+1]]
    end

    return z
end

numstates{TP, K}(::HiddenMarkovModel{TP, K}) = K
numstates{TP, K}(::Type{HiddenMarkovModel{TP, K}}) = K
partype{TP, K}(::HiddenMarkovModel{TP, K}) = TP
partype{TP, K}(::Type{HiddenMarkovModel{TP, K}}) = TP

function fit{HMM <: HiddenMarkovModel}(hmm_type::Type{HMM}, x; conv_eps=1e-10, init_params=None, fit_param=fit, print_iteration=true)
    len = size(x, 1)
    K = numstates(hmm_type)
    TP = partype(hmm_type)

    hmm = if init_params == None
        HiddenMarkovModel(TP, K)
    else
        HiddenMarkovModel(init_params)
    end
        
    old_likelihood = -Inf
    while true
        alpha = zeros(len, K)
        beta = zeros(len, K)
        c = zeros(len)

        alpha[1, :] = hmm.pi .* [pdf(hmm.theta[k], slicedim(x, 1, 1))[1] for k=1:K]
        c[1] = sum(alpha[1, :])
        alpha[1, :] /= K

        for i=2:len
            for k=1:K
                alpha[i, k] = pdf(hmm.theta[k], slicedim(x, 1, i))[1]
                a = 0.
                for t=1:K
                    a += hmm.A[t, k] * alpha[i-1, t]
                end
                alpha[i, k] *= a
            end
            c[i] = sum(alpha[i, :])
            alpha[i, :] /= c[i]
        end

        beta[len, :] = 1.
        for i=len-1:-1:1
            for k=1:K
                b = 0.
                for t=1:K
                    b += beta[i+1, t] * pdf(hmm.theta[t], slicedim(x, 1, i+1))[1] * hmm.A[k, t]
                end
                beta[i, k] = b / c[i+1]
            end
        end

        likelihood = sum(log(c))
        if print_iteration == true; println("EM iteration. log-likelihood=", likelihood); end
    
        gamma = alpha .* beta
        ksi = zeros(len, K, K)

        for i=2:len
            for k=1:K
                for t=1:K
                    ksi[i, t, k] = alpha[i-1, t] * beta[i, k] * pdf(hmm.theta[k], slicedim(x, 1, i))[1] * hmm.A[t, k] / c[i]
                end
            end
        end

        A = zeros(K, K)
        for k=1:K
            for t=1:K
                for i=2:len
                    A[k, t] += ksi[i-1, k, t]
                end
            end
            A[k, :] /= sum(A[k, :])
        end

        theta = Array(TP, 0)
        for k=1:K
            push!(theta, fit_param(TP, x, vec(gamma[:, k])))
        end

        hmm = HiddenMarkovModel{TP, K}(theta, A, vec(gamma[1, :] / sum(gamma[1, :])))
        
#assert(old_likelihood < likelihood, "likelihood should monotonically increase")
        if abs(old_likelihood - likelihood) < conv_eps
            return hmm
        end

        old_likelihood = likelihood
    end
end

function fit(::Type{Normal}, x::Vector{Float64}, weights::Vector{Float64})
    mu = sum(x .* weights) / sum(weights)
    y = x - mu
    var = sum((y .^ 2) .* weights) / sum(weights)

    return Normal(mu, sqrt(var))
end

prior_distribution{TP, K}(hmm::HiddenMarkovModel{TP, K}) = Categorical(hmm.pi)

export HiddenMarkovModel, transition_distributions, prior_distribution, rand
export numstates, partype
export viterbi, fit

end

