# Main functions concerning "doubt coefficient" for work on MCL
# Berkeley 2015 - Maxime Legrand

#Pkg.add("Gadfly")
using Gadfly
include("../plot_tools.jl")
include("mcl.jl")

#####################################
# Step by step (customed algorithm) #
#####################################

"""Apply MCL algorithm with expansion parameter e, inflation parameter r and p iterations
Customed version for doubt coefficient"""
function mcl(A;e=2,r=3,p=20,dc="none",de=(if e==2 0 else 1 end),dr=(r*0.2))
    A = mcl_norm(A)
    if dc=="none"
        for i=1:p
            A = mcl_norm(mcl_inflate(mcl_expand(A,e),r))
        end
        return A
    elseif dc=="parallel"
        B1,B2,B3,B4 = A,A,A,A
        for i=1:p
            A = mcl_norm(mcl_inflate(mcl_expand(A,e),r))
            B1 = mcl_norm(mcl_inflate(mcl_expand(B1,e+de),r+dr))
            B2 = mcl_norm(mcl_inflate(mcl_expand(B2,e-de),r+dr))
            B3 = mcl_norm(mcl_inflate(mcl_expand(B3,e-de),r-dr))
            B4 = mcl_norm(mcl_inflate(mcl_expand(B4,e+de),r-dr))
        end
        dc = maximum([norm(A-B1) norm(A-B1) norm(A-B1) norm(A-B1)])
        return (A,dc)
    elseif dc=="forks"
        dc = zeros(p)
        println("de=$de, dr=$dr")
        for i=1:p
            A = mcl_norm(mcl_inflate(mcl_expand(A,e),r))
            B1 = mcl_norm(mcl_inflate(mcl_expand(A,e+de),r+dr))
            B2 = mcl_norm(mcl_inflate(mcl_expand(A,e-de),r+dr))
            B3 = mcl_norm(mcl_inflate(mcl_expand(A,e-de),r-dr))
            B4 = mcl_norm(mcl_inflate(mcl_expand(A,e+de),r-dr))
            dc[i] = maximum([norm(A-B1) norm(A-B1) norm(A-B1) norm(A-B1)])
        end
        return (A,dc)
    end
end

#################
# Input-focused #
#################

##################
# Output-focused #
##################

# Tools

"""SBM form
Input : A adjacency matrix, C vector of clusters (represented as vectors as well)
Output : B reorganised adjacency matrix from A to fit SBM output common outfit"""
function sbm_form(A,C)
    # Vertices permutation
    n = size(A,1)
    K = size(C,1)
    v = zeros(n)
    s = 1
    for k = 1:K
        for i = 1:(size(C[k],1))
            v[C[k][i]] = s
            s += 1
        end
    end
    # Output making
    B = A
    for i = 1:n
        for j = 1:n
            B[i,j] = A[v[i],v[j]]
        end
    end
    return B
end

# SBM Prototype

# DC-SBM Prototype

################################
# Partition of the input space #
################################