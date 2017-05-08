function difdiv(X,Y)

  j=length(X)
  X=X*1.0
  Y=Y*1.0
  C=copy(Y)
  ordem=copy(Y)

  for i=[1:j-1]

    for p=[1:j-i]
      ordem[p]=(ordem[p+1]-ordem[p])/(X[p+i]-X[p])
    end
    
    C[i+1]=ordem[1]
  end
  return C
end
    
    
    
  
  