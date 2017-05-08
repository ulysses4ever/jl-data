module DictViews

import 
    Base.start,
    Base.done,
    Base.next,
    Base.length,
    Base.eltype
    
export 
    KeysView,
    ValuesView

abstract View{T}

length(v::View) = length(v.a)

eltype{T}(v::View{T}) = T

immutable KeysView{K,V} <: View{K}
    a::Associative{K,V}
end

keys(a::Associative) = KeysView(a)

start(v::KeysView) = start(v.a)
done(v::KeysView, state) = done(v.a, state)
function next(v::KeysView, state)
   n = next(v.a, state)
   n[1][1], n[2]
end

immutable ValuesView{K,V} <: View{V}
    a::Associative{K,V}
end

values(a::Associative) = ValuesView(a)

start(v::ValuesView) = start(v.a)
done(v::ValuesView, state) = done(v.a, state)
function next(v::ValuesView, state)
   n = next(v.a, state)
   n[1][2], n[2]
end

end
