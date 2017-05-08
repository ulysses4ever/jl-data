module CoreBasics_unipolar


export LogicCore, build_core, run_core, sigmoid_act, sigmoid_sqd, sigmoid_exp, strip_core, print_fixpoint, print_mat_round

type LogicCore

    atoms::Array{String,1}
    nAtoms::Int
    nClauses::Int
    nHiddenNeurons::Int
    weights12::Array{Float64,2}
    weights23::Array{Float64,2}

    nIterationCount::Int
    bCountIterations::Bool
    lukaConsequence::Int # if 2, core follows lukasiewicz semantics. 0 for C semantics. 1 for C* semantics
end #type


function build_core(program_dir::String)

    program = open(readlines, program_dir, "r")

    atoms = Array(String,0)                         # A <- -B & A \n
    for i = 1:size(program,1)

        program[i] = rstrip(program[i])             # A <- -B & A

        line = split(program[i], r" <- | & | ")     # A,-B,A
        
        for j = 1:size(line,1)
            line[j] = lstrip(line[j], '-')
            push!(atoms,line[j])                    # [A,B,A]
        end
    end

    atoms = unique(atoms)                           #[A,B]

    i = 1
    while i <= length(atoms)
        if atoms[i] == "TT" || atoms[i] == "FF"
            atoms[i] = atoms[end]
            atoms = atoms[1:end-1]
        else
        i += 1
        end
    end

    nClauses = length(program)
    nHiddenNeurons = 2*nClauses
    nAtoms   = length(atoms)

    sort!(atoms)                      # ensure all core with same atoms have them in the same order
    sort!(atoms, by=length ,rev=true) # to avoid replacement of partial matches

    for i = 1:nAtoms
        for j = 1:nClauses
            program[j] = replace(program[j],atoms[i],"$i")
        end
    end

                                    # create network connectivity matrices


    connections12 = zeros(2*nAtoms,2*nClauses)      # a = atom[i], i > 2 has +a at 2i - 1 and -a at 2i
                                                    # c = program[i] has cT at 2i - 1 and cF at 2i
    connections23 = zeros(2*nClauses,2*nAtoms)     

    factbiases = zeros(2*nClauses)                  # biases from A <- TT or A <- FF clauses are added later



    for i = 1:nClauses
        line = split(program[i], r" <- | & | ")

        connections23[2i-1, 2*int(line[1])-1] = 1   # connect cT to head-out
        connections23[2i  , 2*int(line[1])  ] = 1   # connect cF to -head-out

        for j = 2:size(line,1)
            lit = line[j]

            if lit == "TT"
                factbiases[2i-1] = 1            # connect bias to cT 
            elseif lit == "FF"
                factbiases[2i] = 1              # connect bias to cF
            elseif beginswith(lit,"-")
                lit = lit[2:end]
                connections12[2*int(lit)  , 2i-1] = 1   # connect -lit-in to cT
                connections12[2*int(lit)-1, 2i]   = 1  # and v.v.
            else 
                connections12[2*int(lit)-1, 2i-1] = 1   # connect +lit-in to cT
                connections12[2*int(lit)  , 2i]   = 1  # and v.v.
            end
        end
    end
                                                                # determine ω

    indeg = maximum(sum(connections23,1)) #compute maximum indegree of output nodes
    ω = ceil( 2*log(2*indeg - 1) + 0.0001,1) #check math section for formula derivation
    connections12 *= ω
    connections23 *= ω

                        #compute thresholds based on connection matrices
                       
    #thresh_in = fill(ω/2,2*nAtoms) # thresh_in is probably superfluous now
    #thresh_in[1] = -ω/2            

    thresh_hid = zeros(2*nClauses) #thresh_hid

    for i = 1:length(thresh_hid)
        if (mod(i,2) == 0)
            thresh_hid[i] = ω/2
        else
           
            l = sum(connections12[:,i]) # already contains ω
            thresh_hid[i] = max(ω/2, l - ω/2)
            
        end
    end

    thresh_out = zeros(2*nAtoms) #thresh_out

    for i = 1:length(thresh_out)
        if (mod(i,2) == 0)
            l = sum(connections23[:,i])
            thresh_out[i] = max(ω/2, l - ω/2)
        else
            thresh_out[i] = ω/2
        end
    end

                                            # adapt weights to fit squared use in activation function
    connections12 = sqrt(connections12)
    connections23 = sqrt(connections23)

                                            # adapt factbiases (to full ω as they are not squared)
    factbiases *= ω


                          # translate threshold values into the bias units in the matrices

    weights12 = [(factbiases - thresh_hid)'; connections12]
    weights23 = [-thresh_out'; connections23]

    return LogicCore(atoms, nAtoms, nClauses, nHiddenNeurons, weights12, weights23, 0, false, 0)
end #function





function run_core(core::LogicCore)

    zeroInput = zeros(2*core.nAtoms)

    return run_core(core, zeroInput)
end # function



function run_core(core::LogicCore, input::Array{Float64,1})

    if length(input) != 2*core.nAtoms
        println("ERROR: core/input mismatch")
    end

    #lukaConsequence = true                      # try to correct input usage to reflect x <- TF
    tInput = zeros(length(input))
    tIndex = Array(Int,0)
    fIndex = Array(Int,0)
    if core.lukaConsequence > 0                         # split inputs into positive and negative parts
        for i = 1:(length(input) / 2)
            if input[2i-1] == 1.0
                push!(tIndex, 2i-1)
            end
                            # extract only heads which have no other rules assigned to them
            if input[2i] == 1.0 && maximum(core.weights23[2:end, 2i]) != 0.0 
                input[2i] = 0.0 # delete all false inputs, which are heads of other clauses                        
            end
        end #for
    end #if
                                    # generate fixpoint

    actIn  = zeros(2*core.nAtoms)
    actHid = zeros(core.nHiddenNeurons)
    actOut = zeros(2*core.nAtoms)
    actRet = input

    foundFixpoint = false

    for i = 1:(2 * core.nAtoms) # maximum possible number before fixpoint is found in positive cores.

        actIn  = actRet
        actHid = sigmoid_sqd(actIn , core.weights12)
        actOut = sigmoid_sqd(actHid, core.weights23)
        
        actRet = round(actOut)
        actRet = vec(maximum([actRet input],2))
        

        if core.lukaConsequence == 2  
            for j = 1:length(tIndex)        # enforce all x <- TT clauses
                # println("using tIn. actRet: $actRet   tInd: $tIndex")
                actRet[tIndex[j]+1] = 0 # why does this confuse backprop
                                        # backprop probably doesn't get the interdependency of T and F neurons
                # actOut[tIndex[i]+1] = 0 <-- breaks backprop
            end #for

        end #if

        if actRet == actIn # fixpoint reached
            foundFixpoint = true
            if core.bCountIterations
                core.nIterationCount += i
            end #if
            break
        end

    end

    foundModel = true
    for i = 1:core.nAtoms
        if actRet[2i-1] == 1 && actRet[2i] == 1
            foundModel = false
        end
    end

    return (actRet, foundFixpoint, foundModel, actIn, actHid, actOut)
end # function


function sig1D(A::Array{Float64,1})
    sig(x::Float64) = 1 / (1 + e^-x)
    return float([sig(A[x]) for x = 1:length(A)])
end # function

function sigmoid_act(v_in::Array{Float64,1}, weights::Array{Float64,2})
    return sig1D(vec([1 v_in']*weights))
end # function

function sigmoid_sqd(v_in::Array{Float64,1}, weights::Array{Float64,2})
    netIn = vec(weights[1,:] + v_in' * (weights[2:end,:] .^ 2))
    return sig1D(netIn)
end # function

function sigmoid_exp(v_in::Array{Float64,1}, weights::Array{Float64,2})
    netIn = vec(weights[1,:] + v_in' * exp(weights[2:end,:]))
    return sig1D(netIn)
end # function


function strip_core(core::LogicCore)
    if core.nHiddenNeurons == 2 * core.nClauses
        println("core has no added neurons")
        return deepcopy(core)
    end #if

    keep = [(2 * core.nClauses + 1):core.nHiddenNeurons]
    return strip_core(core, keep)

end # function


function strip_core(core::LogicCore, keep::Array{Int,1})
    c_rest = deepcopy(core)

    if minimum(keep) < 1 || maximum(keep) > core.nHiddenNeurons
        println("Invalid indices")
    else
        c_rest.weights12 = c_rest.weights12[:, keep]
        c_rest.weights23 = c_rest.weights23[[1; keep + 1],:]
    end

    return c_rest

end # function


function print_fixpoint(core::LogicCore)

    cOut, fixp = run_core(core)
    if fixp
        print_fixpoint(core, cOut)
    else
        println("No fixpoint reached.")
    end

end # function



function print_fixpoint(core::LogicCore, fixpoint::Array{Float64,1})

    if length(fixpoint) != 2*core.nAtoms
        println("ERROR: core/fixpoint mismatch")
    else

        for i = 1:core.nAtoms
            if fixpoint[2i-1] == 0 && fixpoint[2i] == 0
                println("$(core.atoms[i]): u")
                elseif fixpoint[2i-1] == 0
                println("$(core.atoms[i]): False")
                elseif fixpoint[2i] == 0
                println("$(core.atoms[i]): True")
            else
                println("$(core.atoms[i]): INVALID - contradiction")
            end
        end
    end
end # function

function print_mat_round(mat::Array{Float64,2})

    if size(mat, 1) > 5 || size(mat, 2) > 5
        for i = 1:size(mat, 1)
            for j = 1:size(mat, 2)
                @printf("%5.2f ",mat[i,j])
            end

            println()
        end
    else
        for i = 1:size(mat, 1)
            for j = 1:size(mat, 2)
                @printf("%7.4f ",mat[i,j])
            end

            println()
        end
    end #if
end # function

end #module