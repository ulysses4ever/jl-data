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
