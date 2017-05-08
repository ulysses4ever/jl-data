module CallableCollections

export ∘

typealias IndexedCollection Union{AbstractArray, Associative}
typealias SetCollection Union{Set, IntSet}

Base.call(arr::IndexedCollection, ind...) = getindex(arr, ind...)
Base.call(set::SetCollection, ind) = ind ∈ set

Base.union(fn1, fn2) = x -> fn1(x) || fn2(x)
Base.intersect(fn1, fn2) = x -> fn1(x) && fn2(x)

Base.map(fn, fns...) = function(xs...)
    fn([f(xs...) for f in fns]...)
end

∘(f, g) = x -> f(g(x))

end  # module
