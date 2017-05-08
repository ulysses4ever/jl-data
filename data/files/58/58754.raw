"""
Numbers.jl -- Decimal 32/64/128-bit formats

Julia conversion of decNumber package, portions are:
Copyright (c) Gandalf Software, Inc. 2015

Made available under the same terms as decNumber, i.e.
ICU License -- ICU 1.8.1 and later.

Any Julia specific issues please send to Scott Jones:
  scottjones@alum.mit.edu

Derived from decNumber package, decSingle.h, decDouble.h, decQuad.h
------------------------------------------------------------------
Copyright (c) IBM Corporation, 2000, 2010.  All rights reserved.

This software is made available under the terms of the
ICU License -- ICU 1.8.1 and later.

The description and User's Guide ("The decNumber C Library") for
this software is included in the package as decNumber.pdf.  This
document is also available in HTML, together with specifications,
testcases, and Web links, on the General Decimal Arithmetic page.

Please send comments, suggestions, and corrections to the author:
  mfc@uk.ibm.com
  Mike Cowlishaw, IBM Fellow
  IBM UK, PO Box 31, Birmingham Road, Warwick CV34 5JL, UK
------------------------------------------------------------------
"""
module Numbers end

Radix(dn::DecimalNumber) = 10

# Top words for a zero
Zero(::Type{Single}) = 0x22500000
Zero(::Type{Double}) = 0x2238000000000000
Zero(::Type{Quad})   = 0x22080000000000000000000000000000

"""
Zero -- set to canonical (integer) zero

 df is the DecimalNumber format number to set to integer +0 (q=0, c=+0)
 returns df

No error is possible, and no status can be set.
"""
Zero{T<:DFTypes}(df::Ref{T}) = (df[] = zero(T); df)

#=
function Zero(df::DecimalFP)
    dn.bits     = 0
    dn.exponent = 0
    dn.digits   = 1
    dn.data[1]  = 0
    dn
end
=#

#=
FromBCD
FromPacked
FromPackedChecked
FromString
FromWider
GetCoefficient
GetExponent
SetCoefficient
SetExponent
Show
ToBCD
ToEngString
ToPacked
ToString
ToWider
Zero
=#

# Non-computational
#define decFloatRadix              decSingleRadix
#define decFloatVersion            decSingleVersion
_asUInt{T<:DFTypes}(df::T) = reinterpret(decUType(T), df)

_topWord(df::UInt32) = df
_topWord{T<:Union{UInt64,UInt128}}(df::T) = df>>>(sizeof(T)*8-32)
_topByte{T<:Union{UInt32,UInt64,UInt128}}(df::T) = df>>>(sizeof(T)*8-8)

_topWord{T<:DFTypes}(df::T) = _topWord(_asUInt(df))
_topByte{T<:DFTypes}(df::T) = _topByte(_asUInt(df))

_signType(::Type{Single}) = Int32
_signType(::Type{Double}) = Int64
_signType(::Type{Quad})   = Int128

# sign and special values [top 32-bits; last two bits are don't-care
# for Infinity on input, last bit don't-care for NaNs]
const global DECFLOAT_Sign  = 0x80000000 # 1 00000 00 Sign
const global DECFLOAT_NaN   = 0x7c000000 # 0 11111 00 NaN generic
const global DECFLOAT_qNaN  = 0x7c000000 # 0 11111 00 qNaN
const global DECFLOAT_sNaN  = 0x7e000000 # 0 11111 10 sNaN
const global DECFLOAT_Inf   = 0x78000000 # 0 11110 00 Infinity
const global DECFLOAT_MinSp = 0x78000000 # minimum special value, [specials are all >=MinSp]
#=
    Format-dependent common tests:
	IsZero    -- test for (any) zero
	IsCCZero  -- test for coefficient continuation being zero
	IsCC01    -- test for coefficient contains only 0s and 1s
	IsInteger -- test for finite and exponent q=0
	IsUInt01  -- test for sign=0, finite, exponent q=0, and MSD=0 or 1

    In IsZero the first test checks the least-significant word
    (most likely to be non-zero); the penultimate tests MSD and
    DPDs in the signword, and the final test excludes specials and
    MSD>7.  IsInt similarly has to allow for the two forms of
    MSD codes.  IsUInt01 only has to allow for one form of MSD
    code.
=#

IsZero(df::Single)    = ((_asUInt(df) & 0x1c0fffff) == 0 &&
                         (_topByte(df) & 0x60) != 0x60)
IsZero(df::Double)    = ((_asUInt(df) & 0x1c03ffffffffffff) == 0 &&
                         (_topByte(df) & 0x60) != 0x60)
IsZero(df::Quad)      = ((_asUInt(df) & 0x1c003fffffffffffffffffffffffffff) == 0 &&
                         (_topByte(df) & 0x60) != 0x60)

IsCCZero(df::Double)  = (_asUInt(df) & 0x0003ffffffffffff) == 0
IsCCZero(df::Quad)    = (_asUInt(df) & 0x00003fffffffffffffffffffffffffff) == 0

IsInteger(df::Double) = ((_topWord(df) & 0x63fc0000) == 0x22380000 ||
                         (_topWord(df) & 0x7bfc0000) == 0x6a380000)
IsInteger(df::Quad)   = ((_topWord(df) & 0x63ffc000) == 0x22080000 ||
                         (_topWord(df) & 0x7bffc000) == 0x6a080000)

IsUInt01(df::Double)  = (_topWord(df) & 0xfbfc0000) == 0x22380000
IsUInt01(df::Quad)    = (_topWord(df) & 0xfbffc000) == 0x22080000

IsCC01(df::Double)    = (_asUInt(df) & ~0xfffc912449124491) == 0
IsCC01(df::Quad)      = (_asUInt(df) & ~0xffffc912449124491244912449124491) == 0

"""
Is -- DecimalNumber tests (IsSigned, etc.)

  df is the DecimalNumber to test
  returns Bool
"""
#=
IsCanonical(dn::DecimalFP) = true	# All decNumbers are saintly
IsFinite(dn::DecimalFP)    = (dn.bits & DECSPECIAL) == 0
IsInfinite(dn::DecimalFP)  = (dn.bits & DECINF)     != 0
IsNegative(dn::DecimalFP)  = (dn.bits & DECNEG)     != 0
IsQNaN(dn::DecimalFP)      = (dn.bits & (DECNAN))   != 0
IsSNaN(dn::DecimalFP)      = (dn.bits & (DECSNAN))  != 0
IsNaN(dn::DecimalFP)       = (dn.bits & (DECNAN|DECSNAN)) != 0
IsSpecial(dn::DecimalFP)   = (dn.bits & DECSPECIAL) != 0
IsZero(dn::DecimalFP)      = dn.data[1] == 0 && dn.digits == 1 && IsFinite(dn)
IsSigned(dn::DecimalFP)    = IsNegative(dn)
=#

# Missing IsLogical, IsInteger, IsPositive for DecimalFP?

# Tests for sign or specials, directly on DECFLOATs
IsSpecial(df::DFTypes)    = (_topByte(df) & 0x78) == 0x78
IsNaN(df::DFTypes)        = (_topByte(df) & 0x7c) == 0x7c
IsQNaN(df::DFTypes)       = (_topByte(df) & 0x7e) == 0x7c
IsSNaN(df::DFTypes)       = (_topByte(df) & 0x7e) == 0x7e

IsLogical(df::DFTypes)    = IsUInt01(df) & IsCC01(df)

IsFinite(df::DFTypes)     = (_topByte(df) & 0x78) != 0x78
IsInfinite(df::DFTypes)   = (_topByte(df) & 0x7c) == 0x78
IsSigned(df::DFTypes)     = (_topByte(df) & 0x80) != 0
IsNegative(df::DFTypes)   = IsSigned(df) && !IsZero(df) && !IsNaN(df)
IsPositive(df::DFTypes)   = !IsSigned(df) && !IsZero(df) && !IsNaN(df)

const global IsSignaling  = IsSNaN # American spelling
const global IsSignalling = IsSNaN # British spelling

"""Get the exponent continuation from a DecimalNumber as an Int"""
_GetEcon{T<:DFTypes}(df::T) = Int((_topWord(df) & 0x03ffffff)>>>(26-decEconL(T)))
"""Get the biased exponent from a DecimalNumber as an Int"""
_GetExp{T<:DFTypes}(df::T) = Int((decCombExp(T)[_topWord(df)>>>26]+_GetEcon(df)))
"""Get the unbiased exponent from a DecimalNumber as an Int"""
_GetExpUn{T<:DFTypes}(df::T) = _GetExp(df) - decBias(T)

#=
# Macros to decode the coefficient in a finite decFloat *df into a BCD string (uByte *bcdin)
# of length DECPMAX uBytes.

# In-line sequence to convert least significant 10 bits of uInt dpd to three BCD8 digits
# starting at uByte u.  Note that an extra byte is written to the right of the three digits
# because four bytes are moved at a time for speed; the alternative macro moves exactly three
# bytes (usually slower).
=#

const DECCOMBMSD =
    UInt8[0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7,
          0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 9, 8, 9, 0, 0,
          0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7,
          0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 9, 8, 9, 0, 0]

const DPD2BCD8 = UInt8[
 0,0,0,0, 0,0,1,1, 0,0,2,1, 0,0,3,1, 0,0,4,1, 0,0,5,1, 0,0,6,1, 0,0,7,1, 0,0,8,1,
 0,0,9,1, 0,8,0,2, 0,8,1,2, 8,0,0,3, 8,0,1,3, 8,8,0,3, 8,8,1,3, 0,1,0,2, 0,1,1,2, 
 0,1,2,2, 0,1,3,2, 0,1,4,2, 0,1,5,2, 0,1,6,2, 0,1,7,2, 0,1,8,2, 0,1,9,2, 0,9,0,2, 
 0,9,1,2, 8,1,0,3, 8,1,1,3, 8,9,0,3, 8,9,1,3, 0,2,0,2, 0,2,1,2, 0,2,2,2, 0,2,3,2, 
 0,2,4,2, 0,2,5,2, 0,2,6,2, 0,2,7,2, 0,2,8,2, 0,2,9,2, 0,8,2,2, 0,8,3,2, 8,2,0,3, 
 8,2,1,3, 8,0,8,3, 8,0,9,3, 0,3,0,2, 0,3,1,2, 0,3,2,2, 0,3,3,2, 0,3,4,2, 0,3,5,2, 
 0,3,6,2, 0,3,7,2, 0,3,8,2, 0,3,9,2, 0,9,2,2, 0,9,3,2, 8,3,0,3, 8,3,1,3, 8,1,8,3, 
 8,1,9,3, 0,4,0,2, 0,4,1,2, 0,4,2,2, 0,4,3,2, 0,4,4,2, 0,4,5,2, 0,4,6,2, 0,4,7,2, 
 0,4,8,2, 0,4,9,2, 0,8,4,2, 0,8,5,2, 8,4,0,3, 8,4,1,3, 0,8,8,2, 0,8,9,2, 0,5,0,2, 
 0,5,1,2, 0,5,2,2, 0,5,3,2, 0,5,4,2, 0,5,5,2, 0,5,6,2, 0,5,7,2, 0,5,8,2, 0,5,9,2, 
 0,9,4,2, 0,9,5,2, 8,5,0,3, 8,5,1,3, 0,9,8,2, 0,9,9,2, 0,6,0,2, 0,6,1,2, 0,6,2,2, 
 0,6,3,2, 0,6,4,2, 0,6,5,2, 0,6,6,2, 0,6,7,2, 0,6,8,2, 0,6,9,2, 0,8,6,2, 0,8,7,2, 
 8,6,0,3, 8,6,1,3, 8,8,8,3, 8,8,9,3, 0,7,0,2, 0,7,1,2, 0,7,2,2, 0,7,3,2, 0,7,4,2, 
 0,7,5,2, 0,7,6,2, 0,7,7,2, 0,7,8,2, 0,7,9,2, 0,9,6,2, 0,9,7,2, 8,7,0,3, 8,7,1,3, 
 8,9,8,3, 8,9,9,3, 1,0,0,3, 1,0,1,3, 1,0,2,3, 1,0,3,3, 1,0,4,3, 1,0,5,3, 1,0,6,3, 
 1,0,7,3, 1,0,8,3, 1,0,9,3, 1,8,0,3, 1,8,1,3, 9,0,0,3, 9,0,1,3, 9,8,0,3, 9,8,1,3, 
 1,1,0,3, 1,1,1,3, 1,1,2,3, 1,1,3,3, 1,1,4,3, 1,1,5,3, 1,1,6,3, 1,1,7,3, 1,1,8,3, 
 1,1,9,3, 1,9,0,3, 1,9,1,3, 9,1,0,3, 9,1,1,3, 9,9,0,3, 9,9,1,3, 1,2,0,3, 1,2,1,3, 
 1,2,2,3, 1,2,3,3, 1,2,4,3, 1,2,5,3, 1,2,6,3, 1,2,7,3, 1,2,8,3, 1,2,9,3, 1,8,2,3, 
 1,8,3,3, 9,2,0,3, 9,2,1,3, 9,0,8,3, 9,0,9,3, 1,3,0,3, 1,3,1,3, 1,3,2,3, 1,3,3,3, 
 1,3,4,3, 1,3,5,3, 1,3,6,3, 1,3,7,3, 1,3,8,3, 1,3,9,3, 1,9,2,3, 1,9,3,3, 9,3,0,3, 
 9,3,1,3, 9,1,8,3, 9,1,9,3, 1,4,0,3, 1,4,1,3, 1,4,2,3, 1,4,3,3, 1,4,4,3, 1,4,5,3, 
 1,4,6,3, 1,4,7,3, 1,4,8,3, 1,4,9,3, 1,8,4,3, 1,8,5,3, 9,4,0,3, 9,4,1,3, 1,8,8,3, 
 1,8,9,3, 1,5,0,3, 1,5,1,3, 1,5,2,3, 1,5,3,3, 1,5,4,3, 1,5,5,3, 1,5,6,3, 1,5,7,3, 
 1,5,8,3, 1,5,9,3, 1,9,4,3, 1,9,5,3, 9,5,0,3, 9,5,1,3, 1,9,8,3, 1,9,9,3, 1,6,0,3, 
 1,6,1,3, 1,6,2,3, 1,6,3,3, 1,6,4,3, 1,6,5,3, 1,6,6,3, 1,6,7,3, 1,6,8,3, 1,6,9,3, 
 1,8,6,3, 1,8,7,3, 9,6,0,3, 9,6,1,3, 9,8,8,3, 9,8,9,3, 1,7,0,3, 1,7,1,3, 1,7,2,3, 
 1,7,3,3, 1,7,4,3, 1,7,5,3, 1,7,6,3, 1,7,7,3, 1,7,8,3, 1,7,9,3, 1,9,6,3, 1,9,7,3, 
 9,7,0,3, 9,7,1,3, 9,9,8,3, 9,9,9,3, 2,0,0,3, 2,0,1,3, 2,0,2,3, 2,0,3,3, 2,0,4,3, 
 2,0,5,3, 2,0,6,3, 2,0,7,3, 2,0,8,3, 2,0,9,3, 2,8,0,3, 2,8,1,3, 8,0,2,3, 8,0,3,3, 
 8,8,2,3, 8,8,3,3, 2,1,0,3, 2,1,1,3, 2,1,2,3, 2,1,3,3, 2,1,4,3, 2,1,5,3, 2,1,6,3, 
 2,1,7,3, 2,1,8,3, 2,1,9,3, 2,9,0,3, 2,9,1,3, 8,1,2,3, 8,1,3,3, 8,9,2,3, 8,9,3,3, 
 2,2,0,3, 2,2,1,3, 2,2,2,3, 2,2,3,3, 2,2,4,3, 2,2,5,3, 2,2,6,3, 2,2,7,3, 2,2,8,3, 
 2,2,9,3, 2,8,2,3, 2,8,3,3, 8,2,2,3, 8,2,3,3, 8,2,8,3, 8,2,9,3, 2,3,0,3, 2,3,1,3, 
 2,3,2,3, 2,3,3,3, 2,3,4,3, 2,3,5,3, 2,3,6,3, 2,3,7,3, 2,3,8,3, 2,3,9,3, 2,9,2,3, 
 2,9,3,3, 8,3,2,3, 8,3,3,3, 8,3,8,3, 8,3,9,3, 2,4,0,3, 2,4,1,3, 2,4,2,3, 2,4,3,3, 
 2,4,4,3, 2,4,5,3, 2,4,6,3, 2,4,7,3, 2,4,8,3, 2,4,9,3, 2,8,4,3, 2,8,5,3, 8,4,2,3, 
 8,4,3,3, 2,8,8,3, 2,8,9,3, 2,5,0,3, 2,5,1,3, 2,5,2,3, 2,5,3,3, 2,5,4,3, 2,5,5,3, 
 2,5,6,3, 2,5,7,3, 2,5,8,3, 2,5,9,3, 2,9,4,3, 2,9,5,3, 8,5,2,3, 8,5,3,3, 2,9,8,3, 
 2,9,9,3, 2,6,0,3, 2,6,1,3, 2,6,2,3, 2,6,3,3, 2,6,4,3, 2,6,5,3, 2,6,6,3, 2,6,7,3, 
 2,6,8,3, 2,6,9,3, 2,8,6,3, 2,8,7,3, 8,6,2,3, 8,6,3,3, 8,8,8,3, 8,8,9,3, 2,7,0,3, 
 2,7,1,3, 2,7,2,3, 2,7,3,3, 2,7,4,3, 2,7,5,3, 2,7,6,3, 2,7,7,3, 2,7,8,3, 2,7,9,3, 
 2,9,6,3, 2,9,7,3, 8,7,2,3, 8,7,3,3, 8,9,8,3, 8,9,9,3, 3,0,0,3, 3,0,1,3, 3,0,2,3, 
 3,0,3,3, 3,0,4,3, 3,0,5,3, 3,0,6,3, 3,0,7,3, 3,0,8,3, 3,0,9,3, 3,8,0,3, 3,8,1,3, 
 9,0,2,3, 9,0,3,3, 9,8,2,3, 9,8,3,3, 3,1,0,3, 3,1,1,3, 3,1,2,3, 3,1,3,3, 3,1,4,3, 
 3,1,5,3, 3,1,6,3, 3,1,7,3, 3,1,8,3, 3,1,9,3, 3,9,0,3, 3,9,1,3, 9,1,2,3, 9,1,3,3, 
 9,9,2,3, 9,9,3,3, 3,2,0,3, 3,2,1,3, 3,2,2,3, 3,2,3,3, 3,2,4,3, 3,2,5,3, 3,2,6,3, 
 3,2,7,3, 3,2,8,3, 3,2,9,3, 3,8,2,3, 3,8,3,3, 9,2,2,3, 9,2,3,3, 9,2,8,3, 9,2,9,3, 
 3,3,0,3, 3,3,1,3, 3,3,2,3, 3,3,3,3, 3,3,4,3, 3,3,5,3, 3,3,6,3, 3,3,7,3, 3,3,8,3, 
 3,3,9,3, 3,9,2,3, 3,9,3,3, 9,3,2,3, 9,3,3,3, 9,3,8,3, 9,3,9,3, 3,4,0,3, 3,4,1,3, 
 3,4,2,3, 3,4,3,3, 3,4,4,3, 3,4,5,3, 3,4,6,3, 3,4,7,3, 3,4,8,3, 3,4,9,3, 3,8,4,3, 
 3,8,5,3, 9,4,2,3, 9,4,3,3, 3,8,8,3, 3,8,9,3, 3,5,0,3, 3,5,1,3, 3,5,2,3, 3,5,3,3, 
 3,5,4,3, 3,5,5,3, 3,5,6,3, 3,5,7,3, 3,5,8,3, 3,5,9,3, 3,9,4,3, 3,9,5,3, 9,5,2,3, 
 9,5,3,3, 3,9,8,3, 3,9,9,3, 3,6,0,3, 3,6,1,3, 3,6,2,3, 3,6,3,3, 3,6,4,3, 3,6,5,3, 
 3,6,6,3, 3,6,7,3, 3,6,8,3, 3,6,9,3, 3,8,6,3, 3,8,7,3, 9,6,2,3, 9,6,3,3, 9,8,8,3, 
 9,8,9,3, 3,7,0,3, 3,7,1,3, 3,7,2,3, 3,7,3,3, 3,7,4,3, 3,7,5,3, 3,7,6,3, 3,7,7,3, 
 3,7,8,3, 3,7,9,3, 3,9,6,3, 3,9,7,3, 9,7,2,3, 9,7,3,3, 9,9,8,3, 9,9,9,3, 4,0,0,3, 
 4,0,1,3, 4,0,2,3, 4,0,3,3, 4,0,4,3, 4,0,5,3, 4,0,6,3, 4,0,7,3, 4,0,8,3, 4,0,9,3, 
 4,8,0,3, 4,8,1,3, 8,0,4,3, 8,0,5,3, 8,8,4,3, 8,8,5,3, 4,1,0,3, 4,1,1,3, 4,1,2,3, 
 4,1,3,3, 4,1,4,3, 4,1,5,3, 4,1,6,3, 4,1,7,3, 4,1,8,3, 4,1,9,3, 4,9,0,3, 4,9,1,3, 
 8,1,4,3, 8,1,5,3, 8,9,4,3, 8,9,5,3, 4,2,0,3, 4,2,1,3, 4,2,2,3, 4,2,3,3, 4,2,4,3, 
 4,2,5,3, 4,2,6,3, 4,2,7,3, 4,2,8,3, 4,2,9,3, 4,8,2,3, 4,8,3,3, 8,2,4,3, 8,2,5,3, 
 8,4,8,3, 8,4,9,3, 4,3,0,3, 4,3,1,3, 4,3,2,3, 4,3,3,3, 4,3,4,3, 4,3,5,3, 4,3,6,3, 
 4,3,7,3, 4,3,8,3, 4,3,9,3, 4,9,2,3, 4,9,3,3, 8,3,4,3, 8,3,5,3, 8,5,8,3, 8,5,9,3, 
 4,4,0,3, 4,4,1,3, 4,4,2,3, 4,4,3,3, 4,4,4,3, 4,4,5,3, 4,4,6,3, 4,4,7,3, 4,4,8,3, 
 4,4,9,3, 4,8,4,3, 4,8,5,3, 8,4,4,3, 8,4,5,3, 4,8,8,3, 4,8,9,3, 4,5,0,3, 4,5,1,3, 
 4,5,2,3, 4,5,3,3, 4,5,4,3, 4,5,5,3, 4,5,6,3, 4,5,7,3, 4,5,8,3, 4,5,9,3, 4,9,4,3, 
 4,9,5,3, 8,5,4,3, 8,5,5,3, 4,9,8,3, 4,9,9,3, 4,6,0,3, 4,6,1,3, 4,6,2,3, 4,6,3,3, 
 4,6,4,3, 4,6,5,3, 4,6,6,3, 4,6,7,3, 4,6,8,3, 4,6,9,3, 4,8,6,3, 4,8,7,3, 8,6,4,3, 
 8,6,5,3, 8,8,8,3, 8,8,9,3, 4,7,0,3, 4,7,1,3, 4,7,2,3, 4,7,3,3, 4,7,4,3, 4,7,5,3, 
 4,7,6,3, 4,7,7,3, 4,7,8,3, 4,7,9,3, 4,9,6,3, 4,9,7,3, 8,7,4,3, 8,7,5,3, 8,9,8,3, 
 8,9,9,3, 5,0,0,3, 5,0,1,3, 5,0,2,3, 5,0,3,3, 5,0,4,3, 5,0,5,3, 5,0,6,3, 5,0,7,3, 
 5,0,8,3, 5,0,9,3, 5,8,0,3, 5,8,1,3, 9,0,4,3, 9,0,5,3, 9,8,4,3, 9,8,5,3, 5,1,0,3, 
 5,1,1,3, 5,1,2,3, 5,1,3,3, 5,1,4,3, 5,1,5,3, 5,1,6,3, 5,1,7,3, 5,1,8,3, 5,1,9,3, 
 5,9,0,3, 5,9,1,3, 9,1,4,3, 9,1,5,3, 9,9,4,3, 9,9,5,3, 5,2,0,3, 5,2,1,3, 5,2,2,3, 
 5,2,3,3, 5,2,4,3, 5,2,5,3, 5,2,6,3, 5,2,7,3, 5,2,8,3, 5,2,9,3, 5,8,2,3, 5,8,3,3, 
 9,2,4,3, 9,2,5,3, 9,4,8,3, 9,4,9,3, 5,3,0,3, 5,3,1,3, 5,3,2,3, 5,3,3,3, 5,3,4,3, 
 5,3,5,3, 5,3,6,3, 5,3,7,3, 5,3,8,3, 5,3,9,3, 5,9,2,3, 5,9,3,3, 9,3,4,3, 9,3,5,3, 
 9,5,8,3, 9,5,9,3, 5,4,0,3, 5,4,1,3, 5,4,2,3, 5,4,3,3, 5,4,4,3, 5,4,5,3, 5,4,6,3, 
 5,4,7,3, 5,4,8,3, 5,4,9,3, 5,8,4,3, 5,8,5,3, 9,4,4,3, 9,4,5,3, 5,8,8,3, 5,8,9,3, 
 5,5,0,3, 5,5,1,3, 5,5,2,3, 5,5,3,3, 5,5,4,3, 5,5,5,3, 5,5,6,3, 5,5,7,3, 5,5,8,3, 
 5,5,9,3, 5,9,4,3, 5,9,5,3, 9,5,4,3, 9,5,5,3, 5,9,8,3, 5,9,9,3, 5,6,0,3, 5,6,1,3, 
 5,6,2,3, 5,6,3,3, 5,6,4,3, 5,6,5,3, 5,6,6,3, 5,6,7,3, 5,6,8,3, 5,6,9,3, 5,8,6,3, 
 5,8,7,3, 9,6,4,3, 9,6,5,3, 9,8,8,3, 9,8,9,3, 5,7,0,3, 5,7,1,3, 5,7,2,3, 5,7,3,3, 
 5,7,4,3, 5,7,5,3, 5,7,6,3, 5,7,7,3, 5,7,8,3, 5,7,9,3, 5,9,6,3, 5,9,7,3, 9,7,4,3, 
 9,7,5,3, 9,9,8,3, 9,9,9,3, 6,0,0,3, 6,0,1,3, 6,0,2,3, 6,0,3,3, 6,0,4,3, 6,0,5,3, 
 6,0,6,3, 6,0,7,3, 6,0,8,3, 6,0,9,3, 6,8,0,3, 6,8,1,3, 8,0,6,3, 8,0,7,3, 8,8,6,3, 
 8,8,7,3, 6,1,0,3, 6,1,1,3, 6,1,2,3, 6,1,3,3, 6,1,4,3, 6,1,5,3, 6,1,6,3, 6,1,7,3, 
 6,1,8,3, 6,1,9,3, 6,9,0,3, 6,9,1,3, 8,1,6,3, 8,1,7,3, 8,9,6,3, 8,9,7,3, 6,2,0,3, 
 6,2,1,3, 6,2,2,3, 6,2,3,3, 6,2,4,3, 6,2,5,3, 6,2,6,3, 6,2,7,3, 6,2,8,3, 6,2,9,3, 
 6,8,2,3, 6,8,3,3, 8,2,6,3, 8,2,7,3, 8,6,8,3, 8,6,9,3, 6,3,0,3, 6,3,1,3, 6,3,2,3, 
 6,3,3,3, 6,3,4,3, 6,3,5,3, 6,3,6,3, 6,3,7,3, 6,3,8,3, 6,3,9,3, 6,9,2,3, 6,9,3,3, 
 8,3,6,3, 8,3,7,3, 8,7,8,3, 8,7,9,3, 6,4,0,3, 6,4,1,3, 6,4,2,3, 6,4,3,3, 6,4,4,3, 
 6,4,5,3, 6,4,6,3, 6,4,7,3, 6,4,8,3, 6,4,9,3, 6,8,4,3, 6,8,5,3, 8,4,6,3, 8,4,7,3, 
 6,8,8,3, 6,8,9,3, 6,5,0,3, 6,5,1,3, 6,5,2,3, 6,5,3,3, 6,5,4,3, 6,5,5,3, 6,5,6,3, 
 6,5,7,3, 6,5,8,3, 6,5,9,3, 6,9,4,3, 6,9,5,3, 8,5,6,3, 8,5,7,3, 6,9,8,3, 6,9,9,3, 
 6,6,0,3, 6,6,1,3, 6,6,2,3, 6,6,3,3, 6,6,4,3, 6,6,5,3, 6,6,6,3, 6,6,7,3, 6,6,8,3, 
 6,6,9,3, 6,8,6,3, 6,8,7,3, 8,6,6,3, 8,6,7,3, 8,8,8,3, 8,8,9,3, 6,7,0,3, 6,7,1,3, 
 6,7,2,3, 6,7,3,3, 6,7,4,3, 6,7,5,3, 6,7,6,3, 6,7,7,3, 6,7,8,3, 6,7,9,3, 6,9,6,3, 
 6,9,7,3, 8,7,6,3, 8,7,7,3, 8,9,8,3, 8,9,9,3, 7,0,0,3, 7,0,1,3, 7,0,2,3, 7,0,3,3, 
 7,0,4,3, 7,0,5,3, 7,0,6,3, 7,0,7,3, 7,0,8,3, 7,0,9,3, 7,8,0,3, 7,8,1,3, 9,0,6,3, 
 9,0,7,3, 9,8,6,3, 9,8,7,3, 7,1,0,3, 7,1,1,3, 7,1,2,3, 7,1,3,3, 7,1,4,3, 7,1,5,3, 
 7,1,6,3, 7,1,7,3, 7,1,8,3, 7,1,9,3, 7,9,0,3, 7,9,1,3, 9,1,6,3, 9,1,7,3, 9,9,6,3, 
 9,9,7,3, 7,2,0,3, 7,2,1,3, 7,2,2,3, 7,2,3,3, 7,2,4,3, 7,2,5,3, 7,2,6,3, 7,2,7,3, 
 7,2,8,3, 7,2,9,3, 7,8,2,3, 7,8,3,3, 9,2,6,3, 9,2,7,3, 9,6,8,3, 9,6,9,3, 7,3,0,3, 
 7,3,1,3, 7,3,2,3, 7,3,3,3, 7,3,4,3, 7,3,5,3, 7,3,6,3, 7,3,7,3, 7,3,8,3, 7,3,9,3, 
 7,9,2,3, 7,9,3,3, 9,3,6,3, 9,3,7,3, 9,7,8,3, 9,7,9,3, 7,4,0,3, 7,4,1,3, 7,4,2,3, 
 7,4,3,3, 7,4,4,3, 7,4,5,3, 7,4,6,3, 7,4,7,3, 7,4,8,3, 7,4,9,3, 7,8,4,3, 7,8,5,3, 
 9,4,6,3, 9,4,7,3, 7,8,8,3, 7,8,9,3, 7,5,0,3, 7,5,1,3, 7,5,2,3, 7,5,3,3, 7,5,4,3, 
 7,5,5,3, 7,5,6,3, 7,5,7,3, 7,5,8,3, 7,5,9,3, 7,9,4,3, 7,9,5,3, 9,5,6,3, 9,5,7,3, 
 7,9,8,3, 7,9,9,3, 7,6,0,3, 7,6,1,3, 7,6,2,3, 7,6,3,3, 7,6,4,3, 7,6,5,3, 7,6,6,3, 
 7,6,7,3, 7,6,8,3, 7,6,9,3, 7,8,6,3, 7,8,7,3, 9,6,6,3, 9,6,7,3, 9,8,8,3, 9,8,9,3, 
 7,7,0,3, 7,7,1,3, 7,7,2,3, 7,7,3,3, 7,7,4,3, 7,7,5,3, 7,7,6,3, 7,7,7,3, 7,7,8,3, 
 7,7,9,3, 7,9,6,3, 7,9,7,3, 9,7,6,3, 9,7,7,3, 9,9,8,3, 9,9,9,3]

const DPD2BIN = UInt16[0,    1,    2,    3,    4,    5,    6,    7, 
    8,    9,   80,   81,  800,  801,  880,  881,   10,   11,   12,   13,   14, 
   15,   16,   17,   18,   19,   90,   91,  810,  811,  890,  891,   20,   21, 
   22,   23,   24,   25,   26,   27,   28,   29,   82,   83,  820,  821,  808, 
  809,   30,   31,   32,   33,   34,   35,   36,   37,   38,   39,   92,   93, 
  830,  831,  818,  819,   40,   41,   42,   43,   44,   45,   46,   47,   48, 
   49,   84,   85,  840,  841,   88,   89,   50,   51,   52,   53,   54,   55, 
   56,   57,   58,   59,   94,   95,  850,  851,   98,   99,   60,   61,   62, 
   63,   64,   65,   66,   67,   68,   69,   86,   87,  860,  861,  888,  889, 
   70,   71,   72,   73,   74,   75,   76,   77,   78,   79,   96,   97,  870, 
  871,  898,  899,  100,  101,  102,  103,  104,  105,  106,  107,  108,  109, 
  180,  181,  900,  901,  980,  981,  110,  111,  112,  113,  114,  115,  116, 
  117,  118,  119,  190,  191,  910,  911,  990,  991,  120,  121,  122,  123, 
  124,  125,  126,  127,  128,  129,  182,  183,  920,  921,  908,  909,  130, 
  131,  132,  133,  134,  135,  136,  137,  138,  139,  192,  193,  930,  931, 
  918,  919,  140,  141,  142,  143,  144,  145,  146,  147,  148,  149,  184, 
  185,  940,  941,  188,  189,  150,  151,  152,  153,  154,  155,  156,  157, 
  158,  159,  194,  195,  950,  951,  198,  199,  160,  161,  162,  163,  164, 
  165,  166,  167,  168,  169,  186,  187,  960,  961,  988,  989,  170,  171, 
  172,  173,  174,  175,  176,  177,  178,  179,  196,  197,  970,  971,  998, 
  999,  200,  201,  202,  203,  204,  205,  206,  207,  208,  209,  280,  281, 
  802,  803,  882,  883,  210,  211,  212,  213,  214,  215,  216,  217,  218, 
  219,  290,  291,  812,  813,  892,  893,  220,  221,  222,  223,  224,  225, 
  226,  227,  228,  229,  282,  283,  822,  823,  828,  829,  230,  231,  232, 
  233,  234,  235,  236,  237,  238,  239,  292,  293,  832,  833,  838,  839, 
  240,  241,  242,  243,  244,  245,  246,  247,  248,  249,  284,  285,  842, 
  843,  288,  289,  250,  251,  252,  253,  254,  255,  256,  257,  258,  259, 
  294,  295,  852,  853,  298,  299,  260,  261,  262,  263,  264,  265,  266, 
  267,  268,  269,  286,  287,  862,  863,  888,  889,  270,  271,  272,  273, 
  274,  275,  276,  277,  278,  279,  296,  297,  872,  873,  898,  899,  300, 
  301,  302,  303,  304,  305,  306,  307,  308,  309,  380,  381,  902,  903, 
  982,  983,  310,  311,  312,  313,  314,  315,  316,  317,  318,  319,  390, 
  391,  912,  913,  992,  993,  320,  321,  322,  323,  324,  325,  326,  327, 
  328,  329,  382,  383,  922,  923,  928,  929,  330,  331,  332,  333,  334, 
  335,  336,  337,  338,  339,  392,  393,  932,  933,  938,  939,  340,  341, 
  342,  343,  344,  345,  346,  347,  348,  349,  384,  385,  942,  943,  388, 
  389,  350,  351,  352,  353,  354,  355,  356,  357,  358,  359,  394,  395, 
  952,  953,  398,  399,  360,  361,  362,  363,  364,  365,  366,  367,  368, 
  369,  386,  387,  962,  963,  988,  989,  370,  371,  372,  373,  374,  375, 
  376,  377,  378,  379,  396,  397,  972,  973,  998,  999,  400,  401,  402, 
  403,  404,  405,  406,  407,  408,  409,  480,  481,  804,  805,  884,  885, 
  410,  411,  412,  413,  414,  415,  416,  417,  418,  419,  490,  491,  814, 
  815,  894,  895,  420,  421,  422,  423,  424,  425,  426,  427,  428,  429, 
  482,  483,  824,  825,  848,  849,  430,  431,  432,  433,  434,  435,  436, 
  437,  438,  439,  492,  493,  834,  835,  858,  859,  440,  441,  442,  443, 
  444,  445,  446,  447,  448,  449,  484,  485,  844,  845,  488,  489,  450, 
  451,  452,  453,  454,  455,  456,  457,  458,  459,  494,  495,  854,  855, 
  498,  499,  460,  461,  462,  463,  464,  465,  466,  467,  468,  469,  486, 
  487,  864,  865,  888,  889,  470,  471,  472,  473,  474,  475,  476,  477, 
  478,  479,  496,  497,  874,  875,  898,  899,  500,  501,  502,  503,  504, 
  505,  506,  507,  508,  509,  580,  581,  904,  905,  984,  985,  510,  511, 
  512,  513,  514,  515,  516,  517,  518,  519,  590,  591,  914,  915,  994, 
  995,  520,  521,  522,  523,  524,  525,  526,  527,  528,  529,  582,  583, 
  924,  925,  948,  949,  530,  531,  532,  533,  534,  535,  536,  537,  538, 
  539,  592,  593,  934,  935,  958,  959,  540,  541,  542,  543,  544,  545, 
  546,  547,  548,  549,  584,  585,  944,  945,  588,  589,  550,  551,  552, 
  553,  554,  555,  556,  557,  558,  559,  594,  595,  954,  955,  598,  599, 
  560,  561,  562,  563,  564,  565,  566,  567,  568,  569,  586,  587,  964, 
  965,  988,  989,  570,  571,  572,  573,  574,  575,  576,  577,  578,  579, 
  596,  597,  974,  975,  998,  999,  600,  601,  602,  603,  604,  605,  606, 
  607,  608,  609,  680,  681,  806,  807,  886,  887,  610,  611,  612,  613, 
  614,  615,  616,  617,  618,  619,  690,  691,  816,  817,  896,  897,  620, 
  621,  622,  623,  624,  625,  626,  627,  628,  629,  682,  683,  826,  827, 
  868,  869,  630,  631,  632,  633,  634,  635,  636,  637,  638,  639,  692, 
  693,  836,  837,  878,  879,  640,  641,  642,  643,  644,  645,  646,  647, 
  648,  649,  684,  685,  846,  847,  688,  689,  650,  651,  652,  653,  654, 
  655,  656,  657,  658,  659,  694,  695,  856,  857,  698,  699,  660,  661, 
  662,  663,  664,  665,  666,  667,  668,  669,  686,  687,  866,  867,  888, 
  889,  670,  671,  672,  673,  674,  675,  676,  677,  678,  679,  696,  697, 
  876,  877,  898,  899,  700,  701,  702,  703,  704,  705,  706,  707,  708, 
  709,  780,  781,  906,  907,  986,  987,  710,  711,  712,  713,  714,  715, 
  716,  717,  718,  719,  790,  791,  916,  917,  996,  997,  720,  721,  722, 
  723,  724,  725,  726,  727,  728,  729,  782,  783,  926,  927,  968,  969, 
  730,  731,  732,  733,  734,  735,  736,  737,  738,  739,  792,  793,  936, 
  937,  978,  979,  740,  741,  742,  743,  744,  745,  746,  747,  748,  749, 
  784,  785,  946,  947,  788,  789,  750,  751,  752,  753,  754,  755,  756, 
  757,  758,  759,  794,  795,  956,  957,  798,  799,  760,  761,  762,  763, 
  764,  765,  766,  767,  768,  769,  786,  787,  966,  967,  988,  989,  770, 
  771,  772,  773,  774,  775,  776,  777,  778,  779,  796,  797,  976,  977, 
  998,  999]

# Decode the declets.  After extracting each one, it is decoded to BCD8 using a table lookup
# (also used for variable-length decode).  Each DPD decode is 3 bytes BCD8 plus a one-byte
# length which is not used, here).  Fixed-length 4-byte moves are fast, however, almost
# everywhere, and so are used except for the final three bytes (to avoid overrun).

# Two macros are defined for each format:
# GETCOEFF extracts the coefficient of the current format

function dpd2bcd8(vec::Vector{UInt8}, pos::Int, val::UInt16)
    @inbounds begin
        vec[pos+1] = DPD2BCD8[val+1]
        vec[pos+2] = DPD2BCD8[val+2]
        vec[pos+3] = DPD2BCD8[val+3]
    end
end

dpd2bcd(vec::Vector{UInt8}, pos::Int, val) = dpd2bcd8(vec, pos, UInt16(val & 0x3ff)<<2)

function get_coeff!(vec::Vector{UInt8}, val::UInt32)
    @inbounds begin
        vec[1] = DECCOMBMSD[(val >> 26)+1]
        dpd2bcd(vec, 1, val >> 10)
        dpd2bcd(vec, 4, val)
    end
    vec
end

function get_coeff!(vec::Vector{UInt8}, val::UInt64)
    @inbounds begin
        vec[1] = DECCOMBMSD[(val >> 58)+1]
        dpd2bcd(vec,  1, val >> 40)
        dpd2bcd(vec,  4, val >> 30)
        dpd2bcd(vec,  7, val >> 20)
        dpd2bcd(vec, 10, val >> 10)
        dpd2bcd(vec, 13, val)
    end
    vec
end

function get_coeff!(vec::Vector{UInt8}, val::UInt128)
    @inbounds begin
        vec[1] = DECCOMBMSD[(val >> 122)+1]
        dpd2bcd(vec,  1, val >> 100)
        dpd2bcd(vec,  4, val >> 90)
        dpd2bcd(vec,  7, val >> 80)
        dpd2bcd(vec, 10, val >> 70)
        dpd2bcd(vec, 13, val >> 60)
        dpd2bcd(vec, 16, val >> 50)
        dpd2bcd(vec, 19, val >> 40)
        dpd2bcd(vec, 22, val >> 30)
        dpd2bcd(vec, 25, val >> 20)
        dpd2bcd(vec, 28, val >> 10)
        dpd2bcd(vec, 31, val)
    end
    vec
end

get_coeff{T<:DFTypes}(df::T) =  get_coeff!(Vector{UInt8}(decPmax(T)), _asUInt(df))

dpd2bin(x) = DPD2BIN[(x & 0x3ff) + 1]

_coeffu(val::UInt32) =
    Int32(dpd2bin(val) + 1000*(dpd2bin(val>>10) + 1000*DECCOMBMSD[(val >> 26)+1]))

_coeffu(val::UInt64) =
    (dpd2bin(val) +
     dpd2bin(val>>10) * UInt64(1000) +
     dpd2bin(val>>20) * UInt64(1000_000) +
     dpd2bin(val>>30) * UInt64(1000_000_000) +
     dpd2bin(val>>40) * UInt64(1000_000_000_000) +
     DECCOMBMSD[(val >> 58)+1] * UInt64(1000_000_000_000_000))

_coeffu(val::UInt128) =
    (dpd2bin(val) +
     dpd2bin(val>>10) * UInt128(1000) +
     dpd2bin(val>>20) * UInt128(1000_000) +
     dpd2bin(val>>30) * UInt128(1000_000_000) +
     dpd2bin(val>>40) * UInt128(1000_000_000_000) +
     dpd2bin(val>>50) * UInt128(1000_000_000_000_000) +
     dpd2bin(val>>60) * UInt128(1000_000_000_000_000_000) +
     dpd2bin(val>>70) * UInt128(1000_000_000_000_000_000_000) +
     dpd2bin(val>>80) * UInt128(1000_000_000_000_000_000_000_000) +
     dpd2bin(val>>90) * UInt128(1000_000_000_000_000_000_000_000_000) +
     dpd2bin(val>>100) * UInt128(1000_000_000_000_000_000_000_000_000_000) +
     DECCOMBMSD[(val >> 122)+1]* UInt128(1000_000_000_000_000_000_000_000_000_000_000))

export coefficient
coefficient{T<:DFTypes}(df::T) =
    (r = reinterpret(_signType(T),_coeffu(_asUInt(df))) ; IsSigned(df) ? -r : r)

"""
IsNormal -- test normality of a decNumber
    df is the decNumber to test
    dc is the context to use for Emin
returns true if |dn| is finite and >=Nmin, false otherwise
"""
function IsNormal{T<:DFTypes}(df::T)
    IsFinite(df) || return false
    IsZero(df)   && return false
    # is finite and non-zero
    # get unbiased exponent and make adjusted exponent
    # < DECEMIN is subnormal
    (_GetExpUn(df) + Digits(df) - 1) >= decEmin(T)
end
#=
function IsNormal(df::DecimalFP, dc::Context)
    IsFinite(df) || return false
    IsZero(df) && return false
    df.exponent + df.digits - 1 >= dc.emin
end
=#

"""
IsSubnormal -- test subnormality of a decNumber
    dn is the decNumber to test
    dc is the context to use for Emin
Returns 1 if |dn| is finite, non-zero, and <Nmin, 0 otherwise
"""
function IsSubnormal(df::DFTypes)
    IsFinite(df) || return false
    IsNormal(df) && return false
    # it is <Nmin, but could be zero
    !IsZero(df)
end
#=
function IsSubnormal(df::DecimalFP, dc:Context)
    IsFinite(df) || return false
    IsZero(df) && return false
    df.exponent + df.digits - 1 < dc.emin
end
=#

# Test if a certain 10 bits are a canonical declet [higher or lower bits are ignored].
# declet is at offset 0 (from the right)
_CanonDPD(dpd) = ((dpd & 0x300) == 0 || (dpd & 0x06e) != 0x06e)

# declet is at offset k (a multiple of 2)
_CanonDPD(T, dpd, k) =
    ((dpd & (T(0x300) << k)) == 0 || (dpd & (T(0x06e) << k)) != (T(0x06e) << k))

_CanonAll{T<:UInt64}(du::T) =
        (_CanonDPD(T, du, 40) && _CanonDPD(T, du, 30) && _CanonDPD(T, du, 20) &&
         _CanonDPD(T, du, 10) && _CanonDPD(du))

_CanonAll{T<:UInt128}(du::T) =
        (_CanonDPD(T, du, 100) && _CanonDPD(T, du, 90) && _CanonDPD(T, du, 80) &&
         _CanonDPD(T, du, 70)  && _CanonDPD(T, du, 60) && _CanonDPD(T, du, 50) &&
         _CanonDPD(T, du, 40)  && _CanonDPD(T, du, 30) && _CanonDPD(T, du, 20) &&
         _CanonDPD(T, du, 10)  && _CanonDPD(du))

# Compile-time computes of the exponent continuation field masks
# full exponent continuation field:                              */
EconMask{T<:DFTypes}(::Type{T}) = ((0x03ffffff>>(32-6-decEconL(T)))<<(32-6-decEconL(T)))
# same, not including its first digit (the qNaN/sNaN selector):
EconNaNMask{T<:DFTypes}(::Type{T}) = ((0x01ffffff>>(32-6-decEconL(T)))<<(32-6-decEconL(T)))

function IsCanonical{T<:Union{Double,Quad}}(df::T)
    if IsSpecial(df)
        IsInf(df) && return (_topWord(df) & EconMask(T) != 0 && IsCCZero(df))
        # is a NaN
        (_topWord(df) & EconNaNMask(T)) && return false # exponent continuation
        IsCCZero(df) && return true                   # coefficient continuation
        # drop through to check payload
    end
    _CanonAll(_asUInt(df))
end

_DecletMask(::Type{Double}) = 0x0400912449124491
_DecletMask(::Type{Quad})   = 0x04000912449124491244912449124491

"""
And -- logical digitwise AND of two DecimalNumbers

  result gets the result of ANDing dfl and dfr
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result, which will be canonical with sign=0

The operands must be positive, finite with exponent q=0, and
comprise just zeros and ones; if not, Invalid operation results.
"""
function And{T<:Union{Double,Quad}}(dfl::T, dfr::T, dc::Context)
    # Check that the operands are positive finite integers (q=0) with just 0s and 1s
    IsUInt01(dfl) && IsUInt01(dfr) && IsCC01(dfl) && IsCC01(dfr) &&
        return (Zero(T) | ((_asUInt(dfl) & _asUInt(dfr)) & _DecletMask(T)))
    decInvalid(dc)
end

"""
Or -- logical digitwise OR of two DecimalNumbers

  result gets the result of ORing dfl and dfr
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result, which will be canonical with sign=0

The operands must be positive, finite with exponent q=0, and
comprise just zeros and ones; if not, Invalid operation results.
"""
function Or{T<:Union{Double,Quad}}(dfl::T, dfr::T, dc::Context)
    # Check that the operands are positive finite integers (q=0) with just 0s and 1s
    IsUInt01(dfl) && IsUInt01(dfr) && IsCC01(dfl) && IsCC01(dfr) &&
        return (Zero(T) | ((_asUInt(dfl) | _asUInt(dfr)) & _DecletMask(T)))
    decInvalid(dc)
end

"""
Xor -- logical digitwise XOR of two DecimalNumbers

  result gets the result of XORing dfl and dfr
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result, which will be canonical with sign=0

The operands must be positive, finite with exponent q=0, and
comprise just zeros and ones; if not, Invalid operation results.
"""
function Xor{T<:Union{Double,Quad}}(dfl::T, dfr::T, dc::Context)
    # Check that the operands are positive finite integers (q=0) with just 0s and 1s
    IsUInt01(dfl) && IsUInt01(dfr) && IsCC01(dfl) && IsCC01(dfr) &&
        return (Zero(T) | ((_asUInt(dfl) ^ _asUInt(dfr)) & _DecletMask(T)))
    decInvalid(dc)
end

for typ in (Single, Double, Quad)
    dce = decEconL(typ) ; dce1 = 1<<dce ; dce2 = 2<<dce
    @eval const global $(symbol("_CombExp", string(typ))) =
        UInt32[    0,     0,     0,     0,     0,     0,     0,     0,
               $dce1, $dce1, $dce1, $dce1, $dce1, $dce1, $dce1, $dce1,
               $dce2, $dce2, $dce2, $dce2, $dce2, $dce2, $dce2, $dce2,
                   0,     0, $dce1, $dce1, $dce2, $dce2, DECFLOAT_Inf, DECFLOAT_NaN,
                   0,     0,     0,     0,     0,     0,     0,     0,
               $dce1, $dce1, $dce1, $dce1, $dce1, $dce1, $dce1, $dce1,
               $dce2, $dce2, $dce2, $dce2, $dce2, $dce2, $dce2, $dce2,
    		   0,     0, $dce1, $dce1, $dce2, $dce2, DECFLOAT_Inf, DECFLOAT_NaN]
    @eval decCombExp(::Type{$typ}) = $(symbol("_CombExp", string(typ)))
end

for typ in (:Single, :Double, :Quad)
    getlib(fun) = (symbol("dec",typ,fun), libdec)
    ref = @eval Ref{$typ}

"""
FromPacked -- set DecimalNumber from exponent and packed BCD

 df is the target DecimalNumber
 exp is the in-range unbiased exponent, q, or a special value in
   the form returned by GetExponent
 packed holds DECPMAX packed decimal digits plus a sign nibble
   (all 6 codes are OK); the first (MSD) is ignored if df is a NaN
   and all except sign are ignored if df is infinite.  For DOUBLE
   and QUAD the first (pad) nibble is also ignored in all cases.
   All coefficient nibbles must be in 0-9 and sign in A-F; results
   are undefined otherwise.
 returns df, which will be canonical

No error is possible, and no status will be set.
"""
@eval FromPacked(result::$ref, y::Int32, z::Vector{UInt8}) =
    ccall($(getlib(:FromPacked)), $ref, ($ref, Int32, Ptr{UInt8}), x, y, z)

"""
FromPackedChecked -- set from exponent and packed; checked

df is the target DecimalNumber
exp is the in-range unbiased exponent, q, or a special value in
    the form returned by GetExponent
packed holds DECPMAX packed decimal digits plus a sign nibble
   (all 6 codes are OK); the first (MSD) must be 0 if df is a NaN
   and all digits must be 0 if df is infinite.  For DOUBLE and
   QUAD the first (pad) nibble must be 0.
   All coefficient nibbles must be in 0-9 and sign in A-F.
returns df, which will be canonical or NULL if any of the
   requirements are not met (if this case df is unchanged); that
   is, the input data must be as returned by ToPacked,
   except that all six sign codes are acccepted.

No status will be set.
"""
@eval FromPackedChecked(result::$ref, y::Int32, z::Vector{UInt8}) =
    ccall($(getlib(:FromPackedChecked)), $ref, ($ref, Int32, Ptr{UInt8}), x, y, z)

"""
FromBCD -- set decFloat from exponent, BCD8, and sign

 df is the target Decimal
 exp is the in-range unbiased exponent, q, or a special value in
   the form returned by GetExponent
 bcdar holds DECPMAX digits to set the coefficient from, one
   digit in each byte (BCD8 encoding); the first (MSD) is ignored
   if df is a NaN; all are ignored if df is infinite.
   All bytes must be in 0-9; results are undefined otherwise.
 sig is DECFLOAT_Sign to set the sign bit, 0 otherwise
 returns df, which will be canonical

No error is possible, and no status will be set.
"""
@eval FromBCD(result::$ref, exp::Int32, bcdarr::Vector{UInt8}, sig::Int32) =
    ccall($(getlib(:FromBCD)), $ref,
          ($ref, Int32, Cstring, Int32), result, exp, bcdarr, sig)

"""
SetCoefficient -- set coefficient from BCD8

 df is the target DecimalNumber (and source of exponent/special value)
 bcdar holds DECPMAX digits to set the coefficient from, one
   digit in each byte (BCD8 encoding); the first (MSD) is ignored
   if df is a NaN; all are ignored if df is infinite.
 sig is DECFLOAT_Sign to set the sign bit, 0 otherwise
 returns df, which will be canonical

No error is possible, and no status will be set.
"""
@eval SetCoefficient(df::$ref, bcdarr::Vector{UInt8}, sig::Int32) =
    ccall($(getlib(:SetCoefficient)), $ref, ($ref, Ptr{UInt8}, Int32), df, bcdarr, sig)

"""
SetExponent -- set exponent or special value

 df  is the target DecimalNumber (and source of coefficient/payload)
 dc  is the context for reporting status
 exp is the unbiased exponent, q, or a special value in the form
   returned by DecimalNumberGetExponent
 returns df, which will be canonical

No error is possible, but Overflow or Underflow might occur.
"""
@eval SetExponent(df::$ref, dc::Context, exp::Int32) =
    ccall($(getlib(:SetExponent)), $ref, ($ref, Ref{Context}, Int32), df, dc, exp)

"""
Show -- printf a DecimalNumber in hexadecimal and decimal
  df  is the DecimalNumber to show
  tag is a tag string displayed with the number

This is a debug aid; the precise format of the string may change.
"""
@eval Show(df::$ref, tag::ASCIIString = "") =
    ccall($(getlib(:Show)), Void, ($ref, Cstring), df, tag)

"""
GetCoefficient -- get coefficient as BCD8

 df is the DecimalNumber from which to extract the coefficient
 bcdarr is where DECPMAX bytes will be written, one BCD digit in
   each byte (BCD8 encoding); if df is a NaN the first byte will
   be zero, and if it is infinite they will all be zero
 returns the sign of the coefficient (DECFLOAT_Sign if negative,
   0 otherwise)

No error is possible, and no status will be set.  If df is a
special value the array is set to zeros (for Infinity) or to the
payload of a qNaN or sNaN.
"""
@eval GetCoefficient(df::$ref, bcdarr::Vector{UInt8}) =
    ccall($(getlib(:GetCoefficient)), Int32, ($ref, Ptr{UInt8}), df, bcdarr)

"""
GetExponent -- get unbiased exponent

 df is the DecimalNumber from which to extract the exponent
 returns the exponent, q.

No error is possible, and no status will be set.  If df is a
special value the first seven bits of the DecimalNumber are returned,
left adjusted and with the first (sign) bit set to 0 (followed by
25 0 bits).  e.g., -sNaN would return 0x7e000000 (DECFLOAT_sNaN).
"""
@eval GetExponent(df::$ref) = ccall($(getlib(:GetExponent)), Int32, ($ref, ), df)

"""
ToBCD -- get sign, exponent, and BCD8 from a DecimalNumber

 df is the source DecimalNumber
 exp will be set to the unbiased exponent, q, or to a special
   value in the form returned by GetExponent
 bcdarr is where DECPMAX bytes will be written, one BCD digit in
   each byte (BCD8 encoding); if df is a NaN the first byte will
   be zero, and if it is infinite they will all be zero
 returns the sign of the coefficient (DECFLOAT_Sign if negative,
   0 otherwise)

No error is possible, and no status will be set.
"""
@eval ToBCD(df::$ref, exp::Ref{Int32}, bcdarr::Ref{UInt8}) =
    ccall($(getlib(:ToBCD)), Int32, ($ref, Ref{Int32}, Ref{UInt8}), df, exp, bcdarr)

"""
ToPacked -- convert DecimalNumber to Packed decimal + exponent

 df is the source DecimalNumber
 exp will be set to the unbiased exponent, q, or to a special
   value in the form returned by GetExponent
 packed is where DECPMAX nibbles will be written with the sign as
   final nibble (0x0c for +, 0x0d for -); a NaN has a first nibble
   of zero, and an infinity is all zeros. decDouble and decQuad
   have a additional leading zero nibble, leading to result
   lengths of 4, 9, and 18 bytes.
 returns the sign of the coefficient (DECFLOAT_Sign if negative,
   0 otherwise)

No error is possible, and no status will be set.
"""
@eval ToPacked(df::$ref, exp::Ref{Int32}, packed::Ref{UInt8}) =
    ccall($(getlib(:ToPacked)), Int32, ($ref, Ref{Int32}, Ref{UInt8}), df, exp, packed)

"""
FromString -- conversion from numeric string

 result  is the DecimalNumber format number which gets the result of
         the conversion
 *string is the character string which should contain a valid
         number (which may be a special value), \0-terminated
         If there are too many significant digits in the
         coefficient it will be rounded.
 dc      is the context
 returns result

The length of the coefficient and the size of the exponent are
checked by this routine, so the correct error (Underflow or
Overflow) can be reported or rounding applied, as necessary.

There is no limit to the coefficient length for finite inputs;
NaN payloads must be integers with no more than DECPMAX-1 digits.
Exponents may have up to nine significant digits.

If bad syntax is detected, the result will be a quiet NaN.
"""
@eval FromString(result::$ref, str::ASCIIString, dc::Context) =
    ccall($(getlib(:FromString)), $ref, ($ref, Cstring, Ref{Context}),
          result, str, dc)


"""
ToString -- conversion to numeric string

 df is the DecimalNumber format number to convert
 str is the string where the result will be laid out

string must be at least DECPMAX+9 characters (the worst case is
"-0.00000nnn...nnn\0", which is as long as the exponent form when
DECEMAXD<=4); this condition is asserted above

No error is possible, and no status will be set
"""
@eval ToString(df::$ref, buf::Vector{UInt8}) =
    ccall($(getlib(:ToString)),  Ptr{UInt8}, ($ref, Ptr{UInt8}), df, buf)

"""
ToEngString -- conversion to numeric string, engineering

 df is the DecimalNumber format number to convert
 str is the string where the result will be laid out

string must be at least DECPMAX+9 characters (the worst case is
"-0.00000nnn...nnn\0", which is as long as the exponent form when
DECEMAXD<=4); this condition is asserted above

No error is possible, and no status will be set
"""
@eval ToEngString(df::$ref, buf::Vector{UInt8}) =
    ccall($(getlib(:ToEngString)), Ptr{UInt8}, ($ref, Ptr{UInt8}), df, buf)

#if typ != :Single

"""
ToInt32 -- round to 32-bit binary integer (4 flavours)

  df    is the DecimalNumber to round
  dc    is the context
  round is the rounding mode to use
  returns a uInt or an Int, rounded according to the name

Invalid will always be signaled if df is a NaN, is Infinite, or is
outside the range of the target; Inexact will not be signaled for
simple rounding unless 'Exact' appears in the name.
"""
for fn in ("", "U"), exact in ("", "Exact")
    sym = symbol("To", fn, "Int32", exact)
    @eval $sym(df::$ref, dc::Context, rnd::rounding) =
        ccall($(getlib(sym)), $(symbol(fn,"Int32")),
              ($ref, Ref{Context}, Int32(rounding)), df, dc, rnd)
end

"""
FromInt32 -- initialise a DecimalNumber from an Int

  result gets the converted Int
  n      is the Int to convert
  returns result

The result is Exact; no errors or exceptions are possible.
"""
@eval FromInt32(result::$ref, y::Int32) =
    ccall($(getlib(:FromInt32)), $ref, ($ref, Int32), result, y)

"""
FromUInt32 -- initialise a DecimalNumber from a uInt

  result gets the converted uInt
  n      is the uInt to convert
  returns result

The result is Exact; no errors or exceptions are possible.
"""
@eval FromUInt32(result::$ref, y::UInt32) =
    ccall($(getlib(:FromUInt32)), $ref, ($ref, UInt32), result, y)

"""
Abs -- absolute value, heeding NaNs, etc.

  result gets the canonicalized df with sign 0
  df     is the DecimalNumber to abs
  dc     is the context
  returns result

This has the same effect as Plus unless df is negative,
in which case it has the same effect as Minus.  The
effect is also the same as CopyAbs except that NaNs are
handled normally (the sign of a NaN is not affected, and an sNaN
will signal) and the result will be canonical.
"""
function Abs end

"""
Add -- add two DecimalNumbers

  result gets the result of adding dfl and dfr:
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result

"""
function Add end


"""
Class -- return the class of a DecimalNumber

  df is the DecimalNumber to test
  returns the decClass that df falls into
"""
function Class end

"""
ClassString -- return the class of a DecimalNumber as a string

  df is the DecimalNumber to test
  returns a constant string describing the class df falls into
"""
function ClassString end

## Computational (result is a DecimalNumber)
"""
Invert -- logical digitwise INVERT of a DecimalNumber

  result gets the result of INVERTing df
  df     is the DecimalNumber to invert
  dc     is the context
  returns result, which will be canonical with sign=0

The operand must be positive, finite with exponent q=0, and
comprise just zeros and ones; if not, Invalid operation results.
"""
function Invert end

"""
LogB -- return adjusted exponent, by 754 rules

  result gets the adjusted exponent as an integer, or a NaN etc.
  df     is the DecimalNumber to be examined
  dc     is the context
  returns result

Notable cases:
  A<0 -> Use |A|
  A=0 -> -Infinity (Division by zero)
  A=Infinite -> +Infinity (Exact)
  A=1 exactly -> 0 (Exact)
  NaNs are propagated as usual
"""
function LobB end

"""
Minus -- negate value, heeding NaNs, etc.

  result gets the canonicalized 0-df
  df     is the DecimalNumber to minus
  dc     is the context
  returns result

This has the same effect as 0-df where the exponent of the zero is
the same as that of df (if df is finite).
The effect is also the same as CopyNegate except that NaNs
are handled normally (the sign of a NaN is not affected, and an
sNaN will signal), the result is canonical, and zero gets sign 0.
"""
function Minus end

"""
NextMinus -- next towards -Infinity

  result gets the next lesser DecimalNumber
  dfl    is the DecimalNumber to start with
  dc     is the context
  returns result

This is 754 nextdown; Invalid is the only status possible (from
an sNaN).
"""
function NextMinus end

"""
NextPlus -- next towards +Infinity

  result gets the next larger DecimalNumber
  dfl    is the DecimalNumber to start with
  dc     is the context
  returns result

This is 754 nextup; Invalid is the only status possible (from
an sNaN).
"""
function NextPlus end

"""
Plus -- add value to 0, heeding NaNs, etc.

  result gets the canonicalized 0+df
  df     is the DecimalNumber to plus
  dc     is the context
  returns result

This has the same effect as 0+df where the exponent of the zero is
the same as that of df (if df is finite).
The effect is also the same as Copy except that NaNs
are handled normally (the sign of a NaN is not affected, and an
sNaN will signal), the result is canonical, and zero gets sign 0.
"""
function Plus end

"""
Reduce -- reduce finite coefficient to minimum length

  result gets the reduced DecimalNumber
  df     is the source DecimalNumber
  dc     is the context
  returns result, which will be canonical

This removes all possible trailing zeros from the coefficient;
some may remain when the number is very close to Nmax.
Special values are unchanged and no status is set unless df=sNaN.
Reduced zero has an exponent q=0.
"""
function Reduce end

for fn in (:Abs, :Invert, :LogB, :Minus, :NextMinus, :NextPlus, :Plus, :Reduce)
    @eval $fn(result::$ref, df::$ref, dc::Context) =
        ccall($(getlib(fn)), $ref, ($ref, $ref, Ref{Context}), result, df, dc)
end

"""
FMA -- multiply and add three DecimalNumbers, fused

  result gets the result of (dfl*dfr)+dff with a single rounding
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dff    is the final DecimalNumber (fhs)
  dc     is the context
  returns result

"""
@eval FMA(result::$ref, dfl::$ref, dfr::$ref, dff::$ref, dc::Context) =
    ccall($(getlib(:FMA)), $ref,
          ($ref, $ref, $ref, $ref, Ref{Context}), result, dfl, dfr, dff, dc)

"""
Max -- return maxnum of two operands

  result gets the chosen DecimalNumber
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result

If just one operand is a quiet NaN it is ignored.
"""
function Max end

"""
MaxMag -- return maxnummag of two operands

  result gets the chosen DecimalNumber
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result

Returns according to the magnitude comparisons if both numeric and
unequal, otherwise returns maxnum
"""
function MaxMag end

"""
Min -- return minnum of two operands

  result gets the chosen DecimalNumber
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result

If just one operand is a quiet NaN it is ignored.
"""
function Min end

"""
MinMag -- return minnummag of two operands

  result gets the chosen DecimalNumber
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result

Returns according to the magnitude comparisons if both numeric and
unequal, otherwise returns minnum
"""
function MinMag end

"""
Multiply -- multiply two DecimalNumbers

  result gets the result of multiplying dfl and dfr:
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result

"""
function Multiply end

"""
NextToward -- next towards a DecimalNumber

  result gets the next DecimalNumber
  dfl    is the DecimalNumber to start with
  dfr    is the DecimalNumber to move toward
  dc     is the context
  returns result

This is 754-1985 nextafter, as modified during revision (dropped
from 754-2008); status may be set unless the result is a normal
number.
"""
function NextToward end

"""
Quantize -- quantize a DecimalNumber

  result gets the result of quantizing dfl to match dfr
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs), which sets the exponent
  dc     is the context
  returns result

Unless there is an error or the result is infinite, the exponent
of result is guaranteed to be the same as that of dfr.
"""
function Quantize end

"""
Remainder -- integer divide and return remainder

  result gets the remainder of dividing dfl by dfr:
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result

"""
function Remainder end

"""
RemainderNear -- integer divide to nearest and remainder

  result gets the remainder of dividing dfl by dfr:
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result

This is the IEEE remainder, where the nearest integer is used.
"""
function RemainderNear end

"""
Rotate -- rotate the coefficient of a DecimalNumber left/right

  result gets the result of rotating dfl
  dfl    is the source DecimalNumber to rotate
  dfr    is the count of digits to rotate, an integer (with q=0)
  dc     is the context
  returns result

The digits of the coefficient of dfl are rotated to the left (if
dfr is positive) or to the right (if dfr is negative) without
adjusting the exponent or the sign of dfl.

dfr must be in the range -DECPMAX through +DECPMAX.
NaNs are propagated as usual.  An infinite dfl is unaffected (but
dfr must be valid).  No status is set unless dfr is invalid or an
operand is an sNaN.  The result is canonical.
"""
function Rotate end

"""
ScaleB -- multiply by a power of 10, as per 754

  result gets the result of the operation
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs), am integer (with q=0)
  dc     is the context
  returns result

This computes result=dfl x 10**dfr where dfr is an integer in the
range +/-2*(emax+pmax), typically resulting from LogB.
Underflow and Overflow (with Inexact) may occur.  NaNs propagate
as usual.
"""
function ScaleB end

"""
Shift -- shift the coefficient of a DecimalNumber left or right

  result gets the result of shifting dfl
  dfl    is the source DecimalNumber to shift
  dfr    is the count of digits to shift, an integer (with q=0)
  dc     is the context
  returns result

The digits of the coefficient of dfl are shifted to the left (if
dfr is positive) or to the right (if dfr is negative) without
adjusting the exponent or the sign of dfl.

dfr must be in the range -DECPMAX through +DECPMAX.
NaNs are propagated as usual.  An infinite dfl is unaffected (but
dfr must be valid).  No status is set unless dfr is invalid or an
operand is an sNaN.  The result is canonical.
"""
function Shift end

"""
Subtract -- subtract a DecimalNumber from another

  result gets the result of subtracting dfr from dfl:
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result

"""
function Subtract end

"""
ToIntegralExact -- round to integral value (two flavours)

  result gets the result
  df     is the DecimalNumber to round
  dc     is the context
  round  is the rounding mode to use
  returns result

No exceptions, even Inexact, are raised except for sNaN input, or
if 'Exact' appears in the name.
"""
function ToIntegralExact end


"""
Compare -- compare two DecimalNumbers; quiet NaNs allowed

  result gets the result of comparing dfl and dfr
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result, which may be -1, 0, 1, or NaN (Unordered)
"""
function Compare end

"""
CompareSignal -- compare two DecimalNumbers; all NaNs signal

  result gets the result of comparing dfl and dfr
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result, which may be -1, 0, 1, or NaN (Unordered)
"""
function CompareSignal end

for fn in (:Add, :Divide, :DivideInteger, :Max, :MaxMag, :Min, :MinMag, :Multiply,
           :NextToward, :Quantize, :Remainder, :RemainderNear, :Rotate, :ScaleB, :Shift,
           :Subtract, :ToIntegralExact, :Compare, :CompareSignal)
    @eval begin
        function $fn(result::$ref, dfl::$ref, dfr::$ref, dc::Context)
            #println($(getlib(fn)), ", ref=", $ref, " dfl=", dfl, ", dfr=", dfr)
            ccall($(getlib(fn)), $ref, ($ref, $ref, $ref, Ref{Context}), result, dfl, dfr, dc)
        end
    end
end

"""
ToIntegralValue -- round to integral value (two flavours)

  result gets the result
  df     is the DecimalNumber to round
  dc     is the context
  round  is the rounding mode to use
  returns result

No exceptions, even Inexact, are raised except for sNaN input, or
if 'Exact' appears in the name.
"""
@eval ToIntegralValue(result::$ref, df::$ref, dc::Context, rnd::rounding) =
    ccall($(getlib(:ToIntegralValue)), $ref,
          ($ref, $ref, Ref{Context}, Int32), result, df, dc, Int32(rnd))

"""
CompareTotal -- compare two DecimalNumbers with total ordering

  result gets the result of comparing dfl and dfr
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  returns result, which may be -1, 0, or 1
"""
@eval CompareTotal(result::$ref, dfl::$ref, dfr::$ref) =
    ccall($(getlib(:CompareTotal)), $ref, ($ref, $ref, $ref), result, dfl, dfr)

"""
CompareTotalMag -- compare magnitudes with total ordering

  result gets the result of comparing abs(dfl) and abs(dfr)
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  returns result, which may be -1, 0, or 1
"""
@eval CompareTotalMag(result::$ref, dfl::$ref, dfr::$ref) =
    ccall($(getlib(:CompareTotal)), $ref, ($ref, $ref, $ref), result, dfl, dfr)

"""
Canonical -- copy a DecimalNumber, making canonical

  result gets the canonicalized df
  df     is the DecimalNumber to copy and make canonical
  returns result

This works on specials, too; no error or exception is possible.
"""
function Canonical end

"""
Copy -- copy a DecimalNumber as-is

  result gets the copy of df
  df     is the DecimalNumber to copy
  returns result

This is a bitwise operation; no errors or exceptions are possible.
"""
function Copy end

"""
CopyAbs -- copy a DecimalNumber as-is and set sign bit to 0

  result gets the copy of df with sign bit 0
  df     is the DecimalNumber to copy
  returns result

This is a bitwise operation; no errors or exceptions are possible.
"""
function CopyAbs end

"""
CopyNegate -- copy a DecimalNumber as-is with inverted sign bit

  result gets the copy of df with sign bit inverted
  df     is the DecimalNumber to copy
  returns result

This is a bitwise operation; no errors or exceptions are possible.
"""
function CopyNegate end

# Copies
for fn in (:Canonical, :Copy, :CopyAbs, :CopyNegate)
    @eval $fn(result::$ref, df::$ref) = ccall($(getlib(fn)), $ref, ($ref, $ref), result, df)
end

"""
CopySign -- copy a DecimalNumber with the sign of another

  result gets the result of copying dfl with the sign of dfr
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  returns result

This is a bitwise operation; no errors or exceptions are possible.
"""
@eval CopySign(result::$ref, dfl::$ref, dfr::$ref) =
    ccall($(getlib(:CopySign)), $ref, ($ref, $ref, $ref), result, dfl, dfr)

# Non-computational
@eval Class(df::$ref) = Class(ccall($(getlib(:Class)), Int32, ($ref,), df))
@eval ClassString(df::$ref) = ccall($(getlib(:ClassString)), Cstring, ($ref,), df)

"""
Version -- return package version string

returns a constant string describing this package
"""
@eval Version(::Type{$typ}) = ccall($(getlib(:Version)), Cstring, ())

"""
SameQuantum -- test DecimalNumbers for same quantum

  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  returns 1 if the operands have the same quantum, 0 otherwise

No error is possible and no status results.
"""
@eval SameQuantum(dfl::$ref, dfr::$ref) =
    ccall($(getlib(:SameQuantum)), UInt32, ($ref, $ref), dfl, dfr)

"""
Digits -- return the number of digits in a DecimalNumber

  df is the DecimalNumber to investigate
  returns the number of significant digits in the DecimalNumber; a
    zero coefficient returns 1 as does an infinity (a NaN returns
    the number of digits in the payload)
"""
@eval Digits(df::$ref) = ccall($(getlib(:Digits)), UInt32, ($ref,), df)

"""
Divide -- divide a DecimalNumber by another

  result gets the result of dividing dfl by dfr:
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result

"""
function Divide end

"""
DivideInteger -- integer divide a DecimalNumber by another

  result gets the result of dividing dfl by dfr:
  dfl    is the first DecimalNumber (lhs)
  dfr    is the second DecimalNumber (rhs)
  dc     is the context
  returns result

"""
function DivideInteger end

end

"""
ToWider -- conversion to next-wider format

 source  is the DecimalNumber format number which will be widened
 wider   is the next wider format number which gets the result of the conversion
 returns wider

Widening is always exact; no status is set (sNaNs are copied and not signal).
The result will be canonical if the source is, and may or may not be if the source is not.

widening is not possible for decQuad format numbers; simply omit
"""
function ToWider end

"""
FromWider -- conversion from next-wider format

 result  is the DecimalNumber format number which gets the result of the conversion
 wider   is the DecimalNumberWider format number which will be narrowed
 dc      is the context
 returns result

Narrowing can cause rounding, overflow, etc., but not Invalid operation
(sNaNs are copied and do not signal).
"""
function FromWider end

ToWider(dst::Ref{Double}, src::Ref{Single}) =
    ccall((:decSingleToWider, libdec), Ref{Double}, (Ref{Single}, Ref{Double}), src, dst)
ToWider(dst::Ref{Quad}, src::Ref{Double}) =
    ccall((:decDoubleToWider, libdec), Ref{Quad}, (Ref{Double}, Ref{Quad}), src, dst)
FromWider(dst::Ref{Single}, src::Ref{Double}, dc::Ref{Context}) =
    ccall((:decSingleFromWider), Ref{Single}, (Ref{Single}, Ref{Double}), dst, src, dc)
FromWider(dst::Ref{Double}, src::Ref{Quad}, dc::Ref{Context}) =
    ccall((:decDoubleFromWider), Ref{Double}, (Ref{Double}, Ref{Quad}), dst, src, dc)

#=
function ToNumber end
function FromNumber end

for (nam, dig) in ((:Single, 32), (:Double, 64), (:Quad, 128))
    @eval ToNumber(dn::Ref{DecimalFP}, dq::Ref{$nam}) =
        ccall((symbol(:decimal,$dig,:ToNumber), @declib), Ref{DecimalFP},
              (Ref{$nam}, Ref{DecimalFP}), dq, dn)
    @eval FromNumber(dq::Ref{$nam}, dn::Ref{DecimalFP}, dc::Ref{Context}) =
        ccall((symbol(:decimal,$dig,:FromNumber), @declib), Ref{$nam},
              (Ref{nam}, Ref{DecimalFP}, Ref{Context}), dq, dn, dc)
=#

function GetCoeffI{T<:DFTypes}(df::T)
    IsInfinite(df) && return zeros(UInt8, decPmax(T))
    vec = get_coeff(df)
    IsNaN(df) && (vec[1] = 0) # MSD needs correcting
    vec
end

GetCoeff{T<:DFTypes}(df::T) = (GetCoeffI(df), IsSigned(df))

function GetExp{T<:DFTypes}(df::T)
    IsSpecial(df) && return (_topWord(df) & 0x7e000000)
    _GetExpUn(df)
end
