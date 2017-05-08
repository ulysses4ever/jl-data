include ("sinh_tanh/sinh_tanh.jl")
include ("sinh_tanh/printError_sinh_tanh.jl")

  n=8

  println("\n Error for f(x)=3: ")
  f(x)=3
  integral(x)=3x
    (a,b)=(-1,1)
    printError_sinh_tanh(f,a,b,integral,n)
    (a,b)=(0,1)
    printError_sinh_tanh(f,a,b,integral,n)
    (a,b)=(1,4)
    printError_sinh_tanh(f,a,b,integral,n)

  println("\n Error for f(x)=5x+1: ")
  f(x)=5x + 1
  integral(x)=(5/2)*x^2+x
    (a,b)=(-1,1)
    printError_sinh_tanh(f,a,b,integral,n)
    (a,b)=(0,1)
    printError_sinh_tanh(f,a,b,integral,n)
    (a,b)=(1,4)
    printError_sinh_tanh(f,a,b,integral,n)

  println("\n Error for f(x)=x^2-x: ")
  f(x)=x^2-x
    integral(x)=(1/3)*x^3-(1/2)*x^2
    (a,b)=(-1,1)
    printError_sinh_tanh(f,a,b,integral,n)
    (a,b)=(0,1)
    printError_sinh_tanh(f,a,b,integral,n)
    (a,b)=(1,4)
    printError_sinh_tanh(f,a,b,integral,n)

  println("\n Error for f(x)=x^3+x^2: ")
  f(x)=x^3+x^2
    integral(x)=(1/4)*x^4+(1/3)*x^3
    (a,b)=(-1,1)
    printError_sinh_tanh(f,a,b,integral,n)
    (a,b)=(0,1)
    printError_sinh_tanh(f,a,b,integral,n)
    (a,b)=(1,4)
    printError_sinh_tanh(f,a,b,integral,n)

  println("\n Error for f(x)=x^4-4x^2+x: ")
    f(x)=x^4-4x^2+x
    integral(x)=(1/5)x^5-(1/3)*4x^3+(1/2)*x^2
    (a,b)=(-1,1)
    printError_sinh_tanh(f,a,b,integral,n)
    (a,b)=(0,1)
    printError_sinh_tanh(f,a,b,integral,n)
    (a,b)=(1,4)
    printError_sinh_tanh(f,a,b,integral,n)

  println("\n Error for f(x)=e^x: ")
    f(x)=e^x
    integral(x)=e^x
    (a,b)=(-1,1)
    printError_sinh_tanh(f,a,b,integral,n)
    (a,b)=(0,1)
    printError_sinh_tanh(f,a,b,integral,n)
    (a,b)=(1,4)
    printError_sinh_tanh(f,a,b,integral,n)
