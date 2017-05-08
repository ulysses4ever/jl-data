@doc """
      Fourth-Order Runge-Kutta Method
      Supported by:
      -PhD Kelvyn B. Sánchez kelvyn.baruc@gmail.com
 """ ->

function rk4(f, tspan, y0; h = 1)
tint = floor((tspan[end] - tspan[1])/h) + 1
t = linspace(tspan[1], tspan[end],tint)
y = zeros(Int(tint), length(y0))
y[1,:] = y0

      try
           error = f(t[1],y0)

            for i=1:1:(length(t) - 1)
                  ymid = zeros(1,Int(length(y0)))
                  k1 = zeros(1,Int(length(y0)))
                  k2 = zeros(1,Int(length(y0)))
                  k3 = zeros(1,Int(length(y0)))
                  k4 = zeros(1,Int(length(y0)))

                  for j=1:length(y0)
                        k1[1,j] = f(t[i],y[i,:])[j]
                        ymid[1,j] = y[i,j] + k1[1,j]*(h/2)
                  end

                  for j=1:length(y0)
                        k2[1,j] = f(t[i] + (1/2)*h,ymid)[j]
                        ymid[1,j] = y[i,j] + k2[1,j]*(h/2)
                  end

                  for j=1:length(y0)
                        k3[1,j] = f(t[i] + (1/2)*h,ymid)[j]
                        ymid[1,j] = y[i,j] + k3[1,j]*h
                  end

                  for j=1:length(y0)
                        k4[1,j] = f(t[i] + h,ymid)[j]
                  end

                  for j=1:length(y0)
                        y[i+1,j] = y[i,j] + (1/6)*(k1[1,j] + 2*(k2[1,j] + k3[1,j]) + k4[1,j])*h
                  end
            end

            return t, y
      catch
           throw(ErrorException("The number of initial values does not match the number of equations"))
      end

 end
