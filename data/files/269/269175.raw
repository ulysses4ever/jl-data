module Taste

export Bitter, Salty, Sour, Sweet, うま味,
    isbitter, issalty, issour, issweet, issavory, measureumami

include("bitter.jl")
include("salty.jl")
include("sour.jl")
include("sweet.jl")
include("うま味.jl")

import Base.svd
function svd(A::うま味)
    println("Bitterness: ", A.concentration * √eps())
    println("Saltiness: ", A.concentration * rand()/1000)
    println("Savoriness: ", 1-rand()*eps()^0.2)
    println("Sourness: ", 0.0)
    println("Sweetness: ", 0.0)
end

end # module
