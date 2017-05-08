
##
# BWP_evwVgl.jl
# Methoden behorend bij de fractionele fisher-vergelijking
##
type GrayScott <: BWP
	toString::String
	analyticSol::Bool
	L::Float64
	eps1::Float64
	eps2::Float64
	a1::Float64
	a2::Float64
	c1::Float64
	c2::Float64
end
GrayScott(;eps1=1e-4, eps2=1e-6, a1=2.0, a2=2.0, c1=0.01, c2=0.0474) = GrayScott("GrayScott", false, 1.0, eps1, eps2, a1, a2, c1, c2)

convert(::Type{GrayScott}, d::Dict{String,Any}) = GrayScott(d["toString"], d["analyticSol"], 1.0, d["eps1"], d["eps2"], d["a1"], d["a2"], d["c1"], d["c2"])

##
# beginOpl
# Geeft de beginvoorwaarde terug
##
function beginOpl1(bwp::GrayScott, x)
	1 - 0.5 * ( sin(pi * x) ).^10;
end
function beginOpl2(bwp::GrayScott, x)
	0.25 * ( sin(pi * x) ).^10;
end

##
# inhom
# Geeft de inhomogene term terug
##
function inhom1(bwp::GrayScott, u, v, x)
    -u.*v.*v + bwp.c1 * (1-u)
end
function inhom2(bwp::GrayScott, u, v, x)
    u.*v.*v - bwp.c2*v
end

##
# randVW!
# Past de randvoorwaarden toe op u_t
##
function randVW1!(bwp::GrayScott, u_t, t)
	u_t[1] = 1;
	u_t[2] = 1;
	u_t[end] = 1;
end
function randVW2!(bwp::GrayScott, u_t, t)
	u_t[1] = 0;
	u_t[end] = 0;
end