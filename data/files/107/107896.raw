
module GoCL

export @forall, @forall_fold,
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

macro forall_fold(i, j, f, r, block)
    :(for $(esc(i)) in 1:19
          for $(esc(j)) in 1:19
              $(esc(block))
          end
      end;
      foldl($(esc(f)), $(esc(r))))
end


# empty is zero means that an empty Row is zero too
@enum Point empty black white
other(t::Point) = t == empty ? empty : (t == black ? white : black)

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
    groups = zeroes(UInt8, 255)
    @forall_fold i j ((a, b) -> a > 0 ? a : b) groups begin
        for k = i+(j-1)*19:19*19:255
            groups[k] = k
        end
        group = g.index[i, j]
        if group > 0
            groups[group] = 0
        end
    end
end

function replace_group!(g::Groups, newgroup, x, y)
    oldgroup = g.index[x, y]
    @forall i j begin
        if g.index[i, j] == oldgroup
            g.index[i, j] = newgroup
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

function check_and_delete_group!(p::Position, t::Point, x, y)
    alive = zeroes(Bool, 19, 19)
    group = p.groups.index[x, y]
    if @forall_fold i j any alive begin
        if p.groups.index[i, j] == group
            for (dx, dy) in ((0, 1), (0, -1), (1, 0), (-1, 0))
                xx, yy = x + dx, y + dy      
                if xx > 0 && xx <= 19 && yy > 0 && yy <= 19
                    if point(p.board, xx, yy) == empty
                        alive[i, j] = true
                    end
                end
            end
        end
    end
        @forall i j begin
            if p.groups.index[i, j] == group
                p.groups.index[i, j] = 0
            end
        end
    end
end

function move!(p::Position, t::Point, x, y)
    move!(p.board, t, x, y)
    newgroup = lowest_empty_group(p.groups)
    p.groups.index[x, y] = newgroup
    for (dx, dy) in ((0, 1), (0, -1), (1, 0), (-1, 0))
        xx, yy = x + dx, y + dy      
        if xx > 0 && xx <= 19 && yy > 0 && yy <= 19
            tt = point(b, xx, yy)
            if tt == t
                replace_group!(g, newgroup, xx, yy)
            elseif tt == other(t)
                check_and_delete_group!(p, tt, xx, yy)
            end
        end
    end
end

print(io::IO, p::Position) = print(io, 
                                   join(map(x -> join(x, " "), 
                                            zip(fmtboard(p.board), 
                                                fmtboard(p.groups))), "\n"))



end
