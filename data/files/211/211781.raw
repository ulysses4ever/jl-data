#%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#%% %%% Script to solve the utility of a stream with time-varying mean
#%% %%% and volatility
#%% %%% reflective boundary on top and bottom
#%% %%%
#%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

let



tic()



#%%% Parameters
#% dynamics
sig0 = 0.0079;
nuD = sig0;     #%consumption volatility X
mub = 0.0013;    #%mean growth rate X
kapmu = 0.0212;   #%growth rate mean reversion X
numu = 0.044*sig0;#%0.005;  %grow rate volatility
kapsig = 0.0131;     #%volatility mean reversion X
nusig = 0.0003/sig0;    #  %volatility volatility



#%preferences
bet = 0.0013;  #   %rate of discount
RRA = 10;       # %relative risk aversion
gam = 1 - RRA;   #
#%IES = 1/RRA;   # %intertemporal elasticity of substitution
IES = 1.5;#
rho = 1 - 1/IES;#

#% =====================================================


#%stationary distribution
nstd = 3;  #     %number of standard deviation

smustd = numu/sqrt(2 * kapmu);# %standard deviation
mu_min = mub - nstd * smustd;
mu_max = mub + nstd * smustd;

ssigstd = nusig/sqrt(2 * kapsig); #  %standard deviation
sig_min = max(0, 1 - nstd * ssigstd);
sig_max = 1 + nstd * ssigstd;




#% =====================================================


#%%% Initialize variables
Nx = 50;# % Choose the number of depth steps
dx = (mu_max - mu_min) / Nx; #% normalize so that depth is 100m
Ny = 50;
dy = (sig_max - sig_min) / Ny;
Nt = iround(500 / 12);# % Choose the number of time steps per year
years = 100 * 12;# % number of years
dt = 1 / Nt;# %Length of each time step in seconds



#% solution matrix

V = zeros(Nx + 1, Ny + 1, Nt * years + 1); #%create price matrix




#%state vectors

time = linspace(0,years,Nt*years+1); time=time';
Xdepth = linspace(mu_min, mu_max , Nx + 1); Xdepth=Xdepth';
Ydepth = linspace(sig_min, sig_max , Ny + 1);Ydepth=Ydepth';



#%matrix version



Xmat = Xdepth'*ones(1, Ny + 1);
Ymat = ones(Nx + 1,1) * Ydepth;



#% =====================================================

#%initial condition
V[:,:,1] = exp(6.65)*ones(Nx + 1, Ny + 1, 1); #   %end of times
#%G(:,:,1) = (bet/gam) ./ (bet - gam * Xmat ...
#%                    - 1/2 * gam * (gam-1) * nuD^2 * Ymat);# %constant state variable


#%Constant parts of the PDE terms
thet = 1;# %for now constant theta
#% thet = Ymat - .6;

#%constant term
flow_0 = ones(Nx +1, Ny +1);
#%linear term
flow_1 = -bet + rho * Xmat- 1/2 * rho * (1 - gam) * nuD^2 * (1 - (thet - 1).^2) .* Ymat;

#%diffusion and drift terms

diff_1X = Ymat * (1/2 * numu^2);
diff_1Y = Ymat * (1/2 * nusig^2);
conv_1X = -kapmu*(Xmat-mub);
conv_1Y =  -kapsig*(Ymat-1);

#%square terems
K = 1/2 * (gam / rho -1) + 1/2 * rho * (1 - gam) * (thet-1).^2;
diff_Xsq = numu^2 * K .* Ymat;
diff_Ysq = nusig^2 * K .* Ymat;

#%solve starting from this



T_temp=Nt*years+1

for i= 2 : T_temp



    F = V[:,:,i-1];
    (m, n)=size(F);

 #    % V_X = diffX(V(:,:,i-1),dx);

    V_X = [zeros(1,n); (F[3:end,:]-F[1:end-2,:])/(2*dx); zeros(1,n)];

  #  % V_Y = diffY(V(:,:,i-1),dy);
    V_Y = [zeros(m,1) (F[:,3:end]-F[:,1:end-2])/(2*dy) zeros(m,1)];

   # % V_XX = diffXX(V(:,:,i-1),dx);
    V_XX = [zeros(1,n); (F[3:end,:]+F[1:end-2,:]-2*F[2:end-1,:])/(dx)^2; zeros(1,n)];

    #% V_YY = diffYY(V(:,:,i-1);
    V_YY = [zeros(m,1) (F[:,3:end]+F[:,1:end-2]-2*F[:,2:end-1])/(dy)^2  zeros(m,1)];

    #% dynamics of state variable
    depth_2D = diff_1X .* V_XX  + diff_1Y .* V_YY;# %diffusion
    conv_1D = conv_1X .* V_X+ conv_1Y .* V_Y;#  %convection
#    % flow term

    flow = flow_0 + flow_1 .* V[:,:,i-1];
 #   % square terms

    sqterms =  (diff_Xsq .* V_X.^2     + diff_Ysq .* V_Y.^2) ./ V[:,:,i-1];
    time_1D =  depth_2D[2:end-1,2:end-1,:] + conv_1D[2:end-1,2:end-1,:] + flow[2:end-1,2:end-1,:] + sqterms[2:end-1,2:end-1,:] ;

    V[2:end-1,2:end-1,i] = time_1D*dt + V[2:end-1,2:end-1,i-1];

    V[[1, end],:,i]=V[[2, end-1],:,i];
    V[:,[1, end],i]=V[:,[2, end-1],i];


end
# =====================================================


#%
t=toc()
end
