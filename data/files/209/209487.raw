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


# Non-exported helper function

function print_iterable(io::IO, itr)
    print(io, '(')
    state = start(itr)
    if !done(itr, state)
        x, state = next(itr, state)
        if typeof(x) <: String
            print_quoted(io, x)
        else
            print(io, x)
        end             
        while !done(itr, state)
            x, state = next(itr, state)
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



# DictView

abstract DictView{T}

length(v::DictView) = length(v.d)

eltype{T}(v::DictView{T}) = T




# KeysView

immutable KeysView{T} <: DictView{T}
    d::Dict{T}
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




# ValuesView

immutable ValuesView{T} <: DictView{T}
    d::Dict{T}
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
