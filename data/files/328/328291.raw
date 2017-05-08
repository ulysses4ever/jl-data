module nbhd
export Nbhd, moore, neumann

typealias Nbhd Set{(Int64, Int64)}

function moore(r)
    delete!(Set([(i, j) for i=-r:r, j=-r:r]), (0,0))
end

function neumann(r)
    list = moore(r)
    filter(x -> abs(x[1]) + abs(x[2]) <= r, list)
end

moore(1)
neumann(2)

end
