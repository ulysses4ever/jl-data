module PredictionModels

export getPredictorBaseline, getPredictorA, getPredictorB, getPredictorC, getPredictorD, getPredictorADPM

using DataFrames

function getPredictorBaseline(df::DataFrame)
    mm = aarModel(df)
    function predictor(df::DataFrame,opt::Symbol)
        if opt == :expected
            expected = zeros(Float64,6)
            for i = 1:length(expected)
                expected[i] = (mm*[0:length(mm)-1])[1]
            end
            return expected::Array
        elseif opt == :probs
            probs = zeros(Float64,6,length(mm))
            for i = 1:size(probs,1)
                probs[i,:] = mm
            end
            return probs::Array
        else
            error("Not a valid input, choose :expected or :probs")
        end
    end
    return predictor::Function
end

function getPredictorA(df::DataFrame)
    mm = weatherAarModel(df)
    wm = weatherMM(df)
    function predictor(df::DataFrame,opt::Symbol)
        if opt == :expected
            expected = zeros(Float64,6)
            for i = 1:length(expected)
                expected[i] = ((wm[VFR(df[:Ceiling_0][1],df[:Visibility_0][1]),:]*wm^(i-1)*mm)*[0:size(mm,2)-1])[1]
            end
            return expected::Array
        elseif opt == :probs
            probs = zeros(Float64,6,size(mm,2))
            for i = 1:size(probs,1)
                probs[i,:] = wm[VFR(df[:Ceiling_0][1],df[:Visibility_0][1]),:]*wm^(i-1)*mm
            end
            return probs::Array
        else
            error("Not a valid input, choose :expected or :probs")
        end
    end
    return predictor::Function
end

function getPredictorB(df::DataFrame)
    mm = forecastAarModel(df)
    function predictor(df::DataFrame,opt::Symbol)
        if opt == :expected
            expected = zeros(Float64,6)
            for i = 1:length(expected)
                expected[i] = (reshape(mm[VFR(df[symbol("Ceiling_"*string(i))][1],df[symbol("Visibility_"*string(i))][1]),i,:],1,size(mm,3))*[0:size(mm,3)-1])[1]
            end
            return expected::Array
        elseif opt == :probs
            probs = zeros(Float64,6,size(mm,3))
            for i = 1:size(probs,1)
                probs[i,:] = mm[VFR(df[symbol("Ceiling_"*string(i))][1],df[symbol("Visibility_"*string(i))][1]),i,:]
            end
            return probs::Array
        else
            error("Not a valid input, choose :expected or :probs")
        end
    end
    return predictor::Function
end

function getPredictorC(df::DataFrame)
    mm = weatherAarModel(df)
    fm = forecastWeatherModel(df)
    function predictor(df::DataFrame,opt::Symbol)
        if opt == :expected
            expected = zeros(Float64,6)
            for i = 1:length(expected)
                expected[i] = ((reshape(fm[i,VFR(df[symbol("Ceiling_"*string(i))][1],df[symbol("Visibility_"*string(i))][1]),:],1,size(fm,2))*mm)*[0:size(mm,2)-1])[1]
            end
            return expected::Array
        elseif opt == :probs
            probs = zeros(Float64,6,size(mm,2))
            for i = 1:size(probs,1)
                probs[i,:] = reshape(fm[i,VFR(df[symbol("Ceiling_"*string(i))][1],df[symbol("Visibility_"*string(i))][1]),:],1,size(fm,2))*mm
            end
            return probs::Array
        else
            error("Not a valid input, choose :expected or :probs")
        end
    end
    return predictor::Function
end

function getPredictorD(df::DataFrame)
    mm = aarMM(df)
    function predictor(df::DataFrame,opt::Symbol)
        if opt == :expected
            expected = zeros(Float64,6)
            for i = 1:length(expected)
                expected[i] = ((mm[df[:AAR_0][1]+1,:]*mm^(i-1))*[0:size(mm,1)-1])[1]
            end
            return expected::Array
        elseif opt == :probs
            probs = zeros(Float64,6,size(mm,1))
            for i = 1:size(probs,1)
                probs[i,:] = mm[df[:AAR_0][1]+1,:]*mm^(i-1)
            end
            return probs::Array
        else
            error("Not a valid input, choose :expected or :probs")
        end
    end
    return predictor::Function
end

function getPredictorADPM(df::DataFrame)
    mm = forecastAarMM(df)
    function predictor(df::DataFrame,opt::Symbol)
        if opt == :expected
            expected = zeros(Float64,6)
            row = reshape(mm[VFR(df[:Ceiling_1][1],df[:Visibility_1][1]),1,df[:AAR_0][1]+1,:],1,size(mm,3))
            expected[1] = (row*[0:size(mm,3)-1])[1]
            for i = 2:length(expected)
                row = row*reshape(mm[VFR(df[symbol("Ceiling_"*string(i))][1],df[symbol("Visibility_"*string(i))][1]),i,:,:],size(mm,3),size(mm,4))
                expected[i] = (row*[0:size(mm,3)-1])[1]
            end
            return expected::Array
        elseif opt == :probs
            probs = zeros(Float64,6,size(mm,3))
            row = reshape(mm[VFR(df[:Ceiling_1][1],df[:Visibility_1][1]),1,df[:AAR_0][1]+1,:],1,size(mm,3))
            probs[1,:] = row
            for i = 2:size(probs,1)
                row = row*reshape(mm[VFR(df[symbol("Ceiling_"*string(i))][1],df[symbol("Visibility_"*string(i))][1]),i,:,:],size(mm,3),size(mm,4))
                probs[i,:] = row
            end
            return probs::Array
        else
            error("Not a valid input, choose :expected or :probs")
        end
    end
    return predictor::Function
end

include("weather.jl")
include("models.jl")
include("normalize.jl")

end # module
