function heun(f, tspan, y0; h = 1, AbsTol = 0.00001)
# Euler method
# Made by PhD Kelvyn Baruc SS
# Steven C. Chapra, Applied Numerical Method with MATLAB® for Engineers and Scientists
# Third Edition, 2008

t = tspan[1]:h:tspan[end]
n = length(t)

      if t[n] < tspan[end]
            t = [t, tspan[end]]
            n += 1
      end

x, y1 = f(t[1],y0)
eq = length(y1) # Test the number of equations in f
y = ones(int64(n),eq) .* y0'
y1 = zeros(int64(n),eq)
y2 = zeros(int64(n),eq)
y3 = zeros(int64(n),eq)

	for i=1:n-1 # Solve for each x
            for j=1:eq # Solve for each equation in f
                  x1, s1 = f(t[i],y[i,:])
                  y1[i,j] = y[i,j] + s1[j] * (t[i+1] - t[i])

                  x2, s2 = f(t[i+1],y1[i,:])
                  y2[i,j] = y[i,j] + ((s1[j] + s2[j])/2) * (t[i+1] - t[i])

                  err = 100
                  while err >= AbsTol
                        x1, s1 = f(t[i],y[i,:])
                        x1, s2 = f(t[i+1],y2[i,:])
                        y3[i,j] = y[i,j] + ((s1[j] + s2[j]) / 2) * (t[i+1] - t[i])
                        err = abs((y3[i,j] - y2[i,j])/y3[i,j]) * 100
                        y2[i,j] = y3[i,j]
                        y[i+1,j] = y3[i,j]
                  end
            end
	end
	return t, y
end
