
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

function fix2DTrace(data::Array, t0index::Int, starting::Int, ending::Int, phase::Real = 0.0)
    I = (exp(-phase/180.0im*pi)*fixOffset(data, t0index))
    avgIr = flatten(mean(real(I[starting:ending,:]), 1)[1,:])
    println("Shape: $(size(avgIr))")
    avgIr = fixProjectionOffset(avgIr)
    avgIr = avgIr/maximum(abs(avgIr))
    
    avgIi = flatten(mean(imag(I[1000:4000,:]), 1)[1,:])
    avgIi = fixProjectionOffset(avgIi)
    avgIi = avgIi/maximum(abs(avgIi))
    
    return avgIr + avgIi*im
end
    