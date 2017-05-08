include ("TR.jl")

using TimeIt

function timeTR (f)

  for (a, b) = [(0, 1), (0, 10), (-1, 1), (-10, 10)]

    println ("\n Intervalo entre $a e $b :")

    for n = [2, 10, 100, 1000]

      println ("\n (n = $n):")

      @timeit TR(f, a, b, n)

    end
  end
end

f(x) = 1
println ("\n Tempo para f(x) = 1 \n")
timeTR (f)

f(x) = x
println ("\n \n Tempo para f(x) = x \n")
timeTR (f)

f(x) = x^2
println ("\n \n Tempo para f(x): = x^2 \n")
timeTR (f)

f(x) = x^3
println ("\n \n Tempo para f(x) = x^3 \n")
timeTR (f)

f(x) = x^4
println ("\n \n Tempo para f(x) = x^4 \n")
timeTR (f)

f(x) = e^x
println ("\n \n Tempo para f(x) = e^x \n")
timeTR (f)