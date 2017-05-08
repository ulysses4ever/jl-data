include("ImageCreatorlxlylz.jl")
include("dipole.jl")

const c = 299792458.
const mu0 = 4*pi*1e-7
const eps0 = 1/(mu0*c^2)

#cavity
L=0.5
l=0.45
h=0.45
lossesx= 0.5
lossesy= 0.998
lossesz= 0.998
order=20

const freq=1e9

##dipole
#dipole position
X=0.01
Y=l/2
Z=h/2
tilt=0#pi/2-acos(sqrt(2/3));
azimut=0#pi/4
phase=0
#dipole moment
#total time averaged radiated power P= 1 W dipole moment => |p|=sqrt(12πcP/µOω⁴)
Pow=1
amplitude=sqrt(12*pi*c*Pow/(mu0*(2*pi*freq)^4))


#Images
POS=IC(L,l,h,X,Y,Z,tilt,azimut,phase,amplitude,order,lossesx,lossesy,lossesz)

#using HDF5,JLD
#@load "POS100.jld" POS

numberofimages=length(POS[:,1])#1+2*order+(2*order*(order+1)*(2*order+1))/3
#POS=POS[1:numberofimages,:]


#observation points
dx=0.01
dy=0.01
dz=0.01
const  nx=int(L/dx)
const  xmax=L
const  ny=int(h/dy)
const  ymax=l
const  x=linspace(0,L,nx)
const  z=h/2
const  y=linspace(0,l,ny)


println("Computing the radiation...")
Z=zeros(nx,ny)
Ez=zeros(nx,ny)
Bz=zeros(nx,ny)
for i=1:nx
  perc=round(i/nx*1000)/10
  println("$perc %")
  for j=1:ny
    r=[x[i],y[j],z]
    E=zeros(Complex128,3)
    B=zeros(Complex128,3)
    for m=1:numberofimages
      p=vec(POS[m,1:3])
      R=vec(POS[m,4:6])
      ord=POS[m,7]
      Ed,Bd=Hertz_dipole (r, p, R, phase, freq)
      E+=Ed
      B+=Bd
    end
    Z[i,j]=sqrt(sum(abs(E).^2))/sqrt(sum(abs(B).^2))*mu0 #real(E).^2#0.5*numpy.cross(E.T,conjugate(B.T))
    Ez[i,j]=abs(E[3])
    Bz[i,j]=abs(B[3])
  end
end

using PyPlot
#pygui(false)

figure(1)
title("\$E_z\$ (V/m)")
pcolor(x,y,Ez',cmap="jet")
#clim(0,20)
colorbar()
axis("scaled")
xlim(0,L)
ylim(0,l)
xlabel("\$x\$/m")
ylabel("\$y\$/m")
savefig("E_$order.png",bbox="tight")
clf()


figure(2)
title("\$H_z\$ (A/m)")
pcolor(x,y,Bz'/mu0,cmap="jet")
#clim(0,.2)
colorbar()
axis("scaled")
xlim(0,L)
ylim(0,l)
xlabel("x/m")
ylabel("\$y\$/m")
savefig("H_$order.png",bbox="tight")
clf()


figure(3)
title("\$Z\$ (\$ \\Omega\$)")
pcolor(x,y,Z',cmap="jet")
clim(0,1000)
colorbar(ticks=[0,100,200,300,120*pi,500,60*pi^2,700,800,900,1000])

axis("scaled")
xlim(0,L)
ylim(0,l)
#xlabel("x/m")
ylabel("\$y\$/m")
savefig("Z_$order.png",bbox="tight")
clf()


