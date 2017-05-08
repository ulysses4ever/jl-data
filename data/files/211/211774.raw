

tic()

t=10;

n=5;

#v = zeros(t,1)
#w = zeros(t,1)



for i = 1:t
    a = randn(n,n);
    b = randn(n,n);
    c = randn(n,n);
    d = randn(n,n);
    P = [a b c d];
    Q = [a b; c d];
    v[i,1]=trace((P.'*P)^4);
    w[i,1]=trace((Q.'*Q)^4);
end

require("test.jl")



toc()











