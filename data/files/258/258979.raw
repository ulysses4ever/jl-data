module NumericDerivatives
  using Base
  import Base.exp, Base.log, Base.sin, Base.cos, Base.tan
  importall Base.Operators

  export ValorDeriv

  type ValorDeriv
    f
    d
  end

  function  +(u::ValorDeriv, v::ValorDeriv)
      ValorDeriv(u.f+v.d, u.f+v.d)
    end

  -(u::ValorDeriv, v::ValorDeriv) = ValorDeriv(u.val-v.val, u.der-v.der)

  *(n::Number, u::ValorDeriv) = ValorDeriv(n*u.val, n*u.der)
  *(u::ValorDeriv, v::ValorDeriv) = ValorDeriv(u.val*v.val, u.val*v.der + v.val*u.der)


  /(u::ValorDeriv, v::ValorDeriv) = ValorDeriv(u.val/v.val, (u.der*v.val - v.der*u.val)/(v.val^2))
  /(n::Number, u::ValorDeriv) = ValorDeriv(n/u.val, -n/(u.val^2))



  sin(u::ValorDeriv) = ValorDeriv(sin(u.val), cos(u.val)*u.der)
  cos(u::ValorDeriv) = ValorDeriv(cos(u.val), -sin(u.val)*u.der)

  exp(u::ValorDeriv) = ValorDeriv(exp(u.val), e(u.val)*u.der)
  log(u::ValorDeriv) = ValorDeriv(log(u.val), u.der/u.val)


  #operators





end

x=ValorDeriv(1,0) #x_0=2
y=ValorDeriv(2,1)

x.d
x+y

