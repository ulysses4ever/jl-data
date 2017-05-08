@doc """
      Heun's Method (with iteration)
      Supported by:
      -PhD Kelvyn B. Sánchez kelvyn.baruc@gmail.com
 """ ->
function heun(f, tspan, y0; h = 1, AbsTol = 0.00001)

t = tspan[1]:h:tspan[end]
n = length(t)

      if t[n] < tspan[end]
            t = [t, tspan[end]]
            n += 1
      end

y1 = f(t[1],y0)
eq = length(y1) # Test the number of equations in f
y = zeros(Int(n),eq)
y[1,:] = y0
y1 = zeros(Int(n),eq)
y2 = zeros(Int(n),eq)
y3 = zeros(Int(n),eq)

	for i=1:n-1 # Solve for each x
            for j=1:eq # Solve for each equation in f
                  s1 = f(t[i],y[i,:])
                  y1[i,j] = y[i,j] + s1[j] * (t[i+1] - t[i])

                  s2 = f(t[i+1],y1[i,:])
                  y2[i,j] = y[i,j] + ((s1[j] + s2[j])/2) * (t[i+1] - t[i])

                  err = 100
                  while err >= AbsTol
                        s1 = f(t[i],y[i,:])
                        s2 = f(t[i+1],y2[i,:])
                        y3[i,j] = y[i,j] + ((s1[j] + s2[j]) / 2) * (t[i+1] - t[i])
                        err = abs((y3[i,j] - y2[i,j])/y3[i,j]) * 100
                        y2[i,j] = y3[i,j]
                        y[i+1,j] = y3[i,j]
                  end
            end
	end
	return t, y
end
