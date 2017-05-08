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

test_greater_population(meth_a, unmeth_a, meth_b, unmeth_b; ci=false )

Uses the right sided Fisher's Test using HypthesisTests' FisherExactTest

       | Cond A | Cond B
---------------------------
  meth |   a     |  b
unmeth |   c     |  d

Test whether a/c == b/d using FisherExactTest(a,b,c,d) - so we have
 FisherExactTest(A_meth,B_meth,A_unmeth,B_unmeth)

Use the one sided test since our alternative is that A is greater than B.

=#
function test_greater_population_fisher(meth_a, unmeth_a, meth_b, unmeth_b; ci=false )
    FE=nothing
    try
        FE=FisherExactTest(meth_a, meth_b, unmeth_a, unmeth_b)
    catch e
         error("Caught error: $e. counts: $meth_a, $unmeth_a, $meth_b, $unmeth_b")
    end
    return pvalue(FE, tail=:right)
end

#=
 The same as above, except, when the FisherTest is instantiated, it calculates a value
 that we don't want it too in the interest of speed. We only want the p value for the
 one sided test, so steal this from the HypothesisTests package
=#

function test_greater_population(meth_a, unmeth_a, meth_b, unmeth_b)
     a = meth_a
     b = meth_b
     c = unmeth_a
     d = unmeth_b
     p = pvalue(Hypergeometric(a + b, c + d, a + c), a, tail=:right)
     p = max(min(p, 1.0), 0.0)
     return p
end
