include("/home/jeb/Teaching/Research/Thermodynamics/eclipse-julia/HnFFTFp/src/FFT.jl")
include("/home/jeb/Teaching/Research/Thermodynamics/eclipse-julia/HnFFTFp/src/IFFT.jl")
println("> FFT-IFFT test ")
N = UInt64(10)
P = UInt(2)^N
M = BigInt(997)
HNF1 = Array(BigInt, P)
for i = 1:P
  HNF1[i] = big(i) % M
end
t1 = time()
FFT = hn_fft(N, P, M, HNF1)
HNF2 = hn_ifft(N, P, M, FFT)
t2 = time()
println("> elapsed time: ", t2-t1)
@assert maximum(abs(HNF1-HNF2)) == 0
println("> success")
