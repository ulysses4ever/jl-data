### STFT ###
# from r9y9/julia-nmf-ss-toy on github
# https://github.com/r9y9/julia-nmf-ss-toy.git

function blackman(n::Integer)
    const a0, a1, a2 = 0.42, 0.5, 0.08
    t = 2*pi/(n-1)
    [a0 - a1*cos(t*k) + a2*cos(t*k*2) for k=0:n-1]
end

function my_hamming(n::Integer)
    [0.54 - 0.46*cos(2*pi*k/(n-1)) for k=0:(n-1)]
end

# countframes returns the number of frames that will be processed.
function countframes{T<:Number}(x::Vector{T}, framelen::Int, hopsize::Int)
    div(length(x) - framelen, hopsize) + 1
end

# splitframes performs overlapping frame splitting.
function splitframes{T<:Number}(x::Vector{T},
                                framelen::Int=1024,
                                hopsize::Int=framelen/2)
    const N = countframes(x, framelen, hopsize)
    frames = Array(eltype(x), framelen, N)

    for i=1:N
        frames[:,i] = x[(i-1)*hopsize+1:(i-1)*hopsize+framelen]
    end

    return frames
end
# N = countframes(v,nFFT,nShift)

# stft performs the Short-Time Fourier Transform (STFT) for real signals.
function mySTFT{T<:Real}(x::Vector{T},
                       framelen::Int=1024,
                       hopsize::Int=div(framelen,2),
                       window = my_hamming(framelen))
    frames = splitframes(x, framelen, hopsize)

    const freqbins = div(framelen, 2) + 1
    spectrogram = Array(Complex64, freqbins, size(frames,2))
    for i=1:size(frames,2)
        spectrogram[:,i] = rfft(frames[:,i] .* window)
    end

    return spectrogram
end

# test
# h = [1:32]
# nFFT = 16
# nShift = 4
# frames = splitframes(h, nFFT, nShift)
# mySTFT(h,nFFT,nShift)

