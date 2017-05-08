module JuliaSetPkg

export juliaSet

function juliaSet{T<:Number}(R::Function, x::Array{T}, y::Array{T}, n_iter = 200, escape_tol=1e6)
    A = zeros(length(x), length(y))
    for i in 1:length(x)
      for j in 1:length(y)
        z = x[i] + im * y[j]
        for k in 1:n_iter
          z = R(z)
          if abs(z) > escape_tol # diverged
            A[i,j] = k
            break
          end
        end
        if A[i,j] == 0 # didn't diverge
            A[i,j] = n_iter + 1
        end
      end
    end
    return A
end

end # module
