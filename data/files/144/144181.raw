
##
# BWP_fisher.jl
# Methoden behorend bij de fractionele fisher-vergelijking
##
type Fisher <: BWP
	toString::String
	analyticSol::Bool
	L::Float64
	chi::Float64
	gamma::Float64
	W::Float64		# W < 0 = right-propagating, W > 0 = left-propagating
	x0::Float64
end
Fisher(;chi=5e-7, gamma=1.0, W=1e-3, x0=3e-3) = Fisher("Fisher", false, 1.0, chi, gamma, W, x0)

convert(::Type{Fisher}, d::Dict{String,Any}) = Fisher(d["toString"], d["analyticSol"], 1.0, d["chi"], d["gamma"], d["W"], d["x0"])

Wmin = ((1.9-1.0)*5e-4 * 3)^(1/1.9);

##
# beginOpl
# Geeft de beginvoorwaarde terug
##
function beginOpl(BWP::Fisher, x, a)
	0.5* ( 1 + tanh((x - BWP.x0)/(2*BWP.W)) );
	#
	#1./(1+e.^x).^2
end

##
# inhom
# Geeft de inhomogene term terug
##
function inhom(BWP::Fisher, u, x, a)
    y = BWP.gamma*u.*(1-u);
	y
end

##
# randVW!
# Past de randvoorwaarden toe op u_t
##
function randVW!(BWP::Fisher, u_t, t, a)
	#u_t[1] = 1;
	#u_t[end] = u_t[end-1];
	
	u_t[1] = u_t[2];
	u_t[end] = u_t[end-1];
	
	#u_t[1] = 1/(1+e^(-5*t))^2;
	#u_t[end] = 0;
end