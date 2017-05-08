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
        push!(decisionValues, float(decisionValue))
        push!(predictionLabels, int(predictionLabel))
        if c != 0 && proteinid != prevProteinid
            predictionResult = PredictionResult(prevProteinid, decisionValues, predictionLabels)
            predictions[prevProteinid] = predictionResult
            dicisionValues = Float64[]
            predictionLabels = Int64[]
        end
        prevProteinid = proteinid
        c += 1
    end
    if length(decisionValues) != 0 && length(predictionLabels) != 0
        predictionResult = PredictionResult(prevProteinid, decisionValues, predictionLabels)
        predictions[prevProteinid] = predictionResult
    end
    return predictions
end


function parseGraphFile(proteinid, graphFile)
    graph = Dict{Int64, Array{Int64}}()
    for line in eachline(open(graphFile))
        if length(rstrip(line)) == 0
            continue
        end
        left, right = map(int, split(line, ' '))
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


function gibbsSampling(prediction, graph)
    iternum = 10000
    σ = 1
    J = 0.5
    maxIndex = length(prediction.predictionLabels)
    ys = map(x-> if x == 0 return -1 else return 1 end, prediction.predictionLabels)
    currentStates = map(x-> if x == 0 return -1 else return 1 end, prediction.predictionLabels)
    sampled = Array{Int8, 1}[]
    for i in 1:maxIndex
        push!(sampled, [])
    end
    for i in 1:iternum
        index = rand(1:maxIndex)
        neighbors = graph[index-1]
        currentState = currentStates[index]
        flippedState = -1*currentState
        dθ = 0
        dθ′ = 0 
        for neighbor in neighbors
            if currentStates[neighbor+1] != currentState
                dθ += 1
            else
                dθ′ += 1
            end
        end
        p′ = exp(-(ys[index]-flippedState)^2/2*(σ^2))*exp(-2*J*(dθ′))
        p  = exp(-(ys[index]-currentState)^2/2*(σ^2))*exp(-2*J*(dθ))
        conditional_p′ = p′ / (p + p′)
        dist = Binomial(1, conditional_p′)
        newState = rand(dist)
        if newState == 1
            newState = -1 * currentState
        else
            newState = currentState
        end
        #@show index
        #@show ys[index]
        #@show currentState
        #@show newState
        #@show conditional_p′
        #@show currentStates
        push!(sampled[index], newState)
        currentStates[index] = newState
    end
    return sampled
end


function main()
    predictionFile = ARGS[1]
    graphDir = ARGS[2]
    predictions =  parsePredictionFile(predictionFile)
    @show predictions
    graphs = parseGraphFiles(predictions, graphDir)
    @show graphs
    for i in 1:100
        for proteinid in keys(predictions)
            sampled =  gibbsSampling(predictions[proteinid], graphs[proteinid].graph)
            @show map(mean, sampled)
        end
    end
end

main()
