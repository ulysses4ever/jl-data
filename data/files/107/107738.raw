

# overview

# so this isn't a neural net.  roughly, it's a series of matrix
# operations, where the "matrix" values are the same size as the
# playing board.

# the final result, after evaluating the operations, is treated as a
# probability distribution for where to make the next move.

# the input matrices are taken from the position itself - so, for
# example, a matrix where spaces are 0, black is 1 and white is -1.
# there are also two contant matrices, with the values 0 and 1 at
# every point.

# the operations available are:
# - convolution with a kernel
# - addition of two values scaled by some factor
# - product of two values raised to some power

# implementation

# to make meta-heuristics as effective as possible we want the
# representation to be very compact (everything counts), and for all
# values to be normalised (everything is useful).

# so we use bytes for values, but evaluate expressins using floats.
# the conversion from byte to float depends on the context.

# byte/serialisation format

# the idea here is to make this as flexible as possible, so that we
# can move data between different experiments.  its quite possible
# that any particular run / optimisation will be much more
# restrictive.

# header: "go" + "xp" (expression) + byte for version (version 0 below)
# length: unsigned two bytes (for following data, excluding header + ;ength)
#         (any final operation that is incomplete because of the length
#         is simply discarded)
# operations: repeated until end (discarding any incomplete at end)
#   first byte of operation mod 3 gives type:
#   0: kernel
#     byte 0: byte used for input outside board edges
#     byte 1: size in x and y (packed into nibbles)
#     byte 2: (mod size of grid) location of output within the kernel 
#     remaining bytes as kernel
#   1: sum
#     byte 0: (mod 8) numer of inputs
#     remaining bytes as pairs:
#       byte 0: (signed) positive (mod available): direct index into input
#                        negative (mod available): indiect index into input
#       byte 1: scale (see below for byte -> float)
#   2: product
#     as sum (above), but power instead of scale (different byte -> float)
# general encoding from byte -> float is
#   float(b) = signed(b) / sqrt(128) with clipping at limits
#   but for powers used signed(b) / 32 (ie roughly +/-4)

# encoding from position to inputs involves pre-scaling, so +1 for
# black becomes 11 (which becomes ~1 on conversion to float)


@enum OpTag kernel=0x00 sum=0x01 product=0x02

abstract Operation

# to preserve "significant noise" these structures contain 

@auto_hash_equals type Kernel <: Operation
    tag::UInt8
    source::Int8
    edge::Int8
    location::UInt8
    coeff::Array{Int8, 2}
end

@auto_hash_equals immutable Input
    source::Int8
    weight::Int8
end

@auto_hash_equals type Sum <: Operation
    tag::UInt8
    inputs::Vector{Input}
end

@auto_hash_equals type Product <: Operation
    tag::UInt8
    inputs::Vector{Input}
end

@auto_hash_equals type Expression
    operations::Vector{Operation}
end

@auto_hash_equals type Context
    values::Array{Int8, 3}
    Context(n, l) = new(zeros(Int8, n, n, l))
end

s2b(n::Int8) = reinterpret(UInt8, n)

function s2b(k::Kernel)
    UInt8[0x00,
    
