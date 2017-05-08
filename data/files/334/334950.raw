function meanSquaredError(test::DataFrame,predictor::Function)
    mse = zeros(Float64,6)
    for i = 1:size(test,1)
        prediction = predictor(test[i,names(test)],:expected)
        for j = 1:length(mse)
            mse[j] += (test[symbol("AAR_"*string(j))][1]-prediction[j])^2
        end
    end
    return mse::Array
end

function brierScore(test::DataFrame,predictor::Function)
    bs = zeros(Float64,6)
    for i = 1:size(test,1)
        prediction = predictor(test[i,names(test)],:probs)
        for j = 1:length(bs)
            for k = 1:size(prediction,2)
                if k == test[symbol("AAR_"*string(j))][1]+1
                    bs[j] += (1-prediction[j,k])^2
                else 
                    bs[j] += prediction[j,k]^2
                end
            end
        end
    end
    return bs::Array
end

function weightedSquaredError(test::DataFrame,predictor::Function)
    wse = zeros(Float64,6)
    for i = 1:size(test,1)
        prediction = predictor(test[i,names(test)],:probs)
        for j = 1:length(wse)
            for k = 1:size(prediction,2)
                wse[j] += prediction[j,k]*(k-1-test[symbol("AAR_"*string(j))][1])^2
            end
        end
    end
    return wse::Array
end
