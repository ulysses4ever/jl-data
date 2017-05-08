# using Interpolations

Fs=44100.0

fqA4=440.0


type Phase
   phi::Float64 # dérivée de fréquence instantanée en Hz
end


function freqToNote(f::Float64)
    return log(f/fqA4)*12/log(2)
end

function noteToFreq(x::Float64)
       return fqA4*exp(x*log(2)/12)
end

function incrementPhaseByFreq!(phase::Phase,freq::Float64)
    phase.phi = rem( phase.phi + freq/Fs , 1.0 )
end

#=
function incrementPhaseByNote(phase::Phase,note::Float64)
    phase.phi = rem( phase.phi + noteToFreq(note)/Fs , 1.0 )
end
=#

function saw(phase::Phase)
    return 2*(phase.phi-0.5)
end

function sine(phase::Phase)
    return sin(2*pi*phase.phi)
end

function square(phase::Phase)
   if phase.phi<0.5
        return 1
    else
        return -1
    end
end

function triangle(phase::Phase)
   if phase.phi<0.5
        return -4*phase.phi + 1
    else
        return 4*(phase.phi-0.5)-1
    end
end

function linearInterpolation(x,y,t)
    # wrapper
    # interpolates the (x[i],y[i]) and produces a piecewise linear function such as f(x[i])=y[i]


end


#=
function getSampleFromPeriodicBuffer(buf::Array{Float64,1},phase::Float64)
end
=#




