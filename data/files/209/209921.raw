
# Possible monotonicities for elementwise functions:
signed = (frow, fcol, vnum, vrow, vcol) -> :signed
incr = (frow, fcol, vnum, vrow, vcol) -> :incr
decr = (frow, fcol, vnum, vrow, vcol) -> :decr

macro elementwise(expr, curvature, monotonicity, func)
    quote
        (rows, cols) = size($expr)
        args = [CvxArg(rows, cols)]
        func = CvxFunction(rows, cols, fill($curvature, (rows, cols)),
                           args, $monotonicity, $func)
        return Composition(func, [$expr])
    end
end

square(expr :: CvxExpr) =
    @elementwise(expr, :convex, signed, x -> x * x)

sqrt(expr :: CvxExpr) =
    @elementwise(expr, :concave, incr, x -> Base.sqrt(x))

log(expr :: CvxExpr) =
    @elementwise(expr, :concave, incr, x -> Base.log(x))

exp(expr :: CvxExpr) =
    @elementwise(expr, :convex, incr, x -> Base.exp(x))

abs(expr :: CvxExpr) =
    @elementwise(expr, :convex, signed, x -> Base.abs(x))


norm(expr :: CvxExpr) = begin
    (m, n) = size(expr)
    args = [CvxArg(m, n)]
    func = CvxFunction(1, 1, fill(:convex, (1,1)), args,
                       signed, X -> Base.norm(X))
    return Composition(func, [expr])
end
