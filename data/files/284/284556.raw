module IntervalMatrices
    using Intervalos
    using Base
    importall Base.Operators
    import Intervalos.Midpoint, Intervalos.Intersection
    export IntervalVector, IntervalMatrix, Midpoint, Norm, AbsoluteValue, Identidad, Intersection, KrawczykMethod, GaussianElimination2x2, Det2x2, *, /, +, -, CramerRule

    typealias IntervalMatrix{Interval} Array{Interval,2}
    #Esto hará que cuando cree funciones pueda llamar IntervalMatrix a lo que yo quiera y
    #julia detectará que es un Array{Interval,2}

    typealias IntervalVector{Interval} Array{Interval,1}





#PUNTO MEDIO


    function Midpoint(M::IntervalMatrix)
        x=zeros(Real,size(M)[1],size(M)[2])
        for i=1:size(M)[1]
            for j=1:size(M)[2]
                x[i,j]=Midpoint(M[i,j])
            end
        end
        return x
    end

    function Midpoint(V::IntervalVector)
        x=zeros(Real,size(V)[1])
        for i=1:size(V)[1]
            x[i]=Midpoint(V[i])
        end
        return x
    end

#NORMA
    function Norm(A::IntervalMatrix)
        v=Real[]
        for i=1:size(A)[1]
            x=0
            for j=1:size(A)[2]
                x=x+AbsoluteValue(A[i,j])
            end
            push!(v,x)
        end
        return findmax(v)[1]
    end


    function Norm(V::IntervalVector)
        v=Real[]
        x=0
        for i=1:size(V)[1]
            x=AbsoluteValue(V[i])
            push!(v,x)
        end
        return findmax(v)[1]
    end




    function Identidad(A::IntervalMatrix) #Da una matriz identidad en intervalos de las dimesiones de A
        Id=zeros(Any,size(A)[1],size(A)[2])
        for i=1:size(A)[1]
                for j=1:size(A)[2]
                    if i==j
                        Id[i,j]=one(A[i,j])
                    end
                end
            end
        return Id
    end


    Base.one(A::Interval)=Interval(1)


    function Intersection(v::IntervalVector, u::IntervalVector) #Intersección entre dos vectores con entradas independientes
        w=Interval[]
        if size(v)[1]==size(u)[1]
            for i=1:size(v)[1]
                push!(w,Intersection(u[i],v[i]))
            end
            return w
        else
            return error("Los vectores proporcionados no tienen la misma cantidad de elementos")
        end
    end

#Operadores

    function +(V::IntervalVector,c::Real)
        U=Interval[]
        for i=1:size(V)[1]
            push!(U,V[i]+c)
        end
        return U
    end

    +(c::Real,V::IntervalVector)=+(V,c)

    function -(V::IntervalVector,x::Real)
        U=Interval[]
        for i=1:size(V)[1]
            push!(U,V[i]-x)
        end
        return U
    end

    -(x::Real,V::IntervalVector)=-(V,x)*(-1)


    function +(V::IntervalVector,x::Interval)
        U=Interval[]
        for i=1:size(V)[1]
            push!(U,V[i]+x)
        end
        return U
    end

    +(x::Interval, V::IntervalVector)=+(V,x)

    function *(V::IntervalVector,x::Interval)
        U=Interval[]
        for i=1:size(V)[1]
            push!(U,V[i]*x)
        end
        return U
    end

    *(x::Interval, V::IntervalVector)=*(V,x)


  function /(V::IntervalVector,x::Interval)
      U=Interval[]
      for i=1:size(V)[1]
          push!(U,ExtendedDivision(V[i],x))
      end
      return U
  end

    function -(V::IntervalVector,x::Interval)
        U=Interval[]
        for i=1:size(V)[1]
            push!(U,V[i]-x)
        end
        return U
    end

    -(x::Interval,V::IntervalVector)=-(V,x)*(-1)

    function +(A::IntervalMatrix,c::Real)
        v=zeros(Any,size(A)[1],size(A)[2])
        for i=1:size(A)[1]
                for j=1:size(A)[2]
                        v[i,j]=A[i,j]+c
                end
            end
        return v
    end

    +(c::Number, A::IntervalMatrix)=+(A,c)

    function -(A::IntervalMatrix,c::Real)
        v=zeros(Any,size(A)[1],size(A)[2])
        for i=1:size(A)[1]
                for j=1:size(A)[2]
                        v[i,j]=A[i,j]-c
                end
            end
        return v
    end

    -(c::Number, A::IntervalMatrix)=(-(A,c))*(-1)

    function +(A::IntervalMatrix,x::Interval)
        v=zeros(Any,size(A)[1],size(A)[2])
        for i=1:size(A)[1]
                for j=1:size(A)[2]
                        v[i,j]=A[i,j]+x
                end
            end
        return v
    end

    +(c::Interval, A::IntervalMatrix)=+(A,c)

    function -(A::IntervalMatrix,x::Interval)
        v=zeros(Any,size(A)[1],size(A)[2])
        for i=1:size(A)[1]
                for j=1:size(A)[2]
                        v[i,j]=A[i,j]-x
                end
            end
        return v
    end

    -(x::Interval, A::IntervalMatrix)=(-(A,x))*(-1)


    function *(A::IntervalMatrix,x::Interval)
        v=zeros(Any,size(A)[1],size(A)[2])
        for i=1:size(A)[1]
                for j=1:size(A)[2]
                        v[i,j]=A[i,j]*x
                end
            end
        return v
    end

    *(c::Interval, A::IntervalMatrix)=*(A,c)

    function *(c::Number,x::IntervalVector) #VECTORES
        v=Interval[]
        for i=1:size(x)[1]
            push!(v,c*x[i])
        end
        return v
    end

    *(x::IntervalVector, c::Number)=*(c,x)

    function /(x::IntervalVector,c::Number)
        *(1/c,x)
    end


    function *(c::Number,x::IntervalMatrix) #MATRICES
        v=zeros(Any,size(x)[1],size(x)[2])
         for i=1:size(x)[1]
                    for j=1:size(x)[2]
                            v[i,j]=c*x[i,j]
                    end
                end
            return v
    end

    *(x::IntervalMatrix,c::Number)=*(c,x)

    function /(x::IntervalMatrix,c::Number)
        *(1/c,x)
    end


#Metodos de solución directos Ax=b


##Gauss
    function GaussianElimination2x2(A::IntervalMatrix, b::IntervalVector) #Eliminación Gaussiana 2x2


        a=A[2,2]-(A[2,1]/A[1,1])*A[1,2]
        d=b[2]-(A[2,1]/A[1,1])*b[1]
        x2=d/a

        c=b[1]-A[1,2]*x2
        x1=c/A[1,1]


        X=[x1,x2]
        return X
    end



##Cramer
    function CramerRule(A::IntervalMatrix, b::IntervalVector) #Regla de Cramer para 2x2, la definición de los determinantes es extraña
        if size(A)[1]==size(A)[2]
                Det=Det2x2(A)
            if contains(Det,0)==true
                return error("Puede haber una indeterminación, es decir, hay dependencia lineal")
            else
                    x=Det2x2([b[1] A[1,2]; b[2] A[2,2]])/Det
                    y=Det2x2([A[1,1] b[1]; A[2,1] b[2]])/Det
                    v=[x;y]
                    return v
            end
        else
            return error("No es una matriz cuadrada de 2x2")
        end
    end

    function Det2x2(A::IntervalMatrix)
        if size(A)[1]==size(A)[2]
            if size(A)[1]==2
                return A[1,1]*A[2,2]-A[1,2]*A[2,1]
                else
                return error("La matriz no es de 2x2")
            end
        else
            return error("La matriz no es cuadrada")
        end
    end


#Métodos iterativos



##KrawczykMethod
function KrawczykMethod(A::IntervalMatrix, b::IntervalVector, e::Float64) #Para un e=error dado, método de Krawczyk
        Y=inv(midpoint(A))
        E=Identidad(A)-Y*A
        c=Norm((Y*b)/(1-Norm(E)))
        X=Interval[]
        if size(A)[1]==size(b)[1]
            for i=1:size(b)[1]
                push!(X,c*Interval(-1,1))
            end

            while length(X[1])>=e&&length(X[2])>=e
                Z=(Y*b + E*X)
                X=Intersection(Z,X)
            end

            return X

        else
            return error("Las dimensiones no son consistentes")
        end
    end


    function KrawczykMethod(A::IntervalMatrix, b::IntervalVector, n::Int64) #Para n número de iteraciones, método de Krawzyk
        Y=inv(midpoint(A))
        E=Identidad(A)-Y*A
        c=Norm((Y*b)/(1-Norm(E)))
        X=Interval[]
        if size(A)[1]==size(b)[1]
            for i=1:size(b)[1]
                push!(X,c*Interval(-1,1))
            end

            for j=1:n
                Z=(Y*b + E*X)
                X=Intersection(Z,X)

            end

            return X
        else
            return error("Las dimensiones no son consistentes")
        end
    end

  function GaussSeidelStep(A::IntervalMatrix,b::IntervalVector,x::IntervalVector)
      Y=inv(Midpoint(A))
      G=Y*A                                                   # x=Vector inicial
      C=Y*b                                                   # Antes de la Intersección
      numerador=C
      n=size(A)[1]   #Numero de ecuaciones

      X=x #Inicialización
      for i=1:n
          if contains(G[i,i],0)==false
              if i>1
                  for j=1:i-1
                  numerador=numerador-G[i,j]*X[j]
                  end
              end

              if i<n
                  for j=i+1:n
                  numerador=numerador-G[i,j]*X[j]
                  end
              end


          else
              return error("Un elemento diágonal contiene al cero")
          end
          return numerador/G[i,i]
      end


      #return numerador/G[i,i]
  end

  function GaussSeidel(A::IntervalMatrix,b::IntervalVector,x::IntervalVector,i::Int64) # i numero de iteraciones
      for n=1:i
          X_=GaussSeidelStep(A,b,x)
          x=Intersection(X_,x)
      end
      return x
  end



end
