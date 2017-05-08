include ("TR.jl")
include ("SR.jl")
using TimeIt

function printError (f, g, spacing, intervals)

  for i=1:1:size(intervals,1)
    a = intervals [i,1]
    b = intervals [i,2]
    println ("\n between $a and $b :\n")
    for i=[1:length(spacing)]
      n = spacing[i]
      println (" Time (n = $n): ")
      @timeit g(f, a, b, n)
    end
  end
end

for g = [TR, SR]
  spacing = [2, 10, 100, 1000]
  intervals = [0 1; 0 10; -1 1; -10 10]

  f(x) = 1
  println ("\n \n Time for f(x) = 1 ($g) \n")
  printError (f, g, spacing, intervals)
   
  f(x) = x
  println ("\n \n Time for f(x) = x ($g) \n")
  printError (f, g, spacing, intervals)

  f(x) = x^2
  println ("\n \n Time for f(x) = x^2 ($g) \n")
  printError (f, g, spacing, intervals)

  f(x) = x^3
  println ("\n \n Time for f(x) = x^3 ($g) \n")
  printError (f, g, spacing, intervals)

  f(x) = x^4
  println ("\n \n Time for f(x) = x^4 ($g) \n")
  printError (f, g, spacing, intervals)

  f(x) = e^x
  println ("\n \n Time for f(x) = e^x ($g) \n")
  printError (f, g, spacing, intervals)

end