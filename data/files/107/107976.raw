
using GoCL
using Base.Test


const regen = false


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

function compare(x, path)
    if regen
        open(path, "w") do io
            print(io, x)
        end
    end
    print(path)
    @test sprint(print, x) == open(readall, path, "r")
    println(" ok")
end

include("position.jl")
include("expression.jl")
