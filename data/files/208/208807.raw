
# Performs a baseline correction by averaging the spectrum recorded before the laser pulse
# and offsetting the rest of the spectrum accordingly
export fixOffset, fixProjectionOffset, fix2DTrace

function fixOffset{T<:Complex}(data::Array{T,2}, index::Int)
    d2 = copy(data)
    for i = 1:size(data)[1]
        d2[i,:] = (real(d2[i,:]) - mean(real(d2[i,1:index]))) + 
                  (imag(d2[i,:]) - mean(imag(d2[i,1:index])))*im
    end
    
    return d2
end
    
# Fixes the wings of field projected data
function fixProjectionOffset(data::Vector, tolerance::Real = 0.05)
    data = copy(data)
    width = int64(length(data)*tolerance + 0.5)
    data = data - mean([data[1:width], data[length(data)-width:]])
    return data
end

function fix2DTrace{T}(data::Array{T,2}, t0index::Int, starting::Int, ending::Int; phase0::Real = 0.0, phase1::Real = 0.0)
    I = copy(data)
    
    fixVector = linearPhaseCorrection(T, size(I)[2], phase0, phase1)'
    
    for i = 1:size(I)[1]
      I[i,:] = I[i,:].*fixVector
    end
    
    I = fixOffset(I, t0index)
    #, phase0, phase1)
    avgIr = flatten(mean(real(I[starting:ending,:]), 1)[1,:])
    
    avgIr = fixProjectionOffset(avgIr)
    scale = maximum(abs(avgIr))   # We want them to be on the same scale, so we arbitrarily scale to the real.
    avgIr = avgIr/scale
    
    avgIi = flatten(mean(imag(I[1000:4000,:]), 1)[1,:])
    avgIi = fixProjectionOffset(avgIi)
    avgIi = avgIi/scale
    
    return avgIr + avgIi*im
end

# Phase shifts the spectrum by multiplying by exp(-p0*pi*im/180) *
#   exp(-p1*pi*im/180)
function linearPhaseCorrection(T::Type, length, p0::Real, p1::Real = 0.0)
    assert(length > 0)
    
    fix = ones(T, length)*exp(-pi*p0*im/180.0)
    
    range = linspace(-1.0, 1.0, length)
    linear = exp(-range*pi*p1*im/180.0)
    fix = fix.*linear
    return convert(Vector{T}, fix)
end
    