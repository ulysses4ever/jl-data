"""
Dec.jl -- wrapper for decNumber library

Copyright (c) 2015 Gandalf Software, Inc. (Scott P. Jones)

This software is made available under the terms of the
MIT license.

Portions of this wrapper are derived from the decNumber C Library,
which is available under the ICU license.
See DecTypes.jl for more information
"""
module Dec

const libdec = symbol(joinpath(dirname(@__FILE__), "..", "deps", "libDecNumber"))

include("DecTypes.jl")
include("Contexts.jl")
include("Numbers.jl")

export ToEng, dec32, dec64, dec128, @dec32_str, @dec64_str, @dec128_str

# Extend various Base functions for Decimal Numbers

import Base: convert, promote_rule

const global _context32 = Default(32)
const global _context64 = Default(64)
const global _context128 = Default(128)

_defaultcontext(::Type{Single})    = _context32
_defaultcontext(::Type{Double})    = _context64
_defaultcontext(::Type{Quad})      = _context128

"""Parse a DecimalNumber from the given string"""
Base.parse{T<:DecimalNumber}(::Type{T}, str::AbstractString) =
    T(FromString(_result(T), ascii(str), _defaultcontext(T))[])

"""Convert a DecimalNumber to string in Scientific notation"""
convert{T<:DecimalNumber}(::Type{ASCIIString}, v::T) =
    (_arg1(T)[] = v; ascii(ToString(_arg1(T), Vector{UInt8}(decString(T)))))

"""Convert a DecimalNumber to string in Engineering notation"""
ToEng{T<:DecimalNumber}(v::T) =
    (_arg1(T)[] = v; ascii(ToEngString(_arg1(T), Vector{UInt8}(decString(T)))))

Base.show{T<:DecimalNumber}(io::IO, v::T) = write(io, ToEng(v))

Base.dump{T<:DecimalNumber}(df::T) = (_arg1(T)[] = df ; Show(_arg1(T)))

Base.zero{T<:DFTypes}(::Type{T}) = reinterpret(T, Zero(T))

Base.isnan{T<:DecimalNumber}(x::T) = IsNan(dn)
Base.isinf{T<:DecimalNumber}(x::T) = IsInfinite(dn)

Base.nextfloat{T<:DecimalNumber}(x::T) =
    (_arg1(T)[] = x ; NextPlus(_result(T), _arg1(T), _defaultcontext(T))[])
Base.prevfloat{T<:DecimalNumber}(x::T) =
    (_arg1(T)[] = x ; NextMinus(_result(T), _arg1(T), _defaultcontext(T))[])

# clear exception flags and return c
nox(dc::Context) = ZeroStatus(c)

# check exception flags in mask & throw, otherwise returning x;
# always clearing exceptions
const _allflags = (Inexact | Overflow | Underflow | Subnormal |
                   Invalid_operation | Division_by_zero)
function chkflags(dc::Context, mask::Integer = _allflags)
    s = dc.status
    dc.status = 0
    mask &= s
    if mask != 0
        mask & Inexact != 0 && throw(InexactError())
        mask & Overflow != 0 && throw(OverflowError())
        mask & Division_by_zero != 0 && throw(DivideError())
        mask & Invalid_operation != 0 && throw(DomainError())
        mask & Underflow != 0 && error("underflow")
        mask & Subnormal != 0 && error("unnormal")
    end
    return s
end

# Set up short, exportable names
# Note: Dec32, Dec64, Dec128 are already used by DecFP package
dec32  = Single
dec64  = Double
dec128 = Quad

for typ in (:Single, :Double, :Quad)
    ref = @eval Ref{$typ}

    @eval const global $(symbol("_result",typ)) = $ref()
    @eval const global $(symbol("_arg1",typ))   = $ref()
    @eval const global $(symbol("_arg2",typ))   = $ref()
    @eval const global $(symbol("_arg3",typ))   = $ref()

    @eval _result(::Type{$typ}) = $(symbol("_result",typ))
    @eval _arg1(::Type{$typ})   = $(symbol("_arg1",typ))
    @eval _arg2(::Type{$typ})   = $(symbol("_arg2",typ))
    @eval _arg3(::Type{$typ})   = $(symbol("_arg3",typ))

    """Constructor from string"""
    @eval $typ(str::AbstractString) = parse($typ, str)
end

#=
for w in (32,64,128)
    BID = symbol(string("dec",w))
    T = eval(BID)
    Ti = eval(symbol(string("UInt",w)))

    for Tf in (Float32,Float64)
        @eval convert(::Type{$Tf}, x::$BID) = parse($Tf, string(x))
        @eval convert(::Type{$BID}, x::$Tf) = parse($T,  string(x))
    end

    @eval Base.one(::Type{$T})     = $(parse(T, "1"))
    @eval Base.typemax(::Type{$T}) = $(parse(T, "+inf"))
    @eval Base.typemin(::Type{$T}) = $(parse(T, "-inf"))

    if w != 32
        @eval convert(::Type{$T}, x::Union{Int8,Int16,Int32}) = FromInt32(_result(T), x)[]
        @eval convert(::Type{$T}, x::Union{UInt8,UInt16,UInt32}) = FromUInt32(_result(T), x)[]

        @eval Base.realmax(::Type{$T}) = $(prevfloat(parse(T, "+inf")))
        @eval Base.realmin(::Type{$T}) = $(nextfloat(zero(T)))
        @eval Base.eps(::Type{$T})     =
            $(_arg1(T) = nextfloat(one(T)) ; _arg2(T) = one(T) ;
              Subtract(_result(T), _arg1(T), _arg2(T), _defaultcontext(T))[])
    end

    for w′ in (32,64,128)
        BID′ = symbol(string("D",w′))
        w > w′ && @eval promote_rule(::Type{$BID}, ::Type{$BID′}) = $BID

        # promote binary*decimal -> decimal, for consistency with other operations above
        # (there doesn't seem to be any clear standard for this)
        if w′ <= 64
            FP′ = symbol(string("Float",w′))
            @eval promote_rule(::Type{$BID}, ::Type{$FP′}) = $(symbol(string("D",max(w,w′))))
            for i′ in ("Int$w′", "UInt$w′")
                Ti′ = eval(symbol(i′))
                @eval convert(::Type{$BID}, x::$Ti′) = parse($T, string(x))
            end
        end
    end
    #=
    @eval convert{T<:DecimalNumber}(::Type{T}, x::$T) =
        (_arg1($T)[] = x ; ToNumber(_result(DecimalNUmber), _arg1($T))[])
    @eval convert{T<:DecimalNumber}(::Type{$BID}, x::T) =
        (_arg1(T)[] = x ; FromNumber(_result($T), _arg1(T))[])

    for w′ in (8,16,32,64)
        for i′ in ("Int$w′", "UInt$w′")
            Ti′ = eval(symbol(i′))
            @eval begin
                Base.floor(::Type{$Ti′}, x::$BID) = 
                Base.ceil(::Type{$Ti′}, x::$BID) = 
                Base.convert(::Type{$Ti′}, x::$BID) = 
            end
        end
    end
    =#
end
=#

convert{F<:DecimalNumber}(::Type{Float16}, x::F) = convert(Float16, convert(Float32, x))
convert{F<:DecimalNumber}(T::Type{F}, x::Float16) = F(Float32(x))

convert(::Type{dec32}, x::dec64) =
    (_arg1(dec64)[] = x ; FromWider(_result(dec32), _arg1(dec64), _defaultcontext(dec32))[])
convert(::Type{dec64}, x::dec128) =
    (_arg1(dec128)[] = x ; FromWider(_result(dec64), _arg1(dec128), _defaultcontext(dec64))[])
convert(::Type{dec32}, x::dec128) = convert(dec32, convert(dec64, x))

convert(::Type{dec64}, x::dec32) =
    (_arg1(dec32)[] = x ; ToWider(_result(dec64), _arg1(dec32), _defaultcontext(dec64))[])
convert(::Type{dec128}, x::dec64) =
    (_arg1(dec64)[] = x ; ToWider(_result(dec128), _arg1(dec64), _defaultcontext(dec128))[])
convert(::Type{dec128}, x::dec32) = convert(dec128, convert(dec64, x))

promote_rule{F<:DecimalNumber}(::Type{F}, ::Type{Float16}) = F
promote_rule{F<:DecimalNumber,T<:Base.Integer64}(::Type{F}, ::Type{T}) = F

# so that mathconsts get promoted to dec32, not dec64, like Float32
promote_rule{s,F<:DecimalNumber}(::Type{Irrational{s}}, ::Type{F}) = F
promote_rule{s,F<:DecimalNumber}(::Type{Irrational{s}}, T::Type{Complex{F}}) = T

# Set up string macros, to be able to do decimal literals, i.e. dec64"1.5e-100"
macro dec32_str(s, flags...)  parse(dec32, s) end
macro dec64_str(s, flags...)  parse(dec64, s) end
macro dec128_str(s, flags...) parse(dec128, s) end

## Set up the operators to call the appropriate functions for each subtype T of DecimalNumber ##

# The ref(T) expressions give a place to hold the values, because the decNumber library
# requires passing decNumbers by reference, instead of by value
# The base operator is extended in each case
# _result(T) holds the returned value
# _arg1(T)   holds the first argument
# _arg2(T)   holds the second argument (if any)
# _arg3(T)   holds the third argument (for fma)
# _defaultcontext(T) holds the context for that particular DecimalNumber type

import Base: +,-,*,/,%,div,&,|,$,fma,abs,min,max,==,<,>,<=,>=

# Set up Unary operators
for (operator, funct) in ((:+, :Plus), (:-, :Minus), (:abs, :Abs))
    @eval begin
        function Base.$operator{T<:DecimalNumber}(df::T)
            _arg1(T)[] = df	# set up argument to be passed by reference
            # Call function, which returns a reference to the result, and dereference it
            $funct(_result(T), _arg1(T), _defaultcontext(T))[]
        end
    end
end

# Set up Binary operators
for (operator, funct) in ((:+, :Add), (:-, :Subtract), (:*, :Multiply), (:/, :Divide),
                          (:%, :Remainder), (:div, :DivideInteger),
                          (:&, :And), (:|, :Or), (:$, :Xor),
                          (:min, :Min), (:max, :Max))
    @eval begin
        function Base.$operator{T<:DecimalNumber}(x::T, y::T)
            _arg1(T)[] = x # set up 1st argument to be passed by reference
            _arg2(T)[] = y # set up 2nd argument to be passed by reference
            # Call function, which returns a reference to the result, and dereference it
            $funct(_result(T), _arg1(T), _arg2(T), _defaultcontext(T))[]
        end
    end
end

# Comparison operators
for operator in (:(<), :(>), :(==), :(>=), :(<=))
    @eval begin
        function $operator{T<:DecimalNumber}(x::T, y::T)
            _arg1(T)[] = x # set up 1st argument to be passed by reference
            _arg2(T)[] = y # set up 2nd argument to be passed by reference
            $operator(Compare(_result(T), _arg1(T), _arg2(T), _defaultcontext(T))[], 0)
        end
    end
end

# floating point multiply and add (x*y + z)
function fma{T<:DecimalNumber}(x::T, y::T, z::T)
    _arg1(T)[] = x # set up 1st argument to be passed by reference
    _arg2(T)[] = y # set up 2nd argument to be passed by reference
    _arg3(T)[] = z # set up 3rd argument to be passed by reference
    FMA(_result(T), _arg1(T), _arg2(T), _arg3(T), _defaultcontext(T))[]
end

# Set up checked operators
for (operator, funct) in ((:checked_add, :Add),
                          (:checked_sub, :Subtract),
                          (:checked_mul, :Multiply))
    @eval begin
        function Base.$operator{T<:DecimalNumber}(df::T)
            dc = _defaultcontext(T)
            dc.status = 0
            _arg1(T)[] = df	# set up argument to be passed by reference
            # Call function, which returns a reference to the result, and dereference it
            $funct(_result(T), _arg1(T), dc)
            checkflags(dc)
            _result(T)[]
        end
    end
end

end
