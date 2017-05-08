
@doc """
      Fifth-Order Runge-Kutta Method
      Supported by:
      -PhD Kelvyn B. Sánchez kelvyn.baruc@gmail.com
      -MSc Lorena S. Galicia lorys92@gmail.com
 """ ->

function rk5(f, tspan, y0; h = 1)
tint = floor((tspan[end] - tspan[1])/h) + 1
t = linspace(tspan[1], tspan[end],tint)
y = zeros(Int(tint), length(y0))
y[1,:] = y0

      # try
      #       error = f(t[1],y0)

            for i=1:1:(length(t) - 1)
                        k1 = f(t[i],y[i,:])
                        k2 = f(t[i] + (1/4)*h,y[i,:]' + (1/4)*k1*h)
                        k3 = f(t[i] + (1/4)*h,y[i,:]' + (1/8)*k1*h + (1/8)*k2*h)
                        k4 = f(t[i] + (1/2)*h,y[i,:]' - (1/2)*k2*h + k3*h)
                        k5 = f(t[i] + (3/4)*h,y[i,:]' + (3/16)*k1*h + (9/16)*k4*h)
                        k6 = f(t[i] + h,y[i,:]' - (3/7)*k1*h + (2/7)*k2*h + (12/7)*k3*h - (12/7)*k4*h + (8/7)*k5*h)
                        y[i+1,:] = y[i,:]' + (1/90)*(7*k1 + 32*k3 + 12*k4 + 32*k5 + 7*k6)*h
            end

             t, y;
      # catch
      #       throw(ErrorException("The number of initial values does not match the number of equations"))
      # end

end
