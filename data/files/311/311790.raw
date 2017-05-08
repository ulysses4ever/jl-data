if !isdefined(:fma)
  # TODO: Extend the definition to floating-point arrays
  for (T, t, i) in ((Float32, "float", "f32"), (Float64, "double", "f64"))
    @eval begin
      function fma(a::$T, b::$T, c::$T)
        Base.llvmcall($("""%4 = call $t @llvm.fma.$i($t %0, $t %1, $t %2)
                           ret $t %4"""), $T, ($T, $T, $T), a, b, c)
      end

      # HACK:
      # The next line is required due to the interplay of the current
      # implementation of llvmcall and LLVM intrinsics.
      try fma($T(1.0), $T(1.0), $T(1.0)); end
    end
  end
  @doc """
    Computes `a * b + c` using the fused multiply-add (FMA) operation. IEEE
    754-2008 states:

    > The operation `fusedMultiplyAdd(x, y, z)` computes `(x * y) + z` as if with
    > unbounded range and precision, rounding only once to the destination format.
    > No underflow, overflow, or inexact exception (see 7) can arise due to the
    > multiplication, but only due to the addition; and so fusedMultiplyAdd
    > differs from a multiplication operation followed by an addition operation.

    References:

      * IEEE 754-2008, IEEE Standard for Floating-Point Arithmetic, August 2008.
    """ -> fma
end


@doc """
  Computes the error-free fused multiply-add `a * b + c = x + y + z`, where
  `x = fl(fma(a, b, c))`. This algorithm requires 17 flops. Different from
  `err_fma_compr`, it is possible that `y` and `z` are overlapping.

  References:

    * S. Boldo, and J.M. Muller, Some functions computable with a fused-mac,
      Proceedings of the 17th Symposium on Computer Arithmetic, IEEE Computer
      Society Press, 2005.
    * S. Boldo, and J.M. Muller, Exact and approximated error of the FMA, IEEE
      Transactions on Computers 60, pp.157-164, 2011.
  """ ->
function err_fma{T<:IEEE754}(a::T, b::T, c::T)
  x = fma(a, b, c)
  p, q = err_fast_mul(a, b)
  s, z = err_add(c, q) # not necessary if |c| ≥ |a b| or |c| ≥ |p| (requires 6 flops)
  u, v = err_add(p, s)
  y = (u-x) + v
  x, y, z
end


@doc """
  Computes the error-free fused multiply-add `a * b + c = x + y + z`, where
  `x = fl(fma(a, b, c))` and `x`, `y`, `z` are non-overlapping. This algorithm
  requires 20 flops.

  References:

  * S. Boldo, and J.M. Muller, Some functions computable with a fused-mac,
  Proceedings of the 17th Symposium on Computer Arithmetic, IEEE Computer
  Society Press, 2005.
  * S. Boldo, and J.M. Muller, Exact and approximated error of the FMA, IEEE
  Transactions on Computers 60, pp.157-164, 2011.
  """ ->
function err_fma_compr{T<:IEEE754}(a::T, b::T, c::T)
  x = fma(a, b, c)
  p, q = err_fast_mul(a, b)
  s, t = err_add(c, q) # not necessary if |c| ≥ |a b| or |c| ≥ |p| (requires 6 flops)
  u, v = err_add(p, s)
  w = (u-x) + v
  y, z = err_fast_add(w, t) # compress floating-point errors (not necessary, requires 3 flops)
  x, y, z
end


@doc """
  Instead of accurately computing the error-free fused multiply-add as in
  `err_fma_compr`, return only one error term `y`: `|(a * b + c) - x - y| ≤
  ulp(y)/2`.

  References:

    * S. Boldo, and J.M. Muller, Exact and approximated error of the FMA, IEEE
      Transactions on Computers 60, pp.157-164, 2011.
  """ ->
function err_fma_nearest{T<:IEEE754}(a::T, b::T, c::T)
  x = fma(a, b, c)
  p, q = err_fast_mul(a, b)
  s, t = err_add(c, q) # not necessary if |c| ≥ |a b| or |c| ≥ |p| (requires 6 flops)
  u, v = err_add(p, s)
  y = ((u-x) + v) + t
  x, y
end


@doc """
  Instead of accurately computing the error-free fused multiply-add as in
  `err_fma`, return an approximated error term `y`: `|(a * b + c) - x - y| ≤
  14 * 2^-p * |x|`, where `p` is the precision of the floating-point type used.
  That is, following `x` there are at least `p - 2` correct bits in `x + y`.

  References:

    * S. Boldo, and J.M. Muller, Exact and approximated error of the FMA, IEEE
      Transactions on Computers 60, pp.157-164, 2011.
  """ ->
function err_fma_approx{T<:IEEE754}(a::T, b::T, c::T)
  x = fma(a, b, c)
  p, q = err_fast_mul(a, b)
  u, v = err_add(p, c)
  y = (u-x) + (q+v)
  x, y
end
