using Distributions


type PredictionResult
    proteinid::UTF8String
    decisionValues::Array{Float64}
    predictionLabels::Array{Int64}
end


type Graph
    proteinid::UTF8String
    graph::Dict{Int64, Array{Int64}}
end


function parsePredictionFile(predictionFile)
    predictions = Dict{UTF8String, PredictionResult}()
    decisionValues = Float64[]
    predictionLabels = Int64[]
    prevProteinid = ""
    c = 0
    for line in eachline(open(predictionFile))
        if length(rstrip(line)) == 0
            continue
        end
        proteinid, index, decisionValue, predictionLabel = split(line, '\t')
        if c != 0 && proteinid != prevProteinid
            predictionLabels = map(x-> if x == 0 return -1 else return 1 end, predictionLabels)
            predictionResult = PredictionResult(prevProteinid, decisionValues, predictionLabels)
            predictions[prevProteinid] = predictionResult
            dicisionValues = Float64[]
            predictionLabels = Int64[]
            push!(decisionValues, float(decisionValue))
            push!(predictionLabels, int(predictionLabel))
        else
            push!(decisionValues, float(decisionValue))
            push!(predictionLabels, int(predictionLabel))
        end
        prevProteinid = proteinid
        c += 1
    end
    if length(decisionValues) != 0 && length(predictionLabels) != 0
        predictionLabels = map(x-> if x == 0 return -1 else return 1 end, predictionLabels)
        predictionResult = PredictionResult(prevProteinid, decisionValues, predictionLabels)
        predictions[prevProteinid] = predictionResult
    end
    return predictions
end


function parseCorrectFile(correctFile)
    corrects = Dict{UTF8String, Array{Int64, 1}}()
    correctLabels = Int64[]
    prevProteinid = ""
    c = 0
    for line in eachline(open(correctFile))
        if length(rstrip(line)) == 0
            continue
        end
        proteinid, index, correctLabel = split(line, '\t')
        if c != 0 && proteinid != prevProteinid
            corrects[prevProteinid] = correctLabels
            correctLabels = Int64[]
        end
        push!(correctLabels, int(correctLabel))
        prevProteinid = proteinid
        c += 1
    end
    if length(correctLabels) != 0
        corrects[prevProteinid] = correctLabels
    end
    return corrects
end


function parseGraphFile(proteinid, graphFile)
    graph = Dict{Int64, Array{Int64}}()
    for line in eachline(open(graphFile))
        if length(rstrip(line)) == 0
            continue
        end
        left, right = map(int, split(line, ' '))

        #convert to Julia index (start from 1)
        left += 1  
        right += 1
        if haskey(graph, left)
            push!(graph[left], right)
        else
            graph[left] = [right]
        end
    end
    return Graph(proteinid, graph)
end


function parseGraphFiles(predictions, graphDir)
    graphs = Dict{UTF8String, Graph}()
    for proteinid in keys(predictions)
        graph = parseGraphFile(proteinid, graphDir*proteinid*".graph")
        graphs[proteinid] = graph
    end
    return graphs
end


function getAllState(numNeighbor)
    allState = ASCIIString[]
    for i in 0:2^numNeighbor-1
        push!(allState, bits(i)[64-numNeighbor+1:end])
    end
    return allState
end


function expEnergy(y, x, σ, J, d)
    return exp(-(y-x)^2/(2*(σ^2)))*exp(-2*J*(d))
end


function disagreeingEdgeNumber(selfState, xs, neighbors)
    d = 0
    for neighbor in neighbors
        if xs[neighbor] != selfState
            d += 1
        end
    end
    return d
end


function encodeState(state)
    encodedStates =  map(x->if x == "0" return -1 elseif x == "1" return 1 end, split(state, ""))
    return encodedStates[1], encodedStates[2:end]
end


function isDisagreeing(selfState, neighborState)
    if selfState != neighborState
        return 1
    end
    return 0
end
 

function pseudolikelihood(xs, ys, σ, J, graph::Dict{Int64, Array{Int64}})
    logPseLike = 0
    for i in 1:length(xs)
        # For x
        neighbors = graph[i]
        allState = getAllState(length(neighbors)+1)
        Z = 0
        for state in allState
            selfState, neighborStates = encodeState(state)
            d = disagreeingEdgeNumber(selfState, neighborStates, [1:length(neighborStates)])
            Z += expEnergy(ys[i], selfState, σ, J, d)
            Z += expEnergy(-ys[i], selfState, σ, J, d)
            #Z += expEnergy(selfState, selfState, σ, J, d)
            #@show neighborStates
            #@show ys[i]
            #@show d
            #@show expEnergy(ys[i], selfState, σ, J, d)
            #@show expEnergy(ys[i], selfState, σ, J, d)
            #@show σ
            #@show selfState
            #@show Z
            #@show neighborStates
            #for j in 1:length(neighborStates)
            #    neighborState = neighborStates[j]
            #    dNeighbor = isDisagreeing(selfState, neighborState)
            #    #dNeighbor = 0
            #    Z += expEnergy(ys[neighbors[j]], neighborState, σ, J, dNeighbor)
            #    #@show ys[neighbors[j]]
            #    #@show neighborState
            #    #@show dNeighbor
            #    #@show expEnergy(ys[neighbors[j]], neighborState, σ, J, dNeighbor)
            #    #@show Z
            #end
        end
        d = disagreeingEdgeNumber(xs[i], xs, neighbors)
        currExpEnergy  = expEnergy(ys[i], xs[i], σ, J, d)
        #currExpEnergy  = expEnergy(xs[i], xs[i], σ, J, d)
        #@show expEnergy(ys[i], xs[i], σ, J, d)
        #@show xs
        #@show neighbors
        #@show d
        #@show currExpEnergy
        #for neighbor in neighbors
        #    dNeighbor = isDisagreeing(xs[i], xs[neighbor])
        #    #dNeighbor = 0
        #    currExpEnergy += expEnergy(ys[neighbor], xs[neighbor], σ, J, dNeighbor)
        #end
        p = currExpEnergy / Z
        logPseLike += log(p)

        # For y
        Z = 0
        Z += expEnergy(ys[i], xs[i], σ, J, 0)
        Z += expEnergy(-ys[i], xs[i], σ, J, 0)
        Z += expEnergy(ys[i], -xs[i], σ, J, 0)
        Z += expEnergy(-ys[i], -xs[i], σ, J, 0)
        currExpEnergy = expEnergy(ys[i], xs[i], σ, J, 0)
        p = currExpEnergy / Z
        logPseLike += log(p)
        #@show i
        #@show currExpEnergy
        #@show p
        #@show Z
        #@show logPseLike
        #@show allState
    end
    return logPseLike
end


function gibbsSampling(ys, iternum, σ, J, graph::Dict{Int64, Array{Int64}}, burnIn)
    maxIndex = length(ys)
    #dist = Binomial(1, 0.5)
    #currentStates = map(x->if x == 0 return -1 else return 1 end, rand(dist, maxIndex))
    currentStates = copy(ys)
    sampled = Array{Int8, 1}[]
    for i in 1:maxIndex
        push!(sampled, [])
    end
    for i in 1:iternum
        index = rand(1:maxIndex)
        neighbors = graph[index]
        s = currentStates[index] # current state 
        s′ = -1*s     # flipped state
        d  = disagreeingEdgeNumber(s, currentStates, neighbors)
        d′ = disagreeingEdgeNumber(s′, currentStates, neighbors)
        #r′ = exp( ((2*ys[index]*s′)/(σ^2)) + (-2*J*(d′-d)) ) # flippedProb / currentProb
        r′ = exp((2*ys[index]*s′)/(σ^2))*exp(-2*J*(d′-d))  # flippedProb / currentProb
        p′ = r′ / (1 + r′)
        dist = Binomial(1, p′)
        flip_or_remain = rand(dist) # 1 means flip, 0 means remain.
        if flip_or_remain == 1
            newState = s′
        else
            newState = s
        end
        if i > burnIn
            push!(sampled[index], newState)
        end
        currentStates[index] = newState
    end
    return map(mean, sampled)
end


function main()
    predictionFile = ARGS[1]
    correctFile    = ARGS[2]
    graphDir       = ARGS[3]
    iternum        = 100000
    burnIn         = 10000
    #σ              = 1
    #J              = 0.5
    predictions =  parsePredictionFile(predictionFile)
    @show predictions
    corrects = parseCorrectFile(correctFile)
    @show corrects
    graphs = parseGraphFiles(predictions, graphDir)
    @show graphs
    logPseudolikelihoods = Tuple[]
    maxPseudolikelihood = (0.0, 0.0, -Inf) # σ, J, logPseudolikelihood
    for σ in 1:20
        σ /= 10.0
        for J in 1:20
            J /= 10.0
            logPseLike = 0
            for proteinid in keys(predictions)
                #@show proteinid
                #@show corrects[proteinid]
                #@show predictions[proteinid].predictionLabels
                #@show graphs[proteinid].graph
                logPseLike += pseudolikelihood(corrects[proteinid], predictions[proteinid].predictionLabels, 
                                                                        σ, J, graphs[proteinid].graph)
            end
            push!(logPseudolikelihoods, (σ, J, logPseLike))
            if logPseLike > maxPseudolikelihood[3]
                maxPseudolikelihood = (σ, J, logPseLike)
            end
        end
    end
    #@show logPseudolikelihoods
    sort!(logPseudolikelihoods, by=x->x[3], rev=true)
    for logPseudolikelihood in logPseudolikelihoods[1:20]
        @show logPseudolikelihood
    end
    @show maxPseudolikelihood
    σ              = 1.0
    J              = 0.6
    proteinApproxMeans = Dict{UTF8String, Array{Array{Float64, 1}}}()
    for proteinid in keys(predictions)
        proteinApproxMeans[proteinid] = Array{Array{Float64, 1}}[]
    end
    for i in 1:10
        for proteinid in keys(predictions)
            approxMean =  gibbsSampling(predictions[proteinid].predictionLabels, iternum, σ, J, graphs[proteinid].graph, burnIn)
            #approxMean =  gibbsSampling(predictions[proteinid].predictionLabels, iternum, maxPseudolikelihood[1],
                                                    #maxPseudolikelihood[2], graphs[proteinid].graph, burnIn)
            push!(proteinApproxMeans[proteinid], approxMean)
        end
    end
    for proteinid in keys(predictions)
        @show proteinid
        #@show proteinApproxMeans[proteinid]
        @show mean(proteinApproxMeans[proteinid])
    end
end

main()
