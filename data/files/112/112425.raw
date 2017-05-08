module cv_geom

# package code goes here

function hom(A)
  sz = size(A)
  o = ones(eltype(A), tuple(1, sz[2:end]...))
  return cat(1, A, o)
end

function ihom(A)
  if ndims(A) == 1
    ret = A[1:end-1] / A[end]
  else
    ret = A[1:end-1,:] ./ A[end, :]
  end
  return ret
end

end
  # module
