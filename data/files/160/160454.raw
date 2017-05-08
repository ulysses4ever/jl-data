import Base.reverse
reverse(n::Number) = n

"""
    partialtrace(ρ,dims,sys)

Compute the partial trace of a matrix ρ with subsystems dimensions specified in
the vector sys_dims (e.g.: [dimA dimB...]) by tracing out the subsystems given
in the vector sys (e.g.: [2 3]).

Function adapted from a MATLAB function by Toby Cubitt available here:
http://www.dr-qubit.org/Matlab_code.html

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


function calc_qubittimeevo(state,time_evo_array)
    excited_prob = zeros(Float64,length(time_evo_array))
    cutoffN = div(size(state,1),2)
    # Time evolve the system density matrix and "measure" the qubit at each time sample taken. This is done by
    # tracing out the resonator and keeping the excited state entry of the density matrix (ie, entry 2,2 in the matrix)
    for i=1:length(time_evo_array)
        excited_prob[i] = real(partialtrace(time_evo_array[i] * state * time_evo_array[i]',[2;cutoffN],2)[2,2])
    end
    return excited_prob
end


function excited_model(x,p,cutoffN,coupling_freq)
    # Fit function (resonator state only)
    a = zeros(Float64,length(x))
    for n=(1:cutoffN)
        a += p[n]*cos(2*sqrt(n-1)*coupling_freq*x)
    end
    return 0.5*(1.0-a)
end


function calc_photonnumbers(time_vec,excited_prob,cutoffN,coupling_freq)
    fun = (x,p)->excited_model(x,p,cutoffN,coupling_freq)
    fit = curve_fit(fun,time_vec,excited_prob,ones(Float64,cutoffN)*0.1)
    return fit.param
end


function calc_densitymatrix_resonator(cutoffN,coupling_freq,initialstate,time_vec,time_evo_array)
    # Solving for the density matrix from photon number distributions
    theta=0:pi/cutoffN:2*pi-pi/cutoffN # we need 2*cutoffN displacements to get enough linearly independent equations
    alpha=1*(cos(theta) + 1im*sin(theta)) # calculating the alpha values for 2*cutoffN displacements from a circle of unit radius

    photon_numbers=zeros(Float64,length(theta),cutoffN)

    M=zeros(Complex128,length(theta)*cutoffN,cutoffN^2)
    for m=1:length(theta)
        # For each angle/displaced state, we first find the photon number distribution
        # Generating the displacement operator for angle m
        displacement_operator = gen_displacementop(alpha[m],cutoffN)
        sys_displacement = (kron(identity,displacement_operator))
        excited_prob = calc_qubittimeevo(sys_displacement'*initialstate*sys_displacement,time_evo_array)
        # Solving for the displaced state photon number distributions
        photon_numbers[m,:] = calc_photonnumbers(time_vec,real(excited_prob),cutoffN,coupling_freq)
        # display(m/length(theta)) # very basic "progress bar"
        # We then calculate the displacement operator matrix elements
        for n=1:cutoffN
            for i=1:cutoffN
                for j=1:cutoffN
                    # Generating the displacement operator matrix elements
                    M[(m-1)*cutoffN+n,(i-1)*cutoffN+j] = convert(Complex128,(displacement_operator'[n,i] * displacement_operator[j,n]))
                end
            end
        end
    end
    # Reshaping the array in a form suitable to solving the system of equations
    photon_numbers=reshape(transpose(photon_numbers),length(theta)*cutoffN,1)
    # Solving the system of equations (very slighly overdetermined, there will
    # be some least square fitting). The system to solve is:
    # photon_numbers = M * densityMatrixElements
    density_matrix = M\photon_numbers; # Vector form of the density matrix (ie the elements are 00, 01, 02, ..., cutoffNcutoffN-1, cutoffNcutoffN)
    density_matrix = transpose(reshape(density_matrix,cutoffN,cutoffN)); # Reshaping the vector into an actual matrix
end


function calc_wignerfunction_resonator(cutoffN,wignerSamples,coupling_freq,initialstate,time_vec,time_evo_array)
    # Solving for the Wigner Function from photon number distributions
    wigner=zeros(Float64,wignerSamples,wignerSamples)
    parity_matrix=ones(Float64,cutoffN,1);parity_matrix[2:2:cutoffN]=-1;
    #
    for realIndex=1:wignerSamples
        for imagIndex=1:wignerSamples
            displacement_operator = kron(identity,gen_displacementop((realIndex-wignerSamples/2)/10 + 1im*(imagIndex-wignerSamples/2)/10,cutoffN)) # generating the displacement operator for angle m
            # For each displaced state, we first find the photon number distribution
            excited_prob = calc_qubittimeevo(displacement_operator'*initialstate*displacement_operator,time_evo_array)
            photon_numbers = calc_photonnumbers(time_vec,real(excited_prob),cutoffN,coupling_freq) # solving for the displaced state photon number distributions
            # We then fill the corresponding entry in the winger function array
            wigner[imagIndex,realIndex] = 2./pi .* sum(parity_matrix .* photon_numbers)
        end
    end
    return wigner
end


function cal_densitymatrix_qubit(xup,yup,zup)
    # A qubit in state |ψ> is defined by two values, a & b, where |ψ> = a|↑>+b|↓>. By convention, a is real and positive, and b is in general complex.

    # From the probability of measuring |↑> (that is, measuring "up" in the z basis), we can deduce a, and the magnitude of b

    a = sqrt(zup)
    magb = sqrt(1-zup)

    # The probability of measuring "up" in the x basis is equal to |1/sqrt(2)*(<↑|+<↓|) |ψ>|^2, which is equal to 1/2(a^2+b^2) + a mag(b) cos(ϕ)
    cosϕ = ( xup - (a^2 + magb^2)/2 ) / (a * magb)

    # The probability of measuring "up" in the y basis is equal to |1/sqrt(2)*(<↑|-i<↓|) |ψ>|^2, which is equal to 1/2(a^2+b^2) + a mag(b) sin(ϕ)
    sinϕ = ( yup - (a^2 + magb^2)/2 ) / (a * magb)

    b = magb * (cosϕ + 1im * sinϕ)

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
        fullVector = kron(eye(dimOfSubsystemToKeep),vector)
        matrix = matrix + fullVector' * rho * fullVector
    end

    return matrix
end
