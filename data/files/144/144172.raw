
##
# BWP_advecDiff.jl
# Methoden behorend bij de evenwichtsvergelijking
##
type AdvecDiff <: BWP # Advectie-Diffusie
	toString::String
	analyticSol::Bool
	L::Float64
	chi::Float64
	x0::Float64
	W::Float64
end
AdvecDiff(;chi=0.05,x0=0.5,W=0.1) = AdvecDiff("AdvecDiff", false, 1.0, chi, x0, W)

convert(::Type{AdvecDiff}, d::Dict{String,Any}) = AdvecDiff(d["toString"], d["analyticSol"], 1.0, d["chi"], d["x0"], d["W"])

##
# beginOpl
# Geeft de beginvoorwaarde terug
##
function beginOpl(BWP::AdvecDiff, x, a)
	exp(-(x-BWP.x0).^2/(2*BWP.W))
end

##
# inhom
# Geeft de inhomogene term terug
##
function inhom(BWP::AdvecDiff, u, x, a)
	0
end

##
# randVW!
# Past de randvoorwaarden toe op u_t
##
function randVW!(BWP::AdvecDiff, u_t, t, a)
	#u_t[1] = u_t[2];
	#u_t[2] = u_t[1];
	u_t[end] = 0;
	u_t[end] = u_t[end-1]
	u_t[1] = u_t[2]
end