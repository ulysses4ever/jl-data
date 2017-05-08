@everywhere function dudu_chud(splitting,index)

    # set_bigfloat_precision(int(N*log2(10))+1)
    # i_bigint_precision(1000)
    k = BigInt(13591409)
    invpi = BigFloat(0)
    # now = time()
    # M = N/14 + 1
    istart = int(index*splitting)
    iend = int((index+1)*splitting-1)
    println("starts "*string(istart)*" to "*string(iend))
    
    prev_d = factorial(BigInt(istart))
    prev_c = factorial(BigInt(3*istart))
    prev_a = factorial(BigInt(6*istart))
    
    
    a = prev_a
    c = prev_c
    d = prev_d
    
    
    for i = istart:iend
        
        d_cubed = (d)^3
        
        e = BigInt(640320)^(3*i)
        b = k + BigInt(545140134)*i
        invpi += (((-1)^i)*a*b)/(c*d_cubed*e)
        
        a = (prev_a) * (BigInt(6*(i-1) + 1))* (BigInt(6*(i-1) + 2))* (BigInt(6*(i-1) + 3))* (BigInt(6*(i-1) + 4))* (BigInt(6*(i-1) + 5))* (BigInt(6*(i-1) + 6))
        c = (prev_c)* (BigInt(3*(i-1) + 1))* (BigInt(3*(i-1) + 2))* (BigInt(3*(i-1) + 3))
        d = (prev_d)*BigInt(i)

        prev_a = a
        prev_c = c
        prev_d = d
    end
    return invpi
    # f = sqrt(BigFloat(BigInt(640320)^3))
    # p = f/(12*invpi)
    # return p
end
