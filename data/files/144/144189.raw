
##
# BWP_heatPi.jl
# Methoden behorend bij de evenwichtsvergelijking
##
type HeatPi <: BWP # Shen & Liu
	toString::String
	analyticSol::Bool
	L::Float64
	chi::Float64
end
HeatPi(;chi=0.4) = HeatPi("HeatPi", false, 1.0*pi, chi)

convert(::Type{HeatPi}, d::Dict{String,Any}) = HeatPi(d["toString"], d["analyticSol"], d["L"], d["chi"])

##
# beginOpl
# Geeft de beginvoorwaarde terug
##
function beginOpl(BWP::HeatPi, x, a)
	x.*x
end

##
# inhom
# Geeft de inhomogene term terug
##
function inhom(BWP::HeatPi, u, x, a)
	0
end

##
# randVW!
# Past de randvoorwaarden toe op u_t
##
function randVW!(BWP::HeatPi, u_t, t, a)
	u_t[end] = u_t[end-1]
	u_t[1] = u_t[2]
end