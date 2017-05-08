
function GS_categories()
	figure();

	fst(list) = map(p -> p[1], list)
	snd(list) = map(p -> p[2], list)

	cat_1_0 = [
		map( a2 -> (1.0, a2), 1.0:0.1:1.9),
		map( a2 -> (1.1, a2), 1.4:0.1:2.0),
		map( a2 -> (1.2, a2), 1.8:0.1:2.0)
	]
	
	cat_1_0_fill = [
		(1.2, 1.8)
	]

	cat_1_1 = [
		map( a2 -> (1.0, a2), 2.0:0.1:2.0),
		map( a2 -> (1.1, a2), 1.0:0.1:1.3),
		map( a2 -> (1.2, a2), 1.0:0.1:1.7),
		map( a2 -> (1.3, a2), 1.5:0.1:2.0),
		map( a2 -> (1.4, a2), 1.7:0.1:2.0),
		map( a2 -> (1.5, a2), 1.9:0.1:2.0),
		map( a2 -> (2.0, a2), 1.0:0.1:1.3)
	]
	
	cat_1_1_fill = [
		(1.2, 1.7)
		(1.2, 1.0)
	]

	cat_1_2 = [
		map( a2 -> (1.3, a2), 1.0:0.1:1.4),
		map( a2 -> (1.4, a2), 1.0:0.1:1.6),
		map( a2 -> (1.5, a2), 1.0:0.1:1.8),
		map( a2 -> (1.6, a2), 1.0:0.1:2.0),
		map( a2 -> (1.7, a2), 1.0:0.1:2.0),
		map( a2 -> (1.8, a2), 1.0:0.1:1.3),
		map( a2 -> (1.8, a2), 1.6:0.1:2.0),
		map( a2 -> (1.9, a2), 1.0:0.1:1.2)
	]
	
	cat_1_2_fill = [
		(1.6, 1.5),
		(1.6, 2.0)
	]

	cat_2_2 = [
		map( a2 -> (1.8, a2), 1.4:0.1:1.5),
		map( a2 -> (1.9, a2), 1.3:0.1:2.0),
		map( a2 -> (2.0, a2), 1.4:0.1:2.0)
	]
	
	cat_2_2_fill = [
		(2.0, 2.0)
	]
	
	println(length(cat_1_0) + length(cat_1_1) + length(cat_1_2) + length(cat_2_2))
	
	s = 100;
	
	scatter(fst(cat_1_0), snd(cat_1_0), s=s, marker="D", facecolors="none", edgecolors="g")
	scatter(fst(cat_1_1), snd(cat_1_1), s=s, marker="^", facecolors="none", edgecolors="r")
	scatter(fst(cat_1_2), snd(cat_1_2), s=s, marker="s", facecolors="none", edgecolors="b")
	scatter(fst(cat_2_2), snd(cat_2_2), s=s, marker="8", facecolors="none", edgecolors="c")

	scatter(fst(cat_1_0_fill), snd(cat_1_0_fill), s=s, marker="D", facecolors="g", edgecolors="g")
	scatter(fst(cat_1_1_fill), snd(cat_1_1_fill), s=s, marker="^", facecolors="r", edgecolors="r")
	scatter(fst(cat_1_2_fill), snd(cat_1_2_fill), s=s, marker="s", facecolors="b", edgecolors="b")
	scatter(fst(cat_2_2_fill), snd(cat_2_2_fill), s=s, marker="8", facecolors="c", edgecolors="c")
	
	legend([
		"Links 0 golven, rechts 1 golf",
		"Links 1 golf, rechts 1 golf",
		"Links 2 golven, rechts 1 golf",
		"Links 2 golven, rechts 2 golven"
	],  fontsize="small", scatterpoints=1, ncol=2,
		bbox_to_anchor=(0.5, -0.12), loc="upper center", borderaxespad=0.);
	subplots_adjust(bottom = 0.2)
	
	axis([0.9, 2.1, 0.9, 2.1])
	title("Classificatie van effecten")
    xlabel(L"\alpha_1");
    ylabel(L"\alpha_2");
end

function monomialDerivatives(;as = 1.0:0.05:3.0)
	p = 3;

	xs = e.^(-10:0.05:0.0); # logaritmische schaal om het stijle gedrag rond x=0 goed weer te geven
	
	AA = maximum(as);
	aa = minimum(as);
	colours = map(a -> (0, 0.8*(1-(a-aa)/(AA-aa)), (a-aa)/(AA-aa)), as);

	f =  x -> x^p;
	
	for i = 1:length(as)
		a = as[i];
		Df = x -> gamma(p+1)/gamma(p-a+1)*x^(p-a)
		dudxa_exact = map(Df, xs);
		plot(xs, dudxa_exact, c=colours[i]);
	end
	
	xlabel(L"x");
	ylabel(L"D^\alpha x^p");

end

function monomialDerivativesMulti()
	monomialDerivatives(as = 0.0:0.05:0.95)
	monomialDerivatives(as = 1.0:0.05:1.95)
	monomialDerivatives(as = 2.0:0.05:3.0)
end

##
# W_plotEV
# Plot eigenwaarden van W-matrix
##
function W_plotEV(W)
	ev = eigvals(W)
	scatter(real(ev), imag(ev))
	
	nothing
end

function plotEV(disc::DiscMethode, dt)
	cs = [
		(0.0, 0.0, 1.0), (0.0, 0.5, 1.0), (0.0, 1.0, 1.0), (0.0, 1.0, 0.5),
		(0.0, 1.0, 0.0), (0.5, 1.0, 0.0), (1.0, 1.0, 0.0), (1.0, 0.5, 0.0),
		(1.0, 0.0, 0.0), (1.0, 0.0, 0.5), (1.0, 0.0, 1.0), (0.5, 0.0, 1.0)
		];
	
	as = [1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0];
	cs = cs[1:length(as)];
	
	Nx = 200;
	
	figure();
	grid(true);
	

	#julia> using PyCall
	#julia> @pyimport matplotlib.patches as patch
	#julia> @pyimport matplotlib.pyplot as plt

	c = patch.Circle((-1,0), 1, alpha=0.2);
	plt.gca()[:add_patch](c)
	
	
	for i = 1:length(as)
		ev = eigvals(dt*berekenW(disc, Nx, as[i], 1.0, 1.0))
		
		#Wred = berekenWReduced(disc, Nx, as[i], 1.0);
		#Wimpl = berekenWimpl(disc, Wred, Nx, dt, 1.0)
		#ev = eigvals(berekenW(disc, Nx, as[i], 1.0, 1.0) - Wimpl)
		
		scatter(real(ev), imag(ev), c=cs[i])
	end
	
	loc = (typeof(disc) == L2C)?"center left":"upper left"
	
	legend( unshift!(map( a -> string(L"$\alpha = $", a), as), "Stab."), loc=loc, fontsize="small", scatterpoints=1, labelspacing = 0.1#=, ncol = 2=#);
	title("Eigenwaarden van $(disc.toString)")
    xlabel("Re(z)");
    ylabel("Im(z)");
    
    if typeof(disc) == L2
		axis([-5, 1, -1, 1])
		axis([-2, 0.1, -0.5, 0.5])
    else
		axis([-1, 0.2, -1.5, 1.5])
		axis([-0.11, 0.01, -0.15, 0.15])
    end
	
	nothing
end

function plotL2StabBound()
	a = 1:0.01:2;
	b = gamma(3-a)./(3-2.^(2-a))
	
	figure();
	grid(true);
	
	plot(a, b);
	
	xlabel(L"$\alpha$");
	ylabel(L"$f(\alpha)$");
	title(L"$f(\alpha) = \Gamma(3-\alpha)/(3-2^{2-\alpha})$");
	
	axis([1, 2, 0.4, 1])
	
	nothing
end

function plotEVGershgorinL2()
	colour = (0.5, 1.0, 0.0);
	
	a = 1.5;
	dt = 1.0;
	disc = L2();
	
	Nx = 200;
	
	figure();
	grid(true);
	
	W = dt*berekenW(disc, Nx, a, 1.0, 1.0);
	
	#c = patch.Circle((-1,0), 1, alpha=0.2);
	#plt.gca()[:add_patch](c)
	
	for (i, color) in [(2, "g"), (Nx-1, "b"), (1,"r")]
		i = Nx-i;
		ri = sumabs(W[i,:]) - abs(W[i,i]);
		println(W[i,i], " ", ri);
		c = patch.Circle((W[i,i],0), ri, alpha=0.4, color=color);
		plt.gca()[:add_patch](c)
	end
	
	ev = eigvals(W)
	scatter(real(ev), imag(ev), c=colour)
	
	loc = (typeof(disc) == L2C)?"center left":"upper left"
	
	legend( [L"i = 2,\ldots,N_x-2", L"i = N_x - 1", L"i = 1", "Eigenwaarden"], loc=loc, fontsize="small", scatterpoints=1, labelspacing = 0.1#=, ncol = 2=#);
	title("Eigenwaarden en Gershgorin schrijven van $(disc.toString)")
    xlabel("Re(z)");
    ylabel("Im(z)");
    
	axis([-4, 0.5, -2, 2])
	
	nothing
end


function plotEVGershgorinExample()
	colour = (0.5, 1.0, 0.0);
	Nx = 3;
	
	W = [
		 3 + 3im  2 - 3im -2 + 1im
		-2 + 2im -2 + 1im -1 - 2im
		 3 - 3im -1 - 2im  3 - 2im
	];
	
	figure();
	grid(true);
	
	for (i, color) in [(1, "r"), (2, "g"), (3,"b")]
		ri = sumabs(W[i,:]) - abs(W[i,i]);
		println(W[i,i], " ", ri);
		c = patch.Circle((real(W[i,i]),imag(W[i,i])), ri, alpha=0.4, color=color);
		plt.gca()[:add_patch](c)
	end
	
	ev = eigvals(W)
	scatter(real(ev), imag(ev), c=colour)
	
	loc = "upper left"
	
	legend( [L"i = 2,\ldots,N_x-2", L"i = N_x - 1", L"i = 1", "Eigenwaarden"], loc=loc, fontsize="small", scatterpoints=1, labelspacing = 0.1#=, ncol = 2=#);
	title("Eigenwaarden en Gershgorin schrijven")
    xlabel("Re(z)");
    ylabel("Im(z)");
    
	axis([-10, 10, -10, 10])
	
	nothing
end