import Base.promote_rule
import Base.convert

type Network
    active::Set
    running::Bool
end

network = Network(Set(), false)

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

to_content(::Type{None}) = None
to_content(v::Value) = v
to_content(n::Number) = Value(n)

from_content(::Type{None}) = None
from_content(v::Value) = v.wrapped

cell() = cell(None)
cell(x) = Cell(to_content(x), Set())

function join_content(content::Value, increment::Value)
    if content != increment
        error("Contradiction!")
    end
    content
end

join_content(::Type{None}, ::Type{None}) = None
join_content(::Type{None}, x) = to_content(x)
join_content(x, ::Type{None}) = to_content(x)

function join_content(x, y)
    join_content(promote(to_content(x), to_content(y))...)
end

function add_content(cell, content)
    new_content = join_content(cell.content, content)
    if cell.content != new_content
        cell.content = new_content
        alert(cell.neighbors)
    end
    cell
end

function new_neighbor(cell, neighbor)
    push!(cell.neighbors, neighbor)
    alert(neighbor)
end

function content(cell)
    run()
    from_content(cell.content)
end

function propagator(neighbors, thunk)
    p = Propagator(thunk)
    for cell in neighbors
        new_neighbor(cell, p)
    end
    alert(p)
end

function lift(f::Function)
    function(cells...)
        inputs = cells[1:end-1]
        output = last(cells)
        propagator(inputs, () ->
          add_content(output, f(map(content, inputs)...)))
    end
end

function handles_none(f)
    function(args...)
        if any((x) -> x == None, args)
            None
        else
            f(args...)
        end
    end
end

function run()
    if network.running
        return
    end
    network.running = true
    try
        while !isempty(network.active)
            p = pop!(network.active)
            p.thunk()
        end
    finally
        network.running = false
    end
end

###########

adder = lift(handles_none(+))
subtractor = lift(handles_none(-))
multiplier = lift(handles_none(*))
divider = lift(handles_none(/))
exponenter = lift(handles_none(^))

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

squarer(x, total) = exponenter(x, cell(2), total)
sqrter(x, total) = exponenter(x, cell(1/2), total)

function quadratic(x, sq)
    squarer(x, sq)
    sqrter(sq, x)
end

##########

function fahrenheit2celsius(f, c)
    thirty_two = cell(32)
    five = cell(5)
    nine = cell(9)
    f32 = cell()
    c9 = cell()
    sum(thirty_two, f32, f)
    product(f32, five, c9)
    product(c, nine, c9)
end

f = cell()
c = cell()
fahrenheit2celsius(f, c)
#add_content(f, 77)
add_content(c, 25)

function celsius2kelvin(c, k)
    sum(c, cell(273.15), k)
end

k = cell()
celsius2kelvin(c, k)

println("f: ", content(f))
println("c: ", content(c))
println("k: ", content(k))

###########

immutable Interval{N<:Number}
    low::N
    high::N
end

function intersect(x::Interval, y::Interval)
    i = Interval(max(x.low, y.low), min(x.high, y.high))
    i.low > i.high ? None : i
end

==(x::Interval, y::Interval) = x.low == y.low && x.high == y.high
+(x::Interval, y::Interval) = Interval(x.low + y.low, x.high + y.high)
-(x::Interval, y::Interval) = Interval(x.low - y.low, x.high - y.high)

function *(x::Interval, y::Interval)
    p1 = x.low * y.low
    p2 = x.low * y.high
    p3 = x.high * y.low
    p4 = x.high * y.high
    Interval(min(p1, p2, p3, p4), max(p1, p2, p3, p4))
end

function /(x::Interval, y::Interval)
    if y.low <= 0 && 0 <= y.high
        None #XXX
    else
        x * Interval(1 / x.high, 1 / x.low)
    end
end

^(x::Interval, i::Integer) = Interval(x.low ^ i, x.high ^ i)
^(x::Interval, n::Number) = Interval(x.low ^ n, x.high ^ n)

#XXX handle promotion of N; eg Interval{Int64} and Int32
promote_rule{N<:Number}(I::Type{Interval{N}}, ::Type{N}) = I
convert{N<:Number}(I::Type{Interval{N}}, n::Number) = I(n, n)

to_content(i::Interval) = i
from_content(i::Interval) = i
join_content{N<:Number}(x::Interval{N}, y::Interval{N}) = intersect(x, y)

#########

function fall_duration(t, h)
    g = cell(Interval(9.789, 9.832))
    half = cell(Interval(1/2, 1/2)) #TODO try just 0.5
    t_sq = cell()
    gt_sq = cell()
    quadratic(t, t_sq)
    product(g, t_sq, gt_sq)
    product(half, gt_sq, h)
end

fall_time = cell()
building_height = cell()
fall_duration(fall_time, building_height)

add_content(fall_time, Interval(2.9, 3.1))

println("fall_time: ", content(fall_time))
println("building_height: ", content(building_height))
