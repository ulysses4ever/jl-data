using PyPlot 
#grid
nr=1.5
dr=0.05
N=100
r=zeros(Float64,N)
mu=1
h=0.5
PSI=zeros(Float64,N)
idr=1/dr
for z=1:N
    r[z]=z*dr
    Psi[z]=exp(-(r[z]**2))
end

#theta=linspace(0,360,100)
#(X,Y)=ndgrid(r*cos(theta),r*sin(theta))
#plot(X,Y)
for z=1:N
    Psi(r)=(Psi(r+h)+Psi(r-h)-2Psi(r))*(idr**2) + (Psi(r+h)+Psi(r-h))*(idr)
end
