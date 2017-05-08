
using Distributions
using NumbericExtensions
using MLBase

import MixtureModels.AbstractModelEstimator
import MixtureModels.MLE_Estimator
import MixtureModels.MAP_Estimator
import MixtureModels.fit

include("util.jl")
include("ssm.jl")


# Can allow mixture distribution at some point as well using Dahua's
# MixtureModels.jl package.
type HMM{C<:Distribution} <: StateSpaceModel
    
    K::Int
    states::Vector{C}
    pi::Vector{Float64}
    A::Matrix{Float64}

end

function HMM{C<:Distribution}(states::Vector{C}, pi::Vector{Float64},
                              A::Matrix{Float64})
    K = length(states)
    @assert K == length(pi)
    @assert K == size(A,1)
    @assert K == size(A,2)

    HMM{C}(K, states, pi, A)
end


type HMMResultEM{C<:Distribution}

    model::HMM{C}

    niters::Int
    converged::Bool
    objective::Float64
end




function fit_hmm!{C<:Distribution}(estim::MLE_Estimator{C}, data, gamma::Matrix{Float64},
                                  xi::Array{Float64,3}; maxiter::Int=100,
                                  tol::Float64=1e-9, verbose)
# Find MLE estimates of parameters for a finite HMM with K components 
# according to data using EM.
#
# estim : MLE_Estimator{C} that determines what fit to call for distribution C
# data : D x N matrix of N observations in D dimensions.
# gamma : N x K matrix where gamma[n,k] = p(z_n = k | x_{1:n}) (i.e.
#         filtering distribution).
# xi : N x K x K array where xi[n,j,k] = p(z_{n-1} = j, z_n = k | x_{1:n})
# maxiter : Maximum number of iterations.
# tol : numerical tolerance to check for convergence.
# verbose : How much information to print.
#
# Notes:
#   - gamma and xi are modified in place
#

    # Setup
    N = size(data, 2)
    @assert size(gamma, 1) == N
    @assert size(xi, 3) == N

    K = size(gamma, 2)

    # Temporary storage
    states = Array(d, K)
    trans = Array(Float64, K, K)
    pi = Array(Float64, K)

    fmsgs = Array(Float64, K, N)
    bmsgs = Array(Float64, K, N)
    trans_norm = Array(Float64, K)

    L = Array(Float64, N, K)  # L[N,k] = lprob(x_N | z_N=k)
    E = Array(Float64, N, K)  # E[N,k] = 


    # Optimization loop
    it = 0
    converged = false

# Maybe print something here about status

    while !converged && t < maxiter
        t += 1

        # Initial gamma and xi can be thought of as E-step
        # M-step

        # Since only one data set just set the initial state distribution as a
        # Dirac measure on the first state.
        pi = gamma[1,:]
        pi = multiply!(pi, inv(N))

        sum!(trans, xi, 3)
        sum!(trans_norm, trans, 2)
        vbroadcast!(trans, 1./trans_norm, 1)
        
        for k in 1:K
            st = fit(estim, data, gamma[:,k])
            states[k] = st

            Lk = pointer_to_array(pointer(L, (k-1)*N + 1), N)
            logpdf!(Lk, comp, data)
        end


        # E-step
        # Compute forward and backward messages
        # Update gamma and xi

    end

end



# TODO
function forward_msgs!(fmsg, fZ, L, N, K)
    fmsg[:,1] = 1. / N
    fZ[1] = 1
    for n in 2:N
        fmsg[:,n] = 
        fZ[n] = 
    end
end

# TODO
function backward_msgs!(bmsg, bZ, trans, L, N, K)
end
