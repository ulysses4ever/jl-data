import Base.reverse
reverse(n::Number) = n

"""
    partialtrace(ρ,dims,sys)

Compute the partial trace of a matrix ρ with subsystems dimensions specified in
the vector sys_dims (e.g.: [dimA dimB...]) by tracing out the subsystems given
in the vector sys (e.g.: [2 3]).

Function adapted from a MATLAB function by Toby Cubitt available here:
http://www.dr-qubit.org/Matlab_code.html and licensed under GPL2.

# Arguments
* `ρ::Matrix`: matrix
* `dims::Vector{Int}`: vector specifying the dimensions of the subsystems
  that the full matrix contains. A qubit and resonator state (with the Fock
  space truncated to 6) would have sys_dim = [2 6].
* `sys::Union{Vector{Int},Int}`: vector (or single value) specifying the indices
  of the subsystems to trace out.

# Examples
```jldoctest
julia> ρ = [0.5 0 0 0.5; 0 0 0 0; 0 0 0 0; 0.5 0 0 0.5]
julia> dims = [2;2] # two qubits
julia> sys = 1 # trace out the first qubit
julia> partialtrace(ρ,dims,sys)
2×2 Array{Float64,2}:
 0.5  0.0
 0.0  0.5
```
"""
function partialtrace(ρ::Matrix,dims::Vector{Int},sys::Union{Vector{Int},Int})
    # Make sure the input arguments make sense
    if any(sys.>length(dims))
        error("You have given a system index too high for the dimensions specified in `dims`")
    end
    if prod(dims) != size(ρ,1)
        error("The subsystem dimensions given in `dims` are not consistent with those of the matrix")
    end
    # First, calculate systems, dimensions, etc.
    n = length(dims)
    rdims = reverse(dims)
    keep = 1:n
    flag = trues(size(keep))
    flag[sys] = false
    keep = keep[flag]
    dimstrace = prod(dims[sys])
    dimskeep = div(size(ρ,1),dimstrace)
    # Reshape density matrix into tensor with one row and one column index
    # for each subsystem, permute traced subsystem indices to the end,
    # reshape again so that first two indices are row and column
    # multi-indices for kept subsystems and third index is a flattened index
    # for traced subsystems, then sum third index over "diagonal" entries
    perm = n+1-[reverse(keep);reverse(keep)-n;sys;sys-n]
    x = reshape(permutedims(reshape(ρ,[rdims;rdims]...),perm),dimskeep,dimskeep,dimstrace^2)
    return sum(x[:,:,1:dimstrace+1:dimstrace^2],3)[:,:,1]
end


function calc_qubittimeevo(ρ,U_array)
    # Time evolve the system density matrix by applying the time evolution
    # operator and measure the qubit state at each step. This is done by
    # tracing out the resonator system and keeping the excited states entry.
    N = div(size(ρ,1),2)
    map(U_array) do U
        real(partialtrace(U*ρ*U',[2,N],2)[2,2])
    end
end


function calc_qubittimeevo_rel(ρ,U_rel_array,steps,decimation=10)
    # Time evolve the system density matrix by applying the relative time
    # evolution in succession and measure the qubit state at each step.
    N = div(size(ρ,1),2)
    c = length(U_rel_array)
    ρ_evo = deepcopy(ρ)
    #nvec = collect(0.0:N-1)'

    e_prob = Array{Float64}(ceil(Int,steps/decimation))
    #n_expect = Array{Float64}(ceil(Int,steps/decimation))

    j = 1
    for i = 1:steps
        # Note the use of the modulo operation to apply U in cycles
        ρ_evo = U_rel_array[(i-1)%c+1]*ρ_evo*U_rel_array[(i-1)%c+1]'
        if (i-1)%decimation==0
            e_prob[j] = real(partialtrace(ρ_evo,[2,N],2)[2,2])
            #n_expect[j] = (nvec'*real(diag(partialtrace(ρ_evo,[2,N],1))))[1]
            j += 1
        end
    end
    return e_prob
end


function calc_photonnumbers(N,g,times,e_prob)
    M = length(times)
    B = Array{Float64}(M,N)
    @compat B[:,1] .= 1.0
    for n = 2:N
        f = 2*sqrt(n-1)*g
        @compat B[:,n] .= cos.(f.*times)
    end
    return B\(1-2*e_prob)
end


function calc_densitymatrix_resonator(ρ,g,times,U_array)
    # Solving for the density matrix from photon number distributions
    N = div(size(ρ,1),2)
    # We need 2*N displacements to get enough linearly independent
    # equations. We sample the alpha values from a circle of unit radius.
    α = [1.0*complex(cos(θ),sin(θ)) for θ in 0:π/N:2π-π/N]
    # Do the math
    res = pmap(α) do α
        # For each angle/displaced state, we first find the photon number distribution
        # Generating the displacement operator for angle α
        Dα = qeye(2) ⊗ gen_displacementop(α,N)
        # Solving for the displaced state photon number distribution
        e_prob = calc_qubittimeevo(Dα'*ρ*Dα,U_array)
        photon_numbers = calc_photonnumbers(N,g,times,e_prob)
        # We then calculate the displacement operator matrix elements
        M = Array{Complex128}(N,N^2)
        for n=1:N, i=1:N, j=1:N
            # Generating the displacement operator matrix elements
            M[n,(i-1)*N+j] = conj(Dα[i,n]) * Dα[j,n]
        end
        photon_numbers,M
    end
    # Reshaping the result into arrays for solving the system of equations
    photon_numbers = vcat([res[1] for res in res]...)
    M = vcat([res[2] for res in res]...)
    # Solving the system of equations (very slighly overdetermined, there will
    # be some least square fitting). The system to solve is:
    # photon_numbers = M * ρ
    ρ_res = M\photon_numbers # Vector form of the density matrix (ie the elements are 0 0, 0 1, 0 2, ..., N N-1, N N)
    ρ_res = transpose(reshape(ρ_res,N,N)) # Reshaping the vector into an actual matrix
end


function calc_wignerfunction_resonator(ρ,g,times,U_array,w_samples;maxdisp=MAXDISP)
    N = div(size(ρ,1),2)
    # Solving for the Wigner function from photon number distributions
    parity_matrix = [(-1.0)^i for i = 0:N-1]
    # Choose where to plot the function
    disp = linspace(-maxdisp,maxdisp,w_samples)
    # Iterate over all displacements
    W = pmap(product(disp,disp)) do id
        # Generating the displacement operator for that matrix element
        Dα = qeye(2) ⊗ gen_displacementop(complex(id[1],id[2]),N)
        # For each displaced state, we first find the photon number distribution
        e_prob = calc_qubittimeevo(Dα'*ρ*Dα,U_array)
        photon_numbers = calc_photonnumbers(N,g,times,e_prob)
        # We then calculate the entry.
        2/π * sum(parity_matrix .* photon_numbers)
    end
    return convert(Array{Float64,2},reshape(W,w_samples,w_samples))
end


function calc_wignerfunction_resonator(ρ_res,w_samples;maxdisp=MAXDISP)
    N = size(ρ_res,1)
    # Solving for the Wigner function from the density matrix
    parity_matrix = [(-1.0)^i for i = 0:N-1]
    # Choose where to plot the function
    disp = linspace(-maxdisp,maxdisp,w_samples)
    # Iterate over all displacements
    map(product(disp,disp)) do id
        # Generating the displacement operator for that matrix element
        Dα = gen_displacementop(complex(id[1],id[2]),N)
        # We then calculate the entry.
        2/π * sum(parity_matrix .* real(diag(Dα'*ρ_res*Dα)))
    end
end


function cal_densitymatrix_qubit(xup,yup,zup)
    # A qubit in state |ψ> is defined by two values, a & b, where |ψ> =
    # a|↑>+b|↓>. By convention, a is real and positive, and b is in general
    # complex. From the probability of measuring |↑> (that is, measuring "up" in
    # the z basis), we can deduce a, and the magnitude of b
    a = sqrt(zup)
    magb = sqrt(1-zup)
    # The probability of measuring "up" in the x basis is equal to
    # |1/sqrt(2)*(<↑|+<↓|)|ψ>|^2, which is equal to 1/2(a^2+b^2)+a*mag(b)cos(ϕ)
    cosϕ = ( xup - (a^2 + magb^2)/2 ) / (a * magb)
    # The probability of measuring "up" in the y basis is equal to
    # |1/sqrt(2)*(<↑|-i<↓|)|ψ>|^2, which is equal to 1/2(a^2+b^2)+a*mag(b)sin(ϕ)
    sinϕ = ( yup - (a^2 + magb^2)/2 ) / (a * magb)
    b = magb * complex(cosϕ,sinϕ)
    return a, b
end


function partialtrace_old(rho,dimOfSubsystemToKeep)
    # First check if the density matrix is Hermitian
    if maximum(abs(rho'-rho))>8E-15
        error("This density matrix is not Hermitian!")
    end
    dimOfSubsystemToTraceOut = div(size(rho)[1] , dimOfSubsystemToKeep)
    matrix = zeros(Complex128,dimOfSubsystemToKeep,dimOfSubsystemToKeep)
    for i=1:dimOfSubsystemToTraceOut
        vector = zeros(Complex128,dimOfSubsystemToTraceOut)
        vector[i] = (1.0+1.0im)/sqrt(2)
        fullVector = qeye(dimOfSubsystemToKeep) ⊗ vector
        matrix = matrix + fullVector' * rho * fullVector
    end
    return matrix
end
