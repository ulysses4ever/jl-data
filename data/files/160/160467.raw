function gen_initialstate(cutoffN::Integer,x::Array{String})

    ketCoeff = zeros(Complex128,length(x),1)
    parameterArray = zeros(Int,length(x),2)

    for (i,str) in enumerate(x)
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

    # Making sure that cutoffN is large enough
    if cutoffN <=  maximum(parameterArray[:,2])
        error("The size of the resonator space (cutoffN) must be at least the size of the larger number state plus one (due to zero state)!")
    end

    # Assembling the state density matrix
    state = zeros(Complex128,2*cutoffN,2*cutoffN)

    for i = 1:length(x)
        for j = 1:length(x)
            # Defining the ket
            qubitPartKet = zeros(Complex128,2,1) # Initialising the qubit ket (2D)
            qubitPartKet[parameterArray[i,1]+1] = 1 # Setting the vector as (1 0) for g or (0 1) for e
            resonatorPartKet = zeros(Complex128,cutoffN,1) # Initialising the resonator ket (cutoffND)
            resonatorPartKet[parameterArray[i,2]+1] = 1 # Setting the vector
            ket = kron(qubitPartKet,resonatorPartKet) # Tensor product
            # Defining the bra
            qubitPartBra =zeros(Complex128,2,1)
            qubitPartBra[parameterArray[j,1]+1] = 1
            resonatorPartBra = zeros(Complex128,cutoffN,1)
            resonatorPartBra[parameterArray[j,2]+1] = 1
            bra = kron(qubitPartBra,resonatorPartBra)'
            # Multiplying the initial ket with its complex conjugate to make
            # the density matrix
            state = state + ketCoeff[i]*ketCoeff[j]'*ket*bra
        end
    end

    norm = 1/sum(abs(ketCoeff[:]).^2)
    state = norm*state # Norming
    return state
end


function gen_hamiltonian(omegaQ,omegaR,g,cutoffN,noiseAdded)
    # This function generates a times invariant matrix for the Jaynes-Cummings
    # Hamiltonian. The parameters omegaR, omegaQ and g should be given in
    # rad/s. The cutoffN parameter is the highest energy level of the harmonic
    # oscillator that is considered. Higher levels are truncated.

    # Some constant parameters for the Jaynes-Cummings
    identity = [1 0 ; 0 1]; sigmaZ = [1 0 ; 0 -1];
    sigmaMinus = [0 1 ; 0 0]; sigmaPlus = [0 0 ; 1 0];

    # The Jaynes-Cummings Hamiltonian is written with the following
    # conventions: omegaR is the resonator frequency, omegaQ is the qubit
    # frequency and g is the coupling. The resonator Hilbert space is truncated
    # to n = cutoffN, and the ground state of the qubit is given by the vector
    # [1;0] (hence the minus sign before sigmaZ).
    jaynesCummings = zeros(Complex128,2*cutoffN,2*cutoffN)
    jaynesCummings = jaynesCummings +
    h_bar * omegaR .* kron(identity,a_dagger(cutoffN)) * kron(identity,a(cutoffN)) -  # harmonic oscillator term
    0.5 .* h_bar .* omegaQ .* kron(sigmaZ,eye(cutoffN)) +  # qubit term
    h_bar .* g .* ( kron(sigmaPlus,a(cutoffN)) + kron(sigmaMinus,a_dagger(cutoffN)) ); # interaction term

    if noiseAdded==1
        randM = rand(2*cutoffN);
        randomness = 0.005*h_bar*g*(randM+randM');
        jaynesCummings = jaynesCummings + randomness;
    end
    return jaynesCummings
end


function gen_timeevoarray(hamiltonian,finalTime,samples)
    # Generate the time evolution array for a time independent Hamiltonian
    time_vec=((1:samples)-1)*finalTime/samples
    time_evo_array = Array(typeof(hamiltonian),samples)

    for i=1:samples
        time_evo_array[i] = expm(-1im .* hamiltonian .* time_vec[i] / h_bar)
    end

    return time_vec, time_evo_array
end


function gen_displacementop(alpha,cutoffN)
    # Generates the displacement operator for a qubit and resonator system
    # (only displaces the resonator, the identity is tensored in for the
    # qubit).
    expm( alpha .* a_dagger(cutoffN) - alpha' .* a(cutoffN) )
end
