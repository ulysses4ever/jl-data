export jacobi, djacobi, jacobi_zeros




function jacobi(x, n, a=0, b=0)

    if n==0
        return one(x)
    elseif n==1
        return 1/2 * (a - b + (a + b + 2)*x)
    end
    
    local p0 = one(1)
    local p1 = 1/2 * (a - b + (a + b + 2)*x)
    local p2 = 0;
    
    for i = 1:(n-1)
	local a1 = 2*(i+1)*(i+a+b+1)*(2*i+a+b);
	local a2 = (2*i+a+b+1)*(a*a-b*b);
	local a3 = (2*i+a+b)*(2*i+a+b+1)*(2*i+a+b+2);
	local a4 = 2*(i+a)*(i+b)*(2*i+a+b+2);
	p2 = 1/a1*( (a2 + a3*x)*p1 - a4*p0);

        p0 = p1
        p1 = p2
    end

    return p2
end




function djacobi(x, n, a=0, b=0)
    1/2 * (a + b + n + 1) * jacobi(x, n-1, a+1, b+1)
end

function jacobi_zeros(m, alpha=0, beta=0; T=Float64)

    local a::T = convert(T, alpha)
    local b::T = convert(T, beta)
    
    local r::T, delta::T, s::T, poly::T
    const MAXITER = 500
    const EPS::T = 100 * eps(one(a))
    local i, k, iter=0

    x = zeros(T, m)
    pp = convert(T, pi)
    for k = 1:m
        # Initial guess.
        r = -cos( (2k-1)/(2*m) * pp)
        if (k > 1)
            r = (r + x[k-1]) / 2
        end
        iter = 0
        while(true)
            s = 0
            for i = 1:(k-1)
                    s += 1/(r - x[i])
            end
            
            poly = jacobi(r, m, a, b)
            delta = -poly / (djacobi(r, m, a, b) - poly*s)

            r += delta
            iter += 1
            
            if iter > MAXITER
                throw("Program did not converge")
            end

            if abs(delta) < EPS
                break
            end
        end
        x[k] = r
    end
        
    return x
        
end


