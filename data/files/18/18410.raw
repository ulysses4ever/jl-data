function localProjector(x::Array{Float64,1},y::Array{Float64,2})
    len = minimum([size(x)[1],size(y)[1]])
    apoWinLen = 2048*4
    winLen=apoWinLen
    halfWinLen=Int(winLen/2)
    w = sin(linspace(0,pi,apoWinLen)).^2
    lastWinNum = floor(2*(len/apoWinLen-1))
    nOsc=size(y)[2]
    out=zeros(len)

    for winNum in 0:lastWinNum
        A = y[winNum*halfWinLen+1:winNum*halfWinLen+winLen,:]
        for iOsc in 1:nOsc
            A[:,iOsc]=(A[:,iOsc].*w)
        end
        z=x[winNum*halfWinLen+1:winNum*halfWinLen+winLen,:]
        pz = A*(A\z)
        out[winNum*halfWinLen+1:winNum*halfWinLen+winLen]+=pz
    end

    return out
end



