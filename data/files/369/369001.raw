@doc """
  Computes the error-free addition `a + b = x + y`, where `x = fl(a + b)`, for
  general floating-point numbers `a` and `b`. The algorithm requires 6 flops;
  twice as many as `err_fast_add`. However, failed branch prediction because of
  the required comparison `|a| ≥ |b|` in the general case, cause this algorithm
  to be faster on modern pipelined architectures.

  References:

    * D.E. Knuth, The Art of Computer Programming, 3rd ed., vol. 2,
      Addison-Wesley, 1998.
    * D. Møller, Quasi double-precision in floating-point addition, BIT
      Numerical Mathematics 5, pp. 37–50, 1965.
""" ->
# TODO: Extend the definition to floating-point arrays
function err_add{T<:IEEE754}(a::T, b::T)
  x = a + b
  c = x - a
  y = (a - (x-c)) + (b-c)
  x, y
end


@doc """
  Computes the error-free addition `a + b = x + y`, where `x = fl(a + b)`, for
  floating-point numbers `a` and `b` such that the exponent of `a` is larger
  than or equal to that of `b`. If `|a| ≥ |b|`, this condition is always
  satisfied. The algorithm requires 3 flops.

  References:

    * T.J. Dekker, A floating-point technique for extending the available
      precision, Numerische Mathematik 18, pp. 224–242, 1971.
  """ ->
# TODO: Extend the definition to floating-point arrays
function err_fast_add{T<:IEEE754}(a::T, b::T)
  x = a + b
  y = b - (x-a)
  x, y
end
