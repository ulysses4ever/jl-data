immutable Partials{T,C}
    data::C
    Partials{N}(data::Vec{N,T}) = new(data)
end

typealias PartialsTup{N,T} Partials{T,Vec{N,T}}

Partials(data) = Partials{eltype(data),typeof(data)}(data)

##############################
# Utility/Accessor Functions #
##############################
@inline data(partials::Partials) = partials.data

@inline eltype{T,C}(::Type{Partials{T,C}}) = T
@inline eltype{T}(::Partials{T}) = T

@inline containtype{T,C}(::Type{Partials{T,C}}) = C
@inline containtype{T,C}(::Partials{T,C}) = C

@inline getindex(partials::Partials, i) = data(partials)[i]

@inline length(partials::Partials) = length(data(partials))

start(partials) = start(data(partials))
next(partials, i) = next(data(partials), i)
done(partials, i) = done(data(partials), i)

################
# Constructors #
################
@inline zero_partials{C<:Vec}(::Type{C}, n::Int) = Partials(zero_tuple(C))
zero_partials{T}(::Type{Vector{T}}, n) = Partials(zeros(T, n))

#####################
# Generic Functions #
#####################
function iszero{T}(partials::Partials{T})
    p = data(partials)
    return isempty(p) || (z = zero(T); all(x -> x == z, p))
end

==(a::Partials, b::Partials) = data(a) == data(b)
isequal(a::Partials, b::Partials) = isequal(data(a), data(b))

hash(partials::Partials) = hash(data(partials))
hash(partials::Partials, hsh::UInt64) = hash(hash(partials), hsh)

@inline copy(partials::Partials) = partials

##################
# Math Functions #
##################

# Addition/Subtraction #
#----------------------#
@inline function +{N,A,B}(a::PartialsTup{N,A}, b::PartialsTup{N,B})
    return Partials(add_tuples(data(a), data(b)))
end

@inline function -{N,A,B}(a::PartialsTup{N,A}, b::PartialsTup{N,B})
    return Partials(subtract_tuples(data(a), data(b)))
end


@inline -{N,T}(partials::PartialsTup{N,T}) = Partials(minus_tuple(data(partials)))

# Multiplication #
#----------------#
@inline function *{N,T}(partials::PartialsTup{N,T}, x::Number)
    return Partials(scale_tuple(data(partials), x))
end

@inline *(x::Number, partials::Partials) = partials*x

function _load_mul_partilas!(result::Vector, a, b, afactor, bfactor)
    @simd for i in eachindex(result)
        @inbounds result[i] = (afactor * a[i]) + (bfactor * b[i])
    end
    return result
end

@inline function _mul_partials{N,A,B}(a::PartialsTup{N,A}, b::PartialsTup{N,B}, afactor, bfactor)
    return Partials(mul_tuples(data(a), data(b), afactor, bfactor))
end

# Division #
#----------#
@inline function /{N,T}(partials::PartialsTup{N,T}, x::Number)
    return Partials(div_tuple_by_scalar(data(partials), x))
end


@inline function _div_partials(a::Partials, b::Partials, aval, bval)
    afactor = inv(bval)
    bfactor = -aval/(bval*bval)
    return _mul_partials(a, b, afactor, bfactor)
end

##################################
# Generated Functions on Vecs #
##################################
# The below functions are generally
# equivalent to directly mapping over
# tuples using `map`, but run a bit
# faster since they generate inline code
# that doesn't rely on closures.

function tupexpr(f,N)
    ex = Expr(:tuple, [f(i) for i=1:N]...)
    return quote
        @inbounds return $ex
    end
end

function zero_tuple{N,T}(tup::Type{Vec{N,T}})
    return SIMD.create(tup, zero(T))
end

@inline rand_tuple(::Type{Tuple{}}) = tuple()

function scale_tuple{N, T}(tup::Vec{N, T}, x)
    return x * tup
end

function div_tuple_by_scalar{N, T}(tup::Vec{N, T}, x)
    return tup / x
end

function minus_tuple{N}(tup::Vec{N})
    return -tup
end

function subtract_tuples{N}(a::Vec{N}, b::Vec{N})
    return b - a
end

function add_tuples{N}(a::Vec{N}, b::Vec{N})
    return a + b
end

function mul_tuples{N, T}(a::Vec{N, T}, b::Vec{N, T}, afactor, bfactor)
    return afactor * a + bfactor * b
end
