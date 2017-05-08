@doc """
      Euler Method
      Supported by:
      -PhD Kelvyn B. Sánchez kelvyn.baruc@gmail.com
 """ ->
function euler(f, tspan, y0; h = 1)
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

for i=1:n-1 # Solve for each x
      for j=1:eq # Solve for each equation in f
            y1 = f(t[i],y[i,:])
            y[i+1,j] = y[i,j] +  y1[j] * (t[i+1] - t[i])

      end
end
return t, y
end
