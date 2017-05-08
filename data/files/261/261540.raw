function f(x::Array)
        return exp(-0.5*x.^2)/sqrt(2*pi);
        #return exp(x).*sin(x);
end

function integral(a::Float64,b::Float64,N::Int64)
        @assert typeof(a) == Float64
        @assert typeof(b) == Float64
        @assert typeof(N) == Int64
        x = Array(Float64,N);
        dx = (b-a)/(N+1);
        for i = 1:N
                x[i] = a + dx*i
        end
        result = sum(f(x))*dx
        return result;
end

{for i = 1:1000;integral(-100.,100.,10000);end}
Profile.clear();
@profile {for i = 1:1000;integral(-100.,100.,10000);end}
Profile.print();
println(integral(-100.,100.,10000),"\n");
@elapsed {for i = 1:1000;integral(-100.,100.,10000);end}
