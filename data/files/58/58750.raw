"""
DecTypes.jl -- Types and constants for Decimals

Julia conversion of decNumber package, portions are:
Copyright (c) Gandalf Software, Inc. 2015

Made available under the same terms as decNumber, i.e.
ICU License -- ICU 1.8.1 and later.

Any Julia specific issues please send to Scott Jones:
  scottjones@alum.mit.edu

Derived from decNumber package, decContext.h:
------------------------------------------------------------------
Copyright (c) IBM Corporation, 2000, 2010.  All rights reserved.

This software is made available under the terms of the
ICU License -- ICU 1.8.1 and later.

The description and User's Guide ("The decNumber C Library") for
this software is called decNumber.pdf.  This document is
available, together with arithmetic and format specifications,
testcases, and Web links, on the General Decimal Arithmetic page.

Please send comments, suggestions, and corrections to the author:
  mfc@uk.ibm.com
  Mike Cowlishaw, IBM Fellow
  IBM UK, PO Box 31, Birmingham Road, Warwick CV34 5JL, UK
------------------------------------------------------------------
"""
module DecTypes end

abstract DecimalFloatingPoint <: AbstractFloat

bitstype 32  Single <: DecimalFloatingPoint
bitstype 64  Double <: DecimalFloatingPoint
bitstype 128 Quad   <: DecimalFloatingPoint

typealias decNU UInt16
typealias DFTypes Union{Single, Double, Quad}

DecimalNumber = DecimalFloatingPoint

#=
type DecimalFP{N} <: DecimalFloatingPoint
    digits::Int32	# Count of digits in the coefficient; >0
    exponent::Int32     # Unadjusted exponent, unbiased, in range: -1999999997 through 999999999
    bits::UInt8		# Indicator bits (see above)
    data::NTuple{N,decNU} # Coefficient, from least significant unit
end
=#

const typnam = (:Single, :Double, :Quad)

for (nam, values) in
    ((:Pmax,   (  7,   16,    34)), # Maximum digits
     (:Emin,   (-95, -383, -6143)), # Minumum adjusted exponent
     (:Emax,   ( 96,  384,  6144)), # Maximum adjusted exponent
     (:EmaxD,  (  3,    3,     4)), # Maximum exponent digits
     (:Bias,   (101,  398,  6176)), # Bias for the exponent
     (:String, ( 16,   25,    43)), # Maximum string length, +1
     (:EconL,  (  6,    8,    12)), # Exponent continuation length
     (:Declets,(  2,    5,    11)), # Count of declets
     (:Bits,   ( 32,   64,   128)), # Bits
     (:UType,  (UInt32,UInt64,UInt128)))
    for i = 1:3
        @eval $(symbol(:dec,nam))(::Type{$(typnam[i])}) = $(values[i])
    end
end

# export Context, rounding, Classification

"""Extended flags setting -- set this to false to use only IEEE flags"""
const global DECEXTFLAG = true

"""Conditional code flag -- set this to 0 for best performance"""
const global DECSUBSET  = false    # true -> enable subset arithmetic

# Bit settings for decNumber.bits
const global DECNEG  = 0x80      # Sign; 1=negative, 0=positive or zero
const global DECINF  = 0x40      # 1=Infinity
const global DECNAN  = 0x20      # 1=NaN
const global DECSNAN = 0x10      # 1=sNaN
# The remaining bits are reserved; they must be 0
const global DECSPECIAL = (DECINF|DECNAN|DECSNAN) # any special value

"""Context for operations, with associated constants"""
@enum(rounding,
    ROUND_CEILING,             # round towards +infinity
    ROUND_UP,                  # round away from 0
    ROUND_HALF_UP,             # 0.5 rounds up
    ROUND_HALF_EVEN,           # 0.5 rounds to nearest even
    ROUND_HALF_DOWN,           # 0.5 rounds down
    ROUND_DOWN,                # round towards 0 (truncate)
    ROUND_FLOOR,               # round towards -infinity
    ROUND_05UP,                # round for reround
    ROUND_MAX                  # enum must be less than this
)

const global ROUND_DEFAULT = ROUND_HALF_EVEN

type Context
    digits::Int32         # working precision
    emax::Int32           # maximum positive exponent
    emin::Int32           # minimum negative exponent
    round::rounding       # rounding mode
    traps::UInt32         # trap-enabler flags
    status::UInt32        # status flags
    clamp::UInt8          # flag: apply IEEE exponent clamp
    #if DECSUBSET
    extended::UInt8       # flag: special-values allowed
    #end
    Context() = new(0,0,0,ROUND_DEFAULT,0,0,0,0)
end

## Maxima and Minima for context settings
const global MAX_DIGITS = 999999999
const global MIN_DIGITS =         1
const global MAX_EMAX   = 999999999
const global MIN_EMAX   =         0
const global MAX_EMIN   =         0
const global MIN_EMIN   =-999999999
const global MAX_MATH   =    999999 # max emax, etc., for math funcs.

"""Classifications for decimal numbers, aligned with 754 (note that
   'normal' and 'subnormal' are meaningful only with a Context
   or a fixed size format).
"""
@enum(Classification,
    CLASS_SNAN,
    CLASS_QNAN,
    CLASS_NEG_INF,
    CLASS_NEG_NORMAL,
    CLASS_NEG_SUBNORMAL,
    CLASS_NEG_ZERO,
    CLASS_POS_ZERO,
    CLASS_POS_SUBNORMAL,
    CLASS_POS_NORMAL,
    CLASS_POS_INF
)
## Strings for the Classes
const global ClassString_SN = "sNaN"
const global ClassString_QN = "NaN"
const global ClassString_NI = "-Infinity"
const global ClassString_NN = "-Normal"
const global ClassString_NS = "-Subnormal"
const global ClassString_NZ = "-Zero"
const global ClassString_PZ = "+Zero"
const global ClassString_PS = "+Subnormal"
const global ClassString_PN = "+Normal"
const global ClassString_PI = "+Infinity"
const global ClassString_UN = "Invalid"

## Trap-enabler and Status flags (exceptional conditions), and
## their names.  The top byte is reserved for internal use
if DECEXTFLAG
    ## Extended flags
    const global Conversion_syntax    = 0x00000001
    const global Division_by_zero     = 0x00000002
    const global Division_impossible  = 0x00000004
    const global Division_undefined   = 0x00000008
    const global Insufficient_storage = 0x00000010 # [when malloc fails]
    const global Inexact              = 0x00000020
    const global Invalid_context      = 0x00000040
    const global Invalid_operation    = 0x00000080
    const global Lost_digits          = 0x00000100
    const global Overflow             = 0x00000200
    const global Clamped              = 0x00000400
    const global Rounded              = 0x00000800
    const global Subnormal            = 0x00001000
    const global Underflow            = 0x00002000
else
    ## IEEE flags only
    const global Conversion_syntax    = 0x00000010
    const global Division_by_zero     = 0x00000002
    const global Division_impossible  = 0x00000010
    const global Division_undefined   = 0x00000010
    const global Insufficient_storage = 0x00000010 # [when malloc fails]
    const global Inexact              = 0x00000001
    const global Invalid_context      = 0x00000010
    const global Invalid_operation    = 0x00000010
    const global Lost_digits          = 0x00000000
    const global Overflow             = 0x00000008
    const global Clamped              = 0x00000000
    const global Rounded              = 0x00000000
    const global Subnormal            = 0x00000000
    const global Underflow            = 0x00000004
end

## IEEE 754 groupings for the flags
## [Clamped, Lost_digits, Rounded, and Subnormal
## are not in IEEE 754]
const global IEEE_754_Division_by_zero = Division_by_zero
if DECSUBSET
    const global IEEE_754_Inexact       = Inexact | Lost_digits
else
    const global IEEE_754_Inexact       = Inexact
end
const global IEEE_754_Invalid_operation =
    (Conversion_syntax | Division_impossible | Division_undefined |
     Insufficient_storage | Invalid_context | Invalid_operation)

const global IEEE_754_Overflow      = Overflow
const global IEEE_754_Underflow     = Underflow

## flags which are normally errors (result is qNaN, infinite, or 0)
const global Errors =
    (IEEE_754_Division_by_zero | IEEE_754_Invalid_operation |
     IEEE_754_Overflow | IEEE_754_Underflow)

## flags which cause a result to become qNaN
const global NaNs   = IEEE_754_Invalid_operation

## flags which are normally for information only (finite results)
if DECSUBSET
    const global Information =
        (Clamped | Rounded | Inexact | Lost_digits)
else
    const global Information = (Clamped | Rounded | Inexact)
end

## IEEE 854 names (for compatibility with older decNumber versions)
const global IEEE_854_Division_by_zero  = IEEE_754_Division_by_zero
const global IEEE_854_Inexact           = IEEE_754_Inexact
const global IEEE_854_Invalid_operation = IEEE_754_Invalid_operation
const global IEEE_854_Overflow          = IEEE_754_Overflow
const global IEEE_854_Underflow         = IEEE_754_Underflow

## Name strings for the exceptional conditions
const global Condition_CS = "Conversion syntax"
const global Condition_DZ = "Division by zero"
const global Condition_DI = "Division impossible"
const global Condition_DU = "Division undefined"
const global Condition_IE = "Inexact"
const global Condition_IS = "Insufficient storage"
const global Condition_IC = "Invalid context"
const global Condition_IO = "Invalid operation"
const global Condition_LD = "Lost digits"
const global Condition_OV = "Overflow"
const global Condition_PA = "Clamped"
const global Condition_RO = "Rounded"
const global Condition_SU = "Subnormal"
const global Condition_UN = "Underflow"
const global Condition_ZE = "No status"
const global Condition_MU = "Multiple status"

# length of the longest string, including terminator    
const global Condition_Length = 21

## Initialization descriptors, used by ContextDefault
const global INIT_BASE       =   0
const global INIT_DECIMAL32  =  32
const global INIT_DECIMAL64  =  64
const global INIT_DECIMAL128 = 128
## Synonyms
const global INIT_DECSINGLE  = INIT_DECIMAL32
const global INIT_DECDOUBLE  = INIT_DECIMAL64
const global INIT_DECQUAD    = INIT_DECIMAL128
