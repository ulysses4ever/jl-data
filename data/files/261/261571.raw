function f(x::Float64)
        return exp(-0.5*x.^2)/sqrt(2*pi);
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

integral(-100.,100.,5000000);
Profile.clear();
@profile integral(-100.,100.,5000000);
@time integral(-100.,100.,5000000);
Profile.print();
