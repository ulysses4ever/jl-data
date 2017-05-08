module Intervalos
  using Base

  importall Base.Operators

  export Interval


  immutable Interval #DEFINICIÓN DE INTERVALO
        left::Float64
        right::Float64

        function Interval(left::Float64, right::Float64) #EN CASO DE NO ESTAR EN ORDEN, LO PONE
            if left > right
                left, right = right, left
            end
            new(left, right)
        end

        function Interval(n::Real)
          m=Interval(n,n)
        end

  end

  show(io::IO, a::Interval) = print(io::IO, "[$(a.left), $(a.right)]") #MUESTRA LOS INTERVALOS COMO [A,B]




  function Redondeo(f, redondeo, x::Float64, y::Float64) #Redondea
        with_rounding(redondeo) do
            f(x, y)
        end
  end

  function Redondeo(f, x::Interval, y::Interval, s::String) #redondea las maximizaciones o minimizaciones de las posibles operaciones...
        if s=="min"                                           #...entre los elementos de dos intervalos
            a = Redondeo(f, RoundDown, x.left, y.left)
            b = Redondeo(f, RoundDown, x.left, y.right)
            c = Redondeo(f, RoundDown, x.right, y.left)
            d = Redondeo(f, RoundDown, x.right, y.right)
            min(a,b,c,d)
        else
            a = Redondeo(f, RoundUp, x.left, y.left)
            b = Redondeo(f, RoundUp, x.left, y.right)
            c = Redondeo(f, RoundUp, x.right, y.left)
            d = Redondeo(f, RoundUp, x.right, y.right)
            max(a,b,c,d)
        end
  end




  function +(x::Interval, y::Interval) #Suma de intervalos
        l = Redondeo(+, RoundDown, x.left, y.left)
        r = Redondeo(+, RoundUp, x.right, y.right)
        Interval(r, l)
  end

  function +(x::Interval, n::Real)
        l = Redondeo(+, RoundDown, x.left, n)
        r = Redondeo(+, RoundUp, x.right, n)
        Interval(r, l)
  end



  function -(x::Interval, y::Interval) #Resta de intervalos
        l = Redondeo(-, RoundDown, x.left, y.left)
        r = Redondeo(-, RoundUp, x.right, y.right)
        Interval(r, l)
  end

  function *(x::Interval, y::Interval) #Multiplicación de intervalos
        l = Redondeo(*, x, y, "min")
        r = Redondeo(*, x, y, "max")
        Interval(r, l)
  end

  function *(x::Interval, n::Real)
          l = Redondeo(*, x, n, "min")
          r = Redondeo(*, x, n, "max")
          Interval(r, l)
  end

  function /(x::Interval, y::Interval) #División de intervalos
        if y.left<=0 && y.right>=0
            error("ERROR: El denominador contiene al 0")
        else
            if y.left==0||y.right==0
                error("ERROR: El denominador contiene al 0")
            else
                l = Redondeo(/, x, y, "min")
                r = Redondeo(/, x, y, "max")
                Interval(r, l)
            end
        end
  end

  function contains(x::Interval, n::Real)
    if n>=x.left && x.right>=n
      true
    else
      false
    end
  end

  function ^(x::Interval, n::Int64)
    if iseven(n)==true
      if x.left>=0.0
        Interval(x.left^n, x.right^n)
      elseif x.right<0.0
        Interval(x.right^n, x.left^n)
      else
        Interval(0.0, max(x.right^n, x.left))
      end
    else
      Interval(x.left^n, x.right^n)
    end
  end


end




