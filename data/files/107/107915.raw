
module GoCL

export @forall, @forall_fold,
       Point, black, empty, white, other,
       Board, point, move, move!,
       Position

using AutoHashEquals
import Base: ==, print



# --- macros


"""execute the same code at each point on the board (tries to
guarantee that the julia code is structured similarly to an opencl
kernel)."""
macro forall(i, j, block)
    :(for $(esc(i)) in 1:19
          for $(esc(j)) in 1:19
              $(esc(block))
          end
      end)
end

"""as forall, but also include a final reduction (again, easy to
implement in a kernel)."""
macro forall_fold(i, j, f, z, r, block)
    :(for $(esc(i)) in 1:19
          for $(esc(j)) in 1:19
              $(esc(block))
          end
      end;
      foldl($(esc(f)), $(esc(z)), $(esc(r))))
end

"""iterate over neigbours - explicit loop (not parallelized) (to
reduce board lookup dx=0 should be grouped)."""
macro forneighbours(x, y, xx, yy, block)
    :(for (dx, dy) in ((0, 1), (0, -1), (1, 0), (-1, 0))
          $(esc(xx)), $(esc(yy)) = $(esc(x)) + dx, $(esc(y)) + dy      
          if $(esc(xx)) > 0 && $(esc(xx)) <= 19 && $(esc(yy)) > 0 && $(esc(yy)) <= 19
              $(esc(block))
          end
      end)
end


# --- data structures


"""a point on the board - empty, or a stone."""
@enum Point empty=0 black=1 white=-1

"""if the point is a stone, give a stone of the other colour.  if
empty, return empty."""
other(t::Point) = t == empty ? empty : (t == black ? white : black)


"""a row of 19 trits fits nicely in 32 bits binary."""
typealias Row UInt32

"""a row of 19 zeros (signed trits)."""
emptyrow = Row(sum([3^(n-1) for n in 1:19]))

"""a trit-map of the entire board."""
@auto_hash_equals immutable Board
    rows::Vector{Row}
    Board() = new(fill(emptyrow, 19))
    Board(b::Board) = new(copy(b.rows))
end

"""extract the point at a given (x, y)."""
point(r::Row, x) = Point(mod(div(r, 3^(x-1)), 3)-1)

"""extract the point at a given (x, y)."""
point(b::Board, x, y) = point(b.rows[y], x)


"""identify all points common to a single group.

this is an optimisation - a cached, updated summary, that makes other
operations (updating the board on a move) more efficient.  it may not
be necessary."""
@auto_hash_equals immutable Groups
    index::Array{UInt8, 2}
    Groups() = new(zeros(UInt8, 19, 19))
    Groups(g::Groups) = new(copy(g.index))
end


"""a map of cartesian signed distances to the nearest non-empty point,
where the sign indicates whether the nearest point is black or white
(via the Point enumeration).

distances are offset by 1, so a value of +/-1 indicates that the point
contains a stone.  a value of zero is used initially (replaced on
first move by flood_to_point!) and as a marker for deleted groups
(replaced by flood_dead_group!).

this contains almost all the information about the state of play (the
+/-1 values duplicate Board).  it may be used as input to a neural
net."""
@auto_hash_equals immutable Flood
    distances::Array{Int8, 2}
    Flood() = new(zeros(Int8, 19, 19))
    Flood(f::Flood) = new(copy(f.distances))
end


"""a single position (implicitly, in a search tree).  combines Board,
Groups and Flood."""
@auto_hash_equals immutable Position
    board::Board
    groups::Groups
    flood::Flood
    Position() = new(Board(), Groups(), Flood())
    Position(p::Position) =
        new(Board(p.board), Groups(p.groups), Flood(p.flood))
end


# --- display


const markers = Set([4, 10, 16])

function fmtrow(r::Row, y)
    fmt(x) = (y in markers && x in markers ? "O+X" : "O.X")[2+Int(point(r, x))]
    join(map(fmt, 1:19), " ")
end
fmtboard(b::Board) = map(y -> fmtrow(b.rows[y], y), 19:-1:1)

print(io::IO, b::Board) = print(io, join(fmtboard(b), "\n"))

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

function fmtrow(f::Flood, y)
    function fmt(x)
        d = f.distances[x, y]
        if abs(d) < 10
            @sprintf("%2d", d)
        elseif d > 0
            string(" ", Char(Int('a') + d - 10))
        else
            string(" ", Char(Int('A') - d - 10))
        end
    end
    join(map(fmt, 1:19))
end
fmtboard(f::Flood) = map(y -> fmtrow(f, y), 19:-1:1)

print(io::IO, f::Flood) = print(io, join(fmtboard(f), "\n"))

function print(io::IO, p::Position)
    print(io, 
          join(map(x -> join(x, " "), 
                   zip(fmtboard(p.board), 
                       fmtboard(p.groups))), "\n"))
    print(io, "\n")
    print(io, "\n")
    print(io, p.flood)
end


# --- update state on move


function lowest_empty_group(g::Groups)
    groups = zeros(UInt8, 255)
    @forall_fold i j ((a, b) -> a > 0 ? a : b) 0 groups begin
        # set groups to count from 1 to 255
        for k = i+(j-1)*19:19*19:255
            groups[k] = k
        end
        # zero out any groups that exist
        group = g.index[i, j]
        if group > 0
            groups[group] = 0
        end
        # final fold returns the first non-zero value - the smallest
        # group
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

function check_and_delete_group!(p::Position, x, y)
    alive = zeros(Bool, 19, 19)
    # the group we want to check
    group = p.groups.index[x, y]
    if ! @forall_fold i j (x,y) -> any([x,y]) false alive begin 
        if p.groups.index[i, j] == group
            @forneighbours x y xx yy begin
                # if a neighbour is empty, return that via the fold
                if point(p.board, xx, yy) == empty
                    alive[i, j] = true
                end
            end
        end
    end
        # if not alive
        @forall i j begin
            if p.groups.index[i, j] == group
                # remove stone
                move!(p.board, empty, i, j)
                # TOOO - increment prisoner count
                # erase group index
                p.groups.index[i, j] = 0
                # set flood to special value (see flood_dead_group!)
                p.flood.distances[i, j] = 0
            end
        end
    end
end

function flood_dead_group!(f::Flood, b::Board, t::Point)
    while ! @forall_fold i j (a,b) -> (a || b!=0) false f.distances begin
        if f.distances[i, j] == 0
           # find closest neighbour
           mind = 256
           @forneighbours i j ii jj begin
               d = f.distances[ii, jj]
               if d != 0
                   mind = min(mind, abs(d))
               end
           end
           # if we have a neighbour, add one to that
           if mind < 256
               f.distances[i, j] = Int(t) * (mind+1)
           end
       end
    end
        # while zero distances exist (repeat above)
    end
end

function flood_to_point!(f::Flood, b::Board, t::Point, x, y)
    @forall i j begin
        if point(b, i, j) == empty
            ii, jj, d = i, j, 1
            while true
                di, dj, d = x-ii, y-jj, d+1
                if abs(di) >= abs(dj)
                    ii = ii + sign(di)
                else
                    jj = jj + sign(dj)
                end
                if point(b, ii, jj) != empty
                    break
                end
            end
            if ii == x && jj == y
                prev = f.distances[i, j]
                if prev == 0 || abs(d) < abs(prev)
                    f.distances[i, j] = d * Int(t)
                end
            end
        end
    end
end

function move(row::Row, t::Point, x) 
    k = 3^(x-1)
    l, r = divrem(row, k)
    l = 3 * div(l, 3) + Row(Int(t)+1)
    l * k + r
end

move!(b::Board, t::Point, x, y) = b.rows[y] = move(b.rows[y], t, x)

move!(f::Flood, t::Point, x, y) = f.distances[x, y] = Int8(t)

function move!(p::Position, t::Point, x, y)
    move!(p.board, t, x, y)
    move!(p.flood, t, x, y)
    flood_to_point!(p.flood, p.board, t, x, y)
    newgroup = lowest_empty_group(p.groups)
    p.groups.index[x, y] = newgroup
    @forneighbours x y xx yy begin
        tt = point(p.board, xx, yy)
        if tt == t
            replace_group!(p.groups, newgroup, xx, yy)
        elseif tt == other(t)
            check_and_delete_group!(p, xx, yy)
        end
    end
    flood_dead_group!(p.flood, p.board, t)
end


end
