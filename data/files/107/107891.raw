
module GoCL

export Point, black, empty, white, 
       Board, point, move, move!,
       Position


using AutoHashEquals
import Base: ==, print


# empty is zero means that an empty Row is zero too
@enum Point empty black white

typealias Row UInt32

@auto_hash_equals type Board
    rows::Vector{Row}
    Board() = new(zeros(Row, 19))
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

const markers = Set([4, 10, 16])

function fmtrow(r::Row, y)
    fmt(x) = (y in markers && x in markers ? "+XO" : ".XO")[1+Row(point(r, x))]
    join(map(fmt, 1:19), " ")
end
fmtboard(b::Board) = map(y -> fmtrow(b.rows[y], y), 19:-1:1)

print(io::IO, b::Board) = print(io, join(fmtboard(b), "\n"))


@auto_hash_equals type Groups
    index::Array{UInt8, 2}
    Groups() = new(zeros(UInt8, 19, 19))
    Groups(g::Groups) = new(copy(g.index))
end

function fmtrow(g::Groups, y)
    function fmt(x)
        if g.index[x, y] > 0
            @sprintf("%2x", g.index[x, y])
        elseif y in markers && x in markers
            "__"
        else
            "  "
        end
    end
    join(map(fmt, 1:19))
end
fmtboard(g::Groups) = map(y -> fmtrow(g, y), 19:-1:1)

print(io::IO, g::Groups) = print(io, join(fmtboard(g), "\n"))


@auto_hash_equals immutable Position
    board::Board
    groups::Groups
    Position() = new(Board(), Groups())
    Position(p::Position) = new(Board(p.board), Groups(p.groups))
end

print(io::IO, p::Position) = print(io, 
                                   join(map(x -> join(x, " "), 
                                            zip(fmtboard(p.board), 
                                                fmtboard(p.groups))), "\n"))



end
