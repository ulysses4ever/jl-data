#include("ImageCreatorlxlylz.jl")
include("ImageCreator.jl")
include("dipole.jl")

const c = 299792458.
const mu0 = 4*pi*1e-7
const eps0 = 1/(mu0*c^2)

#cavity
L=8.7
l=3.7
h=2.9
losses=0.998
order=30

freq=[1e6:1e6:100e6]
nf=length(freq)

##dipole
#dipole position
X=1
Y=2
Z=1
tilt=pi/2-acos(sqrt(2/3));
azimut=pi/4
phase=0
#dipole moment
#total time averaged radiated power P= 1 W dipole moment => |p|=sqrt(12πcP/µOω⁴)
Pow=1
amplitude=sqrt(12*pi*c*Pow/(mu0*(2*pi*freq[end])^4))



#Images
POS=IC(L,l,h,X,Y,Z,tilt,azimut,phase,amplitude,order)
numberofimages=length(POS[:,1])

#observation points
x=4.5
y=3
z=1.5


println("Computing the radiation...")
Et=zeros(nf,3)
for k=1:nf
  println("$k/$nf")
  r=[x,y,z]
  E=zeros(Complex128,3)
  for m=1:numberofimages
    p=vec(POS[m,1:3])*losses^POS[m,7]
    R=vec(POS[m,4:6])
    ord=POS[m,7]
    Ed,Bd=Hertz_dipole_ff (r, p, R, phase, freq[k])
    E+=Ed
  end
  Et[k,:]=abs(E)
end

using PyPlot

figure(1)
title("\$E\$ (V/m)")
semilogy(freq,Et)
xlabel("\$f\$")
ylabel("V/m")
grid()
savefig("E.png",bbox="tight")

