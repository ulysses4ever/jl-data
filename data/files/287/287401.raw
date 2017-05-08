function pruebaAsync()
    @async begin
      sleep(1)
      print("Estoy adentro")
    end
  print("Estoy Afuera")
end

function pruebaSpawn()
  for i=1:5
    @spawn println("Soy $(myid())")
  end
end

function pruebaAsyncConVariosProcs()
  for i=1:5
    @async begin
      println("Soy: $(myid())")
    end
  end
  println("Terminé")
end
1+1
nprocs()
#Agregar Procesos Locales
addprocs(3)
pruebaSpawn()
pruebaAsyncConVariosProcs()
pruebaAsync()

a = zeros(10)
b = SharedArray(Int, 10)
addprocs(1)
nprocs()
a[2]
b[2]

a[3]
b[3]

@spawn a[2]=1
@spawn b[2]=1
addprocs(10)
for i = 1:10
  @spawn  b[1] = i
end
b[1]
1+1
@async a[3] = 1
@async b[3] = 1



