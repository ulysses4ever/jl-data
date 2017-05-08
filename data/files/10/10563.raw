using GSL
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

function test_greater_population( meth_a, unmeth_a, meth_b, unmeth_b)
   p = 0;
   k_begin = (meth_b > unmeth_a) ? meth_b - unmeth_a : 0
   for k=k_begin:(meth_b-1)
        p = log_sum_log(p, log_hyper_g_greater(meth_a, unmeth_a, meth_b, unmeth_b, k))
   end
   return exp(p)
end
