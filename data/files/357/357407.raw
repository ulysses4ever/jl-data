function LLL_runtime(N)  
    runtimes = zeros(N);
    for i = 1:N
        r = 0; A = []
        for trial = 1:10
            while r != i + 2
                A = rand(-100:100, i+2, i+2)
                r = rank(A)
            end
            tic()
            res = LLL_reduce(A);
            runtimes[i] = runtimes[i] + toc()*0.1
        end
    end
    return runtimes
end