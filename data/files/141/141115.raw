module JuliaSet

export GenerateJuliaSet

# package code goes here

# Populates a matrix A with the values to construct a Julia set image
function GenerateJuliaSet(R::Function, x::Array{Float64,1}, y::Array{Float64,1}, n_iter::Int64 = 200, escape_tol::Real = 2)

	nx = length(x)
	ny = length(y)
	A = zeros(nx, ny)
	for i in 1:nx
		for j in 1:ny
			z = x[i] + im * y[j]
			for k in 1:n_iter
				z = R(z)
				if (abs(z) > escape_tol)
					A[i,j] = k
				end
			end
			if A[i,j] == 0
				A[i,j] = n_iter + 1
			end
		end
	end
	
	return A
end

end # module
