include("ImageCreator.jl")


const c = 299792458.
const mu0 = 4*pi*1e-7
const eps0 = 1/(mu0*c^2)
const epsr=1.

#cavity
const L=8.7
const l=3.7
const h=2.9
const losses= 0.998

#simulation parameters
const Lt=1e-6
const freq=.5e9

const dmax=Lt*c
const order=int(round(dmax/minimum([L;l;h]))+1)
const w=2*pi*freq  # omega
const k=w/c     # wave number
const N=int(Lt*freq)
const t=linspace(Lt/N,Lt,N)


using HDF5,JLD

##dipole
#dipole position
const x0=1
const y0=2
const z0=1
const tilt=pi/2-acos(sqrt(2/3));
const azimut=pi/4
const phi=pi/2
#dipole moment
#total time averaged radiated power P= 1 W dipole moment => |p|=sqrt(12πcP/µOω⁴)
const Pow=1
const amplitude=sqrt(12*pi*c*Pow/(mu0*(2*pi*freq)^4))


#Images
println("Computing images...")
POS=IC(L,l,h,x0,y0,z0,tilt,azimut,phi,amplitude,order)
const dist=sqrt(POS[:,4].^2+POS[:,5].^2+POS[:,6].^2)
const perm=sortperm(dist)
const U=find(dist[perm].>dmax)
POS=POS[perm[1:U[1]-1],:]
#@save "POS.jld" POS
#@load "POS.jld" POS

const numberofimages=length(POS[:,1])

tic()

#observation points
M=150
x=rand(M)*(L-c/freq)+2c/freq
y=rand(M)*(l-c/freq)+2c/freq
z=rand(M)*(h-c/freq)+2c/freq



println("Computing the fields...")
E=zeros(Complex128,M,N,3)
B=zeros(Complex128,M,N,3)
Z=zeros(M,N)
for i=1:M
  r=[x[i],y[i],z[i]] #position of the receiver
  Et=zeros(Complex128,3,N)
  Bt=zeros(Complex128,3,N)
  for m=1:numberofimages
    ord=POS[m,7]#order of the dipole
    p=vec(POS[m,1:3])*losses^ord #image dipole moment
    R=vec(POS[m,4:6]) #image dipole position
    rprime=r-R  # r'=r-R
    magrprime=sqrt(sum(rprime.^2)) # |r-R|
    krp=k*magrprime  # k*|r-R|
    rprime_cross_p = cross(rprime, p) # (r-R) x p
    rp_c_p_c_rp = cross(rprime_cross_p, rprime) # ((r-R) x p) x (r-R)
    ta=int(magrprime/c/Lt*N)
    if ta == 0
      ta=1
    end
    expfac=exp(1im*(-w*t+krp-phi))
    Ep=1/(4*pi*eps0*epsr)*(w^2/(c^2*magrprime^3)*rp_c_p_c_rp+(1/magrprime^3-w*im/(c*magrprime^2))*(3*rprime*dot(rprime,p)/magrprime^2-p))
    Bp=1/(4*pi*eps0*epsr)*1/(magrprime*c^3)*(w^2*rprime_cross_p)/magrprime*(1-c/(im*w*magrprime))
    u=1
    for n=ta:N
      Et[:,n]+=expfac[u]*Ep
      Bt[:,n]+=expfac[u]*Bp
      u+=1
    end
  end
  E[i,:,:]=Et' # E-field
  B[i,:,:]=Bt' # B-field
  Z[i,:]=sqrt(sum(real(Et).^2,1))./sqrt(sum(real(Bt).^2,1))*mu0 #real(E).^2#0.5*numpy.cross(E.T,conjugate(B.T)) #impedance
  perc=round(i/M*1000)/10
  println("$perc %")
end

Er=real(E)
Ei=imag(E)
Br=real(B)
Bi=imag(B)

save("Stats150.jld", "Er", Er, "Ei",Ei, "Br", Br, "Bi", Bi,"Z",Z,"t",t,"N",N)
