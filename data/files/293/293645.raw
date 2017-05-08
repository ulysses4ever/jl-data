include("ImageCreatorlxlylz.jl")
include("dipole.jl")

const c = 299792458.
const mu0 = 4*pi*1e-7
const eps0 = 1/(mu0*c^2)

#cavity
L=0.5
l=0.45
h=0.45
lossesx= 0.8
lossesy= 0.998
lossesz= 0.998
order=30
nf=400
const freq=linspace(5e6,2e9,nf)

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
amplitude=sqrt(12*pi*c*Pow/(mu0*(2*pi*freq[end])^4))


#Images
POS=IC(L,l,h,X,Y,Z,tilt,azimut,phase,amplitude,order,lossesx,lossesy,lossesz)

#using HDF5,JLD
#@load "POS100.jld" POS

numberofimages=length(POS[:,1])#1+2*order+(2*order*(order+1)*(2*order+1))/3
#POS=POS[1:numberofimages,:]


#observation points
x=L/2
y=l/2
z=h/2

println("Computing the radiation...")
Z=zeros(nf)
E=zeros(Complex128,nf,3)
B=zeros(Complex128,nf,3)
for i=1:nf
  perc=round(i/nf*1000)/10
  println("$perc %")
  r=[x,y,z]
  Et=zeros(Complex128,3)
  Bt=zeros(Complex128,3)
  for m=1:numberofimages
    p=vec(POS[m,1:3])
    R=vec(POS[m,4:6])
    ord=POS[m,7]
    Ed,Bd=Hertz_dipole (r, p, R, phase, freq[i])
    Et+=Ed
    Bt+=Bd
  end
  Z[i]=sqrt(sum(abs(E).^2))/sqrt(sum(abs(B).^2))*mu0 #real(E).^2#0.5*numpy.cross(E.T,conjugate(B.T))
  E[i,:]=Et
  B[i,:]=Bt
end

using PyPlot

semilogy(freq,abs(E))
grid()
