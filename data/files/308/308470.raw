module CoreBackprop_unipolar

using CoreBasics_unipolar
using SampleGenerator_unipolar
using DataStructures
using Gadfly

export BPSettings, train_core!, eval_core, optimize_core!, plot_aid

Def_maxRandomisation = 0.01     # max of noise initialization
Def_lrate = 0.05                # learning rate
Def_momentum = 0.05             # momentum factor
Def_maxEpochs = 10000           # so optimize always terminates
Def_bGradCheck = false          # activates gradient checking
Def_nGradCheck = 2              # max iterations with gradient checking
Def_gradEps = 0.00001           # epsilon for gradient checking
Def_comments = false            # activates addictional printouts

type DataPoint # store evaluation results for plotting and analysis
    
    percentCorrect
    eTotal
    eSamps
    avgIt
    costJ

end # type


type BPSettings

    maxRandomisation
    lrate         
    momentum 
    maxEpochs     
    bGradCheck
    nGradCheck
    gradEps     
    comments    
    
    nEpochs
    nAddNeurons
    nLockedNeurons

    resultList

    BPSettings(nEp::Int, nAdd::Int, nLock::Int) = new(Def_maxRandomisation, Def_lrate, 
                                    Def_momentum, Def_maxEpochs, Def_bGradCheck, 
                                    Def_nGradCheck, Def_gradEps, Def_comments, 
                                    nEp, nAdd, nLock, Deque{DataPoint}())
end # type


function train_core!(core::LogicCore, samp::LogicSamples, stng::BPSettings)



    # add hidden neurons to core
    core.nHiddenNeurons += stng.nAddNeurons
    core.weights12 = [core.weights12 zeros(2*core.nAtoms+1, stng.nAddNeurons)]
    core.weights23 = [core.weights23; zeros(stng.nAddNeurons, 2*core.nAtoms)]

    # add randomisation
    noise12 = rand(Float64, size(core.weights12)) * stng.maxRandomisation
    noise23 = rand(Float64, size(core.weights23)) * stng.maxRandomisation

    noise12[:,1:stng.nLockedNeurons  ] = 0   # remove noise for locked units
    noise23[2:1+stng.nLockedNeurons,:] = 0

    core.weights12 += noise12
    core.weights23 += noise23

    # backprop

    deltaW12 = zeros(Float64, size(core.weights12))
    deltaW23 = zeros(Float64, size(core.weights23))
    deltaW12Old = zeros(Float64, size(core.weights12))
    deltaW23Old = zeros(Float64, size(core.weights23))

    for i = 1:stng.nEpochs

        ind = rand(1:samp.nSamples)                                                 # index random sample

        sIn  = vec(samp.sIn[ind,:])
        sOut = vec(samp.sOut[ind,:])

        cOut, fixp, model, actIn, actHid, actOut  = run_core(core,sIn)              # forward prop

        errOut = actOut - sOut                                                      # compute deltas
        deltaOut = -errOut                               # <--- logistic cost function  X

        errHid = (core.weights23 .^ 2) * deltaOut               #change to unipolar here
        deltaHid = errHid[2:end] .* (actHid .* (1 - actHid)) #cut off 1 el b/c biasHid unit is irrelevant in W12

        deltaW23 = ([1; actHid] * deltaOut') .* [ ones(size(core.weights23,2))' ; 2 * core.weights23[2:end,:] ] #change to unipolar here
        deltaW12 = ([1; actIn ] * deltaHid') .* [ ones(size(core.weights12,2))' ; 2 * core.weights12[2:end,:] ] #change to unipolar here

        if stng.bGradCheck && i <= stng.nGradCheck                                  # gradient checking
            if !fixp
                println("ERROR: fixp: $fixp")
            end #if
            grad_Check(core, stng, deltaW12, deltaW23, actIn, sOut)
        end #if

        deltaW23 = stng.lrate * deltaW23 .+ stng.momentum * deltaW23Old
        deltaW12 = stng.lrate * deltaW12 .+ stng.momentum * deltaW12Old
        
                                                                                    # cut out difference for locked units @TODO: don't even calculate it
        deltaW12[:,1:stng.nLockedNeurons  ] = 0
        deltaW23[2:1+stng.nLockedNeurons,:] = 0
                                                                                    # Update weights
        core.weights12 = core.weights12 .+ deltaW12
        core.weights23 = core.weights23 .+ deltaW23

        deltaW12Old = deltaW12
        deltaW23Old = deltaW23

        
    end #for

end # function


function eval_core(core::LogicCore, samp::LogicSamples, stng::BPSettings)

    nErrors = 0
    nMismatch = 0
    sumCost = 0

    core.bCountIterations = true

    for i = 1:samp.nSamples

        cOut, fixp, model, actIn, actHid, actOut = run_core(core,vec(samp.sIn[i,:]))
        
        mismatches = sum(abs(vec(cOut) - vec(samp.sOut[i,:])))
        if mismatches > 0 || [fixp model] != samp.sProp[i,:]
            nErrors += 1
            nMismatch += mismatches
        end #if

        if samp.nSamples < 7000 # would likely be too costly otherwise
            sumCost += costf_J(actOut, vec(samp.sOut[i,:]))
            
        end #if

    end # for

    avgIterations = core.nIterationCount / samp.nSamples
    core.bCountIterations = false
    core.nIterationCount = 0

    successRate = (samp.nSamples - nErrors)/samp.nSamples

    sumCost /= samp.nSamples

    data = DataPoint(successRate*100,nMismatch,nErrors,avgIterations,0)
    data.costJ = sumCost
    push!(stng.resultList,data)

    if stng.comments
        print("%corr:")
        @printf "%6.2f   " successRate * 100
        print("eTotal:")
        @printf "%4.0f   " nMismatch
        print("eSamps:")
        @printf "%5i   " nErrors
        print("avgIt:")
        @printf "%4.2f   " avgIterations
        print("costJ:")
        @printf "%7.4f   " sumCost

        println()
    end #if

    return (nErrors, successRate)

end # function


function optimize_core!(core::LogicCore, samp::LogicSamples, stng::BPSettings, goalPerformance::Float64)

    if goalPerformance > 1
        println("Performance should range between 0 and 1")

    else
        print("0: ")
        nErr, perf = eval_core(core, samp, stng)

        nIterations = 0

        while perf < goalPerformance && stng.nEpochs * nIterations < stng.maxEpochs


            train_core!(core, samp, stng)

            
            stng.nAddNeurons = 0

            if stng.comments
                print("$(nIterations+1): ")
            end #if

            nErr, perf = eval_core(core, samp, stng)

            nIterations += 1
        end

        println("Performance of $perf reached after $(nIterations * stng.nEpochs) epochs.")

    end #ifelse

end # function


function costf_J(actOut::Array{Float64,1}, sOut::Array{Float64,1})
    eps = 0.00000001 # prevents numerical errors from computing log(0) * 0 = NaN
    return -sum(sOut .* log(actOut + eps) + (1 - sOut) .* log(1 - actOut + eps))
end # function

                                           # Gradient Checking
function grad_Check(core::LogicCore, stng::BPSettings, deltaW12::Array{Float64,2}, deltaW23::Array{Float64,2},
                    actIn::Array{Float64,1}, sOut::Array{Float64,1})

    gradApprox12 = zeros(Float64, size(core.weights12))
    gradApprox23 = zeros(Float64, size(core.weights23))

    for j = 1: length(core.weights12)
        temp = core.weights12[j]
        core.weights12[j] -= stng.gradEps

        actHid   = sigmoid_sqd(actIn , core.weights12)
        outMinus = sigmoid_sqd(actHid, core.weights23)

        core.weights12[j] += 2*stng.gradEps
        
        actHid  = sigmoid_sqd(actIn , core.weights12)
        outPlus = sigmoid_sqd(actHid, core.weights23)

        costMinus = costf_J(outMinus, sOut)
        costPlus  = costf_J(outPlus , sOut)
        core.weights12[j] = temp

        if stng.comments
            actHid  = sigmoid_sqd(actIn , core.weights12)
            actOut  = sigmoid_sqd(actHid, core.weights23)  
            costOut = costf_J(actOut, sOut)

            if (costOut < costPlus && costOut < costMinus) || (costOut > costPlus && costOut > costMinus)
                println("ERROR: gradEps not sufficiently small")
            end #if
        end #if

        gradApprox12[j] = (costPlus - costMinus)/(2*stng.gradEps)
    end #for

    for j = 1: length(core.weights23)
        temp = core.weights23[j]
        core.weights23[j] -= stng.gradEps
        
        actHid   = sigmoid_sqd(actIn , core.weights12)
        outMinus = sigmoid_sqd(actHid, core.weights23)

        core.weights23[j] += 2*stng.gradEps
        
        actHid  = sigmoid_sqd(actIn , core.weights12)
        outPlus = sigmoid_sqd(actHid, core.weights23)        

        costMinus = costf_J(outMinus, sOut)
        costPlus  = costf_J(outPlus , sOut)
        core.weights23[j] = temp

        if stng.comments
            actHid  = sigmoid_sqd(actIn , core.weights12)
            actOut  = sigmoid_sqd(actHid, core.weights23)  
            costOut = costf_J(actOut, sOut)

            if (costOut < costPlus && costOut < costMinus) || (costOut > costPlus && costOut > costMinus)
                println("ERROR: gradEps not sufficiently small")
            end #if
        end #if

        gradApprox23[j] = (costPlus - costMinus)/(2*stng.gradEps)
    end #for


    # println("Gradient Checking: approx/delta 12")
    # print_mat_round(gradApprox12 ./ deltaW12)
    # println()
    # println("Gradient Checking: approx/delta 23")
    # print_mat_round(gradApprox23 ./ deltaW23)
    # println()
    diff12 = gradApprox12 + deltaW12
    diff23 = gradApprox23 + deltaW23
    maxErr12 = maximum(abs(diff12))
    maxErr23 = maximum(abs(diff23))
    println("Gradient Checking: Error on W12 (max error: $maxErr12 )")
    print_mat_round(diff12)
    println()
    println("Error on W23 (max error: $maxErr23 )")
    print_mat_round(diff23)
    println()
end # function

function plot_aid(stng::BPSettings, feature_id::Int)

    yLabels = [ "%corr";
                "eTotal";
                "eSamps";
                "avgIt";
                "costJ"]

    A = Array(Float64, length(stng.resultList), 5)

    for r = 1:length(stng.resultList)
        d = shift!(stng.resultList)
        A[r, :] = [d.percentCorrect, d.eTotal, d.eSamps, d.avgIt, d.costJ]
        push!(stng.resultList, d)
        
    end # for

    p = plot(
        layer(
            x=(0:size(A,1)-1)*stng.nEpochs, y=A[:,feature_id], Geom.line
        ),
        layer(
            x=(0:size(A,1)-1)*stng.nEpochs, y=A[:,feature_id], Geom.point
        ),
    Guide.xlabel("number of epochs"),
    Guide.ylabel(yLabels[feature_id])
    )
    return p

end # function


end #module