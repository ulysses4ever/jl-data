function f(x::Float64)
        #return exp(-0.5*x.^2)/sqrt(2*pi);
        return exp(x)*sin(x);

end

function erf(a::Float64)
        return erf(a/sqrt(2))
end

function integral(a::Float64,b::Float64,N::Int64)
        @assert typeof(a) == Float64
        @assert typeof(b) == Float64
        @assert typeof(N) == Int64
        dx = (b-a)/(N+1);
        sum = 0.5*dx*(f(a) + f(b));
        for i = 1:N
                sum += dx*f(a+dx*i);
        end
        return sum;
end

{for i = 1:1000;integral(-100.,100.,10000);end}
Profile.clear();
@profile {for i = 1:1000;integral(-100.,100.,10000);end}
@time {for i = 1:1000;integral(-100.,100.,10000);end}
Profile.print();
