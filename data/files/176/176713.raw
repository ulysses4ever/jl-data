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
const Lt=.3e-6
const dmax=Lt*c
const order=int(round(dmax/minimum([L;l;h]))+1)
const freq=.5e9
const w=2*pi*freq  # omega
const k=w/c     # wave number

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
const dx=0.05
const dy=0.05
const dz=0.05

const x=linspace(0,L,int(L/dx))
const y=linspace(0,l,int(l/dy))
const z=2

const nx=length(x)
const ny=length(y)

const N=int(Lt*freq)
const t=linspace(Lt/N,Lt,N)

println("Computing the radiation...")
Z=zeros(nx,ny,N)
Et=zeros(nx,ny,N)
Bt=zeros(nx,ny,N)
for i=1:nx
  perc=round(i/nx*1000)/10
  println("$perc %")
  for j=1:ny
    r=[x[i],y[j],z] #position of the receiver
    E=zeros(Complex128,3,N)
    B=zeros(Complex128,3,N)
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
      #expfac[1:ta]=0
      Ep=1/(4*pi*eps0*epsr)*(w^2/(c^2*magrprime^3)*rp_c_p_c_rp+(1/magrprime^3-w*im/(c*magrprime^2))*(3*rprime*dot(rprime,p)/magrprime^2-p))
      Bp=1/(4*pi*eps0*epsr)*1/(magrprime*c^3)*(w^2*rprime_cross_p)/magrprime*(1-c/(im*w*magrprime))
      u=1
      for n=ta:N
        E[:,n]+=expfac[u]*Ep
        B[:,n]+=expfac[u]*Bp
        u+=1
      end
    end
    Z[i,j,:]=sqrt(sum(real(E).^2,1))./sqrt(sum(real(B).^2,1))*mu0 #real(E).^2#0.5*numpy.cross(E.T,conjugate(B.T)) #impedance
    Et[i,j,:]=real(E[3,:]) #vertical E-field
    Bt[i,j,:]=real(B[2,:]) #y B-field
  end
end

save("Cartos.jld", "Et", Et, "Bt", Bt, "Z", Z, "t", t, "N", N)

#Some figures
using PyPlot
pygui(false)
for u=1:N
  ts=round(t[u]/1e-9*1000)/1000

  figure(num=1,figsize=(10,4)) #total E-field
  title("\$E_z\$ (V/m), t=$ts ns")
  pcolor(x,y,Et[:,:,u]',cmap="jet")
  clim(-20,20)
  axis("scaled")
  xlim(0,L)
  ylim(0,l)
  grid()
  colorbar(shrink=1,orientation="horizontal")
  xlabel("\$x\$/m")
  ylabel("\$y\$/m")
  savefig("Ez_$u.png",bbox="tight")
  clf()

  figure(num=2,figsize=(10,4))  #total B-field
  title("\$B_y\$ (A/m), t=$ts ns")
  pcolor(x,y,Bt[:,:,u]',cmap="jet")
  clim(-7e-8,7e-8)
  axis("scaled")
  xlim(0,L)
  ylim(0,l)
  grid()
  colorbar(shrink=1,orientation="horizontal")
  xlabel("\$x\$/m")
  ylabel("\$y\$/m")
  savefig("By_$u.png",bbox="tight")
  clf()

  figure(num=3,figsize=(10,4))  #Z
  title("\$Z\$ (\$ \\Omega\$), t=$ts ns")
  pcolor(x,y,Z[:,:,u]',cmap="jet")
  clim(0,1000)
  axis("scaled")
  xlim(0,L)
  ylim(0,l)
  grid()
  colorbar(shrink=1,orientation="horizontal")
  xlabel("\$x\$/m")
  ylabel("\$y\$/m")
  savefig("Z_$u.png",bbox="tight")
  clf()
end

