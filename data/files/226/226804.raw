@doc """
      Fifth-Order Runge-Kutta Method
      Supported by:
      -PhD Kelvyn B. Sánchez kelvyn.baruc@gmail.com
 """ ->

function rk5(f, tspan, y0; h = 1)
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
                  k5 = zeros(1,Int(length(y0)))
                  k6 = zeros(1,Int(length(y0)))

                  for j=1:length(y0)
                        k1[1,j] = f(t[i],y[i,:])[j]
                        ymid[1,j] = y[i,j] + k1[1,j]*(h/4)
                  end

                  for j=1:length(y0)
                        k2[1,j] = f(t[i] + (1/4)*h,ymid)[j]
                        ymid[1,j] = y[i,j] + k1[1,j]*(h/8) + k2[1,j]*(h/8)
                  end

                  for j=1:length(y0)
                        k3[1,j] = f(t[i] + (1/4)*h, ymid)[j]
                        ymid[1,j] = y[i,j] - k2[1,j]*(h/2) + k3[1,j]*h
                  end

                  for j=1:length(y0)
                        k4[1,j] = f(t[i] + (1/2)*h,ymid)[j]
                        ymid[1,j] = y[i,j] + k1[1,j]*h*(3/16) + k4[1,j]*h*(9/16)
                  end

                  for j=1:length(y0)
                        k5[1,j] = f(t[i] + (3/4)*h,ymid)[j]
                        ymid[1,j] = y[i,j] - k1[1,j]*h*(3/7) + k2[1,j]*h*(2/7) + k3[1,j]*h*(12/7) - k4[1,j]*h*(12/7) + (8/7)*k5[1,j]*h
                  end

                  for j=1:length(y0)
                        k6[1,j] = f(t[i] + h, ymid)[j]
                  end

                  for j=1:length(y0)
                        y[i+1,j] = y[i,j] + (1/90)*(7*k1[1,j] + 32*k3[1,j] + 12*k4[1,j] + 32*k5[1,j] + 7*k6[1,j])*h
                  end

            end

            return t, y
      catch
            throw(ErrorException("The number of initial values does not match the number of equations"))
      end

end
