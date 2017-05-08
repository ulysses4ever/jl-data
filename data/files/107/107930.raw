
module GoCL

export fix, @forall, @forall_fold,
       Point, black, empty, white, other,
       Board, point, move, move!,
       Position,
       map_space, convolve, blank!

using AutoHashEquals
import Base: ==, print


# todo
# size of spaces?  maybe not important - kindof available in flood fill.
# good scoring (at least for end of game assessment, maybe then fold stuff into
# pre-processing layer.
# graphs, evolution, tournaments etc


# --- utilities


"""this package assumes [x,y] indexing, with x varying fastest and
origin bottom left.  this is not how julia displays matrices (not at
all), so things can be confusing if you use "print" on raw structures.
this function converts for display."""
fix{T}(x::Array{T, 2}) = x'[19:-1:1,:]



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
    row::Vector{Row}
    Board() = new(fill(emptyrow, 19))
    Board(b::Board) = new(copy(b.row))
end


"""identify points common to a group and provide basic stats."""
@auto_hash_equals immutable Groups
    index::Array{UInt8, 2}
    # do we need to care about overflow here?
    size::Array{UInt8, 1}
    space::Array{UInt8, 1}
    Groups() = new(zeros(UInt8, 19, 19), zeros(UInt8, 255), zeros(UInt8, 255))
    Groups(g::Groups) = new(copy(g.index), copy(g.size), copy(g.space))
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
    distance::Array{Int8, 2}
    Flood() = new(zeros(Int8, 19, 19))
    Flood(f::Flood) = new(copy(f.distance))
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


# --- points


"""extract the point at a given (x, y)."""
point(r::Row, x) = Point(mod(div(r, 3^(x-1)), 3)-1)

"""extract the point at a given (x, y)."""
point(b::Board, x, y) = point(b.row[y], x)

"""extract the point at a given (x, y)."""
point(p::Position, x, y) = point(p.board, x, y)


# --- display


"""the location of board markers (dots)."""
const markers = Set([4, 10, 16])

function fmtrow(r::Row, y)
    fmt(x) = (y in markers && x in markers ? "O+X" : "O.X")[2+Int(point(r, x))]
    # extra space aligns with other components that use 2 characters
    # per point
    string(" ", join(map(fmt, 1:19), " "))
end
fmtboard(b::Board) = map(y -> fmtrow(b.row[y], y), 19:-1:1)

print(io::IO, b::Board) = print(io, join(fmtboard(b), "\n"))

function fmtrow(g::Groups, y)
    function fmt(x)
        if g.index[x, y] > 0
            @sprintf("%02X", g.index[x, y])
        elseif y in markers && x in markers
            "__"
        else
            "  "
        end
    end
    join(map(fmt, 1:19))
end
fmtboard(g::Groups) = map(y -> fmtrow(g, y), 19:-1:1)

stats_per_row = 4
function fmtstats(g::Groups, row)
    function fmt(col)
        i = col + (row-1) * stats_per_row
        @sprintf("%02x:%2d/%2d", i, g.space[i], g.size[i])
    end
    join(map(fmt, 1:stats_per_row), ", ")
end
fmtstats(g::Groups) = map(r -> fmtstats(g, r), 1:19)

function print(io::IO, g::Groups)
    print(io, join(fmtboard(g), "\n"))
    print(io, "\n")
    print(io, join(fmtstats(g), "\n"))
end

function fmtrow(f::Flood, y)
    function fmt(x)
        d = f.distance[x, y]
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
          join(map(x -> join(x, "  "), 
                   zip(fmtboard(p.board), 
                       fmtboard(p.groups))), "\n"))
    print(io, "\n")
    print(io, "\n")
    print(io,
          join(map(x -> join(x, "  "), 
                   zip(fmtboard(p.flood), 
                       fmtstats(p.groups))), "\n"))
end


# --- update state on move


"""groups (in Groups.index) are numbered from 1 (0 is for empty
spaces).  this routine returns the smallest number > 0 that is unused
(so it can be used to label a new group)."""
function lowest_empty_group(g::Groups)
    groups = collect(UInt8, 1:255)
    @forall_fold i j ((a, b) -> a > 0 ? a : b) 0 groups begin
        # zero out any groups that exist
        group = g.index[i, j]
        if group > 0
            groups[group] = 0
        end
        # final fold returns the first non-zero value - the smallest
        # group
    end
end

"""merge the group at (x,y) with newgroup."""
function merge_group(g::Groups, newgroup, x, y)
    oldgroup = g.index[x, y]
    if newgroup != oldgroup
        g.size[newgroup], g.size[oldgroup] = g.size[newgroup] + g.size[oldgroup], 0
        @forall i j begin
            if g.index[i, j] == oldgroup
                g.index[i, j] = newgroup
            end
        end
    end
end

"""check whether the group at (x, y) is dead.  if so, remove it from
Groups.index and set Flood.distance to zero (these are later replaced
in flood_dead_group!)."""
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
        p.groups.size[group] = 0
        @forall i j begin
            if p.groups.index[i, j] == group
                # remove stone
                move!(p.board, empty, i, j)
                # TOOO - increment prisoner count
                # erase group index
                p.groups.index[i, j] = 0
                # set flood to special value (see flood_dead_group!)
                p.flood.distance[i, j] = 0
            end
        end
    end
end

"""replace Flood.distance values that have been zeroed."""
function flood_dead_group!(f::Flood, b::Board, t::Point)
    while ! @forall_fold i j (a,b) -> (a || b!=0) false f.distance begin
        if f.distance[i, j] == 0
           # find closest neighbour
           mind = 256
           @forneighbours i j ii jj begin
               d = f.distance[ii, jj]
               if d != 0
                   mind = min(mind, abs(d))
               end
           end
           # if we have a neighbour, add one to that
           if mind < 256
               f.distance[i, j] = Int(t) * (mind+1)
           end
       end
    end
        # while zero distances exist (repeat above)
    end
end

"""update Flood.distance when a stone is played.  this is done by
moving from each point towards the new stone.  if the path reaches the
stone without meeting any other, and the distance is less than the
current value, then it is updated.  i am not completely sure this is
exact, but it appears to work ok."""
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
                prev = f.distance[i, j]
                if prev == 0 || abs(d) < abs(prev)
                    f.distance[i, j] = d * Int(t)
                end
            end
        end
    end
end

"""re-calculate (from scratch) the number of spaces associated with
each group."""
function calculate_space!(g::Groups)
    for k in 1:19
        g.space[k] = 0
    end
    # local vars
    temp = zeros(UInt8, 19, 19, 4)
    n = zeros(UInt8, 19, 19)
    @forall i j begin
        if g.index[i, j] == 0
            @forneighbours i j ii jj begin
                group = g.index[ii, jj]
                # if group is not already known
                if group != 0 && !any([group == temp[i, j, k] for k in 1:n[i, j]])
                    n[i, j] = n[i, j] + 1
                    temp[i, j, n[i, j]] = group
                end
            end
            # thread group mem with memory guard
            for k in 1:n[i, j]
                g.space[temp[i, j, k]] = g.space[temp[i, j, k]] + 1
            end
        end
    end
end

"""update the row to include the given Point."""
function move(row::Row, t::Point, x) 
    k = 3^(x-1)
    l, r = divrem(row, k)
    l = 3 * div(l, 3) + Row(Int(t)+1)
    l * k + r
end

"""update the board to include the given point."""
move!(b::Board, t::Point, x, y) = b.row[y] = move(b.row[y], t, x)

"""update Flood.distance to include the given point (only - full
flood update requires flood_dead_group! and flood_to_point!)."""
move!(f::Flood, t::Point, x, y) = f.distance[x, y] = Int8(t)

"""update the position, given a new point.  this includes all
processing."""
function move!(p::Position, t::Point, x, y)
    move!(p.board, t, x, y)
    move!(p.flood, t, x, y)
    flood_to_point!(p.flood, p.board, t, x, y)
    newgroup = lowest_empty_group(p.groups)
    p.groups.index[x, y] = newgroup
    p.groups.size[newgroup] = 1
    @forneighbours x y xx yy begin
        tt = point(p.board, xx, yy)
        if tt == t
            merge_group(p.groups, newgroup, xx, yy)
        elseif tt == other(t)
            check_and_delete_group!(p, xx, yy)
        end
    end
    flood_dead_group!(p.flood, p.board, t)
    calculate_space!(p.groups)
end


# --- convolution


# http://developer.amd.com/resources/documentation-articles/articles-whitepapers/tiled-convolution-fast-image-filtering/
# has a detailed argument about why and how to do this better on a
# real gpu (although this case is simpler as it fits in a single tile)

"""convolve a 3x3 cross-shaped kernel."""
function convolve(input, border, kernel, output)
    @forall i j begin
        a = 0
        # cannot use forneighbours because we need di, dj
        for (di, dj) in ((0, 1), (0, -1), (1, 0), (-1, 0))
            ii, jj = i+di, j+dj
            if ii > 0 && ii <= 19 && jj > 0 && jj <= 19
                a = a + kernel[di+2, dj+2] * input[ii, jj]
            else
                a = a + kernel[di+2, dj+2] * border
            end
            output[i, j] = a
        end
    end
end

function blank!(data, p::Position)
    @forall i j begin
        if point(p, i, j) != empty
            data[i, j] = 0
        end
    end
end


# --- scoring


# grow boundaries inwards
# expand conflicting values outwards
# reduce to find score

function boundary_mask(t::Point)
    if t == empty
        return 0
    elseif t == black
        return 1
    else
        return 2
    end
end

function worse(s, b)
end

function map_space(p::Position)

    # to make this incremental, we need to have two arrays
    # 1 - an index that numbers spaces (so we know what to zero out)
    # 2 - the border array as below
    # then on a move we need to
    # 1 - zero out the group that was where the move was
    # 2 - expand out from the spaces connected there, propogating both
    #     border and index number (merging to lowest)
    # 3 - handle killed groups
    # not sure this is worth it right now.  on the other hand, it gives an 
    # extrea input array (space index), although not a particularly useful 
    # one

    # this is either zero (unfilled / group) or a bitmask, 1 for black, 2 for
    # white, 3 for both
    space = zeros(UInt8, 19, 19)   # thread group mem

    # local vars
    my_space = zeros(UInt8, 19, 19)
    nsew = zeros(UInt8, 19, 19)   # bitmask of stones (to ignore in second round)

    @forall i j begin
        # only modify empty points
        if point(p, i, j) == empty

            # first round, set from boundary stones
            k = zeros(UInt8, 19, 19)   # local var
            @forneighbours i j ii jj begin
                t = point(p, ii, jj)
                my_space[i, j] = my_space[i, j] | boundary_mask(point(p, ii, jj))
                if t != empty
                    nsew[i, j] = nsew[i, j] | 2^k[i, j]
                end
                k[i, j] = k[i, j] + 1
            end
            space[i, j] = my_space[i, j]
        end
    end

    # second round - update until consistent
    changed = true   # thread group mem
    while changed
        changed = false
        k = zeros(UInt8, 19, 19)   # local var
        @forall i j begin
            # only modify empty points
            if point(p, i, j) == empty
                @forneighbours i j ii jj begin
                    # if not a stone
                    if nsew[i, j] & 2^k[i, j] == 0
                        s = space[ii, jj]
                        l = my_space[i, j]
                        # if neighbour unset, or already included in local value
                        if !(s == 0 || s & l == s)
                            changed = true
                            my_space[i, j] = l | s
                            space[i, j] = l | s
                        end
                    end
                    k[i, j] = k[i, j] + 1
                end
            end

        end
    end
    space
end



end
