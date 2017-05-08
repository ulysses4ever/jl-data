include ("getDistance.jl")


println("\n f(x)= x^3, interval: [0,5] \n")

  (a, b) = (0,5) 
  nvalues=[10:10:100]

  f(x)=x^3

  for n=nvalues

    distance = getDistance(a,b,n,f)
    println ("Max. error for n=$n: $distance ")
  end

println("\n f(x)= x^(1/2), interval: [0,5] \n")

  (a, b) = (0,5) 

  f(x)=x^(1/2)
 
  for n=nvalues

    distance = getDistance(a,b,n,f)
    println ("Max. error for n=$n: $distance")
  end

println("\n f(x)= e^x, interval: [0,3] \n")

  (a, b) = (0,3) 

  f(x)=e^x
 
  for n=nvalues

    distance = getDistance(a,b,n,f)
    println ("Max. error for n=$n: $distance")
  end

println("\n f(x)= cos(x), interval: [0,2*pi] \n")

(a, b) = (0,2*pi) 

f(x)=cos(x)
 
  for n=nvalues

    distance = getDistance(a,b,n,f)
    println ("Max. error for n=$n: $distance")
  end

println("\n f(x)= sin(x+2.8*cos(x), interval: [0,2*pi] \n")

(a, b) = (0,2*pi) 

f(x)=sin(x+2.8*cos(x))

  for n=nvalues

    distance = getDistance(a,b,n,f)
    println ("Max. error for n=$n: $distance ")
  end

println("\n f(x)= 1/(1+25x^2), interval: [-1,1] \n")

(a, b) = (-1,1) 

f(x)=1/(1+25x^2)

  for n=nvalues

    distance = getDistance(a,b,n,f)
    println ("Max. error for n=$n: $distance ")
  end

