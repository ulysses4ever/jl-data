type SharedDict{K,V} <: Associative{K,V}
    slots::SharedArray{UInt8,1}
    keys::SharedArray{K,1}
    vals::SharedArray{V,1}
    count::Int
    idxfloor::Int  # an in
    pids::AbstractVector{Int}
end

function share{T}(a::AbstractArray{T};kwargs...)
    sh = SharedArray(T,size(a);kwargs...)
    @simd for i=1:length(a)
        sh.s[i] = a[i]
    end
    return sh
end
share(A::SharedArray, pids::AbstractVector{Int}) = (pids==A.pids ? A : share(sdata(A), pids))

share(D::Dict) = share(D::Dict, workers())
function share(D::Union{Dict,SharedDict}, pids::AbstractVector{Int})
    isa(D, SharedDict) && (pids == D.pids) && (return D)

    slots = share(D.slots, pids=pids)
    keys = share(D.keys, pids=pids)
    vals = share(D.vals, pids=pids)

    SharedDict(slots, keys, vals, D.count, D.idxfloor, pids)
end

hashindex(key, sz) = ((hash(key)%Int) & (sz-1)) + 1

isslotempty(h::SharedDict, i::Int) = h.slots[i] == 0x0
isslotfilled(h::SharedDict, i::Int) = h.slots[i] == 0x1
isslotmissing(h::SharedDict, i::Int) = h.slots[i] == 0x2

# get the index where a key is stored, or -1 if not present
function ht_keyindex{K,V}(h::SharedDict{K,V}, key)
    sz = length(h.keys)
    iter = 0
    maxprobe = max(16, sz>>6)
    index = hashindex(key, sz)
    keys = h.keys

    while true
        if isslotempty(h,index)
            break
        end
        if !isslotmissing(h,index) && isequal(key,keys[index])
            return index
        end

        index = (index & (sz-1)) + 1
        iter+=1
        iter > maxprobe && break
    end

    return -1
end


function getindex{K,V}(h::SharedDict{K,V}, key)
    index = ht_keyindex(h, key)
    return (index<0) ? throw(KeyError(key)) : h.vals[index]::V
end

haskey(h::SharedDict, key) = (ht_keyindex(h, key) >= 0)
in{T<:SharedDict}(key, v::KeyIterator{T}) = (ht_keyindex(v.dict, key) >= 0)

function skip_deleted(h::SharedDict, i)
    L = length(h.slots)
    while i<=L && !isslotfilled(h,i)
        i += 1
    end
    return i
end

function start(t::SharedDict)
    i = skip_deleted(t, t.idxfloor)
    t.idxfloor = i
    return i
end
done(t::SharedDict, i) = i > length(t.vals)
next{K,V}(t::SharedDict{K,V}, i) = (Pair{K,V}(t.keys[i],t.vals[i]), skip_deleted(t,i+1))

isempty(t::SharedDict) = (t.count == 0)
length(t::SharedDict) = t.count

next{T<:SharedDict}(v::KeyIterator{T}, i) = (v.dict.keys[i], skip_deleted(v.dict,i+1))
next{T<:SharedDict}(v::ValueIterator{T}, i) = (v.dict.vals[i], skip_deleted(v.dict,i+1))

