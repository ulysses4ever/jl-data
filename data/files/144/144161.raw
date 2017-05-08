
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