module PM


    export PM4

    type PM4
        t::Tuple
        function PM4(n)
               t = ( n%2, n%3, n%5, n%7)
        end
        function PM4(t1,t2,t3,t4)
               t = ( t1%2, t2%3, t3%5, t4%7)
        end
    end


    (+)(k::PM4,m::PM4) = PM4(k[1]+m[1],k[2]+m[2],k[3]+m[3],k[4]+m[4])

    pmValue(t1,t2,t3,t4) = (105t1 + 70t2 + 126t3 + 120t4 ) % 210


    function partner(k,m)
        for i in [1:m]
            if(2i-k)%m == 0
                return i%m 
            end
        end
    end
    
    function pm(p, n)
        l = Int64[]
        for k in primes(p)
            push!(l, n%k)
        end
        tuple(l...)
    end 

end
