function integral(a::Float64,b::Float64,N::Int64)
        @assert typeof(a) == Float64
        @assert typeof(b) == Float64
        @assert typeof(N) == Int64
        x = Array(Float64,N);
        dx = (b-a)/(N+1);
        for i = 1:N
                x[i] = a + dx*i
        end
        result = mapreduce(x->dx*exp(-0.5*x.^2)/sqrt(2*pi),+,x)
        return result;
end

integral(-100.,100.,5000000)
Profile.clear();
#@profile integral(-100.,100.,5000000);
@time integral(-100.,100.,5000000);
#Profile.print();
