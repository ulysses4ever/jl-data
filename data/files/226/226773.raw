
@doc """
       Fourth-Order Runge-Kutta Method
       Supported by:
       -PhD Kelvyn B. Sánchez kelvyn.baruc@gmail.com
       -MSc Lorena S. Galicia lorys92@gmail.com
 """ ->

function rk4(f, tspan, y0; h = 1)
tint = floor((tspan[end] - tspan[1])/h) + 1
t = linspace(tspan[1], tspan[end],tint)
y = zeros(Int(tint), length(y0))
y[1,:] = y0

      # try
      #       error = f(t[1],y0)

            for i=1:1:(length(t) - 1)
                  k1 = f(t[i],y[i,:])
                  k2 = f(t[i] + (1/2)*h,y[i,:]' + (1/2)*k1*h)
                  k3 = f(t[i] + (1/2)*h,y[i,:]' + (1/2)*k2*h)
                  k4 = f(t[i] + h,y[i,:]' + k3*h)
                  y[i+1,:] = y[i,:]' + (1/6)*(k1 + 2*k2 + 2*k3 + k4)*h
            end

            return t, y
      #  catch
      #       throw(ErrorException("The number of initial values does not match the number of equations"))
      #  end

end
