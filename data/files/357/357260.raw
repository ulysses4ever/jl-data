module julia_sets
using PyPlot
export gen_jset,show_jset

function gen_jset{T<:Real,U<:Real}(R::Function,x::Array{T,1},y::Array{T,1},n_iter::Int64,escape_tol::U)
  
  A = zeros(length(x),length(y));
  for i=1:length(x)
    for j=1:length(y)
      z = Complex(x[i],y[j])
      for k = 1:n_iter
        z = R(z)
        if abs(z) > escape_tol
          A[i,j] = k
          break;
        end
      end
      if A[i,j]==0
        A[i,j] = escape_tol+1;
        end
    end
  end
  
  return A
end

function show_jset{T<:Real}(A::Array{T,2})
 matshow(A)
end

end


