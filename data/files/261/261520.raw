Pkg.add("Devectorize")

function integral(a::Float64,b::Float64,N::Int64)
        x = Array(Float64,N);
        dx = (b-a)/(N+1);
        for i = 1:N
                x[i] = a + dx*i
        end
        @devec f = dx.*exp(-0.5.*x.^2)/sqrt(2.*pi);
        return sum(f);
end

{for i = 1:1000;integral(-100.,100.,10000);end}
Profile.clear();
@profile {for i = 1:1000;integral(-100.,100.,10000);end}
@time {for i = 1:1000;integral(-100.,100.,10000);end}
Profile.print();
