function integral(a::Float64,b::Float64,N::Int64)
        @assert typeof(a) == Float64
        @assert typeof(b) == Float64
        @assert typeof(N) == Int64
        x = Array(Float64,N);
        dx = (b-a)/(N+1);
        for i = 1:N
                x[i] = a + dx*i
        end
        #result = mapreduce(x->dx*exp(-0.5*x.^2)/sqrt(2*pi),+,x)
        result = mapreduce(x->dx*exp(x)*sin(x),+,x)
        return result;
end

{for i = 1:1000;integral(-100.,100.,10000);end}
Profile.clear();
@profile {for i = 1:1000;integral(-100.,100.,10000);end}
@time {for i = 1:1000;integral(-100.,100.,10000);end}
Profile.print();
