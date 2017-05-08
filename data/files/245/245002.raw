import Base.promote_rule
import Base.convert

type Network
    active::Set
end

network = Network(Set())

type Cell
    content
    neighbors::Set
end

type Propagator
    thunk::Function
end

immutable Value
    wrapped
end

==(x::Value, y::Value) = x.wrapped == y.wrapped

alert(p::Propagator) = alert([p])
function alert(propagators)
    for p in propagators
        push!(network.active, p)
    end
end

toContent(::Type{None}) = None
toContent(v::Value) = v
toContent(n::Number) = Value(n)

fromContent(::Type{None}) = None
fromContent(v::Value) = v.wrapped

cell() = cell(None)
cell(x) = Cell(toContent(x), Set())

function joinContent(content::Value, increment::Value)
    if content != increment
        error("Contradiction!")
    end
    content
end

joinContent(::Type{None}, ::Type{None}) = None
joinContent(::Type{None}, v::Value) = v
joinContent(v::Value, ::Type{None}) = v
joinContent(x, y) = joinContent(promote(toContent(x), toContent(y))...)

function addContent(cell, content)
    newContent = joinContent(cell.content, content)
    if cell.content != newContent
        cell.content = newContent
        alert(cell.neighbors)
    end
    cell
end

function newNeighbor(cell, neighbor)
    push!(cell.neighbors, neighbor)
    alert(neighbor)
end

function content(cell)
    fromContent(cell.content)
end

function propagator(neighbors, thunk)
    p = Propagator(thunk)
    for cell in neighbors
        newNeighbor(cell, p)
    end
    alert(p)
end

function lift(f::Function)
    function(cells...)
        inputs = cells[1:end-1]
        output = last(cells)
        propagator(inputs, () -> addContent(output,
                                            f(map(content, inputs)...)))
    end
end

function handlesNone(f)
    function(args...)
        if any((x) -> x == None, args)
            None
        else
            f(args...)
        end
    end
end

function run()
    while !isempty(network.active)
        p = pop!(network.active)
        p.thunk()
    end
end

###########

adder = lift(handlesNone(+))
subtractor = lift(handlesNone(-))
multiplier = lift(handlesNone(*))
divider = lift(handlesNone(/))

function sum(x, y, total)
    adder(x, y, total)
    subtractor(total, y, x)
    subtractor(total, x, y)
end

function product(x, y, total)
    multiplier(x, y, total)
    divider(total, x, y)
    divider(total, y, x)
end

##########

function fahrenheit2celsius(f, c)
    thirtyTwo = cell(32)
    five = cell(5)
    nine = cell(9)
    f32 = cell()
    c9 = cell()
    sum(thirtyTwo, f32, f)
    product(f32, five, c9)
    product(c, nine, c9)
end

f = cell()
c = cell()
fahrenheit2celsius(f, c)
#addContent(f, 77)
addContent(c, 25)

function celsius2kelvin(c, k)
    sum(c, cell(273.15), k)
end

k = cell()
celsius2kelvin(c, k)

run()

println("f: ", content(f))
println("c: ", content(c))
println("k: ", content(k))

###########

immutable Interval{N<:Number}
    min::N
    max::N
end

function intersect(a::Interval, b::Interval)
    i = Interval(max(a.min, b.min), min(a.max, b.max))
    i.min > i.max ? None : i
end

toContent(i::Interval) = i
fromContent(i::Interval) = i

#XXX handle promotion of N; eg Interval{Int64} and Int32
promote_rule{N<:Number}(I::Type{Interval{N}}, ::Type{N}) = I
convert{N<:Number}(I::Type{Interval{N}}, n::Number) = I(n, n)
joinContent{N<:Number}(a::Interval{N}, b::Interval{N}) = intersect(a, b)

#########
