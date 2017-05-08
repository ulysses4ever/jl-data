include ("difdiv.jl")

function getAprox(x, X, Y)

  C=difdiv(X,Y)
  j=length(X)
  p=C[1]

  for i=[1:j-1]
    difX=x-X[1]

    for k=[2:i]
      difX*=(x-X[k])
    end

  p+=difX*C[i+1]
  end
  return p
end

  
    
    
