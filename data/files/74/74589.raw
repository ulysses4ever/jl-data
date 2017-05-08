module MCepAlpha

# This code is a julia translation of the following project:
# https://bitbucket.org/happyalu/mcep_alpha_calc

export mcepalpha

# mcepalpha computes appropriate alpha for a given sampling frequency.
function mcepalpha(sampfreq;
                   start::Float64=0.0,
                   stop::Float64=1.0,
                   step::Float64=0.001,
                   numpoints::Int=1000)
    alpha_candidates = [start:step:stop]
    mel = melscale_vector(sampfreq, numpoints)
    distances = [rms_distance(mel, warping_vector(alpha, numpoints)) for
                 alpha in alpha_candidates]
    return alpha_candidates[indmin(distances)]
end

function melscale_vector(sampfreq, len::Int)
    const step = (sampfreq / 2.0) / len
    melscalev = 1000.0/log(2)*log(1 + step.*[1:len]./1000.0)
    return melscalev / melscalev[end]
end

function warping_vector(alpha::Float64, len::Int)
    const step = pi / len
    omega = step .* [1:len]
    num = (1-alpha*alpha) * sin(omega)
    den = (1+alpha*alpha) * cos(omega) - 2*alpha
    warpfreq = atan(num./den)
    warpfreq[warpfreq .< 0] += pi
    return warpfreq / warpfreq[end]
end

rms_distance(v1, v2) = sumabs2(v1 - v2) / length(v1)

end # module
