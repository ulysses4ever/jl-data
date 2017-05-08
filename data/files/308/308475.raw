module ModelChecker

using CoreBasics_unipolar
using SampleGenerator_unipolar

export run_discrete, check_models



function heavi_act(v_in::Array{Float64,1}, weights::Array{Float64,2}) 
    return vec(float64([weights[1,i] + dot(weights[2:end,i],v_in) <= 0 ? 
                            0.0 : 1.0 for i = 1:size(weights,2)]))
end # function


function run_discrete(core::LogicCore, input::Array{Float64,1})

    if length(input) != 2*core.nAtoms
        println("ERROR: core/input mismatch")
    end

    squaredW12 = copy(core.weights12)
    squaredW23 = copy(core.weights23)

    squaredW12[2:end,:] = squaredW12[2:end,:] .^ 2 
    squaredW23[2:end,:] = squaredW23[2:end,:] .^ 2

    actIn  = zeros(2*core.nAtoms)
    actHid = zeros(core.nHiddenNeurons)
    actOut = zeros(2*core.nAtoms)
    actRet = input

    improve = true                    # try to correct input usage to reflect x <- TF
    tInput = zeros(length(input))
    tIndex = Array(Int,0)
    fIndex = Array(Int,0)
    if improve                          # split inputs into positive and negative parts
        for i = 1:(length(input) / 2)
            if input[2i-1] == 1.0
                tInput[2i-1] = 1.0
                push!(tIndex, 2i-1)
            end

            if input[2i] == 1.0
                push!(fIndex, 2i)
            end
        end #for
        actRet = tInput
    end #if    

    foundFixpoint = false

    maxIterations = 100
    for i = 1:maxIterations

        actIn  = actRet
        actHid = heavi_act(actIn , squaredW12)
        actOut = heavi_act(actHid, squaredW23)

        actRet = round(actOut)

        if !improve
            actRet = vec(maximum([actRet input],2))
        end

        if improve    

            #actRet = vec(maximum([actRet tInput],2))
                              # enforce x <- FF clauses only if x not rendered true yet
            for i = 1:length(fIndex)
                if actRet[fIndex[i]-1] == 0
                    # println("using fIn. actRet: $actRet   fInd: $fIndex")
                    actRet[fIndex[i]] = 1
                end #if
            end #for

            for i = 1:length(tIndex)        # enforce all x <- TT clauses
                # println("using tIn. actRet: $actRet   tInd: $tIndex")
                actRet[tIndex[i]] = 1
                actRet[tIndex[i]+1] = 0
            end #for

        end #if

        if actRet == actIn
            foundFixpoint = true
            break
        end

    end #for

    foundModel = true
    for i = 1:core.nAtoms
        if actRet[2i-1] == 1 && actRet[2i] == 1
            foundModel = false
        end
    end

    return (actRet, foundFixpoint, foundModel, actIn, actHid, actOut)
end # function


function check_models(core::LogicCore)

    samp = make_samples(core)
    
    nErrors = 0
    nMismatch = 0

    for i = 1:samp.nSamples

        dOut, dFixp, dModel = run_discrete(core, vec(samp.sIn[i,:]))

        mismatches = sum(abs(dOut - vec(samp.sOut[i,:]))) 
        if mismatches > 0 || [dFixp dModel] != samp.sProp[i,:]
            nErrors += 1
            nMismatch += mismatches
        end #if

    end #for   

    return (nErrors, nMismatch) 
end # function

end #module