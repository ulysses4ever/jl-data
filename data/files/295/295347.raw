include ("getAprox.jl")

function errorDifDiv(f, pontos, X, Y)

  for i=[1:length(pontos)]
    
    x = pontos[i]
    error = f(x)-getAprox(x,X,Y)
    println ("\n Erro para $x : $error \n")
    
  end
end