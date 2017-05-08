include ("TR.jl")

function getErro (f, integ)

  for (a, b) = [(0, 1), (0, 10), (-1, 1), (-10, 10)]

    println ("\n Intervalo entre $a e $b :\n")

    for n = [2, 10, 100, 1000]

      erro = integ (a, b) - TR (f, a, b, n)

      println (" Erro (n = $n): $erro")

    end
  end
end

f(x) = 1
println ("\n Erro para f(x) = 1 \n")
integ (a, b) = b - a
getErro (f, integ)

f(x) = x
println ("\n \n Erro para f(x) = x \n")
integ (a, b) = (b^2 - a^2)/2
getErro (f, integ)

f(x) = x^2
println ("\n \n Erro para f(x): = x^2 \n")
integ (a, b) = (b^3 - a^3)/3
getErro (f, integ)

f(x) = x^3
println ("\n \n Erro para f(x) = x^3 \n")
integ (a, b) = (b^4 - a^4)/4
getErro (f, integ)

f(x) = x^4
println ("\n \n Erro para f(x) = x^4 \n")
integ (a, b) = (b^5 - a^5)/5
getErro (f, integ)

f(x) = e^x
println ("\n \n Erro para f(x) = e^x \n")
integ (a, b) = e^b - e^a
getErro (f, integ)