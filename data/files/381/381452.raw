immutable Partials{N,T} <: FixedSizeArrays.FixedVector{N,T}
    _::NTuple{N,T}
end

##############################
# Utility/Accessor Functions #
##############################

@inline numtype{N,T}(::Partials{N,T}) = T
@inline numtype{N,T}(::Type{Partials{N,T}}) = T

@inline npartials{N}(::Partials{N}) = N
@inline npartials{N,T}(::Type{Partials{N,T}}) = N

# setindex{N,T}(partials::Partials{N,T}, v, i) = Partials{N,T}((partials[1:i-1]..., v, partials[i+1:N]...))

#####################
# Generic Functions #
#####################

@inline iszero(partials::Partials) = iszero_tuple(partials._)

# Dear, Simon
#
#   What a lovely day, isn't it?
#
#   I'm writing today to beseech you to implement the following `rand` methods in
#   FixedSizeArrays.jl, which, as you know, is near and dear to my heart. Also, please
#   make more coffee.
#
# Your friend in battle,
# Jarrett
@inline Base.rand(partials::Partials) = rand(typeof(partials))
@inline Base.rand{N,T}(::Type{Partials{N,T}}) = Partials(rand_tuple(NTuple{N,T}))
@inline Base.rand(rng::AbstractRNG, partials::Partials) = rand(rng, typeof(partials))
@inline Base.rand{N,T}(rng::AbstractRNG, ::Type{Partials{N,T}}) = Partials(rand_tuple(rng, NTuple{N,T}))

const PARTIALS_HASH = hash(Partials)

Base.hash(partials::Partials) = hash(partials._, PARTIALS_HASH)
Base.hash(partials::Partials, hsh::UInt64) = hash(hash(partials), hsh)

@inline Base.copy(partials::Partials) = partials

Base.read{N,T}(io::IO, ::Type{Partials{N,T}}) = Partials(ntuple(i->read(io, T), Val{N}))

function Base.write(io::IO, partials::Partials)
    for p in partials
        write(io, p)
    end
end

########################
# Conversion/Promotion #
########################

Base.promote_rule{N,A,B}(::Type{Partials{N,A}}, ::Type{Partials{N,B}}) = Partials{N,promote_type(A, B)}

Base.convert{N,T}(::Type{Partials{N,T}}, partials::Partials) = Partials{N,T}(partials._)
Base.convert{N,T}(::Type{Partials{N,T}}, partials::Partials{N,T}) = partials

########################
# Arithmetic Functions #
########################
#
# @inline @operator(Base.:+){N}(a::Partials{N}, b::Partials{N}) = Partials(add_tuples(a._, b._))
# @inline @operator(Base.:-){N}(a::Partials{N}, b::Partials{N}) = Partials(sub_tuples(a._, b._))
# @inline @operator(Base.:-)(partials::Partials) = Partials(minus_tuple(partials._))
# @inline @operator(Base.:*)(partials::Partials, x::Real) = Partials(scale_tuple(partials._, x))
# @inline @operator(Base.:*)(x::Real, partials::Partials) = partials*x
# @inline @operator(Base.:/)(partials::Partials, x::Real) = Partials(div_tuple_by_scalar(partials._, x))

@inline function _mul_partials{N}(a::Partials{N}, b::Partials{N}, afactor, bfactor)
    return Partials(mul_tuples(a._, b._, afactor, bfactor))
end

@inline function _div_partials(a::Partials, b::Partials, aval, bval)
    afactor = inv(bval)
    bfactor = -aval/(bval*bval)
    return _mul_partials(a, b, afactor, bfactor)
end

##################################
# Generated Functions on NTuples #
##################################
# The below functions are generally
# equivalent to directly mapping over
# tuples using `map`, but run a bit
# faster since they generate inline code
# that doesn't rely on closures.

function tupexpr(f, N)
    ex = Expr(:tuple, [f(i) for i=1:N]...)
    return quote
        @inbounds return $(ex)
    end
end

@inline iszero_tuple(::Tuple{}) = true
@inline zero_tuple(::Type{Tuple{}}) = tuple()
@inline rand_tuple(::AbstractRNG, ::Type{Tuple{}}) = tuple()
@inline rand_tuple(::Type{Tuple{}}) = tuple()

for N in 1:MAX_CHUNK_SIZE
    ex = Expr(:&&, [:(z == tup[$i]) for i=1:N]...)
    @eval @inline iszero_tuple{T}(tup::NTuple{$N,T}) = (z = zero(T); @inbounds return $ex)

    ex = tupexpr(i -> :(z), N)
    @eval @inline zero_tuple{T}(::Type{NTuple{$N,T}}) = (z = zero(T); $ex)

    ex  = tupexpr(i -> :(rand(rng, T)), N)
    @eval @inline rand_tuple{T}(rng::AbstractRNG, ::Type{NTuple{$N,T}}) = $ex

    ex = tupexpr(i -> :(rand(T)), N)
    @eval @inline rand_tuple{T}(::Type{NTuple{$N,T}}) = $ex

    ex = tupexpr(i -> :(tup[$i] * x), N)
    @eval @inline scale_tuple(tup::NTuple{$N}, x) = $ex

    ex = tupexpr(i -> :(tup[$i] / x), N)
    @eval @inline div_tuple_by_scalar(tup::NTuple{$N}, x) = $ex

    ex = tupexpr(i -> :(a[$i]+b[$i]), N)
    @eval @inline add_tuples(a::NTuple{$N}, b::NTuple{$N}) = $ex

    ex = tupexpr(i -> :(a[$i]-b[$i]), N)
    @eval @inline sub_tuples(a::NTuple{$N}, b::NTuple{$N}) = $ex

    ex = tupexpr(i -> :(-tup[$i]), N)
    @eval @inline minus_tuple(tup::NTuple{$N}) = $ex

    ex = tupexpr(i -> :((afactor * a[$i]) + (bfactor * b[$i])), N)
    @eval @inline mul_tuples(a::NTuple{$N}, b::NTuple{$N}, afactor, bfactor) = $ex
end

###################
# Pretty Printing #
###################

Base.show{N}(io::IO, p::Partials{N}) = print(io, "Partials", p._)
