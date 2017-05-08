
Pkg.add("PyPlot")
using PyPlot
using Intervalos

pwd()
using DerivadasNumericas

NumDerive(2,1)



#Dibujito del método de Newton

P_2(x)=x^2-2.0
x_interval = Interval(1.0,2.0)
x = linspace(x_interval.left, x_interval.right, 100);
y = [P_2(i) for i in x]
y_0 = zeros(100)

y_recta = [P_2(NumDerive(2)).f + P_2(NumDerive(2)).d*(i-2) for i in x]


plot(x,y,x,y_0,x,y_recta)

#Algoritmo de Newton para encontrar raices


function FindRoot(F::Function, x::Number, n::Int64) #n iteraciones
  for i=1:n
    x=x-F(NumDerive(x)).f/F(NumDerive(x)).d
  end
  return (x)
end

FindRoot(P_2,2,10) #Raiz cuadrada de 2

P_3(x)=x^3-2.0
FindRoot(P_3,2,10) #Raiz cúbica de 2

#SI LA FUCNIÓN ES COMPLEJA????

f(z)=z^3-1
FindRoot(f, 1+1*im,10)
FindRoot(f, 1-1*im,10)
FindRoot(f, -1+1*im, 10)
FindRoot(f, -1-1*im, 10)

#CONVERGEN A DIFERENTES RAICES


M=zeros(Complex64,1000,1000)

function h(m,y1,y2) #function que logra poner los rangos de la matriz M[m,n] al rango de x_0 que quiero evaluar x_0=h(n)+h(m)*im
  return(((y2-y1)/999)*(m-1)-y2)
end

h(1,-20,20)
h(1000,-20,20)

#Relleno M[n,m] con las raices a la que convergen los x_0
for m=1:1000
  for n=1:1000
    M[n,m]=FindRoot(f,h(n,-2,2)+h(m,-2,2)*im,20)
  end
end

M


realM=real(M)
imagM=imag(M)





R=zeros(Float64,1000,1000)
I=zeros(Float64,1000,1000)

for i = 1:1000
    for j = 1:1000
        R[i,j]=real(FindRoot(f,(i/10-50)+(j/10-50)*im,10))
        I[i,j]=imag(FindRoot(f,(i/10-50)+(j/10-50)*im,10))
    end
end
R
I

imshow(I)






