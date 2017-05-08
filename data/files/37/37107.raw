#get the closed Newton-Cotes
function getIntValByNC(f,a,b,n)

  NewCotCoe=Array(Any,12);
  NewCotCoe=[1/6,2/3,1/6,1/8,3/8,3/8,1/8,7/90,16/45,2/15,16/45,7/90];

  x=linspace(a,b,n+1);
  H=(b-a)/n;##interval h

  Base1=0;
  for k in 2:1:n
    Base1=Base1+k;
  end
  Base1=Base1-2;

  Intf=0;
  for TheCurSta in 1:1:(n+1)
    Intf=Intf+NewCotCoe[TheCurSta+Base1]*f(x[TheCurSta]);
  end
  return Intf*(b-a)
end

function getIntValByGQ(f,a,b,n)
  Roots=Array(Any,12);
  Coefs=Array(Any,12);

  Roots=[0.7745966692,0.0,-0.7745966692,0.8611363116,0.3399810436,-0.3399810436,-0.8611363116,0.9061798459,0.5384693101,0.0,-0.5384693101,-0.9061798459];
  Coefs=[0.5555555556,0.8888888889,0.5555555556,0.3478548451,0.6521451549,0.6521451549,0.3478548451,0.2369268850,0.4786286705,0.5688888889,0.4786286705,0.2369268850];

  Tr1=(b-a)/2;
  Tr2=(b+a)/2;
  x(t)=Tr1*t+Tr2;

  Base1=0;
  for k in 2:1:n
    Base1=Base1+k;
  end
  Base1=Base1-2;

  Intf=0;
  for TheCurSta in 1:1:(n+1)
    x_hat=x(Roots[TheCurSta+Base1]);
    Intf=Intf+Coefs[TheCurSta+Base1]*f(x_hat);
  end

  return Tr1*Intf

end
