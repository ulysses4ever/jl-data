module ErrorFreeTransforms

typealias IEEE754 Union(Float32, Float64)

include("add.jl")
include("mul.jl")
include("fma.jl")

export
  # add.jl
  err_add,
  err_fast_add,

  # mul.jl
  fsplit,
  err_mul,
  err_fast_mul,

  # fma.jl
  err_fma,
  err_fma_compr,
  err_fma_nearest,
  err_fma_approx

end
