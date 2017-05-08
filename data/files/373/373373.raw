# Set up dictionaries to store parameters, etc.

# ---------------------- Basic parameters ---------------------------------

immutable Parameters
    D::Int
    T::Int
    I::Int
    max_b::Int
    w_max::Int
    gamma::Float64
    controls::Vector{Float64}
    num_controls::Int
    o_vec::Matrix{Int}
end

D = 100
T = 15
I = 30
max_b = 500
w_max = 10000
gamma = 100/110
controls = collect(-8:0.5:2)
num_controls = length(controls)
o_vec = collect(-8:2).'

param = Parameters(D, T, I, max_b, w_max, gamma,
                    controls, num_controls, o_vec)

# -------------------------------------------------------------------------
immutable Dist
    prob_o::Matrix{Float64}
end

# hard-code distribution
dist = Dist([param.o_vec; repmat([1/11], 1, 11)])


# ---------------------- Storage of data ----------------------------------
immutable Data
    signals::Matrix{Float64}
end
data = Data(repmat([-4.0], param.I, 1))

