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
const freq=2e9

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
x=4.5
y=1.5
z=2

println("Computing the fields...")

r=[x,y,z] #position of the receiver
E=zeros(3,N)
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
  if ta<N+1
    #expfac=exp(1im*(-w*t+krp-phi))
    Ep=1/(4*pi*eps0*epsr)*(1/(c^2*magrprime^3)*rp_c_p_c_rp) #+(1/magrprime^3-w*im/(c*magrprime^2))*(3*rprime*dot(rprime,p)/magrprime^2-p))
    E[:,ta]+=Ep
  end
end
toc()

#Frequency response

const Fs = N/Lt;  #sampling frequency
const T = 1/Fs;   #sample length

tt = (0:N-1)*T;  #time...

np2 = nextpow2(N) # Next power of 2 from length of y
Yx = fft([E[1,:] zeros(np2-N)']);
Yy = fft([E[2,:] zeros(np2-N)']);
Yz = fft([E[3,:] zeros(np2-N)']);
endfft=int(np2/2)
f = Fs/2*linspace(0,1,endfft)

# Three axis frequency response
FFTx = abs(Yx[1:endfft]);
FFTy = abs(Yy[1:endfft]);
FFTz = abs(Yz[1:endfft]);


using PyPlot

#CIR figure
figure(1)
subplot(311)
plot(t/1e-6,E[1,:]')
title("\$E_x\$")
grid()
xlabel("time in \$\\mu\$s")
ylabel("V/m")

subplot(312)
plot(t/1e-6,E[2,:]')
title("\$E_y\$")
grid()
xlabel("time in \$\\mu\$s")
ylabel("V/m")

subplot(313)
plot(t/1e-6,E[3,:]')
title("\$E_z\$")
grid()
xlabel("time in \$ \\mu \$s")
ylabel("V/m")
savefig("CIR.pdf")
close()

close()

#Frequency response figure
figure(3)
subplot(311)
plot(f/1e6,20*log10(FFTx))
title("\$FFT_x\$")
xlim(0,500)
grid()
xlabel("frequency in MHz")
ylabel("dB")

subplot(312)
plot(f/1e6,20*log10(FFTy))
title("\$FFT_y\$")
xlim(0,500)
grid()
xlabel("frequency in MHz")
ylabel("dB")

subplot(313)
plot(f/1e6,20*log10(FFTz))
title("\$FFT_z\$")
xlim(0,500)
grid()
xlabel("frequency in MHz")
ylabel("dB")

savefig("fft.pdf")
close()

