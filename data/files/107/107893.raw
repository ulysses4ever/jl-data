
module GoCL

export @forall, @forall_reduce,
       Point, black, empty, white, 
       Board, point, move, move!,
       Position


using AutoHashEquals
import Base: ==, print


macro forall(i, j, block)
    :(for $(esc(i)) in 1:19
          for $(esc(j)) in 1:19
              $(esc(block))
          end
      end)
end

macro forall_reduce(i, j, f, r, block)
    :(for $(esc(i)) in 1:19
          for $(esc(j)) in 1:19
              $(esc(block))
          end
      end;
      reduce($(esc(f)), $(esc(r))))
end


# empty is zero means that an empty Row is zero too
@enum Point empty black white

# 19 trits just fit into 32 bits
typealias Row UInt32

@auto_hash_equals type Board
    rows::Vector{Row}
    Board() = new(zeros(Row, 19))
    Board(b::Board) = new(copy(b.rows))
end

point(r::Row, x) = Point(mod(div(r, 3^(x-1)), 3))
point(b::Board, x, y) = point(b.rows[y], x)

function move(row::Row, t::Point, x) 
    k = 3^(x-1)
    l, r = divrem(row, k)
    l = 3 * div(l, 3) + Row(t)
    l * k + r
end
move!(b::Board, t::Point, x, y) = b.rows[y] = move(b.rows[y], t, x)

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

function lowest_empty_group(g::Groups)
    empties = zeroes(UInt8, 19, 19)
#    @forall_reduce(:i, :j, empties, e -> map
end

function move!(g::Groups, b::Board, t::Point, x, y)
    newgroup = 
    for (dx, dy) in ((0, 1), (0, -1), (1, 0), (-1, 0))
        xx, yy = x + dx, y + dy
        if xx > 0 && xx <= 19 && yy > 0 && yy <= 19
            index = g.index[xx, yy]
            @forall i j begin
            end
        end
    end
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


function move!(p::Position, t::Point, x, y)
    move!(p.board, t, x, y)
    move!(p.groups, p.board, x, y)
end


end
