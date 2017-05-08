function rk4(f, tspan, y0; h = 1, iter = false)
#Runge Kutta 5th order
t = floor((tspan[end] - tspan[1])/h)
y = zeros(int64(t) + 1,1)
y[1,1] = y0
j = 1

for i=tspan[1]:h:(tspan[end]-h)
      k1 = f(i,y[j,1])
      k2 = f(i + (1/4)*h,y[j,1] + (1/4)*k1*h)
      k3 = f(i + (1/4)*h,y[j,1] + (1/8)*k1*h + (1/8)*k2*h)
      k4 = f(i + (1/2)*h,y[j,1] - (1/2)*k2*h + k3*h)
      k5 = f(i + (3/4)*h,y[j,1] + (3/16)*k1*h + (9/16)*k4*h)
      k6 = f(i + h,y[j,1] - (3/7)*k1*h + (2/7)*k2*h + (12/7)*k3*h - (12/7)*k4*h + (8/7)*k5*h)
      y[j+1,1] = y[j,1] + (1/90)*(7*k1 + 32*k3 + 12*k4 + 32*k5 + 7*k6)*h

      if iter == true
            if j == 1
                  println("Iter\t\t X\t\t\t Y")
                  @printf("%i\t\t %f\t\t %f\n",0,i,y[1,1])
                  @printf("%i\t\t %f\t\t %f\n",j,i+h,y[j+1,1])
            else
                  @printf("%i\t\t %2f\t\t %f\n",j,i+h,y[j+1,1])
            end
      end
      j += 1
end
return y, tspan[1]:h:tspan[end]
end
