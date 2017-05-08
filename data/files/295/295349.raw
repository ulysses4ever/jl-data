include ("difdiv.jl")

function getAprox(point, X, Y)

  C=difdiv(X,Y)
  j=length(X)
  p=C[1]

  for i=[1:j-1]
    difX=point-X[1]

    for k=[2:i]
      difX*=(point-X[k])
    end

  p+=difX*C[i+1]
  end
  return p
end

  
    
    
