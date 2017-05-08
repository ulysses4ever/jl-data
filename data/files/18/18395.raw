using WAV
using Gaston
# has to return a function giving the pitch and the formant amplitude for each sample

#=
# todo :
function initFeatureExtraction()
    # use metaprogramming
end
=#




type Phase
    phi::Float64 # in the interval [0,1[
end


type VoiceData
    Fs::Float64
    nGap::Int64
    nFFT::Int64
    pitchArray::Array{Float64,1}
    formantsPitchArray::Array{Float64,2}
    formantsNoiseArray::Array{Float64,2}
    snrArray::Array{Float64,1}
    C::SparseMatrixCSC{Float64,Int64}
end


function powerOfTheResidualAfterRemoveFq(dT::Int64,x::Array{Float64,2},sb::Int64,se::Int64)
    s=0.0
    for i in sb:se
        v=2*x[i]-get(x,i-dT,0.0)-get(x,i+dT,0.0) # y = k*(Id - P)*x
        s+=v^2
    end
    return s
end


function selector(x)
    if abs(x)>= 0.5
        return 0
    else
        return cospi(x)^2
    end
end


function incrementPhaseByFreq!(phase::Phase,freq::Float64,Fs::Float64)
    phase.phi = rem( phase.phi + freq/Fs , 1.0 )
end


function saw(phase::Phase)
    return 2*(phase.phi-0.5)
end

verbose=true


function printlnv(s)
    if verbose==true
        println(s)
    end
end


function triangle(x,xLeftZero,xTop,xRightZero)
    if x<xLeftZero || x>xRightZero
        return 0
    elseif x<xTop
        return (x-xLeftZero)/(xTop-xLeftZero)
    else
        return (xRightZero-x)/(xRightZero-xTop)
    end
end



function extractFeatures(x::Array{Float64,2},Fs::Float64)
    nFFT = 2048
    halfNFFT=div(nFFT,2)
    nGap=div(nFFT,4) # between windows
    nWin = round(Int,(size(x)[1] - nFFT +1)/nGap -1) # number of windows
    nFormant=40 # Int
    fqFormantMin=50.0
    fqFormantMax=22050.0
    apoWin=sinpi(linspace(0, 1.0*(nFFT-1)/nFFT ,nFFT))
    apoWin2=apoWin.*apoWin

    nRoughFormant=13


    spectr=zeros(halfNFFT,nWin)

    # fmin et fmax pour la voix
    fqVoiceMin=70.0
    fqVoiceMax=300.0

    dTmax=round(Int,ceil(Fs/fqVoiceMin))
    dTmin=round(Int,floor(Fs/fqVoiceMax))

    nFqVoiceAnalysis=dTmax-dTmin+1

    fqAnalysis=Fs./(collect(dTmin:dTmax))



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

    fqRoughFormantArray=exp(linspace(log(fqFormantMin),log(fqFormantMax),nRoughFormant+2)) # central frequencies
    roughC=spzeros(nRoughFormant,halfNFFT)
    for iFormant in 1:nRoughFormant
        for iFq in 1:halfNFFT
            fq=(iFq-1)*Fs/nFFT
            roughC[iFormant,iFq]=triangle(fq,fqRoughFormantArray[iFormant],
                                          fqRoughFormantArray[iFormant+1],
                                          fqRoughFormantArray[iFormant+2])
        end
        v=norm(roughC[iFormant,:])
        if(v>0)
            roughC[iFormant,:]=roughC[iFormant,:]/v
        end
    end


    printlnv("matrices initialized")
    printlnv("computation of pitch and spectral enveloppe")

    u=zeros(Float64,nFqVoiceAnalysis)

    pitchArray=Array(Float64,nWin)
    formantsPitchArray=Array(Float64,nWin,nFormant)
    formantsNoiseArray=Array(Float64,nWin,nFormant)
    snrArray=Array(Float64,nWin)
    roughLogSpectrum=Array(Float64,nWin,nRoughFormant)



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
        roughLogSpectrum[iWin,:]=log(roughC*s+eps(Float64))
        snrArray[iWin]=log((norm(hatXPitch)+eps(Float64))/(norm(hatNoise)+eps(Float64)))
    end

    printlnv("pitch and spectral enveloppe computed")
    voiceData = VoiceData(Fs,nGap,nFFT,pitchArray,
                          formantsPitchArray,formantsNoiseArray,
                          snrArray,C)
    return (voiceData,roughLogSpectrum)
end




function synthesisFromVoiceData(voiceData::VoiceData)

    Fs=voiceData.Fs
    nGap=voiceData.nGap
    nFFT=voiceData.nFFT
    halfNFFT=div(nFFT,2)
    pitchArray=voiceData.pitchArray
    formantsPitchArray=voiceData.formantsPitchArray
    formantsNoiseArray=voiceData.formantsNoiseArray
    snrArray=voiceData.snrArray
    C=voiceData.C
    nFormant=size(C)[1]

    # regPinvC = regularized pseudo inverse
    fC=full(C)
    sigmaReg=1E-3
    regPinvC=fC'*inv(fC*fC' + sigmaReg^2 * eye(nFormant,nFormant))


    apoWin=sinpi(linspace(0, 1.0*(nFFT-1)/nFFT ,nFFT))
    apoWin2=apoWin.*apoWin

    nWin = length(pitchArray)
    lenX = nWin*nGap+nFFT # /!\ todo : corriger

    ySaw=zeros(Float64,lenX)
    yPitch=zeros(Float64,lenX)
    y=zeros(Float64,lenX)

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

    for it in 1:lenX
        ySaw[it]=saw(phase)
        incrementPhaseByFreq!(phase,yPitch[it],Fs)
    end

    #wavwrite(ySaw*0.1,"outSynth.wav",Fs=Fs)

    yWhiteNoise=randn(lenX)

    Y=zeros(Complex{Float64},nFFT)

    for iWin in 1:nWin
        sb=round(Int,(iWin-1)*nGap + 1)
        se = sb+nFFT-1

        YS=fft(ySaw[sb:se].*apoWin)
        YS=YS./(abs(YS)+1)
        tYS=YS[1:halfNFFT]
        ftYS=tYS.*(regPinvC*formantsPitchArray[iWin,:]')

        YN=fft(yWhiteNoise[sb:se].*apoWin)
        YN=YN./(abs(YN)+1)
        tYN=YN[1:halfNFFT]
        ftYN=tYN.*(regPinvC*formantsNoiseArray[iWin,:]')

        Y[1:halfNFFT]=ftYS + ftYN
        Y[halfNFFT+1:nFFT]=conj(flipdim(Y[1:halfNFFT],1))
        y[sb:se]+=real(ifft(Y)).*apoWin
    end

    return y
end


function testExtractFeatures()
    x, Fs = wavread("in.wav")
    Fs=convert(Float64,Fs)
    voiceData,roughLogSpectrum=extractFeatures(x,Fs)
    y=synthesisFromVoiceData(voiceData)
    y=0.9*y/maximum(abs(y))
    printlnv("Done.")
    wavwrite(y,"out.wav",Fs=Fs)
end





