module Iteration

import Base.start
import Base.next
import Base.done
import Base.length

immutable Slicerator{T}
    array :: Array{T}
    length :: Uint64
    slice_size :: Uint64
end

function slicerator{T}(array :: Array{T}, slice_size)
    len = length(array)
    @assert(len % slice_size == 0)
    Slicerator(array, uint64(len), uint64(slice_size))
end


length(si :: Slicerator) = uint64(si.length / si.slice_size)
start(si :: Slicerator) = int64(0)
done(si :: Slicerator, i :: Int64) = (i * si.slice_size) >= length(si.array)
function next(si :: Slicerator, i :: Int64)
    sidx = int64((i * si.slice_size) + 1)
    eidx = int64((i+1) * si.slice_size)

    (slice(si.array, sidx:eidx), i+1)
end


immutable OffsetIterator
    inner
    offset :: Int64
end

offset(offset :: Int64, inner) = OffsetIterator(inner, offset)

function length(oi :: OffsetIterator)
    len = length(oi.inner)
    if len > oi.offset
        len - oi.offset
    else
        0
    end
end
start(oi :: OffsetIterator) = start(oi.inner) + oi.offset
done(oi :: OffsetIterator, i) = done(oi.inner, i)
next(oi :: OffsetIterator, i) = next(oi.inner, i)

export slicerator, offset

end # module Iteration