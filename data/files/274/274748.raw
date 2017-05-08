# This function returns a vector of classified data (not VFR = 1, VFR = 2) for a dataframe
function VFR(df::DataFrame)
    VFRs = ones(size(df,1))
    for i = 1:size(df,1)
        if df[:Ceiling_0][i]*100.0 > 3000. && df[:Visibility_0][i] > 5.
            VFRs[i] = 2.
        end
    end
    return VFRs::Array
end

# This function returns the classification of a data point (not VFR = 1, VFR = 2) for a single ceiling and visibility value
function VFR(ceil::Float64,vis::Float64)
    VFRs = 1.
    if ceil*100.0 > 3000. && vis > 5.
        VFRs = 2.
    end
    return VFRs::Float64
end
