# This function returns the model that defines  P(AAR_{t}) for all t
function aarModel(df::DataFrame)
    maxAAR = maximum(df[:AAR_0])
    mm = zeros(Float64,1,maxAAR+1)
    for i = 1:length(df[:AAR_0])
        mm[df[:AAR_0][i]+1] += 1.
    end
    normalize(mm)
    return mm::Array
end

# This function returns the Markov chain describing the evolution of weather, that is P(AAR_{t+1}|AAR_{t}) for all t
function aarMM(df::DataFrame)
    maxAAR = maximum(df[:AAR_0])
    mm = zeros(Float64,maxAAR+1,maxAAR+1)
    for i = 1:length(df[:AAR_0])
        mm[df[:AAR_0][i]+1,df[:AAR_1][i]+1] += 1.
    end     
    normalize(mm)
    return mm::Array
end  

# This function returns the Markov chain describing the evolution of weather, that is P(Weather_{t+1}|Weather_{t}), where Weather is a binary variable that is not VFR (1) or VFR (2)
function weatherMM(df::DataFrame)
    mm = zeros(Float64,2,2)
    for i = 1:size(df,1)-1
        mm[VFR(df[:Ceiling_0][i],df[:Visibility_0][i]),VFR(df[:Ceiling_0][i+1],df[:Visibility_0][i+1])] += 1.
    end
    normalize(mm)
    return mm::Array
end

# This function returns the model that defines P(AAR_{t}|Weather_{t}) for all t, where Weather is a binary variable that is either 1 (no VFR) or 2 (VFR)
function weatherAarModel(df::DataFrame)
    maxAAR = maximum(df[:AAR_0])
    mm = zeros(Float64,2,maxAAR+1)
    for i = 1:length(df[:AAR_0])
        mm[VFR(df[:Ceiling_0][i],df[:Visibility_0][i]),df[:AAR_0][i]+1] += 1.
    end
    normalize(mm)
    return mm::Array
end

# This function returns P(AAR_{t+1}|AAR_{t},Weather_{t+1}) for all t
function weatherAarMM(df::DataFrame)
    maxAAR = maximum(df[:AAR_0])
    mm = zeros(Float64,2,maxAAR+1,maxAAR+1)
    for i = 1:size(df,1)-1
        mm[VFR(df[:Ceiling_0][i+1],df[:Visibility_0][i+1]),df[:AAR_0][i]+1,df[:AAR_1][i]+1] += 1.
    end
    normalize(mm)
    return mm::Array
end

# This function returns the model that defines P(Forecast_{t+k}|Weather_{t+k} for k = 1,...,6
function forecastWeatherModel(df::DataFrame)
    mm = zeros(Float64,6,2,2)
    for i = 7:size(df,1)
        for j = 1:size(mm,1)
            mm[j,VFR(df[:Ceiling_0][i],df[:Visibility_0][i]),VFR(df[symbol("Ceiling_"*string(j))][i-j],df[symbol("Visibility_"*string(j))][i-j])] += 1.
        end
    end
    normalize(mm)
    return mm::Array
end

# This function returns P(AAR_{t+k}|Forecast_{t+k}) for k = 1,...,6
function forecastAarModel(df::DataFrame)
    maxAAR = maximum(df[:AAR_0])
    mm = zeros(Float64,2,6,maxAAR+1)
    for i = 1:size(df,1)
        for j = 1:size(mm,2)
            mm[VFR(df[symbol("Ceiling_"*string(j))][i],df[symbol("Visibility_"*string(j))][i]),j,df[symbol("AAR_"*string(j))][i]+1] += 1.
        end
    end
    normalize(mm)
    return mm::Array
end

# This function returns P(AAR_{t+k}|AAR_{t+k-1},Forecast_{t+k}) for all k = 1,...,6
function forecastAarMM(df::DataFrame)
    maxAAR = maximum(df[:AAR_0])
    mm = zeros(Float64,2,6,maxAAR+1,maxAAR+1)
    for i = 1:size(df,1)
        for j = 1:size(mm,2)
            mm[VFR(df[symbol("Ceiling_"*string(j))][i],df[symbol("Visibility_"*string(j))][i]),j,df[symbol("AAR_"*string(j-1))][i]+1,df[symbol("AAR_"*string(j))][i]+1] += 1.
        end
    end
    normalize(mm)
    return mm::Array
end
