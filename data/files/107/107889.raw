
module GoCL

export Point, black, empty, white, Board, point, move, move!


import AutoHashEquals; H = AutoHashEquals
import Base: ==, print


SIZE = 19

# empty is zero means that an empty Row is zero too
@enum Point empty black white

typealias Row UInt32

H.@auto_hash_equals type Board
    rows::Vector{Row}
    Board() = new(zeros(Row, SIZE))
    Board(b::Board) = new(copy(b.rows))
end

point(r::Row, x) = Point(mod(div(r, 3^(x-1)), 3))
point(b::Board, x, y) = point(b.rows[y], x)

function move(row::Row, p::Point, x) 
    k = 3^(x-1)
    l, r = divrem(row, k)
    l = 3 * div(l, 3) + Row(p)
    l * k + r
end
move!(b::Board, p::Point, x, y) = b.rows[y] = move(b.rows[y], p, x)

function fmt(r::Row, y)
    marker = Set([4, 10, 16])
    fmt(x) = (y in marker && x in marker ? "+XO" : ".XO")[1+Row(point(r, x))]
    join(map(fmt, 1:SIZE), " ")
end
fmt(b::Board) = join(map(y -> fmt(b.rows[y], y), SIZE:-1:1), "\n")

print(io::IO, b::Board) = print(io, fmt(b))


end
