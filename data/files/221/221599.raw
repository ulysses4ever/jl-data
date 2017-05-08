module SharedDicts

using Base: KeyIterator, ValueIterator

import Base: getindex, haskey, in, start, done, next, isempty, length
if isdefined(Base, :share)
    import Base.share
end
export SharedDict, share, getindex, haskey, in, start, done, next, isempty, length

include("shareddict.jl")

end # module
