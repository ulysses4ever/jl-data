using WAV
using Gaston
# has to return a function giving the pitch and the formant amplitude for each sample

x, Fs = wavread("in.wav")

nFFT = 2048
halfNFFT=div(nFFT,2)
nGap=512 # between windows
nWin = round(Int,(size(x)[1] - nFFT +1)/nGap -1) # nombre de fenetres

apoWin=sinpi(linspace(0, 1.0*(nFFT-1)/nFFT ,nFFT))
apoWin2=apoWin.*apoWin


# frequencies of the FFT used for pitch estimation
fqAnalysisMin=50 # Hz
fqAnalysisMax=4000.0 # Hz

# indices correspondants
iFqAnalysisMax = round(Int,ceil(fqAnalysisMax*nFFT/Fs + 1))
iFqAnalysisMin = round(Int,floor(fqAnalysisMin*nFFT/Fs + 1))

#spectrCut=zeros(iFqAnalysisMax,nWin)
spectr=zeros(halfNFFT,nWin)


# fmin et fmax pour la voix
fqVoiceMin=70.0
fqVoiceMax=300.0
nFqVoiceAnalysis=200 # Int


fqAnalysis=exp(linspace(log(fqVoiceMin),log(fqVoiceMax),nFqVoiceAnalysis)) # repartition log

fqVoicePrecision=(log2(fqAnalysis[2])-log2(fqAnalysis[1]))/12 # semitones between 2 fqs


function selector(x)
    if abs(x)>= 0.5
        return 0
    else
        return cospi(x)^2
    end
end


println("init des matrices")
# matrices d'analyse de pitch
A=Array(SparseMatrixCSC{Float64,Int64},nFqVoiceAnalysis)
for ifqVoiceAnalysis in 1:nFqVoiceAnalysis
    fq = fqAnalysis[ifqVoiceAnalysis] # fondamentale
    rSmp = Fs/fq
    nPhase = round(Int,ceil(rSmp))
    B=spzeros(nFFT,nPhase)
    for iPhase in 1:nPhase
        for k in round(Int,ceil((1-iPhase)/rSmp)):round(Int,floor((nFFT-iPhase)/rSmp))
            it=round(Int,k*rSmp+iPhase)
            B[it,iPhase]=1
        end
    end
    A[ifqVoiceAnalysis]=B
end



nFormant=40 # Int
fqFormantMin=50.0
fqFormantMax=22050.0

fqFormantArray=exp(linspace(log(fqFormantMin),log(fqFormantMax),nFormant+2)) # central frequencies



function triangle(x,xLeftZero,xTop,xRightZero)
    if x<xLeftZero || x>xRightZero
        return 0
    elseif x<xTop
        return (x-xLeftZero)/(xTop-xLeftZero)
    else
        return (xRightZero-x)/(xRightZero-xTop)
    end
end



C=spzeros(nFormant,halfNFFT)
for iFormant in 1:nFormant
    for iFq in 1:halfNFFT
        fq=(iFq-1)*Fs/nFFT
        C[iFormant,iFq]=triangle(fq,fqFormantArray[iFormant],
                                 fqFormantArray[iFormant+1],
                                 fqFormantArray[iFormant+2])
    end
    v=norm(C[iFormant,:])
    if(v>0)
        C[iFormant,:]=C[iFormant,:]/v
    end
end

# calcul de la pinvC régularisée
fC=full(C)
#U,A,V=svd(C)
# C = U*diagm(A)*V'
sigmaReg=1E-3
regPinvC=fC'*inv(fC*fC' + sigmaReg^2 * eye(nFormant,nFormant))

println("fin init des matrices") # sauvergarder ces matrices pour la demo


#=
figure(19)
c = CurveConf()
c.plotstyle = "image"
Z = full(C)
addcoords([],[],Z,c)
a = AxesConf()
a.title = "Image"
addconf(a)
llplot()
=#



type VoiceData
    Fs::Float64
    nGap::Int64
    nFFT::Int64
    pitchArray::Array{Float64,1}
    formantsPitchArray::Array{Float64,2}
    formantsNoiseArray::Array{Float64,2}
end




println("calcul (du spectrogramme,) du pitch et de l'enveloppe spectrale")

u=zeros(Float64,nFqVoiceAnalysis)

pitchArray=Array(Float64,nWin)
formantsPitchArray=Array(Float64,nWin,nFormant)
formantsNoiseArray=Array(Float64,nWin,nFormant)



for iWin in 1:nWin
    sb=round(Int,(iWin-1)*nGap + 1)
    se = sb+nFFT-1
    s=abs(fft(x[sb:se].*apoWin2))
    #=  spectrCut[:,iWin]=v[1:iFqAnalysisMax] =#
    s=s[1:halfNFFT]

    for ifqVoiceAnalysis in 1:nFqVoiceAnalysis
        B=A[ifqVoiceAnalysis]
        v=B\x[sb:se]
        u[ifqVoiceAnalysis]=norm(x[sb:se]-B*v)
    end

    val,idxFqPitch=findmin(u)
    fqPitch=fqAnalysis[idxFqPitch] # Hz
    B=A[idxFqPitch]
    v=B\x[sb:se]
    hatXPitch=B*v
    hatNoise=x[sb:se]-hatXPitch
    hatSPitch=abs(fft(hatXPitch.*apoWin2))
    formantsPitch=C*hatSPitch[1:halfNFFT]

    hatSNoise=abs(fft(hatNoise.*apoWin2))
    formantsNoise=C*hatSNoise[1:halfNFFT]

    pitchArray[iWin]=fqPitch
    formantsPitchArray[iWin,:]=formantsPitch
    formantsNoiseArray[iWin,:]=formantsNoise
end

println("fin calcul (du spectrogramme,) du pitch et de l'enveloppe spectrale")

# voiceData = VoiceData(Fs,nGap,nFFT,pitchArray,formantsPitchArray,formantsNoiseArray)


type Phase
    phi::Float64 # dérivée de fréquence instantanée en Hz
end


function incrementPhaseByFreq!(phase::Phase,freq::Float64)
    phase.phi = rem( phase.phi + freq/Fs , 1.0 )
end


function saw(phase::Phase)
    return 2*(phase.phi-0.5)
end

function square(phase::Phase)
    if phase.phi<0.1
        return 0.9
    else
        return -0.1
    end
end


ySaw=zeros(Float64,size(x)[1])
yPitch=zeros(Float64,size(x)[1])
y=zeros(Float64,size(x)[1])

println("synthèse")

for iWin in 1:nWin
    sb=round(Int,(iWin-1)*nGap + 1)
    se = sb+nFFT-1
    pitch=pitchArray[iWin]
    yPitch[sb:se]+=pitch*apoWin2/2 # /!\ denominator should depend on nGap and nFFT !
end

phase=Phase(0)

for it in 1:size(x)[1]
    ySaw[it]=saw(phase)
    incrementPhaseByFreq!(phase,yPitch[it])
end

wavwrite(ySaw*0.1,"outSynth.wav",Fs=Fs)

yWhiteNoise=randn(size(x)[1])

Y=zeros(Complex{Float64},nFFT)

for iWin in 1:nWin
    sb=round(Int,(iWin-1)*nGap + 1)
    se = sb+nFFT-1

    YS=fft(ySaw[sb:se].*apoWin)
    YS=YS./(abs(YS)+1)
    tYS=YS[1:halfNFFT]
    #=trTYS=C*tYS
    iTrTYS=1./(trTYS+1E-6)
    iTYS=regPinvC*iTrTYS =#
    ftYS=tYS.*(regPinvC*formantsPitchArray[iWin,:]')

    YN=fft(yWhiteNoise[sb:se].*apoWin)
    YN=YN./(abs(YN)+1)
    tYN=YN[1:halfNFFT]
    ftYN=tYN.*(regPinvC*formantsNoiseArray[iWin,:]')

    Y[1:halfNFFT]=ftYS  + ftYN
    Y[halfNFFT+1:nFFT]=conj(flipdim(Y[1:halfNFFT],1))
    y[sb:se]+=real(ifft(Y)).*apoWin
end

y=0.9*y/maximum(abs(y))

wavwrite(y,"out.wav",Fs=Fs)





