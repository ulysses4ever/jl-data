function agm(N)
    
    set_bigfloat_precision(4*N)
    # now = time()
    a = BigFloat("1.0")
    two = BigFloat("2.0")
    println("computing the square root of 2")
    @time sqtwo = sqrt(two)
    b = BigFloat("1.0")/sqtwo
    s = BigFloat("0.5")
    p = BigFloat("0.0")
    c = BigFloat("0.0")
    
    M = int(floor(log2(N))+1)
    
    for i=1:M
        println(string(i)*"/"*string(M))
        println("computing the arithmetic mean")
        @time a1 = (a+b)/2.0
        println("computing the geometric mean")
        @time b1 = sqrt(a*b)
        println("computing c")
        @time c  = ((a1^2.0)-(b1^2.0))
        println("computing s")
        @time s1 = (s-2.0^(i)*c)
        println("computing pi")
        @time p  =  2*a1^2/s1
        
        a=a1
        b=b1
        s=s1
    end
    # println(p)
    # p
    
    
    # println(p)
    return p
end
