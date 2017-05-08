module Xadrez end

xadrez(n, m) = n == 0 || m == 0 ? "" : mapreduce ( z-> mapreduce(y -> string((z + y -2) % 2), * , [1:n]) * "\n", * , [1:m])

export xadrez
