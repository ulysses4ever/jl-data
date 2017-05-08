module CA
import Base.size
using Base.Random

@edit Base.Random.rand()


type CA
    width::Int64
    height::Int64
#    model
    grid::Array{Int64, 2}
    gen::Int64

    function CA(w, h)
    end
end

function size(ca::CA)
    ca.width, ca.height
end


c = CA(0,0,[[1,3,4] [3,2,0]], 0)
size(c)

rand(1:3, 2,2)
?rand

end
