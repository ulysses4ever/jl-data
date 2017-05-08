include("ImageCreator.jl")
include("dipole.jl")

const c = 299792458.
const mu0 = 4*pi*1e-7
const eps0 = 1/(mu0*c^2)

const freq=[100e6,500e6,1e9,2e9]
const nf=length(freq)

#cavity
const L=5
const l=4
const h=3
const losses=0.95*ones(nf)  #losses can be frequency dependent...
#crit=0.01 #convergence criterion
#order=int(log(crit)/log(maximum(losses)))
const order=10

##dipole
#dipole position
const X=1
const Y=1
const Z=1
const tilt=pi/2-acos(sqrt(2/3));
const azimut=pi/4
const phase=0
#dipole moment
#total time averaged radiated power P= 1 W dipole moment => |p|=sqrt(12πcP/µOω⁴)
const Pow=1
const amplitude=sqrt(12*pi*c*Pow./(mu0*(2*pi*freq).^4))

#Images
POS=IC(L,l,h,X,Y,Z,tilt,azimut,phase,1,order)

const numberofimages=length(POS[:,1])

#observation points
const  dx=0.05
const  dy=0.05
const  dz=0.05
const  xmin=0
const  xmax=L+dx
const  ymin=0
const  ymax=l+dy
const  x=[xmin:dx:xmax]
const  y=[ymin:dy:ymax]
const  z=2

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
        p=vec(POS[m,1:3])*amplitude[k]*losses[k]^POS[m,7]
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
  savefig("E_$k.png",bbox="tight")
  clf()
end

#Back up
using NPZ
npzwrite("Ecarto.npz", ["Et" => Et, "freq" => freq, "x" => x, "y" => y, "z" => z,])



