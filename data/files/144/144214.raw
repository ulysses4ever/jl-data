
##
# disc_L2.jl
# Methoden behorend bij de L2 discretisatie methode
##
type L2 <: DiscMethode
	toString::String
	imex::String
end
L2(imex="im") = L2("L2", imex)

convert(::Type{L2}, d::Dict{String,Any}) = L2(d["toString"], d["imex"])

##
# w
# Bereken w_i^j(a) voor L2-methode
##
function w(disc::L2, i, j, a, dx)
	if i == 1
		if j == -1
			ww = 1;
		elseif j == 0
			ww = -2;
		elseif j == 1
			ww = 1;
		end
	else
		if j == -1
			ww = 1;
		elseif j == 0
			ww = 2^(2-a) - 3;
		elseif j == i-1
			ww = -2*pow0(i,(2-a)) + 3*pow0((i-1),(2-a)) - pow0((i-2),(2-a));
		elseif j == i
			ww = pow0(i,(2-a)) - pow0((i-1),(2-a));
		else
			ww = pow0((j+2),(2-a)) - 3*pow0((j+1),(2-a)) + 3*pow0(j,(2-a)) - pow0((j-1),(2-a));
		end
	end
	ww = ww / (gamma(3-a)*dx^a);
	ww
end

##
# berekenW
# Bereken W_n(a)-matrix voor L2-methode
##
function berekenW(disc::L2, n, a, dx, s)
	W = zeros(n-1, n-1);
	for i = 1:n-1
		for k = 1:i
			j = i-k;
			W[i, k] = w(disc, i, j, a, dx);
		end
		W[i,1] += w(disc, i, i, a, dx);
		if i < n-1
			W[i, i+1] = w(disc, i, -1, a, dx);
		else
			W[i, i] += s * w(disc, i, -1, a, dx);
		end
    end
	W
end

##
# berekenWReduced
# Bereken W_n(a)-matrix voor L2-methode in gereduceerde vorm, gebruikmakend van gelijke coefficienten
##
function berekenWReduced(disc::L2, n, a, dx)
	W = zeros(n-1, 2);
	for i = 1:n-1
		W[i, 1] = w(disc, i, i, a, dx) + w(disc, i, i-1, a, dx);
		W[i, 2] = w(disc, i, i-2, a, dx);
    end
	W
end