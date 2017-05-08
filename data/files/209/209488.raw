module DictViews

import 
    Base.start,
    Base.done,
    Base.next,
    Base.length,
    Base.show,
    Base.eltype
    
export 
    KeysView,
    ValuesView

abstract View{T}

length(v::View) = length(v.d)

eltype{T}(v::View{T}) = T

function print_iterable(io::IO, view::View)
    print(io, '(')
    state = start(view)
    if !done(view, state)
        x, state = next(view, state)
        if typeof(x) <: String
            print_quoted(io, x)
        else
            print(io, x)
        end             
        while !done(view, state)
            x, state = next(view, state)
            print(io, ',')
            if typeof(x) <: String
                print_quoted(io, x)
            else
                print(io, x)
            end
        end
    end
    print(io, ')')
end

immutable KeysView{T} <: View{T}
    d::Associative{T}
end

start(v::KeysView) = start(v.d)
done(v::KeysView, state) = done(v.d, state)
function next(v::KeysView, state)
   n = next(v.d, state)
   n[1][1], n[2]
end

function show{T}(io::IO, v::KeysView{T})
    print(io, "KeysView{$T}")
    print_iterable(io, v)
end

immutable ValuesView{T} <: View{T}
    d::Associative{T}
end

start(v::ValuesView) = start(v.d)
done(v::ValuesView, state) = done(v.d, state)
function next(v::ValuesView, state)
   n = next(v.d, state)
   n[1][2], n[2]
end

function show{T}(io::IO, v::ValuesView{T})
    print(io, "ValuesView{$T}")
    print_iterable(io, v)
end

end
