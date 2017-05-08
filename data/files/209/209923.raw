# A CvxExpr is a multivariate expression.

abstract CvxExpr

type Var <: CvxExpr
    rows :: Int # number of rows
    cols :: Int # number of columns
    name :: String # identifier
end

Var(rows :: Int, name :: String) = Var(rows, 1, name)

curvature(expr :: Var) = fill(:affine, size(expr))
size(expr :: Var) = (expr.rows, expr.cols)
evaluate(expr :: Var, context :: Dict{ASCIIString, Float64}) =
    context[expr.name]


type CvxSum <: CvxExpr
    first :: CvxExpr
    second :: CvxExpr
end

+(first :: CvxExpr, second :: CvxExpr) = begin
    if size(first) != size(second)
        throw(ArgumentError("+: Dimensions do not match"))
    end
    return CvxSum(first, second)
end

curvature(expr :: CvxSum) = begin
    (m, n) = size(expr.first)
    result = Array(Symbol, (m, n))
    first = curvature(expr.first)
    second = curvature(expr.second)
    for i = 1:m
        for j = 1:n
            result[i, j] = plus(first[i,j], second[i,j])
        end
    end
    return result
end

size(expr :: CvxSum) = size(expr.first)

evaluate(expr :: CvxSum, context :: Dict{ASCIIString, Float64}) =
    evaluate(expr.first, context) .+ evaluate(expr.second, context)

type CvxConst <: CvxExpr
    value :: Array{Float64, 2}
end

size(expr :: CvxConst) = Base.size(expr.value)
curvature(expr :: CvxConst) = fill(:affine, size(expr))
evaluate(expr :: CvxConst, context :: Dict{ASCIIString, Float64}) = expr.value

+(first :: Real, second :: CvxExpr) = begin
    (rows, cols) = size(second)
    return CvxConst(fill(float(first), (rows, cols))) + second
end

+(first :: CvxExpr, second :: Real) = second + first

type CvxProd <: CvxExpr
    first :: Array{Float64, 2}
    second :: CvxExpr
end

curvature(expr :: CvxProd) = begin
    result = fill(:unknown, size(expr))
    scalar = expr.first
    curv = curvature(expr.second)
    for i = 1:Base.size(scalar, 1)
        for j = 1:Base.size(scalar, 2)
            result[i, j] = multiply(scalar[i,j], curv[i,j])
        end
    end
    return result
end

size(expr :: CvxProd) = size(expr.second)

.*(first :: Array{Float64, 2}, second :: CvxExpr) = begin
    if Base.size(first) != size(second)
        throw(ArgumentError(".*: Dimensions do not match"))
    end
    CvxProd(first, second)
end

.*(first :: CvxExpr, second :: Array{Float64, 2}) = second .* first

*(first :: Real, second :: CvxExpr) = first * ones(size(second)) .* second
*(first :: CvxExpr, second :: Real) = second * first

type CvxNeg <: CvxExpr
    expr :: CvxExpr
end

size(expr :: CvxNeg) = size(expr.expr)

curvature(expr :: CvxNeg) = map(negative, curvature(expr.expr))

evaluate(expr :: CvxNeg, context :: Dict{ASCIIString, Float64}) =
    -evaluate(expr, context)

-(expr :: CvxExpr) = CvxNeg(expr)

type CvxArg
    rows :: Int
    cols :: Int
end

# This is a function from R^{a_1\times b_1} \times \dots \time
# \R^{a_s\times b_s} to R^{m\times n}
type CvxFunction <: CvxExpr
    rows :: Int
    cols :: Int
    default_curvature :: Array{Symbol, 2}
    args :: Array{CvxArg}
    monotonicity :: Function
    func :: Function
end

size(expr :: CvxFunction) = (expr.rows, expr.cols)

type CvxComposition{E<:CvxExpr} <: CvxExpr
    func :: CvxFunction
    args :: Array{E}
end

size(expr :: CvxComposition) = size(expr.func)

Composition{E<:CvxExpr}(func :: CvxFunction, args :: Array{E}) = begin
    if length(func.args) != length(args)
        throw(ArgumentError("Composition: Number of arguments does not match"))
    end
    return CvxComposition(func, args)
end

# This implements C1--C3 and C4--C6 from the disciplined ruleset. The
# flag indicates if we want to check for convexity of concavity.
composition{E<:CvxExpr}(func :: CvxFunction, func_row :: Int, func_col :: Int,
                        var_num :: Int, arg :: E, flag :: Symbol) =
begin
    result = false
    (m, n) = size(arg)
    for i = 1:m
        for j = 1:n
            if curvature(arg)[i,j] == :affine
                result = true
            end
            monoton = func.monotonicity(func_row, func_col, var_num, i, j)
            if monoton == :incr && curvature(arg)[i, j] == flag
                result = true
            end
            if monoton == :decr && curvature(arg)[i, j] == flag
                result = true
            end
        end
    end
    return result
end

curvature(expr :: CvxComposition) = begin
    (rows, cols) = size(expr.func)
    result = Array(Symbol, (rows, cols))
    for row = 1:rows
        for col = 1:cols
            curv = expr.func.default_curvature[row, col]
            for i = 1:length(expr.args)
                if composition(expr.func, row, col, i, expr.args[i], curv)
                    result[row, col] = curv
                else
                    result[row, col] = :unknown
                end
            end
        end
    end
    return result
end

# Fix this
evaluate(expr :: CvxComposition, context :: Dict{ASCIIString, Float64}) =
    expr.func.func(evaluate(expr.args[1], context))

type CvxVStack
    list :: Array{Var}
end

VStack(list...) = begin
    if length(list) < 1
        throw(ArgumentError("vstack: Empty stack not allowed"))
    end
    (rows, cols) = size(list[1])
    result = Array(Var, 0)
    for e = list
        if size(e)[1] != rows
            throw(ArgumentError("vstack: Vars must have same number of rows"))
        end
        push!(result, e)
    end
    return CvxVStack(result)
end

size(expr :: CvxVStack) = begin
    (rows, cols) = size(expr.list[1])
    return (rows, sum(map(x -> size(x)[2], expr.list)))
end
