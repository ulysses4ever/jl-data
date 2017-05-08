module Model
export AbstractModel, LagerThanLife, Cyclic
export next_cell, next_gen!, rand_cell
export generations, life

using nbhd
using CAType
using CA

function rand_cell(model::AbstractModel)
    rand(0:model.C-1)
end

function next_gen!(ca::CellularAutomata, model::AbstractModel)
    gen_next(x, y) = next_cell(x, y, model, ca)
    init_grid!(ca, gen_next)
end


type LagerThanLife <: AbstractModel
    S::Array{Int64, 1} # survive
    B::Array{Int64, 1} # born
    C::Int64           # num sutates
    r::Int64           # range
    nbhd::Nbhd
end

function next_cell(x::Int64, y::Int64, model::LagerThanLife, ca::CellularAutomata)
    ALIVE = model.C - 1
    DEAD = 0
    cell = ca[y, x]
    live_cells = count(x->x==ALIVE, neighbors(x, y, ca, model.nbhd))
    next = DEAD

    if cell == ALIVE
        if live_cells in model.S 
            next = cell
        else 
            next = cell - 1
        end
    elseif cell == DEAD
        if live_cells in model.B
            next = ALIVE
        end
    else
        next = cell - 1
    end

    next
end

generations(S,B,C) = LagerThanLife(S, B, C, 1, moore(1))
life(S, B) = generations(S, B, 2)

type Cyclic <: AbstractModel
    C::Int64
    r::Int64
    threshold::Int64
    nbhd::Nbhd
end

inc_cyclic(v::Int64, num::Int64) = (v+1) % num

function next_cell(x::Int64, y::Int64, model::Cyclic, ca::CellularAutomata)
    cell = ca[y, x]
    next = cell
    next_state = inc_cyclic(cell, model.C)
    num_next_state = count(x->x==next_state, neighbors(x, y, ca, model.nbhd))

    if num_next_state >= model.threshold
        next = next_state
    end

    next
end


end
