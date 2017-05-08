###############################################
# Finds small solutions to P(x0) = 0 (mod N), #
# as given by the Coppersmith condition       # 
###############################################
function CoppersmithSolve(P, N, ep = 0.03)
    
    # modularize polynomial
    P(x) = P(x)%N;
    d = degree(P);
    
    # set parameters
    m = ceil(1/d/ep)
    mu = ceil(0.5*N^(1/d-ep))
    
    # construct q{i,j}(x)
    q = Array(Function, d, m);
    for i = 1:d
        for j = 1:m
            v(x) = x^i*N^j*f(x)^(m-j)
            q[i, j] = v
        end
    end
            
    # construct lattice of coefficient vectors
    Lambda = Array(Int, d*m, d*m)
    k = 1
    for i = -m+1:1
        for j = 0:delta
            c = zeros(d*m)
            v(x) = q[j, -i](mu*x);
            c[1:length(coeffs(v))] = coeffs(v)
            Lambda[:, k] = flipud(c);
            k = k + 1
        end
    end
    
    # LLL basis reduction
    b_short = LLL_reduce(Lambda)[:, 1];
    
    # construct Q(x) from elements of shortened vector
    Q(x) = 0
    Q_coeffs = flipud(b_short);
    for i = 1:size
        Q(x) = Q + round(Q_coeffs[i]/mu^(i-1))*x^(i-1)
    end

    x0 = roots(Q)
    return x0
end