include ("TR.jl")
include ("SR.jl")

function printError (integral, f, g, spacing, intervals)

  for i=[1:size(intervals,1)]
    a = intervals [i,1]
    b = intervals [i,2]
    println ("\n between $a and $b :\n")
    for i=[1:length(spacing)]
      n = spacing[i]
      error = integral(a, b) - g(f, a, b, n)
      println (" Error (n = $n): $error")
    end
  end
end

for g = [TR, SR]
  spacing = [2, 10, 100, 1000]
  intervals = [0 1; 0 10; -1 1; -10 10]

  f(x) = 1
  println ("\n \n Error for f(x) = 1 ($g) \n")
  integral (a, b) = b - a
  printError (integral, f, g, spacing, intervals)
   
  f(x) = x
  println ("\n \n Error for f(x) = x ($g) \n")
  integral (a, b) = (b^2 - a^2)/2
  printError (integral, f, g, spacing, intervals)

  f(x) = x^2
  println ("\n \n Error for f(x) = x^2 ($g) \n")
  integral (a, b) = (b^3 - a^3)/3
  printError (integral, f, g, spacing, intervals)

  f(x) = x^3
  println ("\n \n Error for f(x) = x^3 ($g) \n")
  integral (a, b) = (b^4 - a^4)/4
  printError (integral, f, g, spacing, intervals)

  f(x) = x^4
  println ("\n \n Error for f(x) = x^4 ($g) \n")
  integral (a, b) = (b^5 - a^5)/5
  printError (integral, f, g, spacing, intervals)

  f(x) = e^x
  println ("\n \n Error for f(x) = e^x ($g) \n")
  integral (a, b) = e^b - e^a
  printError (integral, f, g, spacing, intervals)

end