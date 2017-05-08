#### Script que produce los plots de la energía y magnetización en función de la temperatura
### Los argumentos para la consola van en el siguiente orden ancho, largo, Tmin, Tstep ,Tmax, iteraciones
#cargamos el paquete de ploteo

#ponemos los valores en formato trabajable
num_valores=length(ARGS)
valores=zeros(num_valores)
i=1;
for x in ARGS
  println(x)
  valores[i]=float(x)
  i=i+1
end

##Hacemos semantica
if num_valores<2
    println()
    println("Al menos debes de dar el ancho y el largo de la matriz de espines")
    println()
    println("El formato es el siguiente: ancho largo iteracion Tmin Tmax Tstep")
    println("ancho largo iteracion Tmin Tmax Tstep")
    println()
    println("Si quieres puedes dejar en blanco iteracion o lo de T y se tomara un valor por default")
    println()
    exit()

elseif num_valores==2
    ancho=int(valores[1]);
    largo=int(valores[2]);
    iteraciones=int(4e6)
    Tmin=0.2
    Tmax=5.
    Tstep=0.2

elseif num_valores==3
    ancho=int(valores[1])
    largo=int(valores[2])
    iteraciones=int(valores[3])
    Tmin=0.2
    Tmax=5.
    Tstep=0.2

elseif num_valores==6
    ancho=int(valores[1])
    largo=int(valores[2])
    iteraciones=int(valores[3])
    Tmin=valores[4]
    Tmax=valores[5]
    Tstep=valores[6]

else
    println("Si das un valor de la temperatura debes de dar todos")
    println("El formato es el siguiente ancho largo iteracion Tmin Tmax Tstep")
    exit()
end

#Cargamos el modulo Ising
if(!isfile("Ising.jl"))
    println("Se necesita el archivo 'Ising.jl' en el directorio del script")
    exit()
else
    include("Ising.jl")
end
using Ising

#Armamos nuestra configuracion
conf=configuracion(ancho,largo,Tmin)
Ts=[Tmin:Tstep:Tmax]

#Simulamos
Es,Ms,ds=simulacion_con_E_y_M(conf,iteraciones)
Ts,E_proms,M_proms=(Es,conf.ancho*conf.largo,Ts)

using PyPlot
plot(Ts,E_proms,label="Energia");
plot(Ts,M_proms,label="Magnetizacion");
legend()
xlabel("Temperatura")
title("Energia y magnetizacion promedio vs. temperatura en Ising 2D")
savefig("proms.png")
print("Ploteo guardado en proms.png en el directorio del script")
