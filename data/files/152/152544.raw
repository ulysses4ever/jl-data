# nock.jl
#
# Implementation of a Nock interpreter.
# For formal definition, see http://www.urbit.org/2013/08/22/Chapter-2-nock.html
#
# To use:
# using Nock
# nock(parse_nockdata("[42 [8 [1 0] 8 [1 6 [5 [0 7] 4 0 6] [0 6] 9 2 [0 2] [4 0 6] 0 7] 9 2 0 1]]"))
# --> 41


module Nock
import Base.isequal
import Base.show

export Cell, left, right, parse_nockdata, nock


## Basic types
typealias Atom BigInt

immutable TCell{T}
    first::T
    second::T
end

immutable Noun
    value::Union(TCell{Noun}, Atom)
end
isequal(A::Noun, B::Noun) = isequal(A.value, B.value)

typealias Cell TCell{Noun}

# Helpers
Noun(V::Int) = Noun(Atom(V))
Cell(A, B) = Cell(Noun(A), Noun(B))
Cell(A, Bs...) = Cell(A, Cell(Bs...))

left(V::Cell) = V.first.value
right(V::Cell) = V.second.value

# Pretty-printers
show(io::IO, V::Noun) = show(io, V.value)

function show_noparen(io::IO, V::Cell)
    show(io, left(V))
    write(io, " ")
    if isa(right(V), Cell)
        show_noparen(io, right(V))
    else
        show(io, V.second)
    end
end

function show(io::IO, V::Cell)
    write(io, "[")
    show_noparen(io, V)
    write(io, "]")
end


## Parse strings into Cells
immutable Open end
immutable Close end
immutable EOT end
typealias Tok Union(Open,Close,EOT,BigInt)

immutable ParseException
    v::String
    ParseException() = new()
    ParseException(v) = new(v)
end

function next_tok(str)
    str = lstrip(str)
    if length(str) == 0
        return EOT(), str
    elseif beginswith(str, "[")
        return Open(), str[2:]
    elseif beginswith(str, "]")
        return Close(), str[2:]
    else
        m = match(r"^\d+", str)
        return BigInt(m.match), str[length(m.match)+1:end]
    end
end

function parse_nockdata(str)
    # First, normalize
    str = replace(str, ",", " ")
    str = replace(str, r"\s+", " ")

    value, str = parse2(str)

    tok, str_rem = next_tok(str)
    if !isa(tok, EOT)
        throw(ParseException("Unexpected trailing: $str"))
    end

    return value
end

function parse2(str)
    # Parse a single int
    v1, str = next_tok(str)
    if isa(v1, BigInt)
        return Atom(v1), str
    end

    # Parse a cell
    if isa(v1, Open)
        # Store set of values in vals
        vals = {}

        v1, str = next_tok(str)
        while true
            if isa(v1, EOT)
                throw(ParseException("Expected ] before EOT"))
            elseif isa(v1, BigInt)
                vals = {vals..., Atom(v1)}
            elseif isa(v1, Open)
                newval, str = parse2("[$str")
                vals = {vals..., newval}
            elseif isa(v1, Close)
                return Cell(vals...), str
            end
            v1, str = next_tok(str)
        end
    else
        throw(ParseException("Unexpected token $v1"))
    end
end


## Nock
immutable EvalException
    v::String
    EvalException() = new()
    EvalException(v) = new(v)
end

# Type
# 4  ::    ?[a b]            0
# 5  ::    ?a                1
(?)(V::Cell) = Atom(0)
(?)(V::Atom) = Atom(1)

# Incr
# 6  ::    +[a b]            +[a b]
# 7  ::    +a                1 + a
(+)(V::Cell) = throw(EvalException("+[a b]"))
(+)(V::Atom) = Atom(V + 1)

# Equality
# 8  ::    =[a a]            0
# 9  ::    =[a b]            1
# 10 ::    =a                =a
(==)(V::Cell) = isequal(V.first, V.second) ? Atom(0) : Atom(1)
(==)(V::Atom) = throw(EvalException("=a"))

# Trees
# 12 ::    /[1 a]            a
# 13 ::    /[2 a b]          a
# 14 ::    /[3 a b]          b
# 15 ::    /[(a + a) b]      /[2 /[a b]]
# 16 ::    /[(a + a + 1) b]  /[3 /[a b]]
# 17 ::    /a                /a
function (/)(V::Cell)
    local index::Atom = left(V)

    if index == 1
        return right(V)
    end

    local V2::Cell = right(V)
    if index == 2
        return left(V2)
    elseif index == 3
        return right(V2)
    end
    
    if iseven(index)
        return (/)(Cell(2, (/)(Cell(index >> 1,
                                    V2))))
    else
        return (/)(Cell(3, (/)(Cell(index >> 1,
                                    V2))))
    end
end
(/)(V::Atom) = throw(EvalException("/a"))

# nock
function nock(V::Cell)
    a = left(V)
    local formula::Cell = right(V)

    id = left(formula)
    arg = right(formula)

    # 19 ::    *[a [b c] d]      [*[a b c] *[a d]]
    if isa(id, Cell)
        b = left(id)
        c = right(id)
        d = arg
        return Cell(nock(Cell(a, b, c)),
                    nock(Cell(a, d)))
    end

    # 21 ::    *[a 0 b]          /[b a]
    if id == 0
        b = arg
        return (/)(Cell(b, a))    # 21
    end

    # 22 ::    *[a 1 b]          b
    if id == 1
        b = arg
        return b                # 22
    end

    # 23 ::    *[a 2 b c]        *[*[a b] *[a c]]
    if id == 2
        b = left(arg)
        c = right(arg)
        return nock(Cell(nock(Cell(a, b)),
                         nock(Cell(a, c))))
    end

    # 24 ::    *[a 3 b]          ?*[a b]
    if id == 3
        b = arg
        return (?)(nock(Cell(a, b)))
    end

    # 25 ::    *[a 4 b]          +*[a b]
    if id == 4
        b = arg
        return (+)(nock(Cell(a, b)))
    end

    # 26 ::    *[a 5 b]          =*[a b]
    if id == 5
        b = arg
        return (==)(nock(Cell(a, b)))
    end

    # 28 ::    *[a 6 b c d]      *[a 2 [0 1] 2 [1 c d] [1 0] 2 [1 2 3] [1 0] 4 4 b]
    if id == 6
        b = left(arg)
        c = left(right(arg))
        d = right(right(arg))
        return nock(Cell(a, 2, Cell(0, 1), 2, Cell(1, c, d),
                         Cell(1, 0), 2, Cell(1, 2, 3), Cell(1, 0),
                         4, 4, b))
    end

    # 29 ::    *[a 7 b c]        *[a 2 b 1 c]
    if id == 7
        b = left(arg)
        c = right(arg)
        return nock(Cell(a, 2, b, 1, c))
    end

    # 30 ::    *[a 8 b c]        *[a 7 [[7 [0 1] b] 0 1] c]
    if id == 8
        b = left(arg)
        c = right(arg)
        return nock(Cell(a, 7, Cell(Cell(7, Cell(0, 1), b), 0, 1), c))
    end

    # 31 ::    *[a 9 b c]        *[a 7 c 2 [0 1] 0 b]
    if id == 9
        b = left(arg)
        c = right(arg)
        return nock(Cell(a, 7, c, 2, Cell(0, 1), 0, b))
    end

    # 32 ::    *[a 10 [b c] d]   *[a 8 c 7 [0 3] d]
    # 33 ::    *[a 10 b c]       *[a c]
    if id == 10
        if isa(left(arg), Cell)
            b = left(left(arg))
            c = right(left(arg))
            d = right(arg)
            return nock(Cell(a, 8, c, 7, Cell(0, 3), d))
        else
            b = left(arg)
            c = right(arg)
            return nock(Cell(a, c))
        end
    end

    throw(EvalException("Unrec id: $id"))
end
nock(V, Vs...) = nock(Cell(V, Vs...))

# 35 ::    *a                *a
nock(a::Atom) = throw(EvalException("*a"))

end
