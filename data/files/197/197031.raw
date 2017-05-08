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
    maxIndex = length(prediction.predictionLabels)
    currentState = map(x-> if x == 0 return -1 else return 1 end, prediction.predictionLabels)
    for index in rand(1:maxIndex)

    end
end

function main()
    predictionFile = ARGS[1]
    graphDir = ARGS[2]
    predictions =  parsePredictionFile(predictionFile)
    @show predictions
    graphs = parseGraphFiles(predictions, graphDir)
    @show graphs
    for proteinid in keys(predictions)
        gibbsSampling(predictions[proteinid], graphs[proteinid])
    end
end

main()
