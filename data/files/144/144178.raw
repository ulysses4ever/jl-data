
##
# BWP_evwVgl.jl
# Methoden behorend bij de evenwichtsvergelijking
##
type EvwVgl <: BWP # EvenwichtsVergelijking
	toString::String
	analyticSol::Bool
	L::Float64
	chi::Float64
	b::Float64
end
EvwVgl(;chi=1.0,b=0.1) = EvwVgl("EvwVgl", true, 1.0, chi, b)

convert(::Type{EvwVgl}, d::Dict{String,Any}) = EvwVgl(d["toString"], d["analyticSol"], 1.0, d["chi"], d["b"])

##
# beginOpl
# Geeft de beginvoorwaarde terug
##
function beginOpl(BWP::EvwVgl, x, a)
	u = exact(BWP, x, a) + BWP.b*(x-1)
	#u[1] = u[2]
	#u
end

##
# exact
# Geeft de exacte oplossing terug
##
function exact(BWP::EvwVgl, x, a)
	(1-x.^a)/gamma(1+a) - 0.5*gamma(3-a)*(1-x.*x)
end

##
# inhom
# Geeft de inhomogene term terug
##
function inhom(BWP::EvwVgl, u, x, a)
	1 - x.^(2-a)
end

##
# randVW!
# Past de randvoorwaarden toe op u_t
##
function randVW!(BWP::EvwVgl, u_t, t, a)
	#u_t[1] = u_t[2];
	#u_t[2] = u_t[1];
	u_t[end] = 0;
	#u_t[1] = (u_t[2] - 2^(-a)*u_t[3])/(1-2^(-a))
	u_t[1] = u_t[2]
end