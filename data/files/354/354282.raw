include("ImageCreatorlxlylz.jl")
#include("ImageCreator.jl")
include("dipole.jl")

const c = 299792458.
const mu0 = 4*pi*1e-7
const eps0 = 1/(mu0*c^2)

#cavity
L=0.5
l=0.45
h=0.45
lossesx= 0.8
lossesy= 0.99
lossesz= 0.99
order=20

const freq=[100e6,200e6,300e6,400e6,500e6,600e6,700e6,800e6,900e6,1e9,2e9,3e9,4e9,5e9]
#const freq=[1e9]
nf=length(freq)


##dipole
#dipole position
X=0.05
Y=l/3
Z=h/2
tilt=0#pi/2-acos(sqrt(2/3));
azimut=0#pi/4
phase=0
#dipole moment
#total time averaged radiated power P= 1 W dipole moment => |p|=sqrt(12πcP/µOω⁴)
Pow=1
amplitude=sqrt(12*pi*c*Pow/(mu0*(2*pi*freq[end])^4))



#Images
POS=IC(L,l,h,X,Y,Z,tilt,azimut,phase,amplitude,order,lossesx,lossesy,lossesz)
#POS=IC(L,l,h,X,Y,Z,tilt,azimut,phase,amplitude,order)
Lm=(order+2)*L
lm=(order+2)*l
hm=(order+2)*h

dmax=maximum([Lm,lm,hm])
dist=sqrt(POS[:,4].^2+POS[:,5].^2+POS[:,6].^2)
U=find(dist.<dmax)
POS=POS[U,:]

#using HDF5,JLD
#@load "POS100.jld" POS

numberofimages=length(POS[:,1])#1+2*order+(2*order*(order+1)*(2*order+1))/3
#POS=POS[1:numberofimages,:]


#observation points
dx=0.005
dy=0.005
dz=0.005
const  xmin=0
const  xmax=L+dx
const  ymin=0
const  ymax=l+dy
const  x=[xmin:dx:xmax]
const  y=[ymin:dy:ymax]
const  z=h/3

const nx=length(x)
const ny=length(y)

using PyPlot
println("Computing the radiation...")
Et=zeros(nf,nx,ny,3)
for k=1:nf
  println("$k/$nf")
  for i=1:nx
    perc=round(i/nx*1000)/10
    println("$perc %")
    for j=1:ny
      r=[x[i],y[j],z]
      E=zeros(Complex128,3)
      for m=1:numberofimages
        p=vec(POS[m,1:3])
        R=vec(POS[m,4:6])
        ord=POS[m,7]
        Ed,Bd=Hertz_dipole (r, p, R, phase, freq[k])
        E+=Ed
      end
      Et[k,i,j,:]=abs(E)
    end
  end
  freqtxt=round(freq[k]/1e4)/100
  figure(1)
  title("\$E_z\$ (V/m), $freqtxt MHz")
  pcolor(x,y,squeeze(Et[k,:,:,3],1)',cmap="jet")
  #clim(0,20)
  colorbar()
  axis("scaled")
  xlim(xmin,xmax)
  ylim(ymin,ymax)
  xlabel("\$x\$/m")
  ylabel("\$y\$/m")
  savefig("E_$k.png",bbox_inches="tight")
  clf()
end

using NPZ
npzwrite("Ecarto.npz", ["Et" => Et, "freq" => freq, "x" => x, "y" => y, "z" => z,])

