
@everywhere function parallel_chud(N,z)
    np = nprocs()
    set_bigfloat_precision(int(N*log2(10))+1)
    k = BigInt(13591409)
    invpi = BigFloat(0)
    M = N/14 + 1
    for i = 0:M
        if(mod(i,np)!=z)
            continue # only add i mod nprocs = z terms for parallelization
        end
        a = factorial(BigInt(6*i))
        b = k + BigInt(545140134)*i
        c = factorial(BigInt(3*i))
        d = (factorial(BigInt(i)))^3
        e = BigInt(640320)^(3*i)
        invpi += (((-1)^i)*a*b)/(c*d*e)
    end
    return invpi
    # elapsed = time() - now
    # println(p)
    # println("Elapsed: "*string(elapsed)) 
end
