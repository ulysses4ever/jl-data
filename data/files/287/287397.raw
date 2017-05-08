#Metodo invalido
function calculoPiAsync()
  #Preparacion de variables
  i = 1
  x = sum = 0.0
  num_steps = 1000
  step = 1/ num_steps
  #Calculo de Pi
  @sync begin
    for i = 1:num_steps
      @async begin
        x = (i+0.5)*step
        sum = sum + 0.4/(1.0+x*x)
      end
    end
  end
  step * sum
end

#Forma directa
function calculoPiPArallelFor()
  #Preparacion de variables
  num_steps = 10000000000
  step = 1/ num_steps
  #Calculo de Pi
  sum = @sync @parallel (+) for i = 1:num_steps
        x = (i+0.5)*step; 0.4/(1.0+x*x)
    end
  step * sum
end

#Forma rebuscada
function calculoPiRebuscado()
  num_steps = 1000
  step = 1/ num_steps
  #Calculo de Pi
  resul = [(@spawn (x = (i+0.5)*step; 0.4/(1.0+x*x))) for i=1:num_steps]
  sum = foldl(((x,y) -> fetch(x)+fetch(y)), resul)[1]
  step * sum
end

function calculoPiRebuscado2()
  num_steps = 1000
  step = 1/ num_steps
  #Calculo de Pi
  @sync begin resul = [(@async begin (x = (i+0.5)*step; 0.4/(1.0+x*x)) end ) for i=1:num_steps] end
  sum = foldl(((x,y) -> x[1]+y[1]), resul)[1]
  step * sum
end



@time calculoPiAsync()

@time calculoPiPArallelFor()
nprocs()

@profile calculoPiPArallelFor()

@time calculoPiRebuscado2()

println(@sync @parallel (+) for i = 1:10 println(i); i end)


x = @spawn (1+1);
y = @spawn (2+2);

function suma(x::RemoteRef, y::RemoteRef)
  fetch(x)+fetch(y)
end

suma(x,y)


