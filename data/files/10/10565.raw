using GSL
using HypothesisTests

#=
  This test below is a port from MethPipe methdiff package.

  Which is a one directional Fishers test
    https://groups.google.com/forum/#!topic/methpipe/dBWjZTZjlV0

  In https://github.com/smithlabcode/methpipe/blob/master/src/radmeth/methdiff.cpp a pseudocount
  is added before calculating test_greater_population_s. Likely to avoid zero counts. If there
  are zero counts, this returns 1 - rather than error.

  Currently I don't get values of a similar magnitude between the julia (and R)  based Fisher exact test
=#

function log_sum_log(p, q)
   if p == 0
     return q
   elseif q == 0
     return p
   end
   larger = (p > q) ? p : q
   smaller = (p > q) ? q : p
   return larger + log(1.0 + exp(smaller - larger))
end

function log_hyper_g_greater(meth_a, unmeth_a, meth_b, unmeth_b, k)
   return  sf_lnchoose(meth_b + unmeth_b - 1, k) +
     sf_lnchoose(meth_a + unmeth_a - 1, meth_a + meth_b - 1 - k) -
     sf_lnchoose(meth_a + unmeth_a + meth_b + unmeth_b - 2, meth_a + meth_b - 1)
end

function test_greater_population_s( meth_a, unmeth_a, meth_b, unmeth_b)
   p = 0;
   k_begin = (meth_b > unmeth_a) ? meth_b - unmeth_a : 0
   for k=k_begin:(meth_b-1)
        p = log_sum_log(p, log_hyper_g_greater(meth_a, unmeth_a, meth_b, unmeth_b, k))
   end
   return exp(p)
end


#=
  Right sided Fisher's Test using HypthesisTests' FisherExactTest
=#
function test_greater_population(meth_a, unmeth_a, meth_b, unmeth_b; ci=false )
    FE=FisherExactTest(meth_a, unmeth_a, meth_b, unmeth_b)
    return pvalue(FE, tail=:right)
end
