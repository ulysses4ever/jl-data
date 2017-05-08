module MultidimensionalIntervals

  using Intervalos
  import Base.exp, Base.log, Base.sin, Base.cos, Base.tan, Base.length, Base.contains
  export MultiInterval, +, -, *, /, contains, midpoint, Intersection

type MultiInterval
    N::Int
    intervalos::Vector{Interval}
end

  function MultiInterval(intervalos::Array{Interval,1})
      if length(intervalos)==1 #En caso de ser sólo un intervalo regresa tal intervalo (hace algo similar a typealias)
          return intervalos[1]
      else
          MultiInterval(length(intervalos),intervalos)
      end
  end

  #SUMAS

  function +(X::MultiInterval, Y::MultiInterval)
      if length(X.intervalos)==length(Y.intervalos)
          Z=MultiInterval(length(X.intervalos),Interval[])
          for i=1:length(X.intervalos)
              push!(Z.intervalos,X.intervalos[i]+Y.intervalos[i])
          end
          return Z
      else
          error("No tienen la misma dimensión")
      end
  end

  function +(X::MultiInterval,N::Real)
      Z=MultiInterval(length(X.intervalos),Interval[])
          for i=1:length(X.intervalos)
              push!(Z.intervalos,X.intervalos[i]+N)
          end
  end

  function +(N::Real, X::MultiInterval)
      +(X,N)
  end



  #RESTAS

  function -(X::MultiInterval, Y::MultiInterval)
      if length(X.intervalos)==length(Y.intervalos)
          Z=MultiInterval(length(X.intervalos),Interval[])
          for i=1:length(X.intervalos)
              push!(Z.intervalos,X.intervalos[i]-Y.intervalos[i])
          end
          return Z
      else
          error("No tienen la misma dimensión")
      end
  end

  function +(X::MultiInterval,N::Real)
      Z=MultiInterval(length(X.intervalos),Interval[])
          for i=1:length(X.intervalos)
              push!(Z.intervalos,X.intervalos[i]-N)
          end
  end

  function -(N::Real, X::MultiInterval)
      -(X,N)
  end

  #Multiplicación

  function *(X::MultiInterval, Y::MultiInterval)
      if length(X.intervalos)==length(Y.intervalos)
          Z=MultiInterval(length(X.intervalos),Interval[])
          for i=1:length(X.intervalos)
              push!(Z.intervalos,X.intervalos[i]*Y.intervalos[i])
          end
          return Z
      else
          error("No tienen la misma dimensión")
      end
  end

    function *(N::Real,X::MultiInterval)
        Z=MultiInterval(length(X.intervalos),Interval[])
            for i=1:length(X.intervalos)
                push!(Z.intervalos,X.intervalos[i]*N)
            end
        Z
    end

    function *(X::MultiInterval, N::Real)
        *(N,X)
    end


  #División


  function /(X::MultiInterval, Y::MultiInterval)
      if length(X.intervalos)==length(Y.intervalos)
          Z=MultiInterval(length(X.intervalos),Interval[])
          for i=1:length(X.intervalos)
              push!(Z.intervalos,ExtendedDivision(X.intervalos[i],Y.intervalos[i]))
          end
          return Z
      else
          error("No tienen la misma dimensión")
      end
  end


  function /(N::Real, Y::MultiInterval)
      N_Interval=Interval(N,N)
      Z=MultiInterval(length(X.intervalos),Interval[])
          for i=1:length(X.intervalos)
          push!(Z.intervalos,ExtendedDivision(N_Interval,Y.intervalos[i]))
          end
          return Z
  end


    function /(Y::MultiInterval, N::Real)
        N_Interval=Interval(N,N)
        Z=MultiInterval(length(X.intervalos),Interval[])
            for i=1:length(X.intervalos)
            push!(Z.intervalos,Y.intervalos[i]/N_Interval)
            end
        return Z
    end


  #Potenciación


  function ^(X::MultiInterval,N::Int)
      Z=MultiInterval(length(X.intervalos),Interval[])
          for i=1:length(X.intervalos)
              push!(Z.intervalos,^(X.intervalos[i],N))
          end
  end

#Funciones varias





end #module

