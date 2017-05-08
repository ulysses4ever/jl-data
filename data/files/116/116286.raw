function pchud(N)
    set_bigfloat_precision(int(N*log2(10))+1)
    invpi = @parallel (+) for i=0:nprocs()-1
        parallel_chud(N,i)
    end
    f = sqrt(BigFloat(BigInt(640320)^3))
    p = f/(12*invpi)
    return p
end
