function derivative(f)
	return function(x)
		#= shenanigans de ponto flutuante
			Teoricamente é
			h = 0.0001
			return (f(x + h) - f(x)) / h
		=#
		h = x == 0 ? sqrt(eps(Float64)) : sqrt(eps(Float64))*x
		xph = x + h
		dx = xph - x

		return (f(xph) - f(x)) / dx
	end
end