
using GoCL
using Base.Test


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


include("position.jl")
include("expression.jl")
