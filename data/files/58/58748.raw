"""
Contexts.jl -- Context information for Decimal Float Point

Julia conversion of decNumber package, portions are:
Copyright (c) Gandalf Software, Inc. 2015

Made available under the same terms as decNumber, i.e.
ICU License -- ICU 1.8.1 and later.

Any Julia specific issues please send to Scott Jones:
  scottjones@alum.mit.edu

Derived from decNumber package, decContext.h, decContext.c
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

Context variables must always have valid values:

 status   -- [any bits may be cleared, but not set, by user]
 round    -- must be one of the enumerated rounding modes

The following variables are implied for fixed size formats (i.e.,
they are ignored) but should still be set correctly in case used
with decNumber functions:

 clamp    -- must be either 0 or 1
 digits   -- must be in the range 1 through 999999999
 emax     -- must be in the range 0 through 999999999
 emin     -- must be in the range 0 through -999999999
 extended -- must be either 0 or 1 [present only if DECSUBSET]
 traps    -- only defined bits may be set

------------------------------------------------------------------
"""
module Contexts end

## Context routines

"""
ClearStatus -- clear bits in current status

 dc is the context structure to be queried
 mask indicates the bits to be cleared (the status bit that
   corresponds to each 1 bit in the mask is cleared)
 returns context

No error is possible.
"""
ClearStatus(dc::Context, mask::UInt32) = (dc.status &= ~mask)

"""
Default -- initialize a context structure

 dc is the structure to be initialized
 kind selects the required set of default values, one of:
     INIT_BASE       -- select ANSI X3-274 defaults
     INIT_DECIMAL32  -- select IEEE 754 defaults, 32-bit
     INIT_DECIMAL64  -- select IEEE 754 defaults, 64-bit
     INIT_DECIMAL128 -- select IEEE 754 defaults, 128-bit
     For any other value a valid context is returned, but with
     Invalid_operation set in the status field.
 returns a context structure with the appropriate initial values.
"""
function Default(dc::Context, val::Integer)
    dc.digits   = 9              # 9 digits
    dc.emax     = MAX_EMAX       # 9-digit exponents
    dc.emin     = MIN_EMIN       # .. balanced
    dc.round    = ROUND_HALF_UP  # 0.5 rises
    dc.traps    = Errors         # all but informational
    dc.status   = 0              # cleared
    dc.clamp    = 0              # no clamping
    dc.extended = 0              # cleared

    if val == INIT_DECIMAL32 || val == INIT_DECIMAL64 || val == INIT_DECIMAL128
        dc.round    = ROUND_HALF_EVEN  # 0.5 to nearest even
        dc.traps    = 0                # no traps set
        dc.clamp    = 1                # clamp exponents
        dc.extended = 1                # set
        if val == INIT_DECIMAL32
            dc.digits, dc.emax, dc.emin = (7, 96, -95)
        elseif val == INIT_DECIMAL64
            dc.digits, dc.emax, dc.emin = (16, 384, -383)
        else
            dc.digits, dc.emax, dc.emin = (34, 6144, -6143)
        end
    elseif val != INIT_BASE
        SetStatus(context, Invalid_operation)  # trap
    end
    dc
end

Default(val::Integer) = Default(Context(), val)

"""
GetRounding -- return current rounding mode

 dc is the context structure to be queried
 returns the rounding mode

No error is possible.
"""
GetRounding(dc::Context) = dc.round

"""
GetStatus -- return current status

 dc is the context structure to be queried
 returns status

No error is possible.
"""
GetStatus(dc::Context) = dc.status

"""
RestoreStatus -- restore bits in current status

 dc is the context structure to be updated
 newstatus is the source for the bits to be restored
 mask indicates the bits to be restored (the status bit that
   corresponds to each 1 bit in the mask is set to the value of
   the correspnding bit in newstatus)
 returns context

No error is possible.
"""
RestoreStatus(dc::Context, newstatus::UInt32, mask::UInt32) =
    (dc.status = (dc.status & ~mask) | (newstatus & mask) ; dc)

"""
SaveStatus -- save bits in current status

 dc is the context structure to be queried
 mask indicates the bits to be saved (the status bits that
   correspond to each 1 bit in the mask are saved)
 returns the AND of the mask and the current status

No error is possible.
"""
SaveStatus(dc::Context, mask::UInt32) = dc.status & mask

"""
SetRounding -- set current rounding mode

 dc is the context structure to be updated
 newround is the value which will replace the current mode
 returns context

No error is possible.
"""
SetRounding(dc::Context, newround::rounding) = (dc.round = newround ; dc)

"""
SetStatus -- set status and raise trap if appropriate

 dc is the context structure to be updated
 status  is the exception code
 returns the context structure

Control may never return from this routine, if there is a signal
handler and it takes a long jump.
"""
function SetStatus(dc::Context, status::UInt32)
    dc.status |= status
    (status & dc.traps) != 0 && error("Decimal Floating Point Exception")
    dc
end

const global statusvalues = (
    (Condition_IO, Invalid_operation),
    (Condition_DZ, Division_by_zero),
    (Condition_OV, Overflow),
    (Condition_UN, Underflow),
    (Condition_IE, Inexact),
    (Condition_CS, Conversion_syntax),
    (Condition_DI, Division_impossible),
    (Condition_DU, Division_undefined),
    (Condition_IS, Insufficient_storage),
    (Condition_IC, Invalid_context),
    (Condition_LD, Lost_digits),
    (Condition_PA, Clamped),
    (Condition_RO, Rounded),
    (Condition_SU, Subnormal))

"""
SetStatusFromString -- set status from a string + trap

 dc is the context structure to be updated
 string is a string exactly equal to one that might be returned
           by StatusToString

 The status bit corresponding to the string is set, and a trap
 is raised if appropriate.

 returns the context structure, unless the string is equal to
   Condition_MU or is not recognized.  In these cases NULL is
   returned.
"""
function SetStatusFromString(dc::Context, val::AbstractString)
    for (str, status) in statusvalues
        str == val && return SetStatus(dc, status)
    end
    val == Condition_ZE && return dc
    Void()
end

"""
SetStatusFromStringQuiet -- set status from a string

 dc is the context structure to be updated
 string is a string exactly equal to one that might be returned
           by StatusToString

 The status bit corresponding to the string is set; no trap is
 raised.

 returns the context structure, unless the string is equal to
   Condition_MU or is not recognized.  In these cases NULL is
   returned.
"""
function SetStatusFromStringQuiet(dc::Context, val::AbstractString)
    for (str, status) in statusvalues
        str == val && return SetStatusQuiet(dc, status)
    end
    val == Condition_ZE && return dc
    Void()
end

"""
SetStatusQuiet -- set status without trap

 dc is the context structure to be updated
 status  is the exception code
 returns the context structure

No error is possible.
"""
SetStatusQuiet(dc::Context, status::UInt32) = (dc.status |= status ; dc)

"""
StatusToString -- convert status flags to a string

 context is a context with valid status field

 returns a constant string describing the condition.  If multiple
   (or no) flags are set, a generic constant message is returned.
"""
function StatusToString(dc::Context)
    for (str, status) in statusvalues
        dc.status == status && return str
    end
    dc.status == 0 && return Condition_ZE
    Condition_MU  # Multiple errors
end

"""
TestSavedStatus -- test bits in saved status

 oldstatus is the status word to be tested
 mask indicates the bits to be tested (the oldstatus bits that
   correspond to each 1 bit in the mask are tested)
 returns 1 if any of the tested bits are 1, or 0 otherwise

No error is possible.
"""
TestSavedStatus(oldstatus::UInt32, mask::UInt32) = (oldstatus & mask) != 0

"""
TestStatus -- test bits in current status

 dc is the context structure to be updated
 mask indicates the bits to be tested (the status bits that
   correspond to each 1 bit in the mask are tested)
 returns 1 if any of the tested bits are 1, or 0 otherwise

No error is possible.
"""
TestStatus(dc::Context, mask::Integer) = (dc.status & mask) != 0

"""
ZeroStatus -- clear all status bits

 dc is the context structure to be updated
 returns context

No error is possible.
"""
ZeroStatus(dc::Context) = (dc.status = 0 ; dc)
