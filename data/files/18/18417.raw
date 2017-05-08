include("synth.jl")

Fs=44100.0
nt=44100*10

nOsc=10
phaseSawArray=[Phase(rand()) for i in 1:nOsc]

y=zeros(nt)

dt=1/Fs

noteArray=zeros(Float64,nOsc)
dnoteArray=zeros(Float64,nOsc)

for it in 1:nt
    for iOsc in 1:nOsc
        y[it]+=saw(phaseSawArray[iOsc])/nOsc
        incrementPhaseByFreq!(phaseSawArray[iOsc],noteToFreq(noteArray[iOsc]))
        noteArray[iOsc]+=dnoteArray[iOsc]*dt
        dnoteArray[iOsc]+=(1E3*randn() )*dt
    end
end

wavwrite(y, "out.wav",Fs=Fs)
