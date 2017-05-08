# demo of dereverberation algorithm.
# source: alg_mclp_derev.jl
#         stft.jl
#         istft.jl
#         convmtx.jl
#         solver_irls.jl
# This file produces a demo for dereverberation algorithm.
# Outputs the clean speech spectrogram, the microphone spectrogram,
# and the dereverberated speech spectrogram. Sound of these speeches
# can also be played.


# including library
# If you do not have the following package, please run
# Pkg.add("package_name") to add the packages befure
# using them.
using MAT
using DSP
using PyPlot
using WAV
using AudioIO

# set working directory
cd("/Users/zichaowang/Documents/DSP/dereverb") # CHANGE this to your local directory path to "dereverb" folder
include("alg_mclp_derev.jl")
include("plot_spectrogram.jl")

# load speech samples
# NOTE: the data here is taken from RIR = 1. You cannot choose RIR. But you can choose utterance.
selUtt     = 1   # select utterance
selMic     = 1:2 # select microphone numbers
file       = matopen("generated.mat")
clean      = read(file, "clean")
cleanOrig  = clean[selUtt]["data"]
micro      = read(file, "micro")
microOrig  = micro[selUtt]["data"][:,selMic]
fs         = read(file, "fs"   )

# crop the samples
selTime    = 3                       # speech length for dereverberation (in seconds)
selSamples = floor( selTime * fs );  # round to nearest integer towards zero
# crop clean speech
if selSamples >= length(cleanOrig)
    cln = cleanOrig;
else
    cln = cleanOrig[1:selSamples];
end
# crop microphone speech
if selSamples >= size(microOrig,1)
    mic = microOrig;
else
    mic = microOrig[1:selSamples,:];
end

# parameters for dereverberation
refMic   = 1
tau      = 2
Lg       = 20
nFFT     = 1024
nShift   = 256
winType  = hamming # did not use this parameter in this test
itMax    = 10
myeps    = 1e-8
itTol    = 1e-4
p        = 0

# dereverberation
# do not have the option to choose window type in this simple implementation.
# Using Hamming window by now.
dEst, D = alg_mclp_derev(mic, refMic, tau, Lg, nFFT, nShift, winType, myeps, itMax, itTol, p)

# spectrogram
plot_spectrogram(cln,  fs)
title("Clean Speech")
plot_spectrogram(mic,  fs)
title("Microphone Signal")
plot_spectrogram(dEst, fs)
title("Estimated Speech")


# play sounds (uncomment the following)
# wavplay(cln,  fs)
# wavplay(mic,  fs)
# wavplay(dEst, fs)

