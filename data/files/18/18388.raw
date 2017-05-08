using WAV
using Gaston
# has to return a function giving the pitch and the formant amplitude for each sample

x, Fs = wavread("in.wav")

nFFT = 2048
halfNFFT=div(nFFT,2)
nGap=512 # between windows
nWin = round(Int,(size(x)[1] - nFFT +1)/nGap -1) # number of windows

nFormant=40 # Int
fqFormantMin=50.0
fqFormantMax=22050.0

apoWin=sinpi(linspace(0, 1.0*(nFFT-1)/nFFT ,nFFT))
apoWin2=apoWin.*apoWin


verbose=true

function printlnv(s)
    if verbose==true
        println(s)
    end
end


spectr=zeros(halfNFFT,nWin)


# fmin et fmax pour la voix
fqVoiceMin=70.0
fqVoiceMax=300.0
#nFqVoiceAnalysis=200 # Int

dTmax=round(Int,ceil(Fs/fqVoiceMin))
dTmin=round(Int,floor(Fs/fqVoiceMax))

nFqVoiceAnalysis=dTmax-dTmin+1

fqAnalysis=Fs./(collect(dTmin:dTmax))

#fqAnalysis=exp(linspace(log(fqVoiceMin),log(fqVoiceMax),nFqVoiceAnalysis)) # repartition log
# fqVoicePrecision=(log2(fqAnalysis[2])-log2(fqAnalysis[1]))/12 # semitones between 2 fqs



function powerOfTheResidualAfterRemoveFq(dT::Int64,x::Array{Float64,2},sb::Int64,se::Int64)
    s=0.0
    for i in sb:se
       v=2*x[i]-get(x,i-dT,0.0)-get(x,i+dT,0.0) # y = k*(Id - P)*x
       s+=v^2
    end
    return s/6
end


function selector(x)
    if abs(x)>= 0.5
        return 0
    else
        return cospi(x)^2
    end
end


printlnv("init matrices")
# pitch analysis
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

fC=full(C)
sigmaReg=1E-3
# regPinvC = regularized pseudo inverse
regPinvC=fC'*inv(fC*fC' + sigmaReg^2 * eye(nFormant,nFormant))

printlnv("matrices initialized")


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





printlnv("computation of pitch and spectral enveloppe")

u=zeros(Float64,nFqVoiceAnalysis)

pitchArray=Array(Float64,nWin)
formantsPitchArray=Array(Float64,nWin,nFormant)
formantsNoiseArray=Array(Float64,nWin,nFormant)



for iWin in 1:nWin
    sb=round(Int,(iWin-1)*nGap + 1)
    se = sb+nFFT-1
    s=abs(fft(x[sb:se].*apoWin2))
    
    s=s[1:halfNFFT]

    # nFqVoiceAnalysis=dTmax-dTmin+1
    for idT in 1:nFqVoiceAnalysis
        dT=dTmin+idT-1
        u[idT]=powerOfTheResidualAfterRemoveFq(dT,x,sb,se)
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

printlnv("pitch and spectral enveloppe computed")

# voiceData = VoiceData(Fs,nGap,nFFT,pitchArray,formantsPitchArray,formantsNoiseArray)


type Phase
    phi::Float64 # in the interval [0,1[
end


function incrementPhaseByFreq!(phase::Phase,freq::Float64)
    phase.phi = rem( phase.phi + freq/Fs , 1.0 )
end


function saw(phase::Phase)
    return 2*(phase.phi-0.5)
end

#=
function square(phase::Phase)
    if phase.phi<0.1
        return 0.9
    else
        return -0.1
    end
end
=#

ySaw=zeros(Float64,size(x)[1])
yPitch=zeros(Float64,size(x)[1])
y=zeros(Float64,size(x)[1])

printlnv("synthesis")
sm=1
pitchPrev=0.0
for iWin in 1:nWin
    sb=round(Int,(iWin-1)*nGap + 1)
    se = sb+nFFT-1
    smPrev=sm
    sm=div(sb+se,2)
    pitch=pitchArray[iWin]
    if iWin==1
        pitchPrev=pitch
    end
    yPitch[smPrev:sm]=linspace(pitchPrev,pitch,sm-smPrev+1)
    pitchPrev=pitch
end

yPitch[sm:length(yPitch)]=linspace(pitchPrev,pitchPrev,length(yPitch)-sm+1)

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





