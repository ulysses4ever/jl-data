

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
    #key1 = string(word, " -> ",pr)
    #key2 = string(pr, " -> ", word)
    #pvalues[key1] = pv1
    #pvalues[key2] = pv2
    return (pv1, pv2)
end
