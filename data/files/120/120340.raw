tojs(s::Symbol) = string(s)
tojs(v::Vector) = [tojs(v_i) for v_i in v]
function tojs(v::Dict)
	res = Dict()
	for (k, v) in v
		res[k] = tojs(v)
	end
	return res
end
tojs(x::Any) = x
