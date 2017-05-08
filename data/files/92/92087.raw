using PyCall

@pyimport numpy as np
@pyimport scipy.io as io
@pyimport scipy.signal as pysig

function loadfilter(file :: String)
    io.loadmat("lib/filt/"*file*".mat")[file][:]
end

function filtfilt(b :: Vector, x :: Vector)
    pysig.filtfilt(b, [1.0], x)
end
