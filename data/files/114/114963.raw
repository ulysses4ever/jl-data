

function fisher(a,b,c,d)

# This is a fast implementation of the two tail Fisher exact test
# calculate the natural log p-value of hypergeometric distribution
# Jia Meng, jmeng@mit.edu
# Original matlab code by:
# Meng, J., S. J. Gao, et al. (2009). "Enrichment constrained
# time-dependent clustering analysis for finding meaningful temporal
# transcription modules." Bioinformatics 25(12): 1521-1527.

    t = a
    C = a+b
    T = a+c
    G = a+b+c+d

    logftable=log(0:G)
    logftable[1]=0
    logftable=cumsum(logftable)

    function log_f(x)
        return logftable[x+1]
    end

    if t*G*C*T==0
        logp=0
    else
        minCT = min(C,T)
        ar = Float64[]
        for ind in 1:minCT-t+1
            x = t+ind-1
            push!(ar, -log_f(x)-log_f(T-x)-log_f(C-x)-log_f(G+x-T-C))
        end
        amax = maximum(ar)
        ar = sort(ar)

        logp= log_f(T)+log_f(G-T)+log_f(C)+log_f(G-C)-log_f(G)+amax+log(sum(exp(ar-amax)))
    end
    return exp(logp)
end

function deltap(a,b,c,d)
    pv1 = (a/(a+b))-(c/(c+d))
    pv2 = (a/(a+c))-(c/(b+d))
    return (pv1, pv2)
end

function chisq(a::Int64,b::Int64,c::Int64,d::Int64)

   # _jl_libRmath = dlopen("libRmath")
   # pchisq(q::Number, df::Number, lower_tail::Bool, log_p::Bool) =
   #     ccall(dlsym(_jl_libRmath,:pchisq),Float64,(Float64,Float64,Int32,Int32), q, df, lower_tail, log_p)

    total = a+b+c+d
    e_a = (a+b)*(a+c)/total
    e_b = (b+a)*(b+d)/total
    e_c = (c+a)*(c+d)/total
    e_d = (d+c)*(d+b)/total
    chi = ((a-e_a)^2)/e_a + ((b-e_b)^2)/e_b + ((c-e_c)^2)/e_c + ((d-e_d)^2)/e_d

    return -chi#pchisq(chi, 1, false, false)
end

function logl(a::Int64, b::Int64, c::Int64,d::Int64 )
    total = a+b+c+d
    E1 = (a+c)*(a+b)/total
    E2 = (d+b)*(a+b)/total
    G2 = 2*((a*log(a/E1)) + (b*log(b/E2)))
    return G2
end
