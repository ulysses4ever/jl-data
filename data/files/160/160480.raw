function gen_initialstate(N,kets)

    ketCoeff = zeros(Complex128,length(kets),1)
    parameterArray = zeros(Int,length(kets),2)

    for (i,str) in enumerate(kets)
        # First we find where the ket starts
        ketstart = search(str,'|')
        # Grabbing the coefficient in front of ket
        coeff = str[1:ketstart-1]
        if isempty(coeff)
            ketCoeff[i] = 1
        elseif coeff == '-'
            ketCoeff[i] = -1
        else
            ketCoeff[i] = eval(parse(coeff))
        end
        # Grabbig qubit state
        if str[ketstart+1] == 'g'
            parameterArray[i,1] = 0
        elseif str[ketstart+1] == 'e'
            parameterArray[i,1] = 1
        else
            error("Error, qubit state should be 'g' or 'e'")
        end
        # Grabbing resonator state
        parameterArray[i,2] = parse(Int,str[ketstart+3:end-1])
    end

    # Making sure that N is large enough
    if N <=  maximum(parameterArray[:,2])
        error("The size of the resonator space (N) must be at least the size of the larger number state plus one (due to zero state)!")
    end

    # Assembling the state density matrix
    state = zeros(Complex128,2N,2N)

    for i = 1:length(kets), j = 1:length(kets)
        # Defining the ket
        qubit_ket = zeros(Complex128,2,1) # Initialising the qubit ket (2D)
        qubit_ket[parameterArray[i,1]+1] = 1 # Setting the vector as (1 0) for g or (0 1) for e
        resonator_ket = zeros(Complex128,N,1) # Initialising the resonator ket (ND)
        resonator_ket[parameterArray[i,2]+1] = 1 # Setting the vector
        ket = qubit_ket ⊗ resonator_ket # Tensor product
        # Defining the bra
        qubit_bra =zeros(Complex128,2,1)
        qubit_bra[parameterArray[j,1]+1] = 1
        resonator_bra = zeros(Complex128,N,1)
        resonator_bra[parameterArray[j,2]+1] = 1
        bra = (qubit_bra ⊗ resonator_bra)'
        # Multiplying the initial ket with its complex conjugate to make
        # the density matrix
        state = state + ketCoeff[i]*ketCoeff[j]'*ket*bra
    end

    norm = 1/sum(abs(ketCoeff[:]).^2)
    state = norm*state # Norming
    return state
end


function gen_hamiltonian(N,ω_q,ω_r,g;rwa=true,noisy=false)
    # This function generates a times invariant matrix for the Jaynes-Cummings
    # Hamiltonian. The parameters ω_r, ω_q and g should be given in
    # rad/s. The N parameter is the highest energy level of the harmonic
    # oscillator that is considered. Higher levels are truncated.

    # The Jaynes-Cummings Hamiltonian is written with the following
    # conventions: ω_r is the resonator frequency, ω_q is the qubit
    # frequency and g is the coupling. The resonator Hilbert space is truncated
    # to n = N, and the ground state of the qubit is given by the vector
    # [1;0] (hence the minus sign before σ_z).

    H = ħ * ω_r * qeye(2) ⊗ (a_dagger(N)*a(N)) - # resonator
        0.5 * ħ * ω_q * σ_z ⊗ qeye(N) # qubit

    if rwa # interaction, with or without rotating wave approximation
        H += ħ * g * ( σ_plus ⊗ a(N) + σ_minus ⊗ a_dagger(N) )
    else
        H += ħ * g * (σ_plus + σ_minus) ⊗ (a(N) + a_dagger(N))
    end

    if noisy
        noise = rand(Complex128,2N,2N)
        H += 0.01 * ħ * g * (noise'+noise)
    end

    return H
end


function gen_drive_hamiltonian(ω_d,N,samples=16)
    Δt = (2π/ω_d)/samples # Calculate Δt based on the desired number of samples per period
    time_vec = linspace(0,2π/ω_d,samples+1)[1:end-1] # Calculate operator for a full period
    I_m = qeye(2)
    adag_m = a_dagger(N)
    a_m = a(N)
    H_d_array = map(time_vec) do t
        ħ * I_m ⊗ (adag_m*exp(-im * ω_d * t) + a_m*exp(im * ω_d * t))
    end
    return Δt, H_d_array
end


function gen_timeevoarray(H,t_f,samples)
    # Generate the time evolution operators for a time-independent Hamiltonian
    times = linspace(0,t_f,samples+1)[1:end-1]
    U_array = map(times) do t
        expm(-1.0im * H * t / ħ)
    end
    return times, U_array
end


function gen_displacementop(α,N)
    # Generate the harmonic oscillator displacement operator
    expm( α * a_dagger(N) - α' * a(N) )
end


function qeye(d)
    eye(Complex128,d)
end


function a(N) # Truncated matrix for the lowering operator
    out = zeros(Complex128,N,N)
    for i = 1:N-1
        out[i,i+1] = sqrt(i)
    end
    return out
end


function a_dagger(N) # Truncated matrix for the raising operator
    out = zeros(Complex128,N,N)
    for i = 1:N-1
        out[i+1,i] = sqrt(i)
    end
    return out
end
