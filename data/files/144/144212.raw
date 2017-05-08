
##
# disc_GL.jl
# Methoden behorend bij de GL discretisatie methode
##
type GL <: DiscMethode
	toString::String
	imex::String
end
GL(imex="im") = GL("GL", imex)

convert(::Type{GL}, d::Dict{String,Any}) = GL(d["toString"], d["imex"])

function gw(a, k)
	if k == 0
		ret = 1
	else
		ret = (-1)^k;
		for i = 1:k
			ret *= (a-i+1.0)/i;
		end
	end
	ret
end

##
# w
# Bereken w_i^j(a) voor GL-methode
##
function w(disc::GL, i, j, k, a, dx)
	if i == 0 && j == 0
		ww = 1
	elseif i == 0
		ww = 0
	elseif i == k && j == k
		ww = 1
	elseif i == k
		ww = 0
	else
		ww = gw(a, i-j+1)
	end
	ww = ww / (dx^a);
	ww
end

##
# berekenW
# Bereken W_n(a)-matrix voor GL-methode
##
function berekenW(disc::GL, n, a, dx, s)	
	W = zeros(n-1, n-1);
	for i = 1:n-1
		for j = 1:i
			W[i, j] = w(disc, i, j, n, a, dx);
		end
		W[i,1] += w(disc, i, 0, n, a, dx);
		if i < n-1
			W[i, i+1] = w(disc, i, i+1, n, a, dx);
		else
			W[i, i] += s * w(disc, i, i+1, n, a, dx);
		end
    end
	W
end

##
# berekenWReduced
# Bereken W_n(a)-matrix voor GL-methode in gereduceerde vorm, gebruikmakend van gelijke coefficienten
##
function berekenWReduced(disc::GL, n, a, dx)
	W = zeros(n-1, 2);
	for i = 1:n-1
		W[i, 1] = w(disc, i, 0, n, a, dx) + w(disc, i, 1, n, a, dx);
		W[i, 2] = w(disc, i, 2, n, a, dx);
    end
	W
end