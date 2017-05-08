
using GoCL
using Base.Test


exists(path) = stat(path).inode != 0

function random_position(seed, board_size, n_moves)
    srand(seed)
    p = Position{board_size}()
    for i in 1:n_moves
        for t in (black, white)
            ok = false
            while !ok
                try
                    p = move!(Position(p), t, rand(1:board_size), rand(1:board_size))
                    ok = true
                catch e
                    if !isa(e, IllegalMove)
                        rethrow()
                    end
                end
            end
        end
    end
    p
end

function random_expression(n)
    @assert n > 7
    e = rand(UInt8, n)
    e[1:4] = map(UInt8, collect("goxp"))
    e[5] = 0x00
    e[6:7] = reinterpret(UInt8, UInt16[n])
    e
end

function compare(path, objs...)
    print(path)
    s = join([sprint(print, x) for x in objs], "\n") * "\n"
    if !exists(path)
        print(" (w)")
        open(path, "w") do io
            print(io, s)
        end
    end
    @test s == open(readall, path, "r")
    println(" ok")
end

include("position.jl")
include("expression.jl")
