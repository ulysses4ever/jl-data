module DictWrappers

export DictWrapper,
    ShallowDictWrapper,
    RecursiveDictWrapper

const DICT_WRAPPER_ERROR = ArgumentError("DictWrappers can only wrap composite types.")

iscomposite(t::DataType) = Base.isstructtype(t)
iscomposite{T<:Tuple}(t::Type{T}) = false

abstract DictWrapper <: Associative

immutable ShallowDictWrapper <: DictWrapper
    wrapped

    function ShallowDictWrapper(wrapped)
        if iscomposite(typeof(wrapped))
            return new(wrapped)
        else
            throw(DICT_WRAPPER_ERROR)
        end
    end
end

immutable RecursiveDictWrapper <: DictWrapper
    wrapped

    function RecursiveDictWrapper(wrapped)
        if iscomposite(typeof(wrapped))
            return new(wrapped)
        else
            throw(DICT_WRAPPER_ERROR)
        end
    end
end

Base.getindex(dw::ShallowDictWrapper, key::Symbol) = getfield(dw.wrapped, key)

function Base.getindex(dw::RecursiveDictWrapper, key::Symbol)
    val = getfield(dw.wrapped, key)

    if iscomposite(typeof(val))
        return RecursiveDictWrapper(val)
    else
        return val
    end
end

Base.length(dw::DictWrapper) = length(fieldnames(dw.wrapped))

Base.keys(dw::DictWrapper) = fieldnames(dw.wrapped)

immutable DictWrapperValueIterator{T<:DictWrapper}
    dw::T
    keys::Vector{Symbol}
end

DictWrapperValueIterator(dw::DictWrapper) = DictWrapperValueIterator(dw, keys(dw))

Base.values(dw::DictWrapper) = DictWrapperValueIterator(dw)

Base.start(dwvi::DictWrapperValueIterator) = 1
Base.next(dwvi::DictWrapperValueIterator, state) = (dwvi.dw[dwvi.keys[state]], state + 1)
Base.done(dwvi::DictWrapperValueIterator, state) = state > length(dwvi.keys)

function Base.start(dw::DictWrapper)
    return (fieldnames(dw.wrapped), 1)
end

function Base.next(dw::DictWrapper, state)
    fields, idx = state
    curr_field = fields[idx]
    return (curr_field=>dw[curr_field], (fields, idx + 1))
end

function Base.done(dw::DictWrapper, state)
    fields, idx = state
    return idx > length(fields)
end

function Base.in{T}(item::Pair{Symbol, T}, dw::DictWrapper)
    return item.first in keys(dw) && item.second == dw[item.first]
end

function Base.get(dw::DictWrapper, key::Symbol, default)
    if key in keys(dw)
        return dw[key]
    else
        return default
    end
end

end # module
