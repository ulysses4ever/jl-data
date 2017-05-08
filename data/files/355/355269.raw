require("padcirc.jl")
require("perlap.jl")

Nx = 128;
Ny = 128;
dx = 5.0;
dy = 5.0;
T = 10000;
dt = 0.1;
R = 1.0;
c = 10.0;
g_max = 0.05;
k_1 = 5.0;
D_p = 0.5;
alpha = 0.2;
k_2 = 5.0;
W_0 = 0.2;
r_w = 0.2; 
D_w = 0.5;
D_o = 10.0;
d = 0.25;

random = rand(Nx,Ny)

P = zeros(Nx,Ny)
for j = 1:Nx
    for i = 1:Ny
        if random[i,j] < 0.01
            P[i,j] = 500.0
        end
    end
end

W = R/r_w*ones(Nx,Ny)
O = R/(alpha*W_0)*ones(Nx,Ny)

Nt = T/dt;

for i = 2:Nt
    W = W + dt.*(alpha.*O.*((P+k_2*W_0)./(P+k_2))-g_max.*(W./(W+k_1)).*P-r_w.*W+D_w.*perlap(W,dx));
    O = O + dt.*(R-alpha.*O.*((P+k_2*W_0)./(P+k_2))+D_o*perlap(O,dx));
    P = P + dt.*(c.*g_max.*(W./(W+k_1)).*P-d.*P+D_p*perlap(P,dx));

end

writedlm("HilleRisLambers.dat", P, ' ')
                  
