function EccAnom(M,e,tol=1e-12)

  maxit = 15;
  EPS   = 5.0*tol;
  i     = 0;
  
  M     = mod(M,2*pi);
  if e < 0.8
      E = M;
  else
      E = pi;
  end
  f = E - e*sin(E) - M;
  
  while abs(f) > EPS
      f = E - e*sin(E) - M;
      E = E - f / ( 1.0 - e*cos(E) );
      i = i + 1;
      if i==maxit
          error('convergence problems in EccAnom');
          break;
      end
  end

  return E

end