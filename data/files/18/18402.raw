include("synth.jl")
include("localProjector.jl")

Fs=44100.0
nt=44100*17

nOsc=3*4*8
phaseSawArray=[Phase(rand()) for i in 1:nOsc]

y=zeros(nt,nOsc)

dt=1/Fs

noteShift=-12

noteArray=zeros(Float64,nOsc)

relNote=[0.0,4.0,7.0]

iOsc=1
for iOctave in 1:8
    for imOsc in 1:4
        for note in relNote
            noteArray[iOsc]=note+12*(iOctave-4)
            iOsc+=1
        end
    end
end


dnoteArray=zeros(Float64,nOsc)

for it in 1:nt
    for iOsc in 1:nOsc
        y[it,iOsc]=saw(phaseSawArray[iOsc])
        incrementPhaseByFreq!(phaseSawArray[iOsc],noteToFreq(noteArray[iOsc]))
        #=
        noteArray[iOsc]+=dnoteArray[iOsc]*dt
        dnoteArray[iOsc]+=(1E2*randn() - 1E-1*(noteArray[iOsc]-noteShift))*dt - (1E-7)*dnoteArray[iOsc]
        =#
    end
end


sy=y*ones(nOsc)/nOsc # sums the synths
wavwrite(sy, "out.wav",Fs=Fs)

x, fs = wavread("in.wav")

x=collect(x[:,1])



out=localProjector(x,y)


out=out/maximum(abs(out))
wavwrite(out, "coded.wav",Fs=Fs)
