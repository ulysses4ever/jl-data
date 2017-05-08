include ("SR.jl")

#

function GetErro (f, integ)

  for (a, b) = [(0, 1), (0, 10), (-1, 1), (-10, 10)]

    println ("
    Intervalo entre $a e $b :
                ")

    for n = [2, 10, 100, 1000]

      

      erro = integ (a, b) - SR (f, a, b, n)

      println ("          Erro (n = $n): $erro")
      

          end
      end
  end

#
f(x) = 1
 println ("Erro para f(x) = 1
          ")
 integ (a, b) = b - a
 GetErro (f, integ)

#
f(x) = x
 println ("
 Erro para f(x) = x
          ")
 integ (a, b) = (b^2 - a^2)/2
 GetErro (f, integ)
#
f(x) = x^2
 println ("
 Erro para f(x): = x^2
          ")
 integ (a, b) = (b^3 - a^3)/3
 GetErro (f, integ)
#
f(x) = x^3
 println ("
 Erro para f(x) = x^3
          ")
 integ (a, b) = (b^4 - a^4)/4
 GetErro (f, integ)
#
f(x) = x^4
 println ("
 Erro para f(x) = x^4
          ")
 integ (a, b) = (b^5 - a^5)/5
 GetErro (f, integ)
#
f(x) = e^x
 println ("
 Erro para f(x) = e^x
          ")
  integ (a, b) = e^b - e^a
 GetErro (f, integ)
