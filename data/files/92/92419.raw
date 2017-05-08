module TruncatedNormal

include("table.jl")

function rtnorm(n::Int64, μ::Real, σ::Real, a::Real, b::Real)
    a = (a-μ)/σ 
    b = (b-μ)/σ
    r = rtnomr(a, b)
    r = r*σ + μ
    Z = sqrt(pi/2)*σ*(erf(b/sqrt(2))-erf(a/sqrt(2)))
    Z = max(Z,1e-15)      
    p = exp(-(r-μ).^2/2/σ^2) / Z
    return draw, p
end

function rtnorm(a::Real, b::Real)
    
    const xmin = -2.00443204036
    const xmax = 3.48672170399
    stop = false
    
    if a>=b    
        throw("B must be greater than A.")
    elseif abs(a)>abs(b)
        r = -rtnorm(-b, -a)
    elseif a > xmax
        stop = 0
        twoasq = 2*a^2
        expab = exp(-a*(b-a)) - 1
        while ~stop
            z = log(1 + rand()*expab)
            e = -log(rand())
            stop = (twoasq*e > z^2)
        end
        r = a - z/a        
    elseif a<xmin
        stop = 0
        while ~stop
            r = randn()
            stop = (r>=a) && (r<=b)
        end
    else
        const kmin = 5          
        const INVH = 1631.73284006;  
        const I0 = 3271;                      
        const ALPHA = 1.837877066409345;      
        const N = 4001;                       
        const yl0 = 0.053513975472;           
        const ylN = 0.000914116389555;        

        i = I0 + floor(a*INVH)
        ka = ncell[i+1]
        if b >= xmax
            kb = N
        else
            i = I0 + floor(b*INVH)
            kb = ncell[i+1]
        end

        if abs(kb-ka) < kmin            
            stop = false 
            twoasq = 2*a^2
            expab = exp(-a*(b-a)) - 1
            while ~stop
                z = log( 1 + rand()*expab )
                e = -log(rand())
                stop = (twoasq*e > z^2)
            end
            r = a - z/a
            return r
        end

        while 1>0
            ## Sample integer between ka and kb
            k = rand(ka:kb) + 1           
            if k == N+1            
            ## Right tail            
                lbound = x[end]
                z = -log(rand())
                e = -log(rand())
                z = z / lbound
                if (z^2 <= 2*e) && (z < b-lbound)
                    ## Accept this proposition, otherwise reject
                    r = lbound + z
                    return r
                end
            elseif (k<=ka+2) || (k>=kb && b<xmax)
                ## Two leftmost and rightmost regions            
                sim = x[k] + (x[k+1]-x[k]) * rand()
                if (sim >= a) && (sim <= b)
                    # Accept this proposition, otherwise reject
                    simy = yu[k]*rand()               
                    # Compute y_l from y_k
                    if k == 1
                        ylk = yl0
                    elseif k == N
                        ylk = ylN
                    elseif k <= 1954
                        ylk = yu(k-1)
                    else
                        ylk = yu(k+1)
                    end;
                    
                    if (simy<ylk) || (sim^2 + 2*log(simy) + ALPHA < 0)
                        r = sim
                        return r
                    end
                end
            else
                
                ## All the other boxes            
                u = rand()
                simy = yu[k] * u
                d = x[k+1] - x[k]
                
                ## Compute y_l from y_k
                if k == 1
                    ylk = yl0
                elseif k == N
                    ylk = ylN
                elseif k <= 1954
                    ylk = yu(k-1)
                else
                    ylk = yu(k+1)
                end
                
                if simy < ylk
                    r = x[k] + u*d*yu[k]/ylk
                    return r
                end
                sim = x(k) + d * rand()
                # Otherwise, check you're below the pdf curve

                if sim^2 + 2*log(simy) + ALPHA < 0
                    r = sim
                    return r
                end
            end  # end if
        end    # end while    
    end

end

end

