module cv_geom

# package code goes here

function hom(A)
  sz = size(A)
  o = ones(eltype(A), tuple(1, sz[2:end]...))
  return cat(1, A, o)
end

function ihom{T<:Number}(A::Array{T, 1})
  return A[1:end-1] / A[end]
end

function ihom{T<:Number}(A::Array{T, 2})
  return A[1:end-1,:] ./ A[end, :]
end

end
  # module
