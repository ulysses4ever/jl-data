using julia_sets
using Base.Test

# write your own tests here
function F{T<:Number}(z::T)
	return z
end

@test [11 11;11 11] == gen_jset(F,[-5,5],[-5,5],10,10)

