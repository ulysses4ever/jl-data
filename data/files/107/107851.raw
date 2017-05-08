

# pure-julia (currently) implementation of basic position logic:
# - a Position() instance represents a particular "arrangement"
# - move!(...) updates the position to include the new move
# - groups of stones and spaces are tracked
# - the implementation is written in a style that should be easy to move
#   to a GPU (OpenCL)
# - additional info useful for presenting to a neural net (liek flood
#   fill distances) is included


# --- utilities


"""this package assumes [x,y] indexing, with x varying fastest and
origin bottom left.  this is not how julia displays matrices (not at
all), so things can be confusing if you use "print" on raw structures.
this function converts for display."""
fix{T}(x::Array{T, 2}) = x'[size(x)[1]:-1:1,:]



# --- data structures


"""a point on the board - empty, or a stone."""
@enum Point empty=0 black=1 white=-1

"""if the point is a stone, give a stone of the other colour.  if
empty, return empty."""
other(t::Point) = t == empty ? empty : (t == black ? white : black)


"""a row of 19 trits fits nicely in 32 bits binary."""
typealias Row UInt32

"""a row of n zeros (signed trits)."""
emptyrow(n) = Row(sum([3^(n-1) for n in 1:n]))

"""a trit-map of the entire board."""
@auto_hash_equals immutable Board{N}
    row::Vector{Row}
    Board() = new(fill(emptyrow(N), N))
    Board(b::Board) = new(copy(b.row))
end
# https://groups.google.com/forum/#!topic/julia-users/-n3xsEHxwAI
Board{N}(b::Board{N}) = Board{N}(b)


"""identify points common to a group and provide basic stats."""
@auto_hash_equals immutable Groups{N}
    index::Array{UInt8, 2}
    # do we need to care about overflow here?
    size::Array{UInt8, 1}
    lives::Array{UInt8, 1}
    Groups() = new(zeros(UInt8, N, N), zeros(UInt8, 255), zeros(UInt8, 255))
    Groups(g::Groups{N}) = new(copy(g.index), copy(g.size), copy(g.lives))
end
Groups{N}(g::Groups{N}) = Groups{N}(g)


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
@auto_hash_equals immutable Flood{N}
    distance::Array{Int8, 2}
    Flood() = new(zeros(Int8, N, N))
    Flood(f::Flood{N}) = new(copy(f.distance))
end
Flood{N}(g::Flood{N}) = Flood{N}(g)


@auto_hash_equals immutable Space{N}
    border::Array{Int8, 2}
    index::Array{UInt8, 2}
    Space() = new(zeros(Int8, N, N), zeros(UInt8, N, N))
    Space(s::Space{N}) = new(copy(s.border), copy(s.index))
end
Space{N}(g::Space{N}) = Space{N}(g)


@auto_hash_equals type Details
    spaces::Int
    prisoners::Int
    Details() = new(0, 0)
    Deatils(d::Details) = new(d.spaces, d.prisoners)
end

@auto_hash_equals type Score
    total::Int
    owned::Float32
    stones::Float32
    colour::Dict{Point, Details}
    Score() = new(0, 0, 0, Dict{Point, Details}(black=>Details(), white=>Details()))
    Score(s::Score) = new(s.total, s.owned, s.stones, [x=>s.colour[x] for x in (black, white)])
end

"""a single position (implicitly, in a search tree).  combines Board,
Groups, Flood and Space."""
@auto_hash_equals immutable Position{N}
    board::Board{N}
    groups::Groups{N}
    flood::Flood{N}
    space::Space{N}
    score::Score
    Position() = new(Board{N}(), Groups{N}(), Flood{N}(), Space{N}(), Score())
    Position(p::Position) =
        new(Board(p.board), Groups(p.groups), Flood(p.flood), Space(p.space), Score(p.score))
end
Position{N}(g::Position{N}) = Position{N}(g)
Position() = Position{19}()


# --- points


"""extract the point at a given (x, y)."""
point(r::Row, x) = Point(mod(div(r, 3^(x-1)), 3)-1)

"""extract the point at a given (x, y)."""
point(b::Board, x, y) = point(b.row[y], x)

"""extract the point at a given (x, y)."""
point(p::Position, x, y) = point(p.board, x, y)


# --- display


"""the location of board markers (dots)."""
markers(n) = Set([Integer(floor(n/4)), (n+1)/2, n+1-Integer(floor(n/4))])

function fmtpoint(r::Row, y, n)
    m = markers(n)
    fmt(x) = (y in m && x in m ? "O+X" : "O.X")[2+Int(point(r, x))]
    # extra space aligns with other components that use 2 characters
    # per point
    string(" ", join(map(fmt, 1:n), " "))
end
fmtpoint{N}(b::Board{N}) = map(y -> fmtpoint(b.row[y], y, N), N:-1:1)

Base.print(io::IO, b::Board) = print(io, join(fmtpoint(b), "\n"))

function fmtindex(index::Array{UInt8, 2}, y, n)
    m = markers(n)
    function fmt(x)
        if index[x, y] > 0
            @sprintf("%02x", index[x, y])
        elseif y in m && x in m
            "__"
        else
            "  "
        end
    end
    join(map(fmt, 1:n))
end
fmtindex{N}(g::Groups{N}) = map(y -> fmtindex(g.index, y, N), N:-1:1)

stats_per_row = 4
function fmtstats(g::Groups, row)
    function fmt(col)
        i = col + (row-1) * stats_per_row
        @sprintf("%02x:%2d/%2d", i, g.lives[i], g.size[i])
    end
    join(map(fmt, 1:stats_per_row), ", ")
end
fmtstats{N}(g::Groups{N}) = map(r -> fmtstats(g, r), 1:N)

function Base.print(io::IO, g::Groups)
    print(io, join(fmtindex(g), "\n"))
    print(io, "\n")
    print(io, join(fmtstats(g), "\n"))
end

function fmtdistance{N}(f::Flood{N}, y)
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
    join(map(fmt, 1:1N))
end
fmtdistance{N}(f::Flood{N}) = map(y -> fmtdistance(f, y), N:-1:1)

Base.print(io::IO, f::Flood) = print(io, join(fmtdistance(f), "\n"))

fmtindex{N}(s::Space{N}) = map(y -> fmtindex(s.index, y, N), N:-1:1)

function fmtborder{N}(s::Space{N}, y)
    fmt(x) = " XO."[s.border[x, y]+1]
    string(" ", join(map(fmt, 1:N), " "))
end
fmtborder{N}(s::Space{N}) = map(y -> fmtborder(s, y), N:-1:1)

function Base.print(io::IO, s::Space)
    print(io, join(fmtborder(s), "\n"))
    print(io, "\n")
    print(io, join(fmtindex(s), "\n"))
end

Base.print(io::IO, s::Score) = 
@printf(io, " %2d  [black  pr=%-2d sp=%-3d] [white  pr=%-2d sp=%-3d]", 
        s.total, 
        s.colour[black].prisoners, s.colour[black].spaces,
        s.colour[white].prisoners, s.colour[white].spaces)

function Base.print(io::IO, p::Position)
    print(io, 
          join(map(x -> join(x, "  "), 
                   zip(fmtpoint(p.board), 
                       fmtindex(p.groups))), "\n"))
    print(io, "\n\n")
    print(io,
          join(map(x -> join(x, "  "), 
                   zip(fmtdistance(p.flood), 
                       fmtstats(p.groups))), "\n"))
    print(io, "\n\n")
    print(io,
          join(map(x -> join(x, "  "), 
                   zip(fmtborder(p.space), 
                       fmtindex(p.space))), "\n"))
    print(io, "\n\n")
    print(io, p.score)
end


# --- update state on move


function k_lowest_unused(k, a::Array{UInt8, 2}, n)
    available = collect(UInt8, 1:255)
    result = zeros(UInt8, k)
    function extract(result, value)
        if value > 0
            for i in 1:k
                if result[i] == 0
                    result[i] = value
                    break
                end
            end
        end
        result
    end
    @forall_fold i j n extract result available begin
        if a[i, j] > 0
            available[a[i, j]] = 0
        end
    end
end

"""merge the group at (x,y) with newgroup."""
function merge_group!{N}(g::Groups{N}, newgroup, x, y)
    oldgroup = g.index[x, y]
    if newgroup != oldgroup
        g.size[newgroup], g.size[oldgroup] = g.size[newgroup] + g.size[oldgroup], 0
        @forall i j N begin
            if g.index[i, j] == oldgroup
                g.index[i, j] = newgroup
            end
        end
    end
end

"""delete group g: remove it from Groups.index, sets Flood.distance to
zero (these are later replaced in flood_dead_group!) and Space.index
to the next available value (patched up in fix_space!)."""
function delete_group!{N}(p::Position{N}, t, g)
    space = k_lowest_unused(1, p.space.index, N)[1]
    p.score.colour[t].prisoners = p.score.colour[t].prisoners + p.groups.size[g]
    p.groups.size[g] = 0
    @forall i j N begin
        if p.groups.index[i, j] == g
            # remove stone
            move!(p.board, empty, i, j)
            # erase group index
            p.groups.index[i, j] = 0
            p.space.index[i, j] = space
            # set flood to special value (see flood_dead_group!)
            p.flood.distance[i, j] = 0
        end
    end
end

"""replace Flood.distance values that have been zeroed."""
function flood_dead_group!{N}(f::Flood{N}, b::Board{N}, t::Point)
    while ! @forall_fold i j N (a,b) -> (a || b!=0) false f.distance begin
        if f.distance[i, j] == 0
           # find closest neighbour
           mind = 256
           @forneighbours i j N ii jj begin
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
function flood_to_point!{N}(f::Flood{N}, b::Board{N}, t::Point, x, y)
    @forall i j N begin
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

"""re-calculate (from scratch) the number of lives associated with
each group."""
function calculate_lives!{N}(g::Groups{N})
    # the general idea here is that for each space, we see whether it
    # contributes a life to any group (by lookng at neighbouting
    # groups).  then we add those lives up.  this avoids "double
    # counting" spaces that touch more than one stone.
    for k in 1:255
        g.lives[k] = 0
    end
    # local vars
    temp = zeros(UInt8, N, N, 4)   # neighbouring groups
    n = zeros(UInt8, N, N)         # number of neighbouring groups (<=4)
    @forall i j N begin
        # for spaces
        if g.index[i, j] == 0
            @forneighbours i j N ii jj begin
                group = g.index[ii, jj]
                # if group is not already known
                if group != 0 && !any([group == temp[i, j, k] for k in 1:n[i, j]])
                    n[i, j] = n[i, j] + 1
                    temp[i, j, n[i, j]] = group
                end
            end
            # thread group mem with memory guard
            for k in 1:n[i, j]
                g.lives[temp[i, j, k]] = g.lives[temp[i, j, k]] + 1
            end
        end
    end
end

"""the Space.border array uses this mask to indicate the border
colour(s).  it is chosen so that updating adjacent values using or
works ok, but needs translating at the net level."""
function border_mask(t::Point)
    if t == empty
        return 0
    elseif t == black
        return 1
    else
        return 2
    end
end

"""iteratively update space wherever the border is (initially) zero
until the index and border are consistent acrosss the group (lowest
index, combined border)."""
function fix_space!{N}(s::Space{N}, b::Board{N})
    
    my_active = zeros(Bool, N, N)
    my_nsew = zeros(UInt8, N, N)   # bitmask of stones (to ignore in round 2)
    my_index = zeros(UInt8, N, N)
    my_border = zeros(UInt8, N, N)
    my_k = zeros(UInt8, N, N)

    # first round, set border from stones
    @forall i j N begin
        my_active[i, j] = s.border[i, j] == 0 && point(b, i, j) == empty
        if my_active[i, j]
            my_index[i, j] = s.index[i, j]
            @forneighbours i j N ii jj begin
                t = point(b, ii, jj)
                if t != empty
                    my_border[i, j] = my_border[i, j] | border_mask(t)
                    my_nsew[i, j] = my_nsew[i, j] | 2^my_k[i, j]
                end
                my_k[i, j] = my_k[i, j] + 1
            end
            s.border[i, j] = my_border[i, j]
        end
    end
    
    # second round - update until consistent
    our_changed = true
    while our_changed
        our_changed = false
        my_k = zeros(UInt8, N, N)
        
        @forall i j N begin
            my_changed = zeros(Bool, N, N)
            if my_active[i, j]
                @forneighbours i j N ii jj begin
                    if my_nsew[i, j] & 2^my_k[i, j] == 0
                        index = s.index[ii, jj]
                        if index != my_index[i, j] && index > 0 && (my_index[i, j] == 0 || index < my_index[i, j])
                            my_changed[i, j] = true
                            my_index[i, j] = index
                        end
                        border = s.border[ii, jj]
                        if !(border == 0 || border & my_border[i, j] == border)
                            my_changed[i, j] = true
                            my_border[i, j] = my_border[i, j] | border
                        end
                    end
                    my_k[i, j] = my_k[i, j] + 1
                end
                if my_changed[i, j]
                    s.index[i, j] = my_index[i, j]
                    s.border[i, j] = my_border[i, j]
                    our_changed = true
                end
            end
        end
    end

end

"""add space indices around a new move.  these are then resolved by
fix_space!()."""
function index_new_space!{N}(s::Space{N}, b::Board{N}, x, y)
    available = k_lowest_unused(4, s.index, N)
    k = 1
    @forneighbours x y N xx yy begin
        if point(b, xx, yy) == empty
            s.index[xx, yy] = available[k]
            k = k+1
        end
    end
end

function score!{N}(x::Score, s::Space{N})
    function f(x, b)
        if b == 1
            x.colour[black].spaces = x.colour[black].spaces + 1
        elseif b == 2
            x.colour[white].spaces = x.colour[white].spaces + 1
        end
        x
    end
    x.colour[black].spaces, x.colour[white].spaces = 0, 0
    foldl(f, x, s.border)
    b, w = x.colour[black], x.colour[white]
    x.total = b.prisoners + b.spaces - (w.prisoners + w.spaces)
    # two measures of progress
    x.stones = count(x -> x == 0, s.border)
    x.owned = Float32(count(x -> 0 < x < 3, s.border) / (N^2 - x.stones))
end

type IllegalMove <: Exception end

function assert_empty(p, x, y)
    if point(p, x, y) != empty
        throw(IllegalMove())
    end
end

function assert_alive(p, x, y)
    if p.groups.lives[p.groups.index[x, y]] == 0
        throw(IllegalMove())
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

function move!{N}(s::Space{N}, x, y)
    index = s.index[x, y]
    @forall i j N begin
        if s.index[i, j] == index
            s.index[i, j] = 0
            s.border[i, j] = 0
        end
    end
end

"""update the position, given a new point.  this includes all
processing."""
function move!{N}(p::Position{N}, t::Point, x, y)
    assert_empty(p, x, y)
    move!(p.board, t, x, y)
    move!(p.flood, t, x, y)
    move!(p.space, x, y)
    flood_to_point!(p.flood, p.board, t, x, y)
    index_new_space!(p.space, p.board, x, y)
    newgroup = k_lowest_unused(1, p.groups.index, N)[1]
    p.groups.index[x, y] = newgroup
    p.groups.size[newgroup] = 1
    @forneighbours x y N xx yy begin
        tt = point(p.board, xx, yy)
        if tt == t
            merge_group!(p.groups, newgroup, xx, yy)
        elseif tt == other(t)
            g = p.groups.index[xx, yy]
            # if it had a single life, and we just filled a space next
            # door, then it must have died
            if p.groups.lives[g] == 1
                delete_group!(p, t, g)
            end
        end
    end
    flood_dead_group!(p.flood, p.board, t)
    calculate_lives!(p.groups)
    fix_space!(p.space, p.board)
    assert_alive(p, x, y)
    score!(p.score, p.space)
    p   # support call with new instance
end


# --- query state


# TODO - really needs move history here
function valid(p, t, x, y)
    if point(p, x, y) != empty
        return false
    end
    if p.space.index[x, y]
    end
end
