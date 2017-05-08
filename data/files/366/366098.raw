module SampleGenerator_unipolar


using CoreBasics_unipolar

export make_samples, LogicSamples

type LogicSamples

    sIn::Array{Float64,2}
    sOut::Array{Float64,2}
    sProp::Array{Float64,2}
    nSamples::Int
    nDims::Int # number of input and output neurons
end # type

function make_samples(core::LogicCore)

    if core.nAtoms > 8
        println("cases of this size are not handled yet")
        return (zeros(Float64, 1, 2*core.nAtoms), zeros(Float64, 1, 2*core.nAtoms), zeros(Bool, 1, 2))
    else
        sampleInputs = make_inputs(core.nAtoms)

        nSamples = int(3^core.nAtoms)
        sampleOutputs       = Array(Float64, nSamples, 2*core.nAtoms)
        sampleProperties    = Array(Bool, nSamples, 2)
            
        for i = 1:int(3^core.nAtoms)
            output,fixp,model = run_core(core, vec(sampleInputs[i,:]))

            sampleOutputs[i,:]      = output
            sampleProperties[i,:]   = [fixp, model]
        end

        return LogicSamples(sampleInputs,sampleOutputs, sampleProperties, size(sampleInputs,1), size(sampleInputs,2))
    end
end # function


function make_inputs(nAtoms::Int)
    
    inputs = Array(Float64, int(3^nAtoms),2*nAtoms)
    
    aThird = int(3^(nAtoms-1)) # use it to divide into equal parts True, False and Unknown
    
    inputs[1:aThird,            1:2] = zeros(Float64, aThird,2)
    inputs[aThird+1:2*aThird,   1:2] = [zeros(Float64, aThird) ones(Float64, aThird)]
    inputs[2*aThird+1:end,      1:2] = [ones(Float64, aThird) zeros(Float64, aThird)]

    if nAtoms >= 2
        partial = make_inputs(nAtoms-1)
        inputs[1:aThird,           3:end] = partial
        inputs[aThird+1:2*aThird,  3:end] = partial
        inputs[2*aThird+1:end,     3:end] = partial
    end

    return inputs
end # function


end # module