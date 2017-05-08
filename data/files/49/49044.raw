using ODE
using Datetime

include("FtleMod.jl")

## User data
nu_min = 0
nu_max = pi/2

n_nu = 50

v_min = 1
v_max = 5

n_v = 10

RelTol = 1e-6
AbsTol = 1e-6

## Initialization
nu_0 = linspace(nu_min,nu_max,n_nu)
v_0 = linspace(v_min,v_max,n_v)

(x_0,y_0) = nu2xy(nu_0,R)

ftle = zeros(n_v,n_nu) #WARN ho cambiato l'ordine delle dimensioni così viene diritta l'immagine (colpa di imagesc)
dphi = zeros(4,4)

## run integration
i = 1
tic()
#TODO parallelize @parallel or @pmap
for nu in nu_0
  j=1
  for v in v_0
    @printf("\r %3.1f%% -- integrating (%2i,%2i)  nu=%4.3f v=%4.3f",((i-1)*n_v+(j-1))/(n_nu*n_v)*100,i,j,nu,v)
    (x,y) = nu2xy(nu,R)
    vx = -v*sin(nu)
    vy = v*cos(nu)
#   println("$x $y, $vx $vy")
    X_1=[x+dx, y, vx, vy]
#   println(X_1)
#   println(typeof(X_1))
    X_2=[x-dx, y, vx, vy]
    X_3=[x, y+dy, vx, vy]
    X_4=[x, y-dy, vx, vy]
    X_5=[x, y, vx+dvx, vy]
    X_6=[x, y, vx-dvx, vy]
    X_7=[x, y, vx, vy+dvy]
    X_8=[x, y, vx, vy-dvy]

    (t,Y_1)=ode45(f_ell,[0.0:T],X_1)
    (t,Y_2)=ode45(f_ell,[0.0:T],X_2)
    (t,Y_3)=ode45(f_ell,[0.0:T],X_3)
    (t,Y_4)=ode45(f_ell,[0.0:T],X_4)
    (t,Y_5)=ode45(f_ell,[0.0:T],X_5)
    (t,Y_6)=ode45(f_ell,[0.0:T],X_6)
    (t,Y_7)=ode45(f_ell,[0.0:T],X_7)
    (t,Y_8)=ode45(f_ell,[0.0:T],X_8)
    print(" -- n° steps: $(length(t))")
#   [~,Y_2]=ode45(f_ell,[0,T],X_2,options,mu, ecc)
#   [~,Y_3]=ode45(f_ell,[0,T],X_3,options,mu, ecc)
#   [~,Y_4]=ode45(f_ell,[0,T],X_4,options,mu, ecc)
#   [~,Y_5]=ode45(f_ell,[0,T],X_5,options,mu, ecc)
#   [~,Y_6]=ode45(f_ell,[0,T],X_6,options,mu, ecc)
#   [~,Y_7]=ode45(f_ell,[0,T],X_7,options,mu, ecc)
#   [~,Y_8]=ode45(f_ell,[0,T],X_8,options,mu, ecc)

    dphi[1,1]=(Y_1[end,1]-Y_2[end,1])/(2*dx)
    dphi[1,2]=(Y_3[end,1]-Y_4[end,1])/(2*dy)
    dphi[1,3]=(Y_5[end,1]-Y_6[end,1])/(2*dvx)
    dphi[1,4]=(Y_7[end,1]-Y_8[end,1])/(2*dvy)
    dphi[2,1]=(Y_1[end,2]-Y_2[end,2])/(2*dx)
    dphi[2,2]=(Y_3[end,2]-Y_4[end,2])/(2*dy)
    dphi[2,3]=(Y_5[end,2]-Y_6[end,2])/(2*dvx)
    dphi[2,4]=(Y_7[end,2]-Y_8[end,2])/(2*dvy)
    dphi[3,1]=(Y_1[end,3]-Y_2[end,3])/(2*dx)
    dphi[3,2]=(Y_3[end,3]-Y_4[end,3])/(2*dy)
    dphi[3,3]=(Y_5[end,3]-Y_6[end,3])/(2*dvx)
    dphi[3,4]=(Y_7[end,3]-Y_8[end,3])/(2*dvy)
    dphi[4,1]=(Y_1[end,4]-Y_2[end,4])/(2*dx)
    dphi[4,2]=(Y_3[end,4]-Y_4[end,4])/(2*dy)
    dphi[4,3]=(Y_5[end,4]-Y_6[end,4])/(2*dvx)
    dphi[4,4]=(Y_7[end,4]-Y_8[end,4])/(2*dvy)
#   print(dphi)
    ftle[j,i]=(1/abs(T))*log(norm(dphi))
#   println(ftle)
    j=j+1;
  end
  i=i+1;
end
elapsed_time=toq()
@printf("\nelapsed time = %.2f s\n",elapsed_time)
println(ftle)

# Save
using MAT
file = matopen("ftle.mat", "w")
write(file, "ftle", ftle)
write(file,"nu_0",nu_0)
write(file,"v_0",v_0)
close(file)

# Try to plot in MATLAB
using MATLAB
println("Opening a MATLAB session... It may require some time.")
restart_default_msession()   # Open a default MATLAB session

@matlab load(ftle)              # put x to MATLAB's workspace
@matlab pcolor(nu_0,v_0,ftle);shading flat  # evaluate a MATLAB function

close_default_msession()    # close the default session (optional)
