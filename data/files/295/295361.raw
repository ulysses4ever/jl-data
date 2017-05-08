include ("TR.jl")
include ("SR.jl")
using TimeIt
include ("printTime.jl")

spacing = [2, 10, 100, 1000]
intervals = [0 1; 0 10; -1 1; -10 10]
for g = [TR, SR]

  f(x) = 1
  println ("\n \n Time for f(x) = 1 ($g) \n")
  printTime (f, g, spacing, intervals)
   
  f(x) = x
  println ("\n \n Time for f(x) = x ($g) \n")
  printTime (f, g, spacing, intervals)

  f(x) = x^2
  println ("\n \n Time for f(x) = x^2 ($g) \n")
  printTime (f, g, spacing, intervals)

  f(x) = x^3
  println ("\n \n Time for f(x) = x^3 ($g) \n")
  printTime (f, g, spacing, intervals)

  f(x) = x^4
  println ("\n \n Time for f(x) = x^4 ($g) \n")
  printTime (f, g, spacing, intervals)

  f(x) = e^x
  println ("\n \n Time for f(x) = e^x ($g) \n")
  printTime (f, g, spacing, intervals)

end