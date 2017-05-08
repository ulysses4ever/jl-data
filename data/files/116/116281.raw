function pduduchud(N)
    M = N/14 + 1
    set_bigfloat_precision(int(N*log2(10))+1)
    split = 50
    times = int(M/split)+1
    x = int(linspace(0,times,times+1))
    x = shuffle(x) # for load  balancing
    invpi = @parallel (+) for i=1:times+1
        dudu_chud(split,x[i])
    end
    f = sqrt(BigFloat(BigInt(640320)^3))
    mypi = f/(12*invpi)
    return mypi
    # println("done")
end
