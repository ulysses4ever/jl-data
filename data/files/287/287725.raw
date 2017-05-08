## Utility functions for evaluating the performance of classification methods
module PerformanceEval

export auc, rank_enrichment, evaluate_scores, get_enrichment, notHistone, precision_recall

# fill in any blank spots with nearby values
function fill_nans(vals)
    newVals = copy(vals)
    for i in 2:length(vals)
        if isnan(vals[i])
            newVals[i] = newVals[i-1]
        end
    end
    for i in length(vals)-1:-1:1
        if isnan(vals[i])
            newVals[i] = newVals[i+1]
        end
    end
    newVals
end

# compute the rank enrichment curve
function rank_enrichment(truth, pred)
    rank_enrichment(truth[sortperm(pred, rev=true)])
end
function rank_enrichment(rankedTruth, weights=nothing)
    weights = weights == nothing ? ones(length(rankedTruth)) : weights
    x = zeros(Float64, length(rankedTruth))
    y = zeros(Float64, length(rankedTruth))
    randRate = dot(rankedTruth,weights) / sum(weights)
    totalMatchedWeight = 0
    totalSeenWeight = 0
    for i in 1:length(rankedTruth)
        totalMatchedWeight += rankedTruth[i] * weights[i]
        totalSeenWeight += weights[i]
        x[i] = totalSeenWeight
        y[i] = (totalMatchedWeight/totalSeenWeight) / randRate
    end
    x,fill_nans(y)
end
function rank_precision(rankedTruth, weights=nothing)
    weights = weights == nothing ? ones(length(rankedTruth)) : weights
    x,y = rank_enrichment(rankedTruth, weights)
    randRate = dot(rankedTruth,weights) / sum(weights)
    x,y .* randRate
end

function auc(x, y)
    total = 0.0
    lastx = 0.0
    for i in 1:length(x)
        if x[i] != lastx
            total += y[i] * (x[i] - lastx)
            lastx = x[i]
        end
    end
    total
end

function precision_recall(truth, pred)
    precision_recall(truth[sortperm(pred, rev=true)])
end
function precision_recall(rankedTruth)
    x = Int64[]
    y = Float64[]
    total = 0
    for i in 1:length(rankedTruth)
        total += rankedTruth[i]
        push!(x, total)
        push!(y, total/i)
    end
    
    # prune out the points that fall between other points vertically
    newx = Float64[]
    newy = Float64[]
    push!(newx, x[1])
    push!(newy, y[1])
    for i in 2:length(x)-1
        if x[i-1] == x[i] == x[i+1] && y[i-1] > y[i] > y[i+1]
            # ignore since this point adds no new information
        else
            push!(newx, x[i])
            push!(newy, y[i])
        end
    end
    push!(newx, x[end])
    push!(newy, y[end]);
    
    newx,newy
end

function get_enrichment(data; quiet=false)
    totalRight = sum(data)
    topFound = sum(data[1:totalRight])
    if !quiet println(STDERR, "totalRight $totalRight, total found $topFound") end
    return (topFound/totalRight)/(totalRight/length(data))
end

end