module CA
export CellularAutomata, init_grid!, size, getindex, neighbors

import Base.size

using Base.Random, CAType
using nbhd


type CellularAutomata
    height::Int64
    width::Int64
    grid::Grid
    gen::Int64

    function CellularAutomata(w::Int64, h::Int64)
        new(h, w, zeros(Cell, (h, w)), 0)
    end
end

function init_grid!(ca::CellularAutomata, gen::Function)
    ca.grid = [gen(j, i) for j = 1:ca.height, i = 1:ca.width] # = gen(x, y)
end


function size(ca::CellularAutomata)
    ca.width, ca.height
end

function getindex(ca::CellularAutomata, x::Int64, y::Int64)
    boundary_cell = 1

    (x < 1 || x > ca.width)  && return boundary_cell
    (y < 1 || y > ca.height) && return boundary_cell
    return ca.grid[y, x]
end


function neighbors(x::Int64, y::Int64, ca::CellularAutomata, nbhd::Nbhd)
    [ca[y+n[1], x+n[2]] for n in nbhd]
end


end
