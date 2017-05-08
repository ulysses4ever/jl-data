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
            push!(predictionLabels, parse(Int, predictionLabel))
        else
            push!(decisionValues, float(decisionValue))
            push!(predictionLabels, parse(Int, predictionLabel))
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
        push!(correctLabels, parse(Int, correctLabel))
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
        left, right = map(x->parse(Int, x), split(line, ' '))

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
        if haskey(graph, i) 
            neighbors = graph[i]
            #Z = 0
            s = xs[i] # current state 
            s′ = -1*s # flipped state
            d  = disagreeingEdgeNumber(s, xs, neighbors)
            d′ = disagreeingEdgeNumber(s′, xs, neighbors)
            r  = exp((2*ys[i]*s)/(σ^2))*exp(-2*J*(d-d′))  # currentProb / flippedProb
            p = r / (1 + r)
            #d = disagreeingEdgeNumber(-xs[i], xs, neighbors)
            #Z += expEnergy(ys[i], -xs[i], σ, J, d)
            #d = disagreeingEdgeNumber(xs[i], xs, neighbors)
            #currExpEnergy = expEnergy(ys[i], xs[i], σ, J, d)
            #Z += currExpEnergy
            #p = currExpEnergy / Z
            logPseLike += log(p)
        else # has No Edge.
            #Z = 0
            s = xs[i] # current state 
            s′ = -1*s     # flipped state
            r = exp((2*ys[i]*s)/(σ^2))  # currentProb / flippedProb
            p = r / (1 + r)
            #Z += expEnergy(ys[i], xs[i], σ, J, 0)
            #Z += expEnergy(ys[i], -xs[i], σ, J, 0)
            #currExpEnergy = expEnergy(ys[i], xs[i], σ, J, 0)
            #p = currExpEnergy / Z
            logPseLike += log(p)
        end
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
        if haskey(graph, index)
            neighbors = graph[index]
            s = currentStates[index] # current state 
            s′ = -1*s     # flipped state
            d  = disagreeingEdgeNumber(s, currentStates, neighbors)
            d′ = disagreeingEdgeNumber(s′, currentStates, neighbors)
            r′ = exp((2*ys[index]*s′)/(σ^2))*exp(-2*J*(d′-d))  # flippedProb / currentProb
            p′ = r′ / (1 + r′)
        else # has No Edge.
            s = currentStates[index] # current state 
            s′ = -1*s     # flipped state
            r′ = exp((2*ys[index]*s′)/(σ^2))  # flippedProb / currentProb
            p′ = r′ / (1 + r′)
        end
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
    try
        predictionFile = ARGS[1]
        correctFile    = ARGS[2]
        graphDir       = ARGS[3]
    catch exception
        println(Usage)
        exit()
    end
    predictionFile = ARGS[1]
    correctFile    = ARGS[2]
    graphDir       = ARGS[3]
    iternum        = 100000
    burnIn         = 10000
    σRange         = (0.1, 2.0)
    JRange         = (0.1, 2.0)
    σGrid          = 100
    JGrid          = 100
    predictions =  parsePredictionFile(predictionFile)
    corrects = parseCorrectFile(correctFile)
    graphs = parseGraphFiles(predictions, graphDir)
    logPseudolikelihoods = Tuple[]
    maxPseudolikelihood = (0.0, 0.0, -Inf) # σ, J, logPseudolikelihood
    for σG in 0:σGrid
        σ = (σG/float(σGrid)) * (σRange[2]-σRange[1]) + σRange[1]
        for JG in 0:JGrid
            J = (JG/float(JGrid)) * (JRange[2]-JRange[1]) + JRange[1]
            logPseLike = 0
            for proteinid in keys(predictions)
                logPseLike += pseudolikelihood(corrects[proteinid], predictions[proteinid].predictionLabels, 
                                                                        σ, J, graphs[proteinid].graph)
            end
            push!(logPseudolikelihoods, (σ, J, logPseLike))
            if logPseLike > maxPseudolikelihood[3]
                maxPseudolikelihood = (σ, J, logPseLike)
            end
        end
    end
    sort!(logPseudolikelihoods, by=x->x[3], rev=true)
    for logPseudolikelihood in logPseudolikelihoods[1:10]
        @show logPseudolikelihood
    end
    @show maxPseudolikelihood
    proteinApproxMeans = Dict{UTF8String, Array{Array{Float64, 1}}}()
    for proteinid in keys(predictions)
        proteinApproxMeans[proteinid] = Array{Array{Float64, 1}}[]
    end
    for i in 1:10
        for proteinid in keys(predictions)
            approxMean =  gibbsSampling(predictions[proteinid].predictionLabels, iternum, maxPseudolikelihood[1],
                                                    maxPseudolikelihood[2], graphs[proteinid].graph, burnIn)
            push!(proteinApproxMeans[proteinid], approxMean)
        end
    end
    for proteinid in keys(predictions)
        @show proteinid
        for eachMean in proteinApproxMeans[proteinid]
            @show eachMean
        end
        @show mean(proteinApproxMeans[proteinid])
    end
end

Usage = """

Usage:
    julia gibbs_sampler.jl <prediction_output> <correct_label_file> <graph_dir>


FORMAT:

<prediction_output>
    proteinid\tindex\t0
    proteinid\tindex\t1
    proteinid\tindex\t0
    proteinid\tindex\t0
    ...

<correct_label_file>
    proteinid\tindex\t0
    proteinid\tindex\t1
    proteinid\tindex\t0
    proteinid\tindex\t0
    ...

<graph_dir> is a directory that includes protein_graph_file
protein_graph_file must be "proteinid.graph"

protein_graph_file FORMAT:

    0 1
    1 4
    2 3
    2 4
    3 1
    ...
"""

main()
