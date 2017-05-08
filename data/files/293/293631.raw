include("ImageCreatorlxlylz.jl")
include("dipole.jl")

const c = 299792458.
const mu0 = 4*pi*1e-7
const eps0 = 1/(mu0*c^2)

#cavity
L=0.5
l=0.45
h=0.45
lossesx= 0.95
lossesy= 0.95
lossesz= 0.95
order=20
nf=2000
const freq=linspace(1e6,2e9,nf)

##dipole
#dipole position
X=0.05
Y=l/3
Z=h/2
tilt=pi/2-acos(sqrt(2/3));
azimut=pi/4
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

dx=0.05
dy=0.05
dz=0.05

n=30
#observation points
#x1=[dx, L/2 , L-dx, dx, L/2 , L-dx, dx, L/2 , L-dx]
#y1=dy*ones(9)
#z1=[dz, dz, dz, h/2 , h/2, h/2, h-dz, h-dz, h-dz]

#x=vcat(x1,x1,x1)
#y=vcat(y1,ones(9)*l/2,l-y1)
#z=vcat(z1,z1,z1)
x=rand(n)*(L-0.15)+0.15
y=rand(n)*(l-0.1)+0.05
z=rand(n)*(h-0.1)+0.05

n_m=length(x)
#using PyPlot
using NPZ
println("Computing the radiation...")
E=zeros(Complex128,n_m,nf,3)
#B=zeros(Complex128,n_m,nf,3)
for j=1:n_m
  println("$j/$n_m")
  for i=1:nf
    perc=round(i/nf*10000)/100
    println("$perc %")
    r=[x[j],y[j],z[j]]
    Et=zeros(Complex128,3)
    Bt=zeros(Complex128,3)
    for m=1:numberofimages
      p=vec(POS[m,1:3])
      R=vec(POS[m,4:6])
      ord=POS[m,7]
      Ed,Bd=Hertz_dipole (r, p, R, phase, freq[i])
      Et+=Ed
      #Bt+=Bd
    end
    E[j,i,:]=Et
    #B[j,i,:]=Bt
  end
  #figure()
  #title("Position $j")
  #semilogy(freq,abs(E[j,:,1]'),label="E_x")
  #semilogy(freq,abs(E[j,:,2]'),label="E_y")
  #semilogy(freq,abs(E[j,:,3]'),label="E_z")
  #grid()
  #legend()
  #savefig("rEpos$j.pdf")
  #close()
  #figure()
  #title("Position $j")
  #semilogy(freq,abs(B[j,:,1]')/mu0,label="H_x")
  #semilogy(freq,abs(B[j,:,2]')/mu0,label="H_y")
  #semilogy(freq,abs(B[j,:,3]')/mu0,label="H_z")
  #grid()
  #legend()
  #savefig("rHpos$j.pdf")
  #close()
  npzwrite("E_$j.npy",squeeze(abs(E[j,:,:]),1))
end


npzwrite("Em_r30.npy",abs(E))
npzwrite("data30r.npz", ["E" => abs(E), "freq" => freq, "x" => x, "y" => y, "z" => z])
