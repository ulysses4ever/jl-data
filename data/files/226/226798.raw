function rk5(f, tspan, y0; h = 1)
# Runge Kutta 5th order
t = floor((tspan[end] - tspan[1])/h)
y = zeros(Int64(t) + 1, length(y0))
y[1,:] = y0
j = 1

for i=tspan[1]:h:(tspan[end]-h)
      for g=1:1:length(y0)
            k1 = f(i,y[j,:])[g]
            k2 = f(i + (1/4)*h,y[j,:] + (1/4)*k1*h)[g]
            k3 = f(i + (1/4)*h,y[j,:] + (1/8)*k1*h + (1/8)*k2*h)[g]
            k4 = f(i + (1/2)*h,y[j,:] - (1/2)*k2*h + k3*h)[g]
            k5 = f(i + (3/4)*h,y[j,:] + (3/16)*k1*h + (9/16)*k4*h)[g]
            k6 = f(i + h,y[j,:] - (3/7)*k1*h + (2/7)*k2*h + (12/7)*k3*h - (12/7)*k4*h + (8/7)*k5*h)[g]
            y[j+1,g] = y[j,g] + (1/90)*(7*k1 + 32*k3 + 12*k4 + 32*k5 + 7*k6)*h
      end
      j += 1
end

return tspan[1]:h:tspan[end], y
end
