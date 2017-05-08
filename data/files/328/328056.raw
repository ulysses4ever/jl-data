# Helper functions to generate some common knot sequences

module Knotseqs
linear = (a,b,N) -> linspace(a,b,N+1)
function arcsin(a,b,N)
    N2 = N/2
    asin(linear(-N2,N2,N)/N2)*(b-a)/π + (a+b)/2
end
arcsinHalf = (a,b,N) -> asin(linear(0,N,N)/N)*(b-a)*2.0/π + a
function exponential(a,b,N, ap=1e-1)
    logspace(log10(a == 0 ? ap : a), log10(b), N+1)
end
end
